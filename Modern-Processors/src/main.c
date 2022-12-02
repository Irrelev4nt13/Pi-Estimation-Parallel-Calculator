#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include "../include/monte_carlo.h"
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>

int thread_count;
pthread_barrier_t barrier1;
#define GET_TIME(now)                           \
    {                                           \
        struct timeval t;                       \
        gettimeofday(&t, NULL);                 \
        now = t.tv_sec + t.tv_usec / 1000000.0; \
    }

long long int throws;

void *Hello(void *rank)
{
    int rc;
    long my_rank = (long)rank;
    printf("%ld\n", my_rank);
    if (my_rank == 0)
    {
        double start, end;
        GET_TIME(start);
        long long int arrows;
        long double pi = monte_carlo(throws);
        GET_TIME(end);
        double duration = end - start;
        printf("%Lf\n", pi);
        printf("Time: %f\n", duration);
    }
    pthread_barrier_wait(&barrier1);
    printf("Ok from %ld\n", my_rank);
    return NULL;
}

int main(int argc, char **argv)
{
    double start, end;
    pthread_t *thread_id;
    srand(1);
    if (argc < 3)
    {
        printf("Not enough arguments\n");
        return 1;
    }
    throws = strtoll(argv[1], NULL, 10);
    thread_count = strtol(argv[2], NULL, 10);
    thread_id = malloc(thread_count * sizeof(pthread_t));
    pthread_barrier_init(&barrier1, NULL, thread_count);
    printf("Hello World from master thread\n");
    for (long thread = 0; thread < thread_count; thread++)
        pthread_create(&thread_id[thread], NULL, Hello, (void *)thread);

    for (long thread = 0; thread < thread_count; thread++)
        pthread_join(thread_id[thread], NULL);
    // GET_TIME(start);
    // long long int arrows = 0;
    // arrows = monte_carlo(throws);
    // GET_TIME(end);
    // double duration = end - start;
    // long double pi = 4 * arrows / ((long double)throws);
    // printf("%Lf\n", pi);
    // printf("Time: %f\n", duration);
    free(thread_id);
    return EXIT_SUCCESS;
}
