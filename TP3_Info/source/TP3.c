/*
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    Prueba_serie.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL46Z4.h"
#include "fsl_debug_console.h"
#include "StateMachine.h"

int i = 0;

int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    PRINTF("***** Simulacion de fabrica de cerveza *****\r\n\r\n");

   	Start_sistem();

   	PRINTF("Cinta en movimiento\r\n");

    Estado estado_actual = EN_MOVIMIENTO;
    Estado estado_previo = EN_MOVIMIENTO;

    Evento tapadora_previo = FIN_TAPADO;
    Evento llenadora_previo = FIN_LLENADO;

    Evento evento_actual;
    Evento evento_auxiliar;

    while (1)
    {
    	// Leer entradas y en base a eso determinar el valor de la variable evento

    	 evento_auxiliar = tomar_evento_llenadora();

    	 if(llenadora_previo != evento_auxiliar){
    		 llenadora_previo = evento_auxiliar;
    		 evento_actual = evento_auxiliar;
    	 }
    	 else if((evento_auxiliar = tomar_evento_tapadora()) != tapadora_previo){
    		 tapadora_previo = evento_auxiliar;
    		 evento_actual = evento_auxiliar;
    	 }

    	//Calculo el siguiente estado y aplico las acciones correspondientes

    	estado_actual = procesar_evento(estado_actual, evento_actual);

    	if(estado_actual != estado_previo){
    		estado_previo = estado_actual;

    	    switch (estado_actual){
    	    	case EN_MOVIMIENTO:
    	    		PRINTF("Cinta en movimiento\r\n");
    	    		break;

    	    	case TAPANDO:
    	    		PRINTF("Tapando botella...\r\n");
    	   	   		break;

    	   		case LLENANDO:
    	   			PRINTF("Llenando botella...\r\n");
    	   			break;

        		case TAPANDO_Y_LLENANDO:
   	    			PRINTF("Llenando una botella y tapando otra\r\n");
   	    			break;

    	    	default:
    	    		break;
    	    	}

    	    }
    	}

    	return 0;
    }

