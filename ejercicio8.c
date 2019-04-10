#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(void) {
   int n; 
   int local_n; 
   int i; 
   int escalar; 
   int* vector1 = NULL; 
   int* vector2 = NULL; 
   int* local_vector1; 
   int* local_vector2; 
   int local_suma = 0; 
   int resultado = 0; 
   int comm_sz;
   int my_rank;

   MPI_Init(NULL, NULL); 
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 

   if (my_rank == 0) {
      printf("Ingrese tam de vectores\n");
      scanf("%d", &n);
      printf("Ingrese el escalar\n");
      scanf("%d", &escalar);
      local_n = n/comm_sz;
   }

    MPI_Bcast(&local_n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&escalar, 1, MPI_INT, 0, MPI_COMM_WORLD);

   vector1 = (int*)malloc(n*sizeof(int));
   vector2 = (int*)malloc(n*sizeof(int));
   local_vector1 = (int*)malloc(local_n*sizeof(int));
   local_vector2 = (int*)malloc(local_n*sizeof(int));

    if(my_rank == 0){
        printf("Ingrese el primer vector\n");
        for(i=0;i<n;i++)
            scanf("%d",&vector1[i]);

        printf("Ingrese el segundo vector\n");
        for(i=0;i<n;i++)
            scanf("%d",&vector2[i]);
        MPI_Scatter(vector1, local_n, MPI_INT, local_vector1, local_n, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Scatter(vector2, local_n, MPI_INT, local_vector2, local_n, MPI_INT, 0, MPI_COMM_WORLD);
        free(vector1);
        free(vector2);
    }
    else{
        MPI_Scatter(vector1, local_n, MPI_INT, local_vector1, local_n, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Scatter(vector2, local_n, MPI_INT, local_vector2, local_n, MPI_INT, 0, MPI_COMM_WORLD);
    }

    for(i=0;i<local_n;i++){
        local_vector1[i] *= escalar;
        local_vector1[i] *= local_vector2[i];
        local_suma += local_vector1[i];
    }

    MPI_Reduce(&local_suma, &resultado, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(my_rank == 0){
        printf("Resultado final: %d\n",resultado);
        free(local_vector1);
        free(local_vector2);
    }
    MPI_Finalize(); 

    return 0;
}
