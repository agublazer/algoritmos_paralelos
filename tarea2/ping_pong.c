#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int limit = 10;

// compile using mpicc ping_pong.c
// run using mpiexec a.out -np 2

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    
    int count = 0;
    int step = 0;
    int turn = 0;
    while (count < limit) {
        if (world_rank == turn) {
            // Increment the ping pong count before you send it
            count+=1;
            step +=1;
            MPI_Send(&count, 1, MPI_INT, (turn+1)%2, 0, MPI_COMM_WORLD);
            printf("step %da: process %d sent number: %d to process %d\n",
                step, world_rank, count, (turn+1)%2);
        } 
        else {
            step+=1;
            MPI_Recv(&count, 1, MPI_INT, turn, 0, MPI_COMM_WORLD,
                   MPI_STATUS_IGNORE);
            printf("step %db: process %d received number: %d from process %d\n",
                 step, world_rank, count, (turn+1)%2);
        }
        turn = (turn+1)%2;
    }
    MPI_Finalize();
}
