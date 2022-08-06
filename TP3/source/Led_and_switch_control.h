/*
 * Led_and_switch_control.h
 *
 *  Created on: 6 ago. 2022
 *      Author: lraff
 */

#ifndef LED_AND_SWITCH_CONTROL
#define LED_AND_SWITCH_CONTROL

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


#endif /* LED_AND_SWITCH_CONTROL*/
