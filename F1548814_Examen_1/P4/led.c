#include "regs.h"

void led_init(void) {
    gpio_dir_output(PIN_LED_ROJO);
    gpio_dir_output(PIN_LED_VERDE);
    gpio_dir_output(PIN_LED_AZUL);
    gpio_clear(PIN_LED_ROJO);
    gpio_clear(PIN_LED_VERDE);
    gpio_clear(PIN_LED_AZUL);
}

void led_off(void) {
    gpio_clear(PIN_LED_ROJO);
    gpio_clear(PIN_LED_VERDE);
    gpio_clear(PIN_LED_AZUL);
}

void led_set_red(void) {
    gpio_set(PIN_LED_ROJO);
    gpio_clear(PIN_LED_VERDE);
    gpio_clear(PIN_LED_AZUL);
}
void led_set_green(void) {
    gpio_set(PIN_LED_VERDE);
    gpio_clear(PIN_LED_ROJO);
    gpio_clear(PIN_LED_AZUL);
}
void led_set_blue(void) {
    gpio_set(PIN_LED_AZUL);
    gpio_clear(PIN_LED_ROJO);
    gpio_clear(PIN_LED_VERDE);
}