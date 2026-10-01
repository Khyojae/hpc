#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int NRA, NCA, NRB, NCB, NRC, NCC;
    int i, j, k;
    int n = 1024;
    double tr;
    double **matA, **matB, **matC;
    clock_t start, end;

    /* Determine row and cloumn sizes of matrices matA, matB, and matC */
    NRA = NRB = NRC = NCA = NCB = NCC = n;

    matA = (double**)malloc(NRA * sizeof(double*));
    matB = (double**)malloc(NRB * sizeof(double*));
    matC = (double**)malloc(NRC * sizeof(double*));
    
    for (i = 0; i < NRA; i++)
        matA[i] = (double*)malloc(NCA * sizeof(double));
    for (i = 0; i < NRB; i++)
        matB[i] = (double*)malloc(NCB * sizeof(double));
    for (i = 0; i < NRC; i++)
        matC[i] = (double*)malloc(NCC * sizeof(double));


    /* Initialize matrices matA and matB */
    for (i = 0; i < NRA; i++){
        for (j = 0; j < NCA; j++){
            matA[i][j] = ((double) rand() / (RAND_MAX));
        }
    }

    for (i = 0; i < NRB; i++){
        for (j = 0; j < NCB; j++){
            matB[i][j] = ((double) rand() / (RAND_MAX));
        }
    }

    for (i = 0; i < NRB; i++){
        for (j = 0; j < NCB; j++){
            matC[i][j] = 0.0;
        }
    }    

    start = clock();

    /* Compute matrix multiplication c=a*b */
    for (i = 0; i < NRA; i++){
        for (j = 0; j < NCC; j++){
            for (k = 0; k < NCA; k++){
                matC[i][j] = matC[i][j] + matA[i][k] * matB[k][j];
            }
        }
    }
    
    end = clock();

    /* Compute the trace of c, tr(c)=sum(diag(c)) */
    tr = 0.0;

    for(i = 0; i < n; i++)
        tr = tr + matC[i][i];


    printf("Matrix C[%d][%d], Elapsed time: %f (sec), Tr: %f \n", NRC, NCC, (double)(end - start) / CLOCKS_PER_SEC, tr);

    for(i = 0; i < n; i++){
        free(matA[i]);
        free(matB[i]);
        free(matC[i]);
    }

    free(matA);
    free(matB);
    free(matC);
    
    return 0;
}