
8. 
Migrar el proyecto sapi_examples/edu-ciaa-nxp/bare_metal/gpio/gpio_02_blinky (parpadeo del LEDs c/sAPI) a: projects/TP1 
a. Documentar los pasos a seguir para concretar una migración exitosa 
b. Identificar funciones de librería sAPI útiles para el parpadeo de un led 
i. Documentar mediante tablas c/texto e imágenes la secuencia de funciones invocadas durante la ejecución del ejemplo de aplicación, en qué archivo se encuentran, su descripción detallada, qué efecto tiene la aplicación sobre el hardware (identificar circuitos, puertos, pines, niveles, etc.) así como la interacción entre las mismas (tanto en ResetISR() como en main()) 
ii. Idem c pero con datos (definiciones, constantes, variables, estructuras, etc.) (tanto en ResetISR() como en main())

Respuesta
Para realizar el análisis de las funciones invocadas se hara desde un sentido top–down, es decir, desde mas alto nivel y luego analizando como son por dentro bajando cada vez mas de nivel.
Main()
La secuencia de funciones invocadas para el proyecto gpio_blinky_02 es la que se muestra en la fig. 1. La función main se encuentra en 
/firmware_v2/projects/Tp1/gpio_02_blinky/src/blinky.c
 La misma consiste en una función que inicializa la placa, boardConfig() y luego posee en un loop infinito en el que se llama básicamente a dos funciones gpioWrite() y delay(). Dentro del loop las funciones gpioWrite() siempre utilizan el macro LEDB y van variando el estado del led en prendido y apagado. La función delay tiene harcodeado 500 que simboliza 500ms (medio segundo) en donde el sistema esperara dicho tiempo para continuar la ejecución. El código integral al ejecutarlo prendera y apagara un led cada medio segundo.
 
![alt text] (images/1.8_1.PNG)

Fig. 1 -  Estructura del Main()

1.	boardConfig()
BoardConfig() es una función importante en cada proyecto de embebidos. Se encuentra declarada  en
/firmware_v2/modules/lpc4337_m4/sapi/src/sapi_board.c
Como se observa en la fig. 2 posee funciones en donde configura el Clock interno del core SystemCoreClockUpdate() y cyclesCounterConfig() , tambien inicializa perifericos con Board_init() y luego inicializa las entradas y salidas de propósito general (GPIO) utilizando la función gpioConfig(), la cual necesita de macros para definir como es configurado el pin.
 
![alt text] (images/1.8_2.PNG)
Fig. 2 

1.1.	SystemCoreClockUpdate

Esta función define el clock a bajo nivel y se llama antes de iniciar el sistema o en algún caso particular que se cambie el clock durante la ejecución. Dicha función se encuentra en
 /firmware_v2/modules/lpc4337_m4/chip/src/chip_18xx_43xx.c

Posee como argumento de entrada un tipo enumerativo definido junto a otros en :
/firmware_v2/modules/lpc4337_m4/chip/inc/chip_clocks.h
Dicho tipo enumerativo junto con la función Chip_Clock_GetRate() obtienen la frecuencia de clock del micro.  A pesar que la salida de la función sea void, SystemCoreClock es una variable GLOBAL por lo que aquellas funciones que estén en su alcance podrán usarla.

![alt text] (images/1.8_3.PNG)

1.2.	Board_Init()

Board_Init() es una función que agrupa la inicialización de distintos periféricos (Gpio como Leds y Buttons, USB, etc). Se encuentra en
/firmware_v2/modules/lpc4337_m4/board/src/board.c
 A priori cada pin del micro puede tener varios tipos de funcionamientos y es en esta función donde se dice cual de todas es la función del pin.
 
![alt text] (images/1.8_4.PNG)

1.3.	gpioConfig()
gpioConfig
![alt text] (images/1.8_5.PNG)
 
2.	gpioWrite() 

![alt text] (images/1.8_6.PNG)
3.	delay()

![alt text] (images/1.8_7.PNG)

 
