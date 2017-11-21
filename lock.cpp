#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


int main() {


    #pragma omp parallel private(nite_it) {
        omp_Set_lock(&C1);
        mi_it = i;
        i + = 1;
        omp_unset_lock(&C1);

        while (mi_it < N) {
            A[mi_it] = A[mi_it] + 1;

            omp_set_lock(&C1);

            mi_it = i;
            i += 1;
            omp_unset_lock(&C1);
        }
    }
    return 0;
}