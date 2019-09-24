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





#include "sapi.h"       // <= sAPI header


///////////////////////////////////////////////////////////////////
//#define DONT_RESET_ON_RESTART


#define TP1_2

#ifdef TP1_5
	DEBUG_PRINT_ENABLE
#elif TP1_6
	DEBUG_PRINT_ENABLE
#endif


#define TICKRATE_1MS	(1)				/* 1000 ticks per second */
#define TICKRATE_10MS	(10)			/* 100 ticks per second */
#define TICKRATE_50MS   (50)
#define TICKRATE_100MS	(100)			/* 10 ticks per second */
/* 100 ms parecen no estar soportados por tickConfig (ver sapi_tick.h)*/
#define TICKRATE_MS		(TICKRATE_50MS)	/* ¿? ticks per second */


#define LED_TOGGLE_100MS	(100)
#define LED_TOGGLE_500MS	(500)
#define LED_TOGGLE_1000MS   (1000)

#define LED_TOGGLE_MS   LED_TOGGLE_500MS

// PRECONDICION: LED_TOGGLE_CICLE DEBE SER ENTERO
#define LED_TOGGLE_CICLE LED_TOGGLE_MS/TICKRATE_MS // 100ms/50ms=2 ciclos


#define BUTTON_STATUS_10MS	(10)
#define BUTTON_STATUS_100MS	(100)
#define BUTTON_STATUS_200MS (200)
#define BUTTON_STATUS_500MS	(500)
#define BUTTON_STATUS_MS	(BUTTON_STATUS_200MS / TICKRATE_MS)

volatile bool LED_Time_Flag = false;
volatile bool BUTTON_Status_Flag = false;
volatile bool BUTTON_Time_Flag = false;


/*Prototipo de myTickHook, declarada al final*/
void myTickHook( void *ptr );



