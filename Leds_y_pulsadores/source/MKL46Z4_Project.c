/*
 * Copyright 2016-2018 NXP Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 * of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission.
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
 *

*
 * @file Segundos_pasos_kl46.c
 * @brief Application entry point.
 *
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL46Z4.h"
#include "fsl_debug_console.h"
#include "fsl_device_registers.h"

#define GREEN_PIN 5
#define RED_PIN 29


void RedLedWrite(const bool status)
{
  if (status)
    GPIOE->PSOR |= (1 << RED_PIN);
  else
    GPIOE->PCOR |= (1 << RED_PIN);
}

void GreenLedWrite(const bool status)
{
  if (status)
    GPIOD->PSOR |= 1 << GREEN_PIN;
  else
    GPIOD->PCOR |= 1 << GREEN_PIN;
}




int main(void)
{

	// LED ROJO PUERTO E
	// LED VERDE PUERTO D

	//GiveClockTo(SIM_SCGC5_PORTE_MASK);
	//GiveClockTo(SIM_SCGC5_PORTD_MASK);

	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;

	PORTE->PCR[RED_PIN] = PORT_PCR_MUX(1);
	PORTD->PCR[GREEN_PIN] = PORT_PCR_MUX(1)
	GreenLedWrite(0);
	RedLedWrite(0);

	GPIOE->PDDR |= 1 << RED_PIN;
	GPIOD->PDDR |= 1 << GREEN_PIN;

	for (;;)
	{
		GreenLedWrite(1);
    	RedLedWrite(1);
	}

	return 0;
}

*/
/*

Ejemplo de uso del puerto serie
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"

#include "pin_mux.h"

int main(void)
{
    char ch;

	//Init board hardware.
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("Hola Seba, descubri como hablar con la KL46Z\r\n");

    while (1)
    {
        ch = GETCHAR();
        PUTCHAR(ch);
    }
}
*/

#include "board.h"

#define GREEN_PIN 5
#define RED_PIN 29
#define ON 0			// Para encender el LED, el pin debe ir a cero
#define OFF 1			// Para apagar el LED, el pin debe ir a uno
#define SW1_PIN 3
#define SW3_PIN 12

#define GREEN_LED_OFF (PTD->PSOR |= (1 << GREEN_PIN))
#define GREEN_LED_ON (PTD->PCOR |= (1 << GREEN_PIN))
#define GREEN_LED_TOGGLE (PTD->PTOR |= (1 << GREEN_PIN))

#define RED_LED_OFF (PTE->PSOR |= (1 << RED_PIN))
#define RED_LED_ON (PTE->PCOR |= (1 << RED_PIN))
#define RED_LED_TOGGLE (PTE->PTOR |= (1 << RED_PIN))

void Red_Led_Write(const bool status)
{
  if (status)
    GPIOE->PSOR |= (1 << RED_PIN);
  else
    GPIOE->PCOR |= (1 << RED_PIN);
}

void Green_Led_Write(const bool status)
{
  if (status)
    GPIOD->PSOR |= (1 << GREEN_PIN);
  else
    GPIOD->PCOR |= (1 << GREEN_PIN);
}

void Give_Clock_To(const unsigned int port)
{
	SIM->SCGC5 |= port;
}

bool Sw1_get(void)
 {
	// Si está presionado devuelve 0, sino 1
	return (PTC->PDIR & (1 << SW1_PIN))? 0:1;
 }

bool Sw3_get(void)
 {
	// Si está presionado devuelve 0, sino 1
	return (PTC->PDIR & (1 << SW3_PIN))? 0:1;
 }

int i = 0;

void alternate_blink(void);

int main(void)
{

	// Le damos clocl a los puertos
	Give_Clock_To(SIM_SCGC5_PORTC_MASK);
	Give_Clock_To(SIM_SCGC5_PORTD_MASK);
	Give_Clock_To(SIM_SCGC5_PORTE_MASK);

	// Le da la funcionalidad de GPIO
	PORTE->PCR[RED_PIN] = PORT_PCR_MUX(1);
	PORTD->PCR[GREEN_PIN] = PORT_PCR_MUX(1);
	PORTC->PCR[SW1_PIN] = PORT_PCR_MUX(1);
	PORTC->PCR[SW3_PIN] = PORT_PCR_MUX(1);

	// Declaramos como entradas a los pulsadores
	PTC->PDDR &= ~(1 << SW1_PIN);
	PTC->PDDR &= ~(1 << SW3_PIN);

	// Activamos el Pull-UP
	PORTC->PCR[3] |= (1 << PORT_PCR_PE_SHIFT) | (1 << PORT_PCR_PS_SHIFT);
	PORTC->PCR[12] |= (1 << PORT_PCR_PE_SHIFT) | (1 << PORT_PCR_PS_SHIFT);

	// Por seguridad, previo a declarar los pines como salidas los ponemos en cero
	Red_Led_Write(0);
	Green_Led_Write(0);

	// Declaramos los pines como salidas
	GPIOE->PDDR |= 1 << RED_PIN;
	GPIOD->PDDR |= 1 << GREEN_PIN;

	while(1)
	{
		Green_Led_Write(Sw3_get());
		Red_Led_Write(Sw1_get());
	}

	//alternate_blink();

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
