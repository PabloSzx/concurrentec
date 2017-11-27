#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

struct timeval t0, t1;

int main() {
    int n = 15;
    int i;
    long long fact = 1;
    double tej;
    gettimeofday(&t0, 0);

    printf("\nFACTORIAL CON REDUCTION A PARES\n{");

    #pragma omp parallel for reduction(*: fact)
    for (i = (n % 2) == 0 ? 1 : 2; i <= n; i+=2) {
        fact = (i * (i + 1));
    }

    gettimeofday(&t1, 0);

    tej = (t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec) / 1e6;
    printf("\nT. de ejec. = %1.3f ms\n\n", tej * 1000);


    printf("total es %lli\n", fact);

    printf("}\nFACTORIAL CON REDUCTION INDIVIDUAL\n{");

    fact = 1;
    gettimeofday(&t0, 0);

    #pragma omp parallel for reduction(*: fact)
    for (i = 2; i <= n; i+=1) {
        fact*=i;
    }

    gettimeofday(&t1, 0);

    tej = (t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec) / 1e6;
    printf("\nT. de ejec. = %1.3f ms\n\n", tej * 1000);


    printf("total es %lli\n", fact);

    printf("}\nFACTORIAL SIN REDUCTION INDIVIDUAL\n{");

    fact = 1;
    gettimeofday(&t0, 0);

    #pragma omp parallel for
    for (i = 2; i <= n; i+=1) {
        #pragma omp atomic
            fact*=i;
    }

    gettimeofday(&t1, 0);

    tej = (t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec) / 1e6;
    printf("\nT. de ejec. = %1.3f ms\n\n", tej * 1000);


    printf("total es %lli\n", fact);


    printf("}\nFACTORIAL NO PARALELO\n{");

    fact = 1;
    gettimeofday(&t0, 0);

    for (i = 2; i <= n; i+=1) {
            fact*=i;
    }

    gettimeofday(&t1, 0);

    tej = (t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec) / 1e6;
    printf("\nT. de ejec. = %1.3f ms\n\n", tej * 1000);


    printf("total es %lli\n}", fact);


}