#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


void Hello();

int main(void)
{
    int thread_count
}

void Hello()
{
    int my_rank=omp_get_thread_num();
    printf("Hi from %d",my_rank);
    
}