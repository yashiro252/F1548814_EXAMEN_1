
#ifndef P4_REGS_H
#define P4_REGS_H

#include <stdint.h>

/* Direcciones base de los módulos */
#define BASE_REG_SENS  0x3FF48800UL
#define BASE_REG_GPIO  0x3FF44000UL

/* Registros del módulo SENS */
#define REG_SENS_READ_CTRL    (*(volatile uint32_t *)(BASE_REG_SENS + 0x0000))
#define REG_SENS_START_FORCE  (*(volatile uint32_t *)(BASE_REG_SENS + 0x002C))
#define REG_SENS_ATTEN1       (*(volatile uint32_t *)(BASE_REG_SENS + 0x0034))
#define REG_SENS_MEAS_START1  (*(volatile uint32_t *)(BASE_REG_SENS + 0x0054))

/* Registros del módulo GPIO */
#define REG_GPIO_OUT        (*(volatile uint32_t *)(BASE_REG_GPIO + 0x0004))
#define REG_GPIO_OUT_SET    (*(volatile uint32_t *)(BASE_REG_GPIO + 0x0008))
#define REG_GPIO_OUT_CLR    (*(volatile uint32_t *)(BASE_REG_GPIO + 0x000C))
#define REG_GPIO_ENABLE     (*(volatile uint32_t *)(BASE_REG_GPIO + 0x0020))
#define REG_GPIO_ENABLE_SET (*(volatile uint32_t *)(BASE_REG_GPIO + 0x0020))
#define REG_GPIO_ENABLE_CLR (*(volatile uint32_t *)(BASE_REG_GPIO + 0x0024))
#define REG_GPIO_IN         (*(volatile uint32_t *)(BASE_REG_GPIO + 0x003C))

/* Asignación de pines GPIO */
#define PIN_BOTON_INC    5
#define PIN_BOTON_DEC    4
#define PIN_POTENCIOMETRO       34
#define PIN_LED_AZUL     25
#define PIN_LED_VERDE     26
#define PIN_LED_ROJO     27

/* Macro para crear máscara de bits */
#define MASCARA_BIT(n) (1U << (n))

/* Funciones auxiliares para manejo de GPIO */
#define gpio_set(pin)   (REG_GPIO_OUT_SET = MASCARA_BIT(pin))
#define gpio_clear(pin) (REG_GPIO_OUT_CLR = MASCARA_BIT(pin))
#define gpio_dir_output(pin) (REG_GPIO_ENABLE_SET = MASCARA_BIT(pin))
#define gpio_dir_input(pin)  (REG_GPIO_ENABLE_SET = MASCARA_BIT(pin))
#define gpio_read(pin)  ((REG_GPIO_IN >> (pin)) & 0x1U)
