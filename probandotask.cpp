#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>
#include <unistd.h>

int main() {
#pragma omp parallel
	{
	#pragma omp single
	{
	#pragma omp task
    {
        while (true) 
            printf("hello world from thread %d\n", omp_get_thread_num());
        
    }
	 
	#pragma omp task
        while (true)
            printf("hello again from thread %d!\n", omp_get_thread_num());

    }

#pragma omp single
    {
#pragma omp task
        {
            while (true)
                printf("bye world from thread %d\n", omp_get_thread_num());
        }

#pragma omp task
        while (true)
            printf("bye again from thread %d!\n", omp_get_thread_num());
    }
    }


    return 0;
}

