/* ------------------------------------------------------------
    Name:     Jacobi Iteration, Serial Execution
    Author:   Siyu Yue
    Date:     11/10/2013
------------------------------------------------------------ */
#include <stdio.h>
#include <stdlib.h>

#define STEP 20

int main(int argc, char **argv)
{
    if( argc != 2 )
        printf("Usage: %s, [MATRIX_SIZE]\n", argv[0]);
    int i,j,k;
	int in;
    double *matA;
    double *matB;
	double *swap;
    int N = atoi(argv[1]);      // matrix size
    if( N <= 0 )
    {
        printf("Matrix size must be positive!\n");
    }

	matA = (double*)malloc(sizeof(double)*N*N);
	matB = (double*)malloc(sizeof(double)*N*N);
    // initialize matrix A and B
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            matB[i*N+j] = 1.0;
        }
    }

    // Jacobi Iteration
    for(k=0;k<STEP;k++)
    {
        for(i=1;i<N-1;i++)
        {
			in = i*N;
            for(j=1;j<N-1;j++)
            {
				matA[in+j] = matB[in+j] + 0.25*(matB[in-N+j]+matB[in+N+j]+matB[in+j-1]+matB[in+j+1]);
            }
        }

		// left
		matA[0] = matB[0] + 0.25*(matB[1]+matB[N]);
		for(i=1;i<N-1;i++)
			matA[i*N] = matB[i*N] + 0.25*(matB[i*N+1]+matB[(i+1)*N]+matB[(i-1)*N]);
		matA[(N-1)*N] = matB[(N-1)*N] + 0.25*(matB[(N-2)*N]+matB[(N-1)*N+1]);
		// right
		matA[N-1] = matB[N-1] + 0.25*(matB[N+N-1]+matB[N-2]);
		for(i=1;i<N-1;i++)
			matA[(i+1)*N-1] = matB[(i+1)*N-1] + 0.25*(matB[(i+1)*N-2]+matB[i*N-1]+matB[(i+2)*N-1]);
		matA[N*N-1] = matB[N*N-1] + 0.25*(matB[N*N-2]+matB[(N-1)*N-1]);
		// up
		for(j=1;j<N-1;j++)
			matA[j] = matB[j] + 0.25*(matB[j-1]+matB[N+j]+matB[j+1]);
		// down
		for(j=1;j<N-1;j++)
			matA[(N-1)*N+j] = matB[(N-1)*N+j] + 0.25*(matB[(N-1)*N+j-1]+matB[(N-2)*N+j]+matB[(N-1)*N+j+1]);
			
		// swap
        swap = matA;
		matA = matB;
		matB = swap;

    } // for(k=0;k<STEP;k++)

	free(matA);
	free(matB);
	
    return 0;
}