//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//							MAIN									//
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void){


///////////////////////////////////////////////////////////////////
	#ifdef TP1_1  //Blinky
		   /* ------------- INICIALIZACIONES ------------- */
		   /* Inicializar la placa */
		   boardConfig();
		   /* ------------- REPETIR POR SIEMPRE ------------- */
		   while(1) {
			  /* Prendo el led azul */
			  gpioWrite( LEDB, ON );

			  delay(500);

			  /* Apago el led azul */
			  gpioWrite( LEDB, OFF );

			  delay(500);
		   }

	#endif
///////////////////////////////////////////////////////////////////
	#ifdef TP1_2 //Switches Leds

		   boardConfig();

		     gpioConfig( GPIO0, GPIO_INPUT );

		     gpioConfig( GPIO1, GPIO_OUTPUT );

		     /* Variable para almacenar el valor de tecla leido */
		     bool_t valor;

		     /* ------------- REPETIR POR SIEMPRE ------------- */
		     while(1) {

		        valor = !gpioRead( TEC1 );
		        gpioWrite( LEDB, valor );

		        valor = !gpioRead( TEC2 );
		        gpioWrite( LED1, valor );

		        valor = !gpioRead( TEC3 );
		        gpioWrite( LED2, valor );

		        valor = !gpioRead( TEC4 );
		        gpioWrite( LED3, valor );

		        valor = !gpioRead( GPIO0 );
		        gpioWrite( GPIO1, valor );

		     }

	#endif
///////////////////////////////////////////////////////////////////
	#ifdef TP1_3 //TickHooks

		   /* Inicializar la placa */
		   boardConfig();

		   /* Inicializar el conteo de Ticks con resolucion de 50ms (se ejecuta
			  periodicamente una interrupcion cada 50ms que incrementa un contador de
			  Ticks obteniendose una base de tiempos). */
		   tickConfig( 50 );

		   /* Se agrega ademas un "tick hook" nombrado myTickHook. El tick hook es
			  simplemente una funcion que se ejecutara peri�odicamente con cada
			  interrupcion de Tick, este nombre se refiere a una funcion "enganchada"
			  a una interrupcion.
			  El segundo parametro es el parametro que recibe la funcion myTickHook
			  al ejecutarse. En este ejemplo se utiliza para pasarle el led a titilar.
		   */
		   tickCallbackSet( myTickHook, (void*)LEDR );
		   delay(1000);

		   /* ------------- REPETIR POR SIEMPRE ------------- */
		   while(1) {
			  tickCallbackSet( myTickHook, (void*)LEDG );
			  delay(1000);
			  tickCallbackSet( myTickHook, (void*)LEDB );
			  delay(1000);
			  tickCallbackSet( myTickHook, (void*)LED1 );
			  delay(1000);
			  tickCallbackSet( myTickHook, (void*)LED2 );
			  delay(1000);
			  tickCallbackSet( myTickHook, (void*)LED3 );
			  delay(1000);
			  tickCallbackSet( myTickHook, (void*)LEDR );
			  delay(1000);
		   }

		   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
			  por ningun S.O. */
	#endif
///////////////////////////////////////////////////////////////////
	#ifdef TP1_4 //TickHooks + Leds


		/* ------------- INICIALIZACIONES ------------- */

		   /* Inicializar la placa */
		   boardConfig();

		   /* Inicializar el conteo de Ticks con resolucion de 50ms (se ejecuta
			  periodicamente una interrupcion cada 50ms que incrementa un contador de
			  Ticks obteniendose una base de tiempos). */
		   tickConfig( TICKRATE_MS );

		   /* Se agrega ademas un "tick hook" nombrado myTickHook. El tick hook es
			  simplemente una funcion que se ejecutara peri�odicamente con cada
			  interrupcion de Tick, este nombre se refiere a una funcion "enganchada"
			  a una interrupcion.
			  El segundo parametro es el parametro que recibe la funcion myTickHook
			  al ejecutarse. En este ejemplo se utiliza para pasarle el led a titilar.
		   */
		   tickCallbackSet( myTickHook, (void*)LEDR );
		   delay(1000);

		   /* ------------- REPETIR POR SIEMPRE ------------- */
		   while(1) {
			  tickCallbackSet( myTickHook, (void*)LEDG );
			  delay(1000);
			  tickCallbackSet( myTickHook, (void*)LEDB );
			  delay(1000);
			  tickCallbackSet( myTickHook, (void*)LED1 );
			  delay(1000);
			  tickCallbackSet( myTickHook, (void*)LED2 );
			  delay(1000);
			  tickCallbackSet( myTickHook, (void*)LED3 );
			  delay(1000);
			  tickCallbackSet( myTickHook, (void*)LEDR );
			  delay(1000);
		   }
	#endif
///////////////////////////////////////////////////////////////////
	#ifdef TP1_5

	 /* ------------- INICIALIZACIONES ------------- */
	uint32_t LED_Toggle_Counter = 0;

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
       simplemente una funcion que se ejecutara peri odicamente con cada
       interrupcion de Tick, este nombre se refiere a una funcion "enganchada"
       a una interrupcion.
       El segundo parametro es el parametro que recibe la funcion myTickHook
       al ejecutarse. En este ejemplo se utiliza para pasarle el led a titilar.
	*/
	tickCallbackSet( myTickHook, (void*)NULL );

	/* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {
		__WFI();

		if (LED_Time_Flag == true) {
			LED_Time_Flag = false;

			if (LED_Toggle_Counter == 0) {
				LED_Toggle_Counter = LED_TOGGLE_MS;
				gpioToggle(LED3);
				debugPrintString( "LED Toggle\n" );
			}
			else
				LED_Toggle_Counter--;
		}
	}

	#endif
///////////////////////////////////////////////////////////////////
	#ifdef TP1_6 //Puerto serie + Push Buttons

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

	#endif
///////////////////////////////////////////////////////////////////

return 0 ;
} //end Main

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//					CALLBACK FUNCTIONS							//
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

/* FUNCION que se ejecuta cada vez que ocurre un Tick. */
void myTickHook( void *ptr ){

	#ifdef TP1_3
	   static bool_t ledState = OFF;

	   gpioMap_t led = (gpioMap_t)ptr;

	   if( ledState ){
		  ledState = OFF;
	   }
	   else{
		  ledState = ON;
	   }
	   gpioWrite( led, ledState );
	#endif

	#ifdef TP1_4


	   static bool_t ledState = OFF;
	   static size_t cicleCounter = 1;

	   gpioMap_t led = (gpioMap_t)ptr;

	   if(cicleCounter == LED_TOGGLE_CICLE){
		   if( ledState ){
			  ledState = OFF;
		   }
		   else{
			  ledState = ON;
		   }
		   gpioWrite( led, ledState );
		   cicleCounter = 1;
	   }
	   else{
		   cicleCounter++;
	   }

	#endif

	#ifdef TP1_5
	   LED_Time_Flag = true;
	#endif

	#ifdef TP1_6

		LED_Time_Flag = true;
		BUTTON_Time_Flag = true;

	    if (!gpioRead( TEC1 ))
			BUTTON_Status_Flag = true;
		else
			BUTTON_Status_Flag = false;
	#endif
}



