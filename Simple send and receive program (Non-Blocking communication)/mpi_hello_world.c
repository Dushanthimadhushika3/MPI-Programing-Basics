//Example 04
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {

  int myid,numprocs;
  int tag,source,destination,count;
  int buffer;
  MPI_Status status;
  MPI_Request request;

  MPI_Init(&argc, &argv);

  // Get the number of processes
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

  // Get the rank of the process
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);

  tag = 1234;
  source = 0;
  destination = 1;
  count = 1;
  request = MPI_REQUEST_NULL;

 if(myid == source){
	buffer = 5678;
MPI_Isend(&buffer,count,MPI_INT,destination,tag,MPI_COMM_WORLD,&request);
 }
 
if(myid == destination){
	MPI_Irecv(&buffer,count,MPI_INT,source,tag,MPI_COMM_WORLD,&request);
 }

MPI_Wait(&request,&status);
if(myid == source){
	printf("processor %d sent %d\n",myid,buffer);
 }
 if(myid == destination){
	printf("processor %d got %d\n",myid,buffer);
 }

  // Finalize the MPI environment. No more MPI calls can be made after this
  MPI_Finalize();
}
