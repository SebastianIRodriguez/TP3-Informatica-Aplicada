#include "Led_and_switch_control.h"

#include <stdio.h>
#include "peripherals.h"		// Contiene a BOARD_InitBootPeripherals()
#include "pin_mux.h"			// Contiene a BOARD_InitBootPins();
#include "clock_config.h"		// Contiene a BOARD_InitBootClocks()
#include "MKL46Z4.h"			// Contiene los registros y máscaras

void Give_Clock_To(const unsigned int port)
{
	SIM->SCGC5 |= port;
}

bool Sw1_get(void)
{
	// Si está presionado devuelve 1, sino 0
	return (PTC->PDIR & (1 << SW1_PIN)) ? 0 : 1;
}

bool Sw3_get(void)
{
	// Si está presionado devuelve 1, sino 0
	return (PTC->PDIR & (1 << SW3_PIN)) ? 0 : 1;
}

void Configurar_sistema(void)
{
	// Para el puerto serie
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();

	#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	BOARD_InitDebugConsole();
	#endif

	// Le damos clock a los puertos
	Give_Clock_To(SIM_SCGC5_PORTC_MASK);
	Give_Clock_To(SIM_SCGC5_PORTD_MASK);
	Give_Clock_To(SIM_SCGC5_PORTE_MASK);

	// Le da la funcionalidad de GPIO
	PORTE->PCR[PIN_LED_ROJO] = PORT_PCR_MUX(1);
	PORTD->PCR[PIN_LED_VERDE] = PORT_PCR_MUX(1);
	PORTC->PCR[SW1_PIN] = PORT_PCR_MUX(1);
	PORTC->PCR[SW3_PIN] = PORT_PCR_MUX(1);

	// Declaramos como entradas a los pulsadores
	PTC->PDDR &= ~(1 << SW1_PIN);
	PTC->PDDR &= ~(1 << SW3_PIN);

	// Activamos el Pull-UP
	PORTC->PCR[3] |= (1 << PORT_PCR_PE_SHIFT) | (1 << PORT_PCR_PS_SHIFT);
	PORTC->PCR[12] |= (1 << PORT_PCR_PE_SHIFT) | (1 << PORT_PCR_PS_SHIFT);

	// Por seguridad, ponemos los de manera que las máquinas estén apagadas antes de declararlas como salidas
	LED_VERDE_OFF;
	LED_ROJO_OFF;

	// Declaramos los pines como salidas
	GPIOE->PDDR |= 1 << PIN_LED_ROJO;
	GPIOD->PDDR |= 1 << PIN_LED_VERDE;
}


