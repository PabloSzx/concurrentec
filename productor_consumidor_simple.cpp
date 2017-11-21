#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

void consumir(int *n)
{
    if (*n != 0)
    {
        printf("Producto %d consumiendose...\n", *n);
        usleep(1000000);
        printf("Producto %d consumido\n", *n);
        *n = 0;
    }
}

void producir(int *n)
{
    if (*n == 0)
    {
        *n = rand() % 20 + 1;
        printf("Nuevo producto %d disponible\n", *n);
    }
}

int main() //Pablo Sáez Parra
{
    omp_lock_t cerrojo;
    omp_init_lock(&cerrojo);

    int producto = 0;
    srand(time(NULL));

#pragma omp parallel sections
    {
#pragma omp section
        {
            while (true)
            {
                omp_set_lock(&cerrojo);
                consumir(&producto);
                omp_unset_lock(&cerrojo);
            }
        }

#pragma omp section
        {
            while (true)
            {
                omp_set_lock(&cerrojo);
                producir(&producto);
                omp_unset_lock(&cerrojo);
            }
        }
    }
}