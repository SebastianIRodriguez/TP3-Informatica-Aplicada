/*
	TP3 - Informática aplicada:
	Enunciado A: Simulador de fábrica de cerveza
	Trabajo realizado por: Leonel Lingotti, Luciano Raffagnini y Sebastián I. Rodríguez
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL46Z4.h"
#include "fsl_debug_console.h"
#include "MEF.h"

void imprimir_estado(Estado estado_actual)
{
	switch (estado_actual)
	{
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

int main(void)
{
	// Iniciamos el sistema
	Configurar_sistema();

	PRINTF("***** Simulacion de fabrica de cerveza *****\r\n\r\n");

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

		if ((evento_auxiliar = tomar_evento_llenadora()) != llenadora_previo)
		{
			llenadora_previo = evento_auxiliar;
			evento_actual = evento_auxiliar;
		}
		else if ((evento_auxiliar = tomar_evento_tapadora()) != tapadora_previo)
		{
			tapadora_previo = evento_auxiliar;
			evento_actual = evento_auxiliar;
		}

		// Calculo el siguiente estado y aplico las acciones correspondientes

		estado_actual = procesar_evento(estado_actual, evento_actual);

		if (estado_actual != estado_previo)
		{
			estado_previo = estado_actual;
			imprimir_estado(estado_actual);
		}
	}

	return 0;
}
