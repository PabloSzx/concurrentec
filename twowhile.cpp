#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


using namespace std;
int main() {

    omp_set_num_threads(2);
    // #pragma omp parallel do
    // {
    //     while (true)
    //     {
    //         printf("caca\n");
    //     }
    // }

    // // omp_set_num_threads(1);
    // #pragma omp parallel do
    // {
    //     while (true)
    //     {
    //         printf("pene\n");
    //     }
    // }

#pragma omp parallel num_threads(2)
    {
        switch (omp_get_thread_num()) {
            case 0:
                while (true) {
                    printf("caca\n");
                }
            case 1:
                while (true) {
                    printf("pene\n");
                }
        }
        // printf("my thread id: %d\n", omp_get_thread_num());
    }
    return 0;
}