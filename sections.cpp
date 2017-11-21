#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int main()
{
#pragma omp parallel sections
    {
#pragma omp section
        {
            // while (true) {
            //     printf("hola\n");
            // }
            printf("id = %d, \n", omp_get_thread_num());
        }

#pragma omp section
        {
            // while (true)
            // {
            //     printf("chao\n");
            // }
            printf("id = %d, \n", omp_get_thread_num());
        }

#pragma omp section
        {
            // while (true)
            // {
            //     printf("como estas\n");
            // }
            printf("id = %d, \n", omp_get_thread_num());
        }

#pragma omp section
        {
            printf("id = %d, \n", omp_get_thread_num());
        }

#pragma omp section
        {
            printf("id = %d, \n", omp_get_thread_num());
        }

#pragma omp section
        {
            printf("id = %d, \n", omp_get_thread_num());
        }

#pragma omp section
        {
            printf("id = %d, \n", omp_get_thread_num());
        }

#pragma omp section
        {
            printf("id = %d, \n", omp_get_thread_num());
        }

#pragma omp section
        {
            printf("id = %d, \n", omp_get_thread_num());
        }
#pragma omp section
        {
            printf("id = %d, \n", omp_get_thread_num());
        }
#pragma omp section
        {
            printf("id = %d, \n", omp_get_thread_num());
        }
#pragma omp section
        {
            printf("id = %d, \n", omp_get_thread_num());
        }
#pragma omp section
        {
            printf("id = %d, \n", omp_get_thread_num());
        }
    }

    return 0;
}