#include<iostream>
#include<vector>
#include<omp.h>
using namespace std;

int main(int argc, char *argv[]){
    int proc_amount_min = atoi (argv[1]);
    int proc_amount_max = atoi (argv[2]);
    int N = 20000, R = 10000;
    
    for(int p = proc_amount_min; p <= proc_amount_max; p++)
    {
      vector<vector<bool> > matrix(N, vector<bool>(N, 0));
      omp_set_num_threads(p);
      double start_time = omp_get_wtime();
      
      for(int i = 0;i < N; i++)
      {
        for(int j = max(0, i - R); j < min(N, i + R); j++)
        {
          matrix[i][j] = true;
        }
      }
      double end_time = omp_get_wtime();
      cout << "Execution time on " << p << " processors = " << end_time - start_time << endl;
    }
}
