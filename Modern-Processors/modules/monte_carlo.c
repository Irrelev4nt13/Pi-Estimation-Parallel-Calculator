#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#define _MY_RAND_H_
#define MR_MULTIPLIER 279470273
#define MR_INCREMENT 0
#define MR_MODULUS 4294967291U
#define MR_DIVISOR ((double)4294967291U)
unsigned my_rand(unsigned* seed_p) {
   long long z = *seed_p;
   z *= MR_MULTIPLIER; 
// z += MR_INCREMENT;
   z %= MR_MODULUS;
   *seed_p = z;
   return *seed_p;
}

long double my_drand(unsigned* seed_p) {
   unsigned x = my_rand(seed_p);
   long double y = -1 + 2 * x / MR_DIVISOR;
   return y;
}

long long int monte_carlo(long long int throws)
{
    unsigned seed=1,tmp;
    long long int arrows1=0;
    long double x,y;
    tmp=my_rand(&seed);
    for (int i = 0; i < throws; i++)
    {
        tmp=my_rand(&tmp);
        x=my_drand(&tmp);
        y=my_drand(&tmp);
        long double distance = x * x + y * y;
        if (distance <= 1)
            arrows1++;
    }
    return arrows1;
}