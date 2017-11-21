#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int main() { //Pablo Sáez Parra
    int sum = 0;
    int val;
    int x[4][4] = {
        {1, 1, 1, 1},
        {1, 1, 2, 1},
        {1, 1, 1, 1},
        {4, 1, 1, 1}};

    omp_set_num_threads(4);
    #pragma omp parallel reduction(+ : sum)
    {
        #pragma omp parallel for private(val)
        for (int i = 0; i < 16; i++) 
        {
            val = x[i / 4][i % 4];
            sum = sum + val;
        }

        #pragma omp barrier
        {
            printf("Suma de thread %d es: %d\n", omp_get_thread_num(), sum);
        }
        
    }

    printf("\n\nLa suma total da: %d\n", sum);


    return 0;
}