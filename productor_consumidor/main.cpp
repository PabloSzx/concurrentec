#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <unistd.h>

using namespace std;

vector<omp_lock_t> cerrojos(8);

vector<int> buffer(8);

void consumir() {

    vector<omp_lock_t>::iterator it = cerrojos.begin();

    while (it != cerrojos.end())
    {
        // omp_init_lock(&(*it));

        ++it;
    }

    // vector<int>::iterator it = buffer.begin();

    // int pos = 0;
    // while (it != buffer.end()) {
    //     if (*it != 0) {
    //         printf("Producto %d consumiendose en la posicion %d\n", *it, pos);
    //         usleep(rand()%5 * 1000000);
    //         printf("Producto %d consumido en la posicion %d\n", *it, pos);
    //         (*it) = 0;
    //         break;
    //     }
    //     ++pos;
    //     ++it;
    // }
}

void producir() {
    vector<int>::iterator it = buffer.begin();
    int pos = 0;

    while (it != buffer.end())
    {
        if (*it == 0)
        {
            (*it) = rand() % 20 + 1;
            printf("Nuevo producto %d disponible en la posicion %d\n", *it, pos);
            break;
        }

        ++pos;
        ++it;
    }
}

int main() {
    vector<omp_lock_t>::iterator it = cerrojos.begin();

    while (it != cerrojos.end()) {
        omp_init_lock(&(*it));

        ++it;
    }

    // omp_lock_t cerrojo;
    // omp_init_lock(&cerrojo);


    // int producto = 0;
    fill(buffer.begin(), buffer.end(), 0);
    // buffer.fill(0);
    srand(time(NULL));

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            while (true)
            {

            // #pragma omp critical
            //     {
                    // omp_set_lock(&cerrojo);
                    consumir();
                    // omp_unset_lock(&cerrojo);
                // }
            }
        }

        #pragma omp section
        {
            while (true) {
            // #pragma omp critical
            //     {
                    // omp_set_lock(&cerrojo);
                    producir();
                    // omp_unset_lock(&cerrojo);
                // }
            }
        }
    }
}