#include <mpi.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char** argv)
{
	char message[256];
	int my_rank;
	MPI_Status status;
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if (my_rank == 0) {
		strcpy_s(message, "Hello, There!");
		MPI_Send(message, strlen(message) + 1, MPI_CHAR, 1, 99, MPI_COMM_WORLD);
	}

	else if (my_rank == 1) {
		MPI_Recv(message, 256, MPI_CHAR, 0, 99, MPI_COMM_WORLD, &status);
		printf("Process % d received : % s\n", my_rank, message);
	}

	MPI_Finalize();
	return 0;
}