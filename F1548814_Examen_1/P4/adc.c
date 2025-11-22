#include "regs.h"
#include <stdint.h>

/* Configuración inicial del ADC mediante acceso directo a registros */
void adc_init_regs(void) {
    REG_SENS_ATTEN1 |= (MASCARA_BIT(12) | MASCARA_BIT(13));

    REG_SENS_READ_CTRL |= MASCARA_BIT(27);
    REG_SENS_READ_CTRL |= (MASCARA_BIT(16) | MASCARA_BIT(17));

    REG_SENS_START_FORCE |= (MASCARA_BIT(0) | MASCARA_BIT(1));
}

/* Ejecuta una lectura única del canal 6 y retorna el resultado de 12 bits */
uint32_t adc_read_one_shot_channel6(void) {
    uint32_t registro_medida = REG_SENS_MEAS_START1;

    registro_medida |= MASCARA_BIT(31) | MASCARA_BIT(18) | MASCARA_BIT(17);
    registro_medida |= MASCARA_BIT(25);
    REG_SENS_MEAS_START1 = registro_medida;

    uint32_t estado_actual;
    do {
        estado_actual = (REG_SENS_MEAS_START1 >> 16) & 0x1U;
    } while (estado_actual == 0);

    uint32_t resultado = REG_SENS_MEAS_START1 & 0xFFFFU;
    return resultado;
}