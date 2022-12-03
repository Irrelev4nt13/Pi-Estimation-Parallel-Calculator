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

pthread_mutex_t mutex1;
long long int arrows = 0;
void *Hello(void *rank)
{
    long my_rank = (long)rank;
    long long int seg = throws / thread_count, my_arrows = 0, i;
    long long int first_throw = my_rank * seg, last_throw = (my_rank + 1) * seg;

    unsigned tmp, seed = 1;
    long double x, y;
    tmp = my_rand(&seed);
    for (i = first_throw; i < last_throw; i++)
    {
        tmp = my_rand(&tmp);
        x = my_drand(&tmp);
        y = my_drand(&tmp);
        long double distance = x * x + y * y;
        if (distance <= 1)
            my_arrows++;
    }
    // printf("Ok from %ld\n", my_rank);
    pthread_mutex_lock(&mutex1);
    arrows += my_arrows;
    pthread_mutex_unlock(&mutex1);
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
    GET_TIME(start);
    long long int arrows1 = monte_carlo(throws);
    printf("%lld \n", arrows1);
    long double pi = 4 * arrows1 / ((long double)throws);
    GET_TIME(end);
    double duration = end - start;
    printf("%Lf \n", pi);
    printf("Time: %f\n", duration);

    pthread_mutex_init(&mutex1, NULL);
    thread_count = strtol(argv[2], NULL, 10);
    thread_id = malloc(thread_count * sizeof(pthread_t));
    // pthread_barrier_init(&barrier1, NULL, thread_count);
    printf("Hello World from master thread\n");
    // arrows=0;

    GET_TIME(start);
    for (long thread = 0; thread < thread_count; thread++)
        pthread_create(&thread_id[thread], NULL, Hello, (void *)thread);

    for (long thread = 0; thread < thread_count; thread++)
        pthread_join(thread_id[thread], NULL);
    // GET_TIME(start);
    // long long int arrows = monte_carlo(throws);
    pi = 4 * arrows / ((long double)throws);
    pthread_mutex_destroy(&mutex1);
    // GET_TIME(end);
    GET_TIME(end);
    duration = end - start;
    printf("%Lf \n", pi);

    printf("Time: %f\n", duration);

    free(thread_id);
    return EXIT_SUCCESS;
}
