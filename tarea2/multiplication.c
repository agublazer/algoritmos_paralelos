#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <assert.h>

// Creates an array of random numbers. Each number has a value from 0 - 1
int max_rand = 9;
int *create_rand_nums(int rows, int cols) {
    int *rand_nums = (int *)malloc(sizeof(int) * rows*cols);
    assert(rand_nums != NULL);
    for (int i = 0; i < rows*cols; i++) {
        rand_nums[i] = (rand() % (int)max_rand);
    }
    printf("matrix \n");
    for (int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++){
            printf("%d ", rand_nums[cols*i + j]);
        }
        printf("\n");
    }
    return rand_nums;
}

int *create_rand_vector(int rows) {
    int *rand_nums = (int *)malloc(sizeof(int) * rows);
    assert(rand_nums != NULL);
    for (int i = 0; i < rows; i++) {
        rand_nums[i] = (rand() % (int)max_rand);
    }
    printf("vector \n");
    for (int i = 0; i < rows; i++) {
        printf("%d ", rand_nums[i]);
        printf("\n");
    }
    return rand_nums;
}

// Computes the average of an array of numbers
int compute_sum(int *array, int num_elements) {
    int sum = 0;
    int i;
    for (i = 0; i < num_elements; i++) {
        sum += array[i];
    }
    return sum ;
}

int main(int argc, char** argv) {
  MPI_Init(NULL, NULL);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  // Create a random array of elements on the root process. Its total
  // size will be the number of elements per process times the number
  // of processes
  int *rand_nums = NULL;
  int *rand_vector = NULL;
  int cols = 5;
  if (world_rank == 0) {
    rand_vector = create_rand_vector(cols);
    rand_nums = create_rand_nums(world_size , cols);
  }
  else{
    rand_vector = (int *)malloc(sizeof(int) * cols);
  }

  // MPI_Barrier(MPI_COMM_WORLD);
  assert(rand_vector!= NULL);
  MPI_Bcast(rand_vector, 5, MPI_INT, 0, MPI_COMM_WORLD);
  // MPI_Barrier(MPI_COMM_WORLD);
  // MPI_Barrier(MPI_COMM_WORLD);

  // Seed the random number generator to get different results each time
  srand(time(NULL));

  // For each process, create a buffer that will hold a subset of the entire
  // array
  int *sub_rand_nums = (int *)malloc(sizeof(int) * cols);
  // int *rand_vector_copy = (int *)malloc(sizeof(int) * cols);
  assert(sub_rand_nums != NULL);

  // Scatter the random numbers from the root process to all processes in
  // the MPI world
  MPI_Scatter(rand_nums, cols, MPI_INT, sub_rand_nums,
    cols, MPI_INT, 0, MPI_COMM_WORLD);


  printf("process number %d: ", world_rank);
  for(int i = 0; i<cols;i++){
    printf("%d ", sub_rand_nums[i]);
  }
  printf("\n");
  for(int i = 0; i<cols;i++){
    printf("%d ", rand_vector[i]);
  }
  printf("\n");
  // Compute the average of your subset
  // int sub_sum = compute_sum(sub_rand_nums, num_elements_per_proc);

  // Gather all partial averages down to the root process
  /*float *sub_avgs = NULL;
  if (world_rank == 0) {
    sub_avgs = (float *)malloc(sizeof(float) * world_size);
    assert(sub_avgs != NULL);
  }
  MPI_Gather(&sub_avg, 1, MPI_FLOAT, sub_avgs, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

  // Now that we have all of the partial averages on the root, compute the
  // total average of all numbers. Since we are assuming each process computed
  // an average across an equal amount of elements, this computation will
  // produce the correct answer.
  if (world_rank == 0) {
    float avg = compute_avg(sub_avgs, world_size);
    printf("Avg of all elements is %f\n", avg);
    // Compute the average across the original data for comparison
    float original_data_avg =
    compute_avg(rand_nums, num_elements_per_proc * world_size);
    printf("Avg computed across original data is %f\n", original_data_avg);
  }

  // Clean up
  if (world_rank == 0) {
    free(rand_nums);
    free(sub_avgs);
  }
  free(sub_rand_nums);

  MPI_Barrier(MPI_COMM_WORLD);*/
  MPI_Finalize();
}
