#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    int i;
    vector<int> x(2000);
    srand(time(NULL));

    int aBuscar = rand()%1000;


    for (i = 0; i < x.size(); i++) {
        x[i] = rand()%1000;
    }

    bool found = false;
    #pragma omp parallel private(i) 
    {
    int total = omp_get_num_threads();
    i =  omp_get_thread_num();
    while (!found && i < (int)x.size()) {
        if (x[i] == aBuscar) {
            found = true;
            printf("Se encontro el valor %d en la posicion %d\n", x[i], i);
        }
        i += total;
    }
    }

    if (!found) {
        cout << "No se encontro el valor " << aBuscar << endl;
    }
    

    
}
