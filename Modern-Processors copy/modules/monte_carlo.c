#include <stdlib.h>
#include <stdio.h>
#include "../include/my_rand.h"
#include "../include/monte_carlo.h"

long long int monte_carlo(long long int throws, long long int start, int id)
{
    unsigned seed = id;
    long long int my_arrows = 0, i;
    long double x, y;
    for (i = start; i < throws; i++)
    {
        x = -1 + 2 * my_drand(&seed);
        y = -1 + 2 * my_drand(&seed);
        long double distance = x * x + y * y;
        if (distance <= 1)
            my_arrows++;
    }
    return my_arrows;
}