#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

void work(int myrank);
bool isPrimeNumber(int i);

int main() {

	MPI_Init(NULL, NULL);
	int myrank, numprocs;

	/*variables used for gathering timing statistics*/
	double mytime, maxtime, mintime, avgtime;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Barrier(MPI_COMM_WORLD); /*synchronize all processes*/
	mytime = MPI_Wtime(); /*get time just before work section */
	work(myrank);
	mytime = MPI_Wtime() - mytime; /*get time just after work section*/

	/*compute max, min, and average timing statistics*/
	MPI_Reduce(&mytime, &maxtime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
	MPI_Reduce(&mytime, &mintime, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);
	MPI_Reduce(&mytime, &avgtime, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	if (myrank == 0) {
		avgtime /= numprocs;
		printf("Min: %lf Max: %lf Avg: %lf\n", mintime, maxtime, avgtime);
	}

	MPI_Finalize();

	return(0);
}

void work(int myrank) {
	for (int i = 1000 * myrank; i < 1000 * myrank + 999; i++) {
		if (isPrimeNumber(i)) {
			printf("Prime Number in Process %d\'s Range - %d\n",myrank, i);
		}
	}
}

bool isPrimeNumber(int number) {

	int isPrime = true;
	int loopCount = number / 2;

	if (number <= 1) {
		isPrime = false;
	}
	else {
		for (int j = 2; j <= loopCount; j++) {
			if (number % j == 0) {
				isPrime = false;
				break;
			}
		}
	}

	return isPrime;
}
