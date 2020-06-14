#include <mpi.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char** argv)
{
	int num_students;
	double grade[10];
	char note[1024];
	int tag1 = 1001, tag2 = 1002;
	int rank, ncpus;
	MPI_Status status;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// set num_students,grade,note in rank=0 cpu
		if (rank == 0) {
			MPI_Send(&num_students, 1, MPI_INT, 1, tag1, MPI_COMM_WORLD);
			MPI_Send(grade, 10, MPI_DOUBLE, 2, tag1, MPI_COMM_WORLD);
			MPI_Send(note, strlen(note) + 1, MPI_CHAR, 1, tag2, MPI_COMM_WORLD);
		}
	if (rank == 1) {
		MPI_Recv(&num_students, 1, MPI_INT, 0, tag1, MPI_COMM_WORLD, &status);
		//printf("Process % d received : % s\n", rank, num_students);

		MPI_Recv(note, 2048, MPI_CHAR, 0, tag2, MPI_COMM_WORLD, &status);
		//printf("Process % d received : % s\n", rank, note);
	}

	if (rank == 2) {
		MPI_Recv(grade, 10, MPI_DOUBLE, 0, tag1, MPI_COMM_WORLD, &status);
		printf("Process % d received : % s\n", rank, grade);
	}

	MPI_Finalize();
	return 0;
}