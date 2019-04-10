#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void leer_matriz(double* matriz, int n);
void imprimir_matriz(double* matriz, int tamano);
void const_tipo_indexado(double* matriz, int n, MPI_Datatype* nuevo_tipo_construido);
void recibir_n(int * n, int my_rank, MPI_Comm mpi_comm);

int main(void) {
    int my_rank, comm_sz;
    int n;
    MPI_Comm mpi_comm = MPI_COMM_WORLD;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(mpi_comm, &comm_sz);
    MPI_Comm_rank(mpi_comm, &my_rank);

    recibir_n(&n, my_rank, mpi_comm);
    double matriz[n*n];
    MPI_Datatype nuevo_tipo;
    const_tipo_indexado(matriz, n, &nuevo_tipo);
    if (my_rank == 0) {
        leer_matriz(matriz, n);
        MPI_Send(matriz, 1, nuevo_tipo, 1, 0, mpi_comm);
    }
    else {
        MPI_Recv(matriz, 1, nuevo_tipo, 0, 0, mpi_comm, MPI_STATUS_IGNORE);
        imprimir_matriz(matriz, n);
    }

    MPI_Type_free(&nuevo_tipo);
    MPI_Finalize();
    return 0;
}

void leer_matriz(double* matriz, int tamano) {
    printf("Ingrese matriz n x n:\n");
    int i;
    for (i = 0; i < tamano; i++) {
        int j;
        for (j = 0; j < tamano; j++) {

            scanf("%lf", &matriz[i*tamano+j]);
        }
    }
}


void imprimir_matriz(double* matriz, int tamano) {
    printf("Matriz:\n");
    int i;
    for (i = 0; i < tamano; i++) {
        int j;
        for (j = 0; j < tamano; j++) {
            printf("%f ", matriz[i*tamano + j]);
        }
        printf("\n");
    }
}

void const_tipo_indexado(double* matriz, int n, MPI_Datatype* nuevo_tipo_construido) {
    int array_tamano_bloques[n];
    int array_distancias[n];
    array_distancias[0] = 0;
    int i;
    int j;
    for (i = 0, j = n; i < n; i++, j--) {
        array_tamano_bloques[i] = j;
    }
    for (i = 1; i < n;  i++) {
        array_distancias[i] = i*n + i;
    }
    MPI_Type_indexed(n, array_tamano_bloques, array_distancias, MPI_DOUBLE, nuevo_tipo_construido);
    MPI_Type_commit(nuevo_tipo_construido);
}

void recibir_n(int * n, int my_rank, MPI_Comm mpi_comm) {
    if (my_rank == 0) {
        printf("Ingrese tam de n:\n");
        scanf("%d", n);
        MPI_Send(n, 1, MPI_INT, 1, 0, mpi_comm);
    } 
    else {
        MPI_Recv(n, 1, MPI_INT, 0, 0, mpi_comm, MPI_STATUS_IGNORE);
    }
}
