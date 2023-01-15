#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "../../include/my_rand.h"

long long int monte_carlo();

int main(int argc, char *argv[])
{
    int comm_sz; /* Number of processes    */
    int my_rank; /* My process rank        */
    long long int arrows = 0, local_arrows = 0, throws, local_throws = 0, seg;
    long double pi;
    MPI_Comm comm;

    double start, end;
    MPI_Init(NULL, NULL);
    comm = MPI_COMM_WORLD;
    /* Get the number of processes */
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    /* Get my rank among all the processes */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    if (my_rank == 0)
    {
        if (argc != 2)
        {
            perror("Wrong number of arguments");
            return 1;
        }
        throws = strtol(argv[1], NULL, 10);
    }
    start = MPI_Wtime();
    MPI_Bcast(&throws, 1, MPI_LONG_LONG, 0, comm);
    local_throws = throws / comm_sz;

    local_arrows = monte_carlo((my_rank + 1) * local_throws, my_rank * local_throws, my_rank + 1);

    MPI_Reduce(&local_arrows, &arrows, 1, MPI_LONG_LONG, MPI_SUM, 0, comm);
    if (my_rank == 0)
    {
        pi = 4 * arrows / (long double)throws;
        end = MPI_Wtime();

        double duration = end - start;
        printf("%Lf %f\n", pi, duration);
    }
    MPI_Finalize();

    return 0;
}
long long int monte_carlo(long long int throws, long long int start, int id)
{
    unsigned seed = id, tmp;
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