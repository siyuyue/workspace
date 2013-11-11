/* ------------------------------------------------------------
    Name:     Jacobi Iteration with MPI N*N
    Author:   Siyu Yue
    Date:     11/10/2013
------------------------------------------------------------ */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

#define STEP 20

//#define OUTPUT    // output the result for checking

//#define DEBUG

int main(int argc, char **argv)
{
	if( argc != 2 )
        printf("Usage: %s, [MATRIX_SIZE]\n", argv[0]);
    int i,j,k;
	int im;
	int rank;
	int size;
	int sizeu,sizev;
	int ranku,rankv;
	int n,m;
	int N = atoi(argv[1]);      // matrix size
	double *matA,*matB,*swap;
	double *leftbuf = NULL,*rightbuf = NULL,*upbuf = NULL,*downbuf = NULL;
	MPI_Datatype MPI_VVEC;
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

	// Decide the division of matrix
	sizeu = (int)sqrt((double)size);
	while( size%sizeu != 0)
		sizeu --;
	sizev = size/sizeu;
	ranku = rank/sizev;
	rankv = rank - ranku*sizev;	

	if( ranku == sizeu - 1 )
		n = N - N/sizeu*ranku;
	else
		n = N/sizeu;
	if( rankv == sizev - 1 )
		m = N - N/sizev*rankv;
	else
		m = N/sizev;

	MPI_Type_vector(n,1,m,MPI_DOUBLE,&MPI_VVEC);
	MPI_Type_commit(&MPI_VVEC);
#ifdef DEBUG
	printf("Process (%d,%d) of (%d,%d) created, with %d*%d job size.\n",ranku,rankv,sizeu,sizev,n,m);
#endif
	matA = (double*)malloc(sizeof(double)*n*m);
	matB = (double*)malloc(sizeof(double)*n*m);
	if( rankv != 0 )
		leftbuf = (double*)malloc(sizeof(double)*n);
	if( rankv != sizev - 1 )
		rightbuf = (double*)malloc(sizeof(double)*n);
	if( ranku != 0 )
		upbuf = (double*)malloc(sizeof(double)*m);
	if( ranku != sizeu - 1 )
		downbuf = (double*)malloc(sizeof(double)*m);
    // Initialize Matrix B
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            matB[i*m+j] = 1.0;
        }
    }


    // Jacobi Iteration
    for(k=0;k<STEP;k++)
    {
#ifdef DEBUG
		printf("Process (%d,%d) started communication.\n",ranku,rankv);
#endif
		// Communication
		if( ranku%2 == 0 )
		{
			if( ranku != 0 )
			{
				MPI_Sendrecv(matB,m,MPI_DOUBLE,(ranku-1)*sizev+rankv,0,upbuf,m,MPI_DOUBLE,(ranku-1)*sizev+rankv,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			}
			if( ranku != sizeu - 1 )
			{
				MPI_Sendrecv(matB+(n-1)*m,m,MPI_DOUBLE,(ranku+1)*sizev+rankv,0,downbuf,m,MPI_DOUBLE,(ranku+1)*sizev+rankv,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			}
		}
		else
		{
			if( ranku != sizeu - 1 )
			{
				MPI_Sendrecv(matB+(n-1)*m,m,MPI_DOUBLE,(ranku+1)*sizev+rankv,0,downbuf,m,MPI_DOUBLE,(ranku+1)*sizev+rankv,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			}
			MPI_Sendrecv(matB,m,MPI_DOUBLE,(ranku-1)*sizev+rankv,0,upbuf,m,MPI_DOUBLE,(ranku-1)*sizev+rankv,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		}
		if( rankv%2 == 0 )
		{
			if( rankv != 0 )
			{
				MPI_Sendrecv(matB,1,MPI_VVEC,(ranku)*sizev+rankv-1,0,leftbuf,n,MPI_DOUBLE,(ranku)*sizev+rankv-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			}
			if( rankv != sizev - 1 )
			{
				MPI_Sendrecv(matB+m-1,1,MPI_VVEC,(ranku)*sizev+rankv+1,0,rightbuf,n,MPI_DOUBLE,(ranku)*sizev+rankv+1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			}
		}
		else
		{
			if( rankv != sizev - 1 )
			{
				MPI_Sendrecv(matB+m-1,1,MPI_VVEC,(ranku)*sizev+rankv+1,0,rightbuf,n,MPI_DOUBLE,(ranku)*sizev+rankv+1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			}
			MPI_Sendrecv(matB,1,MPI_VVEC,(ranku)*sizev+rankv-1,0,leftbuf,n,MPI_DOUBLE,(ranku)*sizev+rankv-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		}
#ifdef DEBUG
		printf("Process (%d,%d) finished communication.\n",ranku,rankv);
#endif
        for(i=1;i<n-1;i++)
        {
			im = i*m;
            for(j=1;j<m-1;j++)
            {
				matA[im+j] = matB[im+j] + 0.25*(matB[im-m+j]+matB[im+m+j]+matB[im+j-1]+matB[im+j+1]);
            }
        }
#ifdef DEBUG
		printf("Process (%d,%d) started four sides.\n",ranku,rankv);
#endif
		// left
		if( rankv == 0 )
		{
			if( ranku == 0 )
				matA[0] = matB[0] + 0.25*(matB[1]+matB[m]);
			else
				matA[0] = matB[0] + 0.25*(matB[1]+matB[m]+upbuf[0]);
			for(i=1;i<n-1;i++)
				matA[i*m] = matB[i*m] + 0.25*(matB[i*m+1]+matB[(i+1)*m]+matB[(i-1)*m]);
			if( ranku == sizeu - 1 )
				matA[(n-1)*m] = matB[(n-1)*m] + 0.25*(matB[(n-2)*m]+matB[(n-1)*m+1]);
			else
				matA[(n-1)*m] = matB[(n-1)*m] + 0.25*(matB[(n-2)*m]+matB[(n-1)*m+1]+downbuf[0]);
		}
		else
		{
			if( ranku == 0 )
				matA[0] = matB[0] + 0.25*(matB[1]+matB[m]+leftbuf[0]);
			else
				matA[0] = matB[0] + 0.25*(matB[1]+matB[m]+upbuf[0]+leftbuf[0]);
			for(i=1;i<n-1;i++)
				matA[i*m] = matB[i*m] + 0.25*(matB[i*m+1]+matB[(i+1)*m]+matB[(i-1)*m]+leftbuf[i]);
			if( ranku == sizeu - 1 )
				matA[(n-1)*m] = matB[(n-1)*m] + 0.25*(matB[(n-2)*m]+matB[(n-1)*m+1]+leftbuf[n-1]);
			else
				matA[(n-1)*m] = matB[(n-1)*m] + 0.25*(matB[(n-2)*m]+matB[(n-1)*m+1]+downbuf[0]+leftbuf[n-1]);
		}
		// right
		if( rankv == sizev - 1 )
		{
			if( ranku == 0 )
				matA[m-1] = matB[m-1] + 0.25*(matB[m+m-1]+matB[m-2]);
			else
				matA[m-1] = matB[m-1] + 0.25*(matB[m+m-1]+matB[m-2]+upbuf[m-1]);
			for(i=1;i<n-1;i++)
				matA[(i+1)*m-1] = matB[(i+1)*m-1] + 0.25*(matB[(i+1)*m-2]+matB[i*m-1]+matB[(i+2)*m-1]);
			if( ranku == sizeu - 1 )
				matA[n*m-1] = matB[n*m-1] + 0.25*(matB[n*m-2]+matB[(n-1)*m-1]);
			else
				matA[n*m-1] = matB[n*m-1] + 0.25*(matB[n*m-2]+matB[(n-1)*m-1]+downbuf[m-1]);
		}
		else
		{
			if( ranku == 0 )
				matA[m-1] = matB[m-1] + 0.25*(matB[m+m-1]+matB[m-2]+rightbuf[0]);
			else
				matA[m-1] = matB[m-1] + 0.25*(matB[m+m-1]+matB[m-2]+upbuf[m-1]+rightbuf[0]);
			for(i=1;i<n-1;i++)
				matA[(i+1)*m-1] = matB[(i+1)*m-1] + 0.25*(matB[(i+1)*m-2]+matB[i*m-1]+matB[(i+2)*m-1]+rightbuf[i]);
			if( ranku == sizeu - 1 )
				matA[n*m-1] = matB[n*m-1] + 0.25*(matB[n*m-2]+matB[(n-1)*m-1]+rightbuf[n-1]);
			else
				matA[n*m-1] = matB[n*m-1] + 0.25*(matB[n*m-2]+matB[(n-1)*m-1]+downbuf[m-1]+rightbuf[n-1]);
		}
		// up
		if( ranku == 0 )
			for(j=1;j<m-1;j++)
				matA[j] = matB[j] + 0.25*(matB[j-1]+matB[m+j]+matB[j+1]);
		else
			for(j=1;j<m-1;j++)
				matA[j] = matB[j] + 0.25*(matB[j-1]+matB[m+j]+matB[j+1]+upbuf[j]);
		// down
		if( ranku == sizeu - 1 )
			for(j=1;j<m-1;j++)
				matA[(n-1)*m+j] = matB[(n-1)*m+j] + 0.25*(matB[(n-1)*m+j-1]+matB[(n-2)*m+j]+matB[(n-1)*m+j+1]);
		else
			for(j=1;j<m-1;j++)
				matA[(n-1)*m+j] = matB[(n-1)*m+j] + 0.25*(matB[(n-1)*m+j-1]+matB[(n-2)*m+j]+matB[(n-1)*m+j+1]+downbuf[j]);
        // swap
        swap = matA;
		matA = matB;
		matB = swap;
#ifdef DEBUG
		printf("Process (%d,%d) finished %dth iteration.\n",ranku,rankv,k);
#endif

    } // for(k=0;k<STEP;k++)

#ifdef OUTPUT
	MPI_File_open(MPI_COMM_WORLD,"out2.txt",MPI_MODE_WRONLY|MPI_MODE_CREATE,MPI_INFO_NULL,&fout);

	for(k=0;k<sizeu;k++)
	{
		for(i=0;i<n;i++)
		{
			if( ranku == k )
			{
				if( rankv != 0 )
					MPI_Recv(NULL,0,MPI_BYTE,ranku*sizev+rankv-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

				MPI_File_write_shared(fout,matB+i*m,m,MPI_DOUBLE,MPI_STATUS_IGNORE);

				if( rankv != sizev - 1 )
					MPI_Ssend(NULL,0,MPI_BYTE,ranku*sizev+rankv+1,0,MPI_COMM_WORLD);
			}
			MPI_Barrier(MPI_COMM_WORLD);
		}
	}
	MPI_File_close(&fout);
#endif
	free(matA);
	free(matB);
	free(leftbuf);
	free(rightbuf);
	free(upbuf);
	free(downbuf);

	MPI_Finalize();
    return 0;
}
