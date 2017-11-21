#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


int main() {

    const int n = 1000;

    float x[n], y[n], a = 2;
    int i;

    #pragma omp parallel for
    for (i = 0; i < n; i++) {
        y[i] = a*x[i] + y[i];
    }
    return 0;
}