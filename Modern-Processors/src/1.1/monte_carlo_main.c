#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "../../include/monte_carlo.h"
#include "../../include/my_rand.h"
#include "../../include/timer.h"

pthread_mutex_t mutex;

int thread_count;
long long int throws;
long long int arrows = 0;
void *monte_carlo_parallel(void *rank)
{
    long my_rank = (long)rank;
    long long int seg = throws / thread_count, my_arrows = 0, i;
    long long int first_throw = my_rank * seg, last_throw = (my_rank + 1) * seg;

    my_arrows = monte_carlo(last_throw, first_throw, my_rank + 1);
    pthread_mutex_lock(&mutex);
    arrows += my_arrows;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int argc, char **argv)
{
    double start, end;
    pthread_t *thread_id;
    if (argc < 3)
    {
        perror("Not enouh arguments\n");
        return EXIT_FAILURE;
    }
    throws = strtoll(argv[1], NULL, 10);

    GET_TIME(start);
    long long int arrows1 = monte_carlo(throws, 0, 1);
    long double pi = 4 * arrows1 / ((long double)throws);
    printf("%Lf\n", pi);
    GET_TIME(end);
    double duration = end - start;

    printf("%Lf %f\n", pi, duration);
    fprintf(stderr, "Time duration for serial code: %f\n", duration);

    pthread_mutex_init(&mutex, NULL);
    thread_count = strtol(argv[2], NULL, 10);
    thread_id = malloc(thread_count * sizeof(pthread_t));

    GET_TIME(start);
    for (long thread = 0; thread < thread_count; thread++)
        if (pthread_create(&thread_id[thread], NULL, monte_carlo_parallel, (void *)thread) != 0)
        {
            perror("Failed to create thread\n");
            return EXIT_FAILURE;
        }

    for (long thread = 0; thread < thread_count; thread++)
        if (pthread_join(thread_id[thread], NULL) != 0)
        {
            perror("Failed to create thread\n");
            return EXIT_FAILURE;
        }

    pi = 4 * arrows / ((long double)throws);
    GET_TIME(end);
    duration = end - start;
    printf("%Lf %f\n", pi, duration);
    fprintf(stderr, "Time duration for parallel code: %f\n", duration);
    pthread_mutex_destroy(&mutex);
    free(thread_id);
    return EXIT_SUCCESS;
}
