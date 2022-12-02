#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include "../include/monte_carlo.h"

#define GET_TIME(now)                           \
    {                                           \
        struct timeval t;                       \
        gettimeofday(&t, NULL);                 \
        now = t.tv_sec + t.tv_usec / 1000000.0; \
    }

int main(int argc, char **argv)
{
    double start, end;
    srand(1);
    if (argc < 2)
    {
        printf("Not enough arguments\n");
        return 1;
    }
    long long int throws = atoll(argv[1]);
    long long int arrows = 0;
    GET_TIME(start);
    arrows = montecarlo(throws);
    long double pi = 4 * arrows / ((long double)throws);
    GET_TIME(end);
    double duration = end - start;
    printf("%Lf\n", pi);
    printf("Time: %f\n", duration);
    return EXIT_SUCCESS;
}