/* ------------------------------------------------------------
	Name:     Jacobi Iteration with MPI N*1, Approach 2
	Author:   Siyu Yue
	Date:     11/10/2013
------------------------------------------------------------ */
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define STEP 20

//#define OUTPUT    // output the result for checking

//#define DEBUG

int main(int argc, char **argv)
{
	if( argc != 2 )
        printf("Usage: %s, [MATRIX_SIZE]\n", argv[0]);
    int i,j,k;
	int jn;
	int rank;
	int size;
	int M;
	int N = atoi(argv[1]);      // matrix size
	double *matA,*matB,*swap;
	double *leftbuf = NULL,*rightbuf = NULL;
	double *sendbuf = NULL;
	MPI_Request reqsl,reqsr,reqrl,reqrr;
#ifdef OUTPUT
    MPI_File fout;
#endif
    if( N <= 0 )
    {
        printf("Matrix size must be positive!\n");
        return -1;
    }

	// Initialize MPI	
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if( rank == size - 1 )
		M = N - N/size*rank;
	else
		M = N/size;
#ifdef DEBUG
	printf("Process %d of %d created, with %d*%d job size.\n",rank,size,N,M);
#endif
	matA = (double*)malloc(sizeof(double)*N*M);
	matB = (double*)malloc(sizeof(double)*N*M);
	if( rank != 0 )
		leftbuf = (double*)malloc(sizeof(double)*N);
	if( rank != size - 1 )
		rightbuf = (double*)malloc(sizeof(double)*N);
	sendbuf = (double*)malloc(sizeof(double)*N*3);
	MPI_Buffer_attach(sendbuf,sizeof(double)*N*3);
    // Initialize Matrix B
    for(j=0;j<M;j++)
    {
        for(i=0;i<N;i++)
        {
            matB[j*N+i] = 1.0;
        }
    }


    // Jacobi Iteration
    for(k=0;k<STEP;k++)
    {
#ifdef DEBUG
		printf("Process %d started communication.\n",rank);
#endif
		// Communication
		if( rank != 0 )
		{
			MPI_Ibsend(matB,N,MPI_DOUBLE,rank-1,0,MPI_COMM_WORLD,&reqsl);
			MPI_Irecv(leftbuf,N,MPI_DOUBLE,rank-1,0,MPI_COMM_WORLD,&reqrl);
		}
		if( rank != size - 1 )
		{
			MPI_Ibsend(matB+(M-1)*N,N,MPI_DOUBLE,rank+1,0,MPI_COMM_WORLD,&reqsr);
			MPI_Irecv(rightbuf,N,MPI_DOUBLE,rank+1,0,MPI_COMM_WORLD,&reqrr);
		}
#ifdef DEBUG
		printf("Process %d finished communication.\n",rank);
#endif
		for(j=1;j<M-1;j++)
		{
			jn = j*N;
			for(i=1;i<N-1;i++)
			{
				matA[jn+i] = matB[jn+i] + 0.25*(matB[jn+i-1]+matB[jn+i+1]+matB[jn+N+i]+matB[jn-N+i]);
			}
		}
		if( rank != 0 )
			MPI_Wait(&reqrl,MPI_STATUS_IGNORE);
		if( rank != size - 1 )
			MPI_Wait(&reqrr,MPI_STATUS_IGNORE);
		// left
		if( rank == 0 )
		{
			matA[0] = matB[0] + 0.25*(matB[1]+matB[N]);
			for(i=1;i<N-1;i++)
				matA[i] = matB[i] + 0.25*(matB[i-1]+matB[i+1]+matB[N+i]);
			matA[N-1] = matB[N-1] + 0.25*(matB[N-2]+matB[2*N-1]);
		}
		else
		{
			matA[0] = matB[0] + 0.25*(matB[1]+matB[N]+leftbuf[0]);
			for(i=1;i<N-1;i++)
				matA[i] = matB[i] + 0.25*(matB[i-1]+matB[i+1]+matB[N+i]+leftbuf[i]);
			matA[N-1] = matB[N-1] + 0.25*(matB[N-2]+matB[2*N-1]+leftbuf[N-1]);
		}
		// right
		if( rank == size - 1 )
		{
			matA[(M-1)*N] = matB[(M-1)*N] + 0.25*(matB[(M-1)*N+1]+matB[(M-2)*N]);
			for(i=1;i<N-1;i++)
				matA[(M-1)*N+i] = matB[(M-1)*N+i] + 0.25*(matB[(M-1)*N+i-1]+matB[(M-1)*N+i+1]+matB[(M-2)*N+i]);
			matA[(M-1)*N+N-1] = matB[(M-1)*N+N-1] + 0.25*(matB[M*N-2]+matB[(M-1)*N-1]);
		}
		else
		{
			matA[(M-1)*N] = matB[(M-1)*N] + 0.25*(matB[(M-1)*N+1]+matB[(M-2)*N]+rightbuf[0]);
			for(i=1;i<N-1;i++)
				matA[(M-1)*N+i] = matB[(M-1)*N+i] + 0.25*(matB[(M-1)*N+i-1]+matB[(M-1)*N+i+1]+matB[(M-2)*N+i]+rightbuf[i]);
			matA[(M-1)*N+N-1] = matB[(M-1)*N+N-1] + 0.25*(matB[M*N-2]+matB[(M-1)*N-1]+rightbuf[N-1]);
		}
		// up
		for(j=1;j<M-1;j++)
			matA[j*N] = matB[j*N] + 0.25*(matB[(j-1)*N]+matB[j*N+1]+matB[(j+1)*N]);
		// down
		for(j=1;j<M-1;j++)
			matA[(j+1)*N-1] = matB[(j+1)*N-1] + 0.25*(matB[j*N-1]+matB[(j+1)*N-2]+matB[(j+2)*N-1]);

        // swap
        swap = matA;
		matA = matB;
		matB = swap;
		if( rank != 0 )
			MPI_Wait(&reqsl,MPI_STATUS_IGNORE);
		if( rank != size - 1 )
			MPI_Wait(&reqsr,MPI_STATUS_IGNORE);
#ifdef DEBUG
		printf("Process %d finished %dth iteration.\n",rank,k);
#endif

    } // for(k=0;k<STEP;k++)

#ifdef OUTPUT
	MPI_File_open(MPI_COMM_WORLD,"out3.txt",MPI_MODE_WRONLY|MPI_MODE_CREATE,MPI_INFO_NULL,&fout);
	for(i=0;i<N;i++)
    {
		if( rank != 0 )
			MPI_Recv(NULL,0,MPI_BYTE,rank-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        for(j=0;j<M;j++)
        {
            MPI_File_write_shared(fout,matB+j*N+i,1,MPI_DOUBLE,MPI_STATUS_IGNORE);
        }
		if( rank != size - 1 )
			MPI_Ssend(NULL,0,MPI_BYTE,rank+1,0,MPI_COMM_WORLD);

		MPI_Barrier(MPI_COMM_WORLD);
    }
	MPI_File_close(&fout);
#endif
	MPI_Buffer_detach(sendbuf,&k);

	free(matA);
	free(matB);
	free(leftbuf);
	free(rightbuf);
	free(sendbuf);

	MPI_Finalize();
    return 0;
}
