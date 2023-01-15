#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "../../include/monte_carlo.h"
#include "../../include/my_rand.h"
#include "../../include/timer.h"

int thread_count;
long long int throws;
long long int arrows = 0;

int main(int argc, char **argv)
{
    double start, end;
    throws = strtoll(argv[1], NULL, 10);

    GET_TIME(start);
    long long int arrows1 = monte_carlo(throws, 0, 1);
    long double pi = 4 * arrows1 / ((long double)throws);
    GET_TIME(end);
    double duration = end - start;
    printf("%Lf %f\n", pi, duration);
    return EXIT_SUCCESS;
}
