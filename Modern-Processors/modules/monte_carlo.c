#include <stdlib.h>
#include <stdbool.h>

long long int montecarlo(long long int throws)
{
    long long int arrows;
    for (int i = 0; i < throws; i++)
    {
        long double x = -1 + 2 * ((double)rand()) / RAND_MAX;
        long double y = -1 + 2 * ((double)rand()) / RAND_MAX;
        double distance = x * x + y * y;
        if (distance <= 1)
            arrows++;
    }
    return arrows;
}