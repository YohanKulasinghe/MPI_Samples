#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
	//Initialize MPI Environemt 
	MPI_Init(NULL, NULL);

    //Get the number og processes
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	//Get the rank of Processes
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	//Get the name of processor
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
	MPI_Get_processor_name(processor_name, &name_len);

	//Print off hello world message
	printf("Hello World from processor %s, rank %d out of %d processors\n", processor_name, world_rank,world_size);

	//Finnalize the MPI Environment
	MPI_Finalize();
}