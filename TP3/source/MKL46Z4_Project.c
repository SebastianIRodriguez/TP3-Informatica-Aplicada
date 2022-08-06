#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"

#include "pin_mux.h"
#include "StateMachine.h"

int i = 0;

void alternate_blink(void);

int main(void)
{
	// Iniciamos lo necesario para los mensajes por puerto serie
	BOARD_InitPins();
	BOARD_BootClockRUN();
	BOARD_InitDebugConsole();

	PRINTF("Hola Seba, descubri como hablar con la KL46Z\r\n");
	PRINTF("Simulacion de fabrica de cocucha\r\n");

	Start_sistem();

	Estado estado_actual = EN_MOVIMIENTO;
	Estado estado_previo = TAPANDO;

	while (1)
	{
		// Leer entradas y en base a eso determinar el valor de la variable evento

	    //Calculo el siguiente estado, y prendo/apago las lucecitas
	    estado_actual = procesar_evento(estado_actual, tomar_evento_llenadora());
	    estado_actual = procesar_evento(estado_actual, tomar_evento_tapadora());

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

void alternate_blink()
{
	for (;;)
	{
		i++;
		if(i < 40000)
		{
			Red_Led_Write(1);
			Green_Led_Write(0);
		}
		if(i > 40000)
		{
			Red_Led_Write(0);
			Green_Led_Write(1);
		}
		if(i > 80000)
			i=0;
	}
}
