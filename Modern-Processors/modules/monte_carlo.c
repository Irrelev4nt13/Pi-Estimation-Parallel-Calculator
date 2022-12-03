#include <stdlib.h>
#include <stdio.h>
#include "../include/my_rand.h"

long long int monte_carlo(long long int throws)
{
    unsigned seed = 1, tmp;
    long long int arrows1 = 0;
    long double x, y;
    tmp = my_rand(&seed);
    for (int i = 0; i < throws; i++)
    {
        tmp = my_rand(&tmp);
        x = my_drand(&tmp);
        y = my_drand(&tmp);
        long double distance = x * x + y * y;
        if (distance <= 1)
            arrows1++;
    }
    return arrows1;
}