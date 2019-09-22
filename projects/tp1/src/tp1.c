/* Copyright 2016, Eric Pernia.
 * All rights reserved.
 *
 * This file is part sAPI library for microcontrollers.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*
 * Date: 2016-04-26
 */

/*==================[inclusions]=============================================*/



#define TEST TP1_6



///////////////////////////////////////////////////////////////////
#if (TEST == TP1_1)

 /*  Aca va el codigo del inciso 1 del TP1
  *
  *
  */

#endif

///////////////////////////////////////////////////////////////////
#if (TEST == TP1_2)

 /*  Aca va el codigo del inciso 2 del TP1
  *
  *
  */


#endif

///////////////////////////////////////////////////////////////////
#if (TEST == TP1_3)

 /*  Aca va el codigo del inciso 3 del TP1
  *
  *
  */

#endif


///////////////////////////////////////////////////////////////////
#if (TEST == TP1_4)

 /*  Aca va el codigo del inciso 4 del TP1
  *
  *
  */

#endif


///////////////////////////////////////////////////////////////////
#if (TEST == TP1_5)

 /*  Aca va el codigo del inciso 5 del TP1
  *
  *
  */

#endif




///////////////////////////////////////////////////////////////////
#if (TEST == TP1_6)

#include "sapi.h"
DEBUG_PRINT_ENABLE;

#define TICKRATE_1MS	(1)				/* 1000 ticks per second */
#define TICKRATE_10MS	(10)			/* 100 ticks per second */

/* 100 ms parecen no estar soportados por tickConfig (ver sapi_tick.h)*/
// #define TICKRATE_100MS	(100)			/* 10 ticks per second */

#define TICKRATE_50MS (50) 
#define TICKRATE_MS		(TICKRATE_50MS)	/* ¿? ticks per second */

#define BUTTON_STATUS_10MS	(10)
#define BUTTON_STATUS_100MS	(100)
#define BUTTON_STATUS_200MS (200)
#define BUTTON_STATUS_500MS	(500)
#define BUTTON_STATUS_MS	(BUTTON_STATUS_200MS / TICKRATE_MS)

volatile bool LED_Time_Flag = false;

volatile bool BUTTON_Status_Flag = false;
volatile bool BUTTON_Time_Flag = false;


/* FUNCION que se ejecuta cada vez que ocurre un Tick. */
void myTickHook( void *ptr ) {
	LED_Time_Flag = true;
	BUTTON_Time_Flag = true;

    if (!gpioRead( TEC1 ))
		BUTTON_Status_Flag = true;
	else
		BUTTON_Status_Flag = false;

}


/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void) {

	/* ------------- INICIALIZACIONES ------------- */
	uint32_t BUTTON_Status_Counter = 0;
	uint32_t idx = LED3;

	/* Inicializar la placa */
	boardConfig();

	/* UART for debug messages. */
	debugPrintConfigUart( UART_USB, 115200 );
	debugPrintString( "DEBUG c/sAPI\r\n" );

	/* Inicializar el conteo de Ticks con resolucion de 1ms (se ejecuta
       periodicamente una interrupcion cada TICKRATE_MS que incrementa un contador de
       Ticks obteniendose una base de tiempos). */
	tickConfig( TICKRATE_MS );

	/* Se agrega ademas un "tick hook" nombrado myTickHook. El tick hook es
       simplemente una funcion que se ejecutara peri�odicamente con cada
       interrupcion de Tick, este nombre se refiere a una funcion "enganchada"
       a una interrupcion.
       El segundo parametro es el parametro que recibe la funcion myTickHook
       al ejecutarse. En este ejemplo se utiliza para pasarle el led a titilar.
	*/
	tickCallbackSet( myTickHook, (void*)NULL );

	gpioToggle(LED3);

	/* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {
		__WFI();

		if (BUTTON_Time_Flag == true) {
			BUTTON_Time_Flag = false;

			if (BUTTON_Status_Flag == true) {
				BUTTON_Status_Flag = false;

				if (BUTTON_Status_Counter == 0) {
					BUTTON_Status_Counter = BUTTON_STATUS_MS;

					gpioToggle(idx);

					/* Se agrega que el cambio de indice al siguiente 
					LED sea cuando este este apagado. */
					if(!gpioRead(idx))
						((idx > LEDR) ? idx-- : (idx = LED3));

					debugPrintString( "LED Toggle\n" );
				}
				else
					BUTTON_Status_Counter--;
			}

		}
	}

	/* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
       por ningun S.O. */
	return 0 ;
}

#endif
