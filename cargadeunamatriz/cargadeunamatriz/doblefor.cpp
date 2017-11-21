#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
int main() { //Pablo Sáez Parra
    int i, j;
    const int N = 3;
    const int M = 3;
    int X;
    int A[N][M] = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    int B[N][M] = {
        {3, 1, 1},
        {1, 5, 1},
        {1, 1, 8}};

    int C[N][M];

    
    #pragma omp parallel for private(j , X)
        for (i = 0; i < N; i++) {
            for (j = 0; j < M; j++) {
                printf("Actual thread: %d\n", omp_get_thread_num());
                X = B[i][j] * B[i][j];
                A[i][j] = A[i][j] + X;
                C[i][j] = X * 2 + 1;
            }
        }


    cout << endl << endl;

    for (int k = 0; k < 3; k ++) {
        for (int l = 0; l < 3; l++)
        {
            cout << C[k][l];
            if (l != 2)
            {
                cout << "-";
            }
        }
        cout << endl;
    }

    return 0;
}