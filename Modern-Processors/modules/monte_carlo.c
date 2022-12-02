#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
long long int monte_carlo(long long int throws)
{
    long long int arrows=0;
    for (int i = 0; i < throws; i++)
    {
        long double x = -1 + 2 * ((double)rand()) / RAND_MAX;
        long double y = -1 + 2 * ((double)rand()) / RAND_MAX;
        double distance = x * x + y * y;
        if (distance <= 1)
            arrows++;
    }
    // long double pi = 4 * arrows / ((long double)throws);
    // printf("%lld\n", arrows);
    return arrows;
}