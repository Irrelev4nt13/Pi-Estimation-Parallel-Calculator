#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

// #ifdef _OPENMP
#include <omp.h>
// #endif

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
    long long int seg = throws / thread_count, my_arrows = 0;
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
    GET_TIME(end);
    double duration = end - start;
    printf("%Lf %f\n", pi, duration);

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

    long long int arrowsMP=0;
    int i, x, y,tmp;
    long double distance;
    unsigned seed;
    int first=0;
    #pragma omp parallel for num_threads(thread_count) \
    default(none) reduction(+: arrowsMP) private(i, x, y, distance,tmp,seed,first) shared(throws)
    for(i=0; i<throws; i++)
    {
        if(first==0)
        {
            seed=omp_get_thread_num();
            printf("asd\n");
            tmp=my_rand(&seed);
            first=1;
        }
        tmp=my_rand(&seed);
        x = my_drand(&tmp);
        y = my_drand(&tmp);
        distance = x * x + y * y;
        if (distance <= 1)
            arrowsMP+=1;
    }
    pi = 4 * arrowsMP / ((long double)throws);
    printf("%Lf %lld %lld\n",pi,arrowsMP,arrows);
    pthread_mutex_destroy(&mutex);
    free(thread_id);
    return EXIT_SUCCESS;
}

