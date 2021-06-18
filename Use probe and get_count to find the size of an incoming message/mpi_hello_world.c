//Example 03
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv) {

  int myid,numprocs;
  int mytag,ierr,icount,j,*i;
  MPI_Status status;

  MPI_Init(&argc, &argv);

  // Get the number of processes
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

  // Get the rank of the process
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);

  printf("Hello from c process: %d Numprocs is %d\n",myid,numprocs);

  mytag = 123;

 if(myid == 0){
	j = 200;
	icount = 1;
	ierr = MPI_Send(&j,icount,MPI_INT,1,mytag,MPI_COMM_WORLD);
 }
 
if(myid == 1){
	ierr=MPI_Probe(0,mytag,MPI_COMM_WORLD,&status);
	ierr=MPI_Get_count(&status,MPI_INT,&icount);
	i=(int*)malloc(icount*sizeof(int));
	printf("getting %d\n",icount);
	ierr=MPI_Recv(i,icount,MPI_INT,0,mytag,MPI_COMM_WORLD,&status);
	printf("i= ");
	for(j=0;j<icount;j++)
		printf("%d ",i[j]);
	printf("\n");
 }
 

  // Finalize the MPI environment. No more MPI calls can be made after this
  MPI_Finalize();
}
