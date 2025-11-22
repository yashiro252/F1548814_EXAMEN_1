/* p2_divisores.c
   Genera números aleatorios, obtiene la suma de divisores (sin incluir el número mismo)
   y determina si cada valor es Deficiente, Perfecto o Abundante.
   Compilación: gcc -o p2_divisores p2_divisores.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CANTIDAD_NUMEROS 15

/* Obtiene la suma de todos los divisores propios del valor dado */
int calcular_suma_divisores(int valor) {
    if (valor <= 1) return 0;
    int total = 1;
    int divisor = 2;
    int limite = valor;
    while (divisor * divisor <= limite) {
        if (valor % divisor == 0) {
            total = total + divisor;
            int complemento = valor / divisor;
            if (complemento != divisor && complemento != valor) {
                total = total + complemento;
            }
        }
        divisor++;
    }
    return total;
}

int main(void) {
    int numeros[CANTIDAD_NUMEROS];
    unsigned int semilla = (unsigned int) time(NULL);
    srand(semilla);

    int indice = 0;
    while (indice < CANTIDAD_NUMEROS) {
        numeros[indice] = (rand() % 100) + 1;
        indice++;
    }

    printf("El arreglo es: ");
    int pos = 0;
    while (pos < CANTIDAD_NUMEROS) {
        printf("%d", numeros[pos]);
        if (pos < CANTIDAD_NUMEROS - 1) printf(", ");
        pos++;
    }
    printf("\n\n");

    int idx = 0;
    while (idx < CANTIDAD_NUMEROS) {
        int numero_actual = numeros[idx];
        int resultado_suma = calcular_suma_divisores(numero_actual);

        if (resultado_suma < numero_actual) {
            printf("%d - Deficiente (suma divisores = %d)\n", numero_actual, resultado_suma);
        } else {
            if (resultado_suma == numero_actual) {
                printf("%d - Perfecto  (suma divisores = %d)\n", numero_actual, resultado_suma);
            } else {
                printf("%d - Abundante (suma divisores = %d)\n", numero_actual, resultado_suma);
            }
        }
        idx++;
    }

    return 0;
}
