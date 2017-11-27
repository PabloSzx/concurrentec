#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>
#include <unistd.h>

using namespace std;

#define second 1000000

void consumir(const char *n);
void producir(const char *n);

static omp_lock_t hay_productos;
static omp_lock_t hay_espacios_vacios;

static vector<int> buffer(8);
static queue<int> posiciones_productos_disponibles;
static queue<int> posiciones_espacios_vacios;

int main() {
    srand(time(NULL));

    omp_init_lock(&hay_productos);
    omp_set_lock(&hay_productos); //SE PARTE SIN PRODUCTOS DISPONIBLES

    omp_init_lock(&hay_espacios_vacios);
    fill(buffer.begin(), buffer.end(), 0); //SE PARTE CON TODOS LOS ESPACIOS VACIOS
    for (int i = 0; i < buffer.size(); i++) {
        posiciones_espacios_vacios.push(i);
    }

    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task //CONSUMIDOR 1
            {
                while (true) consumir("Juan");
            }

            #pragma omp task //CONSUMIDOR 2
            {
                while (true) consumir("Pedro");
            }
            #pragma omp task //PRODUCTOR 1
            {
                while (true) producir("Pablo");
            }
            #pragma omp task //PRODUCTOR 2
            {
                while (true) producir("Ignacio");
            }
        }
    }

    return 0;
}

void consumir(const char *n)
{
    omp_set_lock(&hay_productos); //SI HAY PRODUCTOS DISPONIBLES, VOY A CONSUMIR, SI NO, ESPERO
    int pos = posiciones_productos_disponibles.front();
    posiciones_productos_disponibles.pop();
    if (!posiciones_productos_disponibles.empty())
    { //SI QUEDAN PRODUCTOS AUN, SE PUEDE SEGUIR COMIENDO
        omp_unset_lock(&hay_productos);
    }

    printf("                                                                            Producto <%d> consumiendose por el consumidor <%s> en la posicion <%d>.\n", buffer[pos], n, pos);
    usleep((rand() % 2 + 1) * second); //CONSUMIR SE DEMORA ENTRE 1 Y 2 SEGUNDOS
    printf("                                                                            Producto <%d> ya consumido en la posicion <%d> por el consumidor <%s>.\n", buffer[pos], pos, n);
    buffer[pos] = 0;
    posiciones_espacios_vacios.push(pos); //"pos" AHORA ES UNA POSICION VACIA
    omp_unset_lock(&hay_espacios_vacios); //SE ACABA DE CONSUMIR, POR LO TANTO, HAY AL MENOS UN ESPACIO VACIO
}

void producir(const char *n)
{
    omp_set_lock(&hay_espacios_vacios); //SI HAY ESPACIOS VACIOS, VOY A PRODUCIR, SI NO, ESPERO
    int pos = posiciones_espacios_vacios.front();
    posiciones_espacios_vacios.pop();
    if (!posiciones_espacios_vacios.empty())
    { //SI QUEDAN ESPACIOS VACIOS, SE PUEDE SEGUIR LLENANDO
        omp_unset_lock(&hay_espacios_vacios);
    }

    printf("Nuevo espacio <%d> disponible, el productor <%s> esta trabajando.\n", pos, n);
    usleep((rand() % 5 + 1) * second); //PRODUCIR SE DEMORA ENTRE 1 Y 5 SEGUNDOS
    buffer[pos] = rand() % 20 + 1;
    printf("Nuevo producto <%d> disponible en la posicion <%d> gracias al productor <%s>.\n", buffer[pos], pos, n);
    posiciones_productos_disponibles.push(pos); //"pos" AHORA ES UNA POSICION DISPONIBLE
    omp_unset_lock(&hay_productos);             //SE ACABA DE PRODUCIR, POR LO TANTO, HAY AL MENOS UN PRODUCTO DISPONIBLE
}
