#include <mpi.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>

int a[];
int a2[6];
int a3[6];
int localArray[6];

int main(int argc, char* argv[])
{
	int rank, world_size, elements_per_process, i, q;
	time_t t;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	srand((unsigned)time(&t));

	if (rank == 0) {

		// Generate random numbers
		q = (world_size - 1) * 6;
		int* a = (int*)malloc(6 * sizeof(int));
		for (i = 0; i < q; i++) {
			a[i] = 1000 + rand() % 5000;
		}

		for (int i = 1; i <= world_size-1; i++) {

			// Devide array into chanks of 6 elements
			int j = 0;
			for (int k = (i - 1) * 6; k < (i-1)*6 +6; k++) {
				localArray[j++] = a[k];
			}

			//MPI Message passing
			MPI_Send(localArray,6,MPI_INT, i, 0,MPI_COMM_WORLD);
			MPI_Recv(a3, 6, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);

			printf("!!! Results From Processor %d  ", status.MPI_SOURCE);
			
			for (int i = 0; i < 6; i++) {
				printf("%d ", a3[i]);
			}
			printf("\n");
		}
	}
	
	else {
		MPI_Recv(a2, 6,MPI_INT, 0, 0,MPI_COMM_WORLD,&status);
		printf("# Inputs to Processer %d  ", rank);

		for (int i = 0; i < 6; i++) {
			printf("%d ", a2[i]);
			a2[i] = a2[i] * 3;
		}
		printf("\n");

		MPI_Send(a2, 6, MPI_INT, 0, 1, MPI_COMM_WORLD);
	}

	MPI_Finalize();

	return 0;
}
