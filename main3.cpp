#include <omp.h>
#include <stdio.h>
#include  <stdlib.h>
#include <iostream>
//compilar con -fopenmp

using namespace std;
int main(int argc, char *argv[]){
  //printf("Hello World! \n");
  int nth, tid;
  omp_set_num_threads(32);
  printf("numproc: %d\n", omp_get_num_procs());

#pragma omp parallel //aqui comienza la ejecucion paralela
  {
    printf("numproc actual: %d\n", omp_get_active_level());

    nth = omp_get_num_threads();

    tid = omp_get_thread_num();
    // printf("numproc: %d", omp_get_procs_num());

    printf("Hello from a thread! %i \n",tid); //se imprime tantas veces como nucleos tenga
    printf("Number of threads! %i \n",nth);
  }
  printf("I am sequential now. \n");
  return 0;
}
