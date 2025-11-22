# F1548814_Examen_1

Este repositorio contiene las soluciones para el examen 1, organizadas en tres preguntas principales.

## Estructura del Proyecto

```
F1548814_Examen_1/
├── P2/                    # Pregunta 2: Programa de divisores
│   ├── p2_divisores.c     # Código fuente principal
│   ├── p2_divisores.exe   # Ejecutable compilado
│   ├── p2_divisores_x86.s # Ensamblador x86-64
│   └── p2_divisores_arm.s # Ensamblador ARM Cortex-M4
├── P3/                    # Pregunta 3: Microcontroladores
│   ├── punteros_nrf52840.c      # Definiciones de punteros para nRF52840
│   └── tabla_microcontroladores # Tabla comparativa de microcontroladores
├── P4/                    # Pregunta 4: Sistema ADC con ESP32
│   ├── main.c             # Programa principal
│   ├── regs.h             # Definiciones de registros y macros
│   ├── adc.c              # Funciones de configuración y lectura ADC
│   ├── buttons.c          # Manejo de botones con debounce
│   └── led.c              # Control de LED RGB
├── datos.txt              # Datos adicionales del examen
└── README.md              # Este archivo
```

---

## PREGUNTA 2: Programa de Divisores

### Descripción
Programa en C que genera 15 números aleatorios entre 1 y 100, calcula la suma de divisores propios de cada número y los clasifica como:
- **Deficiente**: suma de divisores < número
- **Perfecto**: suma de divisores = número
- **Abundante**: suma de divisores > número

### Archivos
- `p2_divisores.c`: Código fuente principal con función `calcular_suma_divisores()`
- `p2_divisores_x86.s`: Código ensamblador generado para arquitectura x86-64
- `p2_divisores_arm.s`: Código ensamblador generado para ARM Cortex-M4

### Compilación y Ejecución

#### Configurar PATH (Windows con MinGW)
```bash
export PATH="/c/ProgramData/mingw64/mingw64/bin:$PATH"
```

#### Compilar el programa
```bash
cd P2
gcc -O2 -Wall -o p2_divisores p2_divisores.c
```

#### Ejecutar
```bash
./p2_divisores.exe
```

#### Generar código ensamblador

**Para x86-64 (AT&T syntax):**
```bash
gcc -O2 -Wall -S p2_divisores.c -o p2_divisores_x86.s
```

**Para ARM Cortex-M4:**
```bash
arm-none-eabi-gcc -O2 -Wall -mcpu=cortex-m4 -mthumb -S p2_divisores.c -o p2_divisores_arm.s
```

---

## PREGUNTA 3: Microcontroladores y Punteros

### Descripción
Análisis comparativo de microcontroladores y definición de punteros para acceso a registros.

### Archivos

#### `tabla_microcontroladores`
Tabla comparativa que incluye las siguientes características para cada microcontrolador:
- **SAMD21**: ARM Cortex-M0+, 32 KB RAM, 256 KB Flash
- **ESP32**: Tensilica Xtensa LX6 Dual-Core, 520 KB SRAM, hasta 16 MB Flash
- **nRF52840**: ARM Cortex-M4F, 256 KB RAM, 1 MB Flash

Características comparadas:
- Tipo de Core y frecuencia
- Memoria RAM, Flash y ROM
- Puertos GPIO
- Canales ADC
- UARTs disponibles

#### `punteros_nrf52840.c`
Definiciones de punteros para acceso directo a registros del puerto 0 del microcontrolador nRF52840:
- Dirección base del puerto 0
- Registros de salida (OUT, OUTSET, OUTCLR)
- Registros de entrada (IN)
- Registros de dirección (DIR, DIRSET, DIRCLR)

---

## PREGUNTA 4: Sistema ADC con ESP32

### Descripción
Sistema de adquisición de datos mediante ADC en ESP32 que:
- Lee valores del potenciómetro conectado al canal 6 (GPIO34)
- Permite ajustar el tiempo de muestreo mediante botones (incremento/decremento)
- Muestra el estado mediante LED RGB según el rango de tiempo configurado
- Calcula y muestra el promedio de 10 muestras ADC

### Funcionalidad
1. **Inicialización**: Configura botones, LED RGB y ADC
2. **Ajuste de tiempo**: Permite modificar el tiempo de muestreo (2-20 segundos, valores pares)
3. **Indicación visual**: LED cambia de color según el rango de tiempo:
   - Rojo: 2-10 segundos
   - Azul: 12-16 segundos
   - Verde: 18-20 segundos
4. **Adquisición**: Toma 10 muestras del ADC mientras el LED está encendido
5. **Resultado**: Calcula y muestra el promedio de las muestras

### Archivos

#### `main.c`
Programa principal que orquesta el sistema:
- Bucle principal con ciclo de muestreo
- Gestión del tiempo de muestreo
- Control de LED según rango
- Cálculo de promedios

#### `regs.h`
Archivo de cabecera con:
- Definiciones de direcciones base (SENS, GPIO)
- Macros para acceso a registros del ADC
- Macros para acceso a registros GPIO
- Definiciones de pines (botones, LED, potenciómetro)
- Funciones auxiliares para manejo de GPIO

#### `adc.c`
Funciones para el módulo ADC:
- `adc_init_regs()`: Configuración inicial del ADC
- `adc_read_one_shot_channel6()`: Lectura única del canal 6

#### `buttons.c`
Manejo de botones con debounce:
- `buttons_init()`: Inicialización de pines como entrada
- `buttons_check_and_update()`: Verificación y actualización del tiempo de muestreo
- Función interna de debounce para filtrado de rebotes

#### `led.c`
Control del LED RGB:
- `led_init()`: Configuración inicial de pines como salida
- `led_off()`: Apaga todos los LEDs
- `led_set_red()`, `led_set_green()`, `led_set_blue()`: Activa cada color

### Compilación

**Nota importante**: Este código utiliza acceso directo a registros del ESP32. Se recomienda compilar dentro del framework ESP-IDF o con un toolchain que soporte ESP32.

#### Con ESP-IDF:
```bash
cd P4
idf.py build
idf.py flash monitor
```

#### Requisitos:
- Toolchain de ESP32 (ESP-IDF)
- Hardware ESP32 o emulador compatible
- Conexiones:
  - Botón incremento: GPIO 5
  - Botón decremento: GPIO 4
  - Potenciómetro: GPIO 34 (ADC1_CH6)
  - LED Rojo: GPIO 27
  - LED Verde: GPIO 26
  - LED Azul: GPIO 25

### Características Técnicas
- **ADC**: 12 bits (valores 0-4095)
- **Debounce**: 20 ms para botones
- **Muestras**: 10 lecturas por ciclo
- **Rango de tiempo**: 2-20 segundos (valores pares)
- **Retardos**: Implementados mediante bucles bloqueantes

---

## Notas Adicionales

- Todos los archivos de código han sido refactorizados para mantener la misma funcionalidad con diferentes nombres de variables y estructuras.
- Los comentarios están en español y describen la funcionalidad de cada sección.
- Los archivos de ensamblador (`.s`) son generados automáticamente y no deben editarse manualmente.