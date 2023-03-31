#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

void *handler(void*param)
{
	int *individual_row_column = (int*) param;  // each row 
	int x = individual_row_column[0];
	int k=0;
	int i=0;
	for(int i=1;i<=x;i++)
	{
		k+= individual_row_column[i]*individual_row_column[i+x];
		
	}
	int *pointer_to_result = (int *)malloc(sizeof(int));
	*pointer_to_result = k;
	pthread_exit(pointer_to_result);

}
void main(int argc, char *argv[])
{
	if(argc!=2)
	{
		printf("Error!! wrong number of arguments\n");
	}
	else
	{
		clock_t start, end;
		double exec_time=0.0;
		start = clock();


		int MAX_ROW= atoi(argv[1]); // MAX
		printf("%d is the maximum number of rows of matrices entered by user\n", MAX_ROW);
		int MatM[MAX_ROW][MAX_ROW];
		int MatN[MAX_ROW][MAX_ROW];
		int row_m = MAX_ROW;
		int row_n = MAX_ROW;
		int col_m = MAX_ROW;
		int col_n = MAX_ROW;

		printf("\nMatrix M:\n");
		for(int i=0;i< MAX_ROW; i++)
		{
			for(int j=0;j< MAX_ROW; j++)
			{
				scanf("%d", &MatM[i][j]);
			}
		}
		printf("\nMatrix N:\n");	
		for(int i=0;i< MAX_ROW; i++)
		{
			for(int j=0;j< MAX_ROW; j++)
			{
				scanf("%d", &MatN[i][j]);
			}
		}

		int c=0;
		int num_threads= row_m * col_n;
		pthread_t threads_total[num_threads];
		int *individual_row_column;

		for(int i=0;i<row_m;i++)
		{
			for(int j=0;j<col_n;j++)
			{
				individual_row_column = (int*) malloc((MAX_ROW*(MAX_ROW+1))*sizeof(int));
				individual_row_column[0] = col_m;

				for(int l = 0; l<col_m; l++)
				{
					individual_row_column[l+1] = MatM[i][l];
				}
				for(int l = 0; l<row_n; l++)
				{
					individual_row_column[l+col_m+1] = MatN[l][j];
				}

				pthread_create(&threads_total[c++], NULL, handler, (void*) individual_row_column);

			}
		}

		printf("\nMatrix  C (The result of the matrix multiplication:)\n");
		for(int g=0;g<num_threads;g++)
		{
			void *results;
			pthread_join(threads_total[g], &results);

			int *pointer_to_result = (int *)results;
			printf("%d ", *pointer_to_result);
			if((g+1)%col_n==0) // to print on a new line
			{
				printf("\n");
			}
		}


		end = clock();
		exec_time = ((double)(end-start))/CLOCKS_PER_SEC;

		printf("\nTime of execution: %.8f\n",exec_time);
	} }
