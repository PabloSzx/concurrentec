#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


#define N 24
#define TAM 8
int tid, nth, A[N], B[TAM],cont;

using namespace std;
int main(){ 

  srand(time(NULL));
  
  for(int i=0;i<N;i++){ //A[i]=0;
      //generar valores aleatorios para todos los valores del arreglo
      A[i]=rand() % 11;
      printf("A(%d) = %d \n",i,A[i]);
  }

  for(int i=0;i<TAM;i++){ //A[i]=0;
      //generar valores aleatorios para todos los valores del arreglo
      B[i]=0;
  }
  #pragma omp parallel private(tid, nth) shared(A)
  {
    nth = omp_get_num_threads();
    tid = omp_get_thread_num();

    // cout << "Thread " << tid << " de " << nth << " en marcha" << endl;
    printf("Thread %d de %d en marcha \n", tid, nth);
    // cout << "El thread" << tid << " ha terminado" << endl;

    for(int j=0;j<TAM-1;j++){
      printf("suma es %d\n", 3*tid + j);
      B[tid]=A[3*tid+j]+B[tid];
    }

    printf("El thread %d ha terminado \n", tid);
  }

  for (int i = 0; i < TAM; i++) {
    // cout << "B(" << i << ") = " << B[i] << endl;
    printf("B(%d) = %d \n", i, B[i]);
  }
  // for(int i=0; i<TAM;i++) printf("B(%d) = %d \n",i,B[i]);
}

//modicar para que ccada uno de los thread hagan en paralelo lo que le coresponde en ese vector
//el primer thread sume los valores contenidos en a[0] a[1] y a[2]
//el segundo en a[3] a[4] a[5] y asi sucesivamente
