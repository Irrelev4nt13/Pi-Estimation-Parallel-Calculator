/* File:
 *     pth_mat_vect_rand_split.c
 *
 * Purpose:
 *     Computes a parallel matrix-vector product.  Matrix
 *     is distributed by block rows.  Vectors are distributed by
 *     blocks.  This version uses a random number generator to
 *     generate A and x.  It also makes some small changes to
 *     the multiplication.  These are intended to improve
 *     performance and explicitly use temporary variables.
 *
 * Input:
 *     none
 *
 * Output:
 *     y: the product vector
 *     Elapsed time for the computation
 *
 * Compile:
 *    gcc -g -Wall -o pth_mat_vect_rand pth_mat_vect_rand.c -lpthread
 * Usage:
 *     pth_mat_vect <thread_count> <m> <n>
 *
 * Notes:
 *     1.  Local storage for A, x, y is dynamically allocated.
 *     2.  Number of threads (thread_count) should evenly divide
 *         m.  The program doesn't check for this.
 *     3.  We use a 1-dimensional array for A and compute subscripts
 *         using the formula A[i][j] = A[i*n + j]
 *     4.  Distribution of A, x, and y is logical:  all three are
 *         globally shared.
 *     5.  Compile with -DDEBUG for information on generated data
 *         and product.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "../../include/timer.h"

/* Global variables */
int thread_count;
int cache_line;
int m, n;
double *A;
double *x;
double *y;

/* Serial functions */
void Usage(char *prog_name);
void Gen_matrix(double A[], int m, int n);
void Read_matrix(char *prompt, double A[], int m, int n);
void Gen_vector(double x[], int n);
void Read_vector(char *prompt, double x[], int n);
void Print_matrix(char *title, double A[], int m, int n);
void Print_vector(char *title, double y[], double m);
int pad;
/* Parallel function */
void *Pth_mat_vect(void *rank);

/*------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
   long thread;
   pthread_t *thread_handles;
   if (argc != 4)
      Usage(argv[0]);
   thread_count = strtol(argv[1], NULL, 10);
   m = strtol(argv[2], NULL, 10);
   while (thread_count <= 0 || (m % thread_count) != 0)
   {
      printf("m %% thread_count != 0. Give a different number of threads: ");
      if (scanf("%d", &thread_count) == 0)
      {
         perror("Invalid imput characters\n");
         return EXIT_FAILURE;
      }
   }
   n = strtol(argv[3], NULL, 10);
   cache_line = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
   if (cache_line == -1)
   {
      perror("Couldn't get cache line length\n");
      return EXIT_FAILURE;
   }

#ifdef DEBUG
   printf("thread_count =  %d, m = %d, n = %d\n", thread_count, m, n);
#endif

   thread_handles = malloc(thread_count * sizeof(pthread_t));
   int pad_el = cache_line / sizeof(double);
   pad = abs(pad_el - (m / thread_count) % pad_el);
   // printf("%d\n", pad);
   // exit(0);
   // y = malloc((pad * thread_count + m) * sizeof(double));
   y = malloc((8 * thread_count + (m + 8)));
   x = malloc(n * sizeof(double));
   A = malloc(m * n * sizeof(double));

   Gen_matrix(A, m, n);
#ifdef DEBUG
   Print_matrix("We generated", A, m, n);
#endif

   Gen_vector(x, n);
#ifdef DEBUG
   Print_vector("We generated", x, n);
#endif
   for (thread = 0; thread < thread_count; thread++)
      if (pthread_create(&thread_handles[thread], NULL, Pth_mat_vect, (void *)thread) != 0)
      {
         perror("Failed to create thread\n");
         return EXIT_FAILURE;
      }
   for (thread = 0; thread < thread_count; thread++)
      if (pthread_join(thread_handles[thread], NULL) != 0)
      {
         perror("Thread failed to finish execution\n");
         return EXIT_FAILURE;
      }
   // Print_vector("The product is", y, m + pad);
#ifdef DEBUG
   Print_vector("The product is", y, m);
#endif
   free(A);
   free(x);
   free(y);
   free(thread_handles);
   return 0;
} /* main */

