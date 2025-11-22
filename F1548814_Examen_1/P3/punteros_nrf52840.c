/* Base de direcciones para el puerto 0 */
#define BASE_PUERTO_0 0x50000000UL

/* Definiciones de registros del puerto 0 */
#define PUERTO0_SALIDA      (*(volatile uint32_t *)(BASE_PUERTO_0 + 0x504))
#define PUERTO0_SALIDA_SET  (*(volatile uint32_t *)(BASE_PUERTO_0 + 0x508))
#define PUERTO0_SALIDA_CLR  (*(volatile uint32_t *)(BASE_PUERTO_0 + 0x50C))
#define PUERTO0_ENTRADA     (*(volatile uint32_t *)(BASE_PUERTO_0 + 0x510))
#define PUERTO0_DIRECCION   (*(volatile uint32_t *)(BASE_PUERTO_0 + 0x514))
#define PUERTO0_DIR_SET     (*(volatile uint32_t *)(BASE_PUERTO_0 + 0x518))
#define PUERTO0_DIR_CLR     (*(volatile uint32_t *)(BASE_PUERTO_0 + 0x51C))
