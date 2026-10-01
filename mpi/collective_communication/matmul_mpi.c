#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

double **alloc_2d_double(int rows, int cols)
{
    int i;
    
    double *data = (double *)malloc(sizeof(double) * rows * cols);
    double **array = (double **)malloc(sizeof(double *) * rows);
    
    for(i = 0; i < rows; i++)
        array[i] = &(data[cols * i]);

    return array;
}

int main(int argc, char **argv)
{
    int NRA, NCA, NRB, NCB, NRC, NCC, NRS, NCS, NRG, NCG;
    int i, j, k;
    int root, nprocs, myrank, rows;
    int size = 1024;
    double tr;
    double **matA, **matB, **matC, **matS, **matG;
    double start, end;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    
    root = 0;
    rows = (int)size/nprocs;

    /* Determine row and cloumn sizes of matrices matA, matB, and matC */
    NRA = NRB = NRC = NCA = NCB = NCC = NRS = NCS = NRG = NCG = size;

    matA = alloc_2d_double(NRA, NCA);
    matB = alloc_2d_double(NRB, NCB);
    matC = alloc_2d_double(NRC, NCC);
    matS = alloc_2d_double(rows, NCS);
    matG = alloc_2d_double(rows, NCG);
    
    /* Initialize matrices matA and matB */
    if(myrank == root) {      
        for(i = 0; i < NRA; i++)
            for(j = 0; j < NCA; j++)
                matA[i][j] = ((double) rand() / (RAND_MAX));

        for(i = 0; i < NRB; i++)
            for(j = 0; j < NCB; j++)
                matB[i][j] = ((double) rand() / (RAND_MAX));
    }
    
    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();    
    
    /* 1. put here bcast Matrix B */
    MPI_Bcast(&(matB[0][0]), ???, MPI_DOUBLE, ???, MPI_COMM_WORLD);

    /* 2. put here scatter Matrix A */
    MPI_Scatter(???, ???, MPI_DOUBLE, ???, ???, MPI_DOUBLE, ???, MPI_COMM_WORLD);

    /* 3. matrix-matrix multiplication */
    for(i = 0; i < ???; i++) {
        for(j = 0; j < NCB; j++) {
            matG[i][j] = 0.0;
            for(k = 0; k < NCA; k++) {
                matG[i][j] = matG[i][j] + matS[i][k]*matB[k][j];
            }
        }
    }

    /* 4. put gather each partial matrix C */
    MPI_Gather(???, ???, MPI_DOUBLE, ???, ???, MPI_DOUBLE, ???, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    end = MPI_Wtime();

    /* Compute the trace of c, tr(c)=sum(diag(c)) */
    if(myrank == root) {
        tr = 0.0;

        for(i = 0; i < size; i++)
            tr = tr + matC[i][i];

        printf("Matrix C[%d][%d], Elapsed time: %f (sec), Tr: %f \n", NRC, NCC, end - start, tr);            
    }

    free(matA[0]);
    free(matB[0]);
    free(matC[0]);
    free(matS[0]);
    free(matG[0]);    
    free(matA);
    free(matB);
    free(matC);
    free(matS);
    free(matG);
  
    MPI_Finalize();

    return 0;
}
