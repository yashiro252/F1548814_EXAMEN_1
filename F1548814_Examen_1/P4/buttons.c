#include "regs.h"
#include <stdint.h>
#include <stdio.h>

/* Retardo bloqueante mediante bucles anidados */
static void retardo_ms(volatile uint32_t milisegundos) {
    volatile uint32_t contador1, contador2;
    contador1 = 0;
    while (contador1 < milisegundos) {
        contador2 = 0;
        while (contador2 < 4000) {
            __asm__ volatile("nop");
            contador2++;
        }
        contador1++;
    }
}

void buttons_init(void) {
    gpio_dir_input(PIN_BOTON_INC);
    gpio_dir_input(PIN_BOTON_DEC);
}

/* Verifica estado del botón con filtrado de rebotes, retorna 1 si está presionado */
static int leer_boton_con_debounce(int pin_gpio) {
    int lectura1 = gpio_read(pin_gpio);
    if (lectura1 != 0) return 0;
    retardo_ms(20);
    int lectura2 = gpio_read(pin_gpio);
    return (lectura2 == 0);
}

/* Modifica el tiempo de muestreo respetando valores pares y límites establecidos */
void buttons_check_and_update(uint32_t *tiempo_muestreo) {
    if (leer_boton_con_debounce(PIN_BOTON_INC)) {
        if (*tiempo_muestreo < 20) {
            *tiempo_muestreo = *tiempo_muestreo + 2;
        }
        while (gpio_read(PIN_BOTON_INC) == 0) {
            retardo_ms(10);
        }
    }
    if (leer_boton_con_debounce(PIN_BOTON_DEC)) {
        if (*tiempo_muestreo > 2) {
            *tiempo_muestreo = *tiempo_muestreo - 2;
        }
        while (gpio_read(PIN_BOTON_DEC) == 0) {
            retardo_ms(10);
        }
    }
}