#include <omp.h>
#include <stdio.h>
#include  <stdlib.h>
#include <iostream>
//compilar con -fopenmp

using namespace std;
int main(int argc, char *argv[]){
  //printf("Hello World! \n");
  int nth, tid;
  omp_set_num_threads(4);
  // printf("numproc: %d\n", omp_get_num_procs());
  int contador = 0;
  int x = 2;
#pragma omp parallel private(x)
  {
    // printf("numproc actual: %d\n", omp_get_active_level());

    // nth = omp_get_num_threads();
    printf("%d\n", x);

    x = rand() % 10;
    printf("%d\n", x);
    // tid = omp_get_thread_num();
    // printf("numproc: %d", omp_get_procs_num());
    contador += 1;

    printf("hola mundo!! %d\n", contador);
    // cout << "hola mundo!!";
    // printf("%d", contador);
    #pragma omp barrier
    {
      printf("%d\n", contador);
      // cout << contador << endl;
    }
    // printf("Hello from a thread! %i \n",tid); //se imprime tantas veces como nucleos tenga
    // printf("Number of threads! %i \n",nth);
  }
  printf("I am sequential now. \n");
  return 0;
}
