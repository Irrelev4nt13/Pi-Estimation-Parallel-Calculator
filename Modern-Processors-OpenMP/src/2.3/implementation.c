
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "../../include/timer.h"

/* Serial functions */
void Get_args(int argc, char *argv[], int *thread_count_p,
              int *m_p, int *n_p, int *, int *, int *);
void Usage(char *prog_name);
void Gen_matrix(int A[],int x[], int m, int n);
void Read_matrix(char *prompt, int A[], int m, int n);
void Gen_vector(int x[], int n);
void Read_vector(char *prompt, int x[], int n);
void Print_matrix(char *title, int A[], int m, int n);
void Print_vector(char *title, int b[], int m);

/* Parallel functions */
void rows(int A[],int b[],int x[],int n,int m,int thread_count, int schedule_type, int chunk_size);
void cols(int A[],int b[],int x[],int n,int m,int thread_count, int schedule_type, int chunk_size);

/*------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
   int thread_count;
   int m, n, chunk_size, schedule_type,row=0;
   int *A;
   int *b;
   int *x;

   Get_args(argc, argv, &thread_count, &m, &n, &chunk_size, &schedule_type, &row);
   if (m % thread_count != 0)
   {
      fprintf(stdout, "m %% thread_count != 0\n");
      return EXIT_FAILURE;
   }
   A = malloc(m * n * sizeof(int));
   b = malloc(m * sizeof(int));
   x = malloc(n * sizeof(int));
  Gen_matrix(A, b, m, n);

    if(row == 1)
      rows(A,b,x,n,m,thread_count,schedule_type,chunk_size);
    else
      cols(A,b,x,n,m,thread_count,schedule_type,chunk_size);

   // Print_matrix("We read", A, m, n);
   // Print_vector("The product is", b, m);
#ifdef DEBUG
#else
/* Print_vector("The product is", b, m); */
#endif

   free(A);
   free(x);
   free(b);

   return 0;
} /* main */

/*------------------------------------------------------------------
 * Function:  Get_args
 * Purpose:   Get command line args
 * In args:   argc, argv
 * Out args:  thread_count_p, m_p, n_p
 */
void Get_args(int argc, char *argv[], int *thread_count_p, int *m_p, int *n_p, int *chunk_size, int *schedule_type, int *row)
{

   if (argc != 6)
      Usage(argv[0]);
   *thread_count_p = strtol(argv[1], NULL, 10);
   *m_p = strtol(argv[2], NULL, 10);
   *n_p = strtol(argv[2], NULL, 10);
   *schedule_type = strtol(argv[3], NULL, 10);
   if (*schedule_type > 4 || *schedule_type < 0)
   {
      fprintf(stderr, "The scedule type has to be >0 and <5\n");
      exit(0);
   }
   *chunk_size = strtol(argv[4], NULL, 10);
   if (*chunk_size < 1)
   {
      fprintf(stderr, "The chunk size has to be positive\n");
      exit(0);
   }
   *row = strtol(argv[5], NULL, 10);
   if (*thread_count_p <= 0 || *m_p <= 0 || *n_p <= 0 || *schedule_type<=0 || *schedule_type>4 || *row < 0 || *row > 1 )
      Usage(argv[0]);

}/* Get_args */

/*------------------------------------------------------------------
 * Function:  Usage
 * Purpose:   print a message showing what the command line should
 *            be, and terminate
 * In arg :   prog_name
 */
void Usage(char *prog_name)
{
   fprintf(stderr, "usage: %s <thread_count> <m> <n> <schedule_type> <chunk_size> <rows_implementation(0 or 1)>\n", prog_name);
   exit(0);
} /* Usage */

/*------------------------------------------------------------------
 * Function:    Read_matrix
 * Purpose:     Read in the matrix
 * In args:     prompt, m, n
 * Out arg:     A
 */
void Read_matrix(char *prompt, int A[], int m, int n)
{
   int i, j;

   printf("%s\n", prompt);
   for (i = 0; i < m; i++)
      for (j = 0; j < n; j++)
         scanf("%d", &A[i * n + j]);
} /* Read_matrix */