/*------------------------------------------------------------------
 * Function:  Usage
 * Purpose:   print a message showing what the command line should
 *            be, and terminate
 * In arg :   prog_name
 */
void Usage(char *prog_name)
{
   fprintf(stderr, "usage: %s <thread_count> <m> <n>\n", prog_name);
   exit(0);
} /* Usage */

/*------------------------------------------------------------------
 * Function:    Read_matrix
 * Purpose:     Read in the matrix
 * In args:     prompt, m, n
 * Out arg:     A
 */
void Read_matrix(char *prompt, double A[], int m, int n)
{
   int i, j;

   printf("%s\n", prompt);
   for (i = 0; i < m; i++)
      for (j = 0; j < n; j++)
         scanf("%lf", &A[i * n + j]);
} /* Read_matrix */

/*------------------------------------------------------------------
 * Function: Gen_matrix
 * Purpose:  Use the random number generator random to generate
 *    the entries in A
 * In args:  m, n
 * Out arg:  A
 */
void Gen_matrix(double A[], int m, int n)
{
   int i, j;
   for (i = 0; i < m; i++)
      for (j = 0; j < n; j++)
         A[i * n + j] = random() / ((double)RAND_MAX);
} /* Gen_matrix */

/*------------------------------------------------------------------
 * Function: Gen_vector
 * Purpose:  Use the random number generator random to generate
 *    the entries in x
 * In arg:   n
 * Out arg:  A
 */
void Gen_vector(double x[], int n)
{
   int i;
   for (i = 0; i < n; i++)
      x[i] = random() / ((double)RAND_MAX);
} /* Gen_vector */

/*------------------------------------------------------------------
 * Function:        Read_vector
 * Purpose:         Read in the vector x
 * In arg:          prompt, n
 * Out arg:         x
 */
void Read_vector(char *prompt, double x[], int n)
{
   int i;

   printf("%s\n", prompt);
   for (i = 0; i < n; i++)
      scanf("%lf", &x[i]);
} /* Read_vector */

/*------------------------------------------------------------------
 * Function:       Pth_mat_vect
 * Purpose:        Multiply an mxn matrix by an nx1 column vector
 * In arg:         rank
 * Global in vars: A, x, m, n, thread_count
 * Global out var: y
 */
void *Pth_mat_vect(void *rank)
{
   long my_rank = (long)rank;
   int i;
   int j;
   int local_m = m / thread_count;
   int my_first_row = my_rank * local_m;
   int my_last_row = my_first_row + local_m;
   register int sub = my_first_row * n;
   double start, finish;
   double temp;
#ifdef DEBUG
   printf("Thread %ld > local_m = %d, sub = %d\n",
          my_rank, local_m, sub);
#endif
   GET_TIME(start);
   for (i = my_first_row; i < my_last_row; i++)
   {
      y[i + pad * my_rank] = 0.0;
      for (j = 0; j < n; j++)
      {
         temp = A[sub++];
         temp *= x[j];
         y[i + pad * my_rank] += temp;
      }
   }
   GET_TIME(finish);
   printf("Thread %ld > Elapsed time = %e seconds\n", my_rank, finish - start);

   return NULL;
} /* Pth_mat_vect */

/*------------------------------------------------------------------
 * Function:    Print_matrix
 * Purpose:     Print the matrix
 * In args:     title, A, m, n
 */
void Print_matrix(char *title, double A[], int m, int n)
{
   int i, j;

   printf("%s\n", title);
   for (i = 0; i < m; i++)
   {
      for (j = 0; j < n; j++)
         printf("%6.3f ", A[i * n + j]);
      printf("\n");
   }
} /* Print_matrix */

/*------------------------------------------------------------------
 * Function:    Print_vector
 * Purpose:     Print a vector
 * In args:     title, y, m
 */
void Print_vector(char *title, double y[], double m)
{
   int i, counter = 1;

   printf("%s\n", title);
   for (i = 0; i < m; i++)
   {
      /* if (i == (pad * counter))
      {
         i += (pad % thread_count);
         counter++;
      } */
      printf("%6.3f\n", y[i]);
   }
   printf("\n");
} /* Print_vector */
