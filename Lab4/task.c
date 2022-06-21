#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    int n = 3;
    int m = 6;
    int colPerThread = atoi(argv[1]);

  
    double matrix1[3][6] = {
             {1.0, 2.0, 3.0, 4.0, 5.0, 6.0},
             {11.0, 12.0, 13.0, 14.0, 15.0, 16.0},
             {21.0, 22.0, 23.0, 24.0, 25.0, 26.0},
    };
    double matrix2[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    double matrixFinal[3]={ 0, 0, 0};
  
    int world_size;
    int world_rank;
  
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  
    int numOfCells = colPerThread * n;
    double dataToExecute[numOfCells];
  
    double matrixThreadSorted[m][n];
  
    for ( int i = 0; i < n; i++) {  
            for (int j = 0; j < m; j++) {
                    matrixThreadSorted[j][i] = matrix1[i][j];
            }
    }
    MPI_Bcast(matrix2, m, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(matrixThreadSorted, numOfCells, MPI_DOUBLE, dataToExecute, numOfCells, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  
    double result[n];
  
    int basicColOffset = world_rank*colPerThread;
    for (int j = 0; j < colPerThread; j++) {
            int currentCol = basicColOffset + j;
            for (int i = 0; i < n; i++) {
                    int index = j * n + i;
                    result[i] += dataToExecute[index] * matrix2[currentCol];
            }
    }
  
    MPI_Reduce( result, matrixFinal, n, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  
    if (world_rank == 0)
  {
            printf("---------- \n");
            for (int i = 0; i < n; i++)
            {
                      printf("%f \n", matrixFinal[i]);
            }
  }
    MPI_Finalize();
    return 0;
} 
