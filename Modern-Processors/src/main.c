#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "../include/monte_carlo.h"
#include "../include/my_rand.h"
#include "../include/timer.h"

pthread_mutex_t mutex;

int thread_count;
long long int throws;
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
        printf("Not enough arguments\n");
        return 1;
    }
    throws = strtoll(argv[1], NULL, 10);

    GET_TIME(start);
    long long int arrows1 = monte_carlo(throws);
    long double pi = 4 * arrows1 / ((long double)throws);
    GET_TIME(end);
    double duration = end - start;
    printf("%Lf \n", pi);
    printf("Time: %f\n", duration);

    pthread_mutex_init(&mutex, NULL);
    thread_count = strtol(argv[2], NULL, 10);
    thread_id = malloc(thread_count * sizeof(pthread_t));

    GET_TIME(start);
    for (long thread = 0; thread < thread_count; thread++)
        pthread_create(&thread_id[thread], NULL, Hello, (void *)thread);

    for (long thread = 0; thread < thread_count; thread++)
        pthread_join(thread_id[thread], NULL);
        
    pi = 4 * arrows / ((long double)throws);
    GET_TIME(end);
    duration = end - start;
    printf("%Lf \n", pi);
    printf("Time: %f\n", duration);

    pthread_mutex_destroy(&mutex);
    free(thread_id);
    return EXIT_SUCCESS;
}
