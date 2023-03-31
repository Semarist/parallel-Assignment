#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
#include <omp.h>

pthread_mutex_t mutex;
int MSize=0;

void main(int argc, char *argv[])
{
	if(argc!=2)
	{
		printf("Error!! Wrong number of arguments\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		clock_t start, end;
		double runtime_exec=0.0;

		
		int MATRICES_SIZE = atoi(argv[1]);

		pthread_mutex_lock(&mutex);
		MSize = MATRICES_SIZE;
		pthread_mutex_unlock(&mutex);

		int Matrix_M[MATRICES_SIZE][MATRICES_SIZE]; // 1st matrix
		int Matrix_N[MATRICES_SIZE][MATRICES_SIZE]; // 2nd matrix
		int Result_Matrix[MATRICES_SIZE][MATRICES_SIZE]; // Resulting matrix

		printf("Filling matrices M and N:\n");
		printf("\nMatrixM:\n");
		for(int i=0;i<MATRICES_SIZE;i++)
		{
			for(int j=0;j<MATRICES_SIZE;j++)
			{
				scanf("%d", &Matrix_M[i][j]);
			}
		}
		printf("\nMatrix N:\n");
		for(int i=0;i<MATRICES_SIZE;i++)
		{
			for(int j=0;j<MATRICES_SIZE;j++)
			{
				scanf("%d", &Matrix_N[i][j]);
			}
		}

		start = clock();

		#pragma omp parallel for private(i,j,k) shared(Matrix_M, Matrix_N, Result_Matrix)
		{
			for(int i=0;i<MSize; i++)
			{
				for(int j=0;j<MSize;j++)
				{
					Result_Matrix[i][j] =0.0;
					for(int k=0;k<MSize;k++)
					{
						Result_Matrix[i][j] += Matrix_M[i][k]*Matrix_N[k][j];
					}
				}
			}
		}
		end= clock();
		runtime_exec = ((double)(end-start))/CLOCKS_PER_SEC;


		printf("\nResulting Matrix, Matrix C: \n");

		for(int i=0;i<MATRICES_SIZE;i++)
		{
			for(int j=0;j<MATRICES_SIZE;j++)
			{
				printf("%d ", Result_Matrix[i][j]);

				if((j+1)%MATRICES_SIZE==0)
				{
					printf("\n");
				}
			}
		}
		printf("Time of execution: %.8f\n", runtime_exec);

	}
}
