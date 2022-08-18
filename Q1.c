#include  <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int encontra_maior(int *partial_max, int length);
int zeramaior(int *arr, int maior);

int main(int argc, char* argv[])    
{    

	int my_rank = 0;
    int comm_size = 0;
   
    int arr[12] ;      
	
	int aux = 1;
	
    int max;
	int partial_max;
    int receive_buffer[3];
	
	MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
	
	if (comm_size != 4)
    {
        printf("Please set process count = %d and run again.", 4);
        MPI_Finalize();
        return 0;
    }	
	
	if (my_rank == 0)
    {
        for(int i=0;i<12;i++){
	printf("Preencha a posicao %d: \n", i+1);
    scanf("%d",&arr[i]);
    } 
    }
	
	for (int i = 0; i<2;i++){
	MPI_Scatter(arr, 3, MPI_INT, receive_buffer, 3, MPI_INT, 0, MPI_COMM_WORLD);

    partial_max = encontra_maior(receive_buffer, 3);
	
    MPI_Reduce(&partial_max, &max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
	
    if (my_rank == 0)
    {	
		if(i == 1){
			printf("Segundo maior: %d\n", max);
		} else {
		printf("Maior: %d\n", max);
		}
    }
	zeramaior(arr, max);
	}
	
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
	
    return 0;    
}    

int encontra_maior(int* partial_max, int length){  
    int max = partial_max[0]; 
    for (int i = 0; i < length; i++) {         
       if(partial_max[i] > max)    
           max = partial_max[i];    
    }      
	return max;
}

int zeramaior(int *arr, int maior){
	for(int i = 0; i<12; i++){
		if(maior== arr[i]){
			arr[i]=0;
	}
	}
}
	