/*------------------------------------------------------------------
 * Function: Gen_matrix
 * Purpose:  Use the random number generator random to generate
 *    the entries in A
 * In args:  m, n
 * Out arg:  A
 */
void Gen_matrix(int A[],int b[], int m, int n)
{
   int i, j;
   int *x;
   x = malloc(n * sizeof(int));
   Gen_vector(x, n);

   for (i = 0; i < m; i++)
    {
        b[i]=0;
        for (j = 0; j < n; j++)
        { 
            if (i <= j)
                A[i * n + j] = random()*10 / ((int)RAND_MAX)+1;
            else
               A[i * n + j] = 0;
            b[i] += x[j]*A[i * n + j];
        }
    }
    
//    Print_matrix("We read", A, m, n);
//    Print_vector("The product is", x, m);
//    Print_vector("The product is", b, m);
} /* Gen_matrix */

/*------------------------------------------------------------------
 * Function: Gen_vector
 * Purpose:  Use the random number generator random to generate
 *    the entries in x
 * In arg:   n
 * Out arg:  A
 */
void Gen_vector(int x[], int n)
{
   int i;
   for (i = 0; i < n; i++)
      x[i] = random()*10 / ((int)RAND_MAX);
} /* Gen_vector */

/*------------------------------------------------------------------
 * Function:        Read_vector
 * Purpose:         Read in the vector x
 * In arg:          prompt, n
 * Out arg:         x
 */
void Read_vector(char *prompt, int x[], int n)
{
   int i;

   printf("%s\n", prompt);
   for (i = 0; i < n; i++)
      scanf("%d", &x[i]);
} /* Read_vector */


/*------------------------------------------------------------------
 * Function:    Print_matrix
 * Purpose:     Print the matrix
 * In args:     title, A, m, n
 */
void Print_matrix(char *title, int A[], int m, int n)
{
   int i, j;

   printf("%s\n", title);
   for (i = 0; i < m; i++)
   {
      for (j = 0; j < n; j++)
         printf("%d ", A[i * n + j]);
      printf("\n");
   }
} /* Print_matrix */

/*------------------------------------------------------------------
 * Function:    Print_vector
 * Purpose:     Print a vector
 * In args:     title, b, m
 */
void Print_vector(char *title, int b[], int m)
{
   int i;

   printf("%s\n", title);
   for (i = 0; i < m; i++)
      printf("%d ", b[i]);
   printf("\n");
} /* Print_vector */

void rows(int A[],int b[],int x[],int n,int m,int thread_count, int schedule_type, int chunk_size)
{
   int row,col,tmp;
   
   if(schedule_type!=4)/* If its not auto */
      omp_set_schedule(schedule_type, chunk_size);
   else
      omp_set_schedule(schedule_type,chunk_size=0);
   
#pragma omp parallel num_threads(thread_count) default(none) private(row,col) shared(A,b,x,n,tmp)
    for(row=n-1; row>=0; row--)
    {
    #pragma omp single 
        tmp = b[row];
    #pragma omp for reduction(+: tmp)  schedule(runtime)
        for(col= row+1; col<n; col++)
            tmp -= A[n*row + col] * x[col];
      
    #pragma omp single
        x[row]=tmp / A[n*row + row];
    }
//    Print_matrix("We read", A, m, n);
//    Print_vector("The product is", x, m);
//    Print_vector("The product is", b, m);
}


void cols(int A[],int b[],int x[],int n,int m,int thread_count, int schedule_type, int chunk_size)
{
#pragma omp parallel for num_threads(thread_count) default(none) shared(A,b,x,n)
    for (int row = 0; row < n; row++)
        x[row] = b[row];
   if(schedule_type!=4)/* If its not auto */
      omp_set_schedule(schedule_type, chunk_size);
   else
      omp_set_schedule(schedule_type,chunk_size=0);
#pragma omp parallel num_threads(thread_count) default(none) shared(A,b,x,n)
    for (int col = n - 1; col >= 0; col--) {
        
    #pragma omp single 
        x[col] /= A[n*col + col];
    
    #pragma omp for schedule(runtime)
        for (int row = 0; row < col; row++)
            x[row] -= A[n*row + col] * x[col];
        
    }
}