#include <stdlib.h>
#include <stdio.h>
#include "../include/my_rand.h"
#include "monte_carlo.h"

long long int monte_carlo(long long int throws, long long int start)
{
    unsigned seed = 1, tmp;
    long long int my_arrows = 0, i;
    long double x, y;
    tmp = my_rand(&seed);
    for (i = start; i < throws; i++)
    {
        tmp = my_rand(&tmp);
        x = my_drand(&tmp);
        y = my_drand(&tmp);
        long double distance = x * x + y * y;
        if (distance <= 1)
            my_arrows++;
    }
    return my_arrows;
}