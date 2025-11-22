#include <stdio.h>
#include <stdint.h>
#include "regs.h"

/* Declaraciones de funciones */
void buttons_init(void);
void buttons_check_and_update(uint32_t *tiempo_muestreo);
void led_init(void);
void led_off(void);
void led_set_red(void);
void led_set_green(void);
void led_set_blue(void);
void adc_init_regs(void);
uint32_t adc_read_one_shot_channel6(void);

/* Función de retardo bloqueante en milisegundos */
static void delay_ms(volatile uint32_t milisegundos) {
    volatile uint32_t contador_externo, contador_interno;
    contador_externo = 0;
    while (contador_externo < milisegundos) {
        contador_interno = 0;
        while (contador_interno < 4000) {
            __asm__ volatile("nop");
            contador_interno++;
        }
        contador_externo++;
    }
}

int main(void) {
    uint32_t tiempo_muestreo = 2;
    uint32_t valores_adc[10];

    buttons_init();
    led_init();
    adc_init_regs();

    printf("Sistema ADC - inicio\n");

    while (1) {
        printf("Tiempo de muestreo actual: %u s. Ajuste con botones...\n", tiempo_muestreo);
        uint32_t tiempo_ajuste = 2000;
        uint32_t tiempo_transcurrido = 0;
        while (tiempo_transcurrido < tiempo_ajuste) {
            buttons_check_and_update(&tiempo_muestreo);
            delay_ms(50);
            tiempo_transcurrido = tiempo_transcurrido + 50;
        }

        if (tiempo_muestreo >= 2 && tiempo_muestreo <= 10) {
            led_set_red();
        } else {
            if (tiempo_muestreo >= 12 && tiempo_muestreo <= 16) {
                led_set_blue();
            } else {
                led_set_green();
            }
        }

        uint32_t acumulador = 0;
        int contador = 0;
        while (contador < 10) {
            valores_adc[contador] = adc_read_one_shot_channel6();
            acumulador = acumulador + valores_adc[contador];
            delay_ms(10);
            contador++;
        }

        led_off();

        uint32_t promedio = acumulador / 10U;
        printf("Promedio ADC (10 muestras) = %u  |  Tiempo de muestreo = %u s\n", promedio, tiempo_muestreo);

        uint32_t segundos = 0;
        while (segundos < tiempo_muestreo) {
            int iteraciones = 0;
            while (iteraciones < 5) {
                buttons_check_and_update(&tiempo_muestreo);
                delay_ms(200);
                iteraciones++;
            }
            segundos++;
        }
    }

    return 0;
}