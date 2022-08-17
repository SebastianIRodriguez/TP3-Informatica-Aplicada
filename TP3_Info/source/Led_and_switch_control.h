//Contiene funciones utilizadas para interactuar con la placa
#ifndef LED_AND_SWITCH_CONTROL
#define LED_AND_SWITCH_CONTROL

#include "board.h"

#define PIN_LED_VERDE 5
#define PIN_LED_ROJO 29
#define SW1_PIN 3
#define SW3_PIN 12

#define LED_VERDE_OFF (PTD->PSOR |= (1 << PIN_LED_VERDE))
#define LED_VERDE_ON (PTD->PCOR |= (1 << PIN_LED_VERDE))

#define LED_ROJO_OFF (PTE->PSOR |= (1 << PIN_LED_ROJO))
#define LED_ROJO_ON (PTE->PCOR |= (1 << PIN_LED_ROJO))

void Give_Clock_To(const unsigned int port);

bool Sw1_get(void);

bool Sw3_get(void);

void Configurar_sistema(void);

//#include "Led_and_switch_control.c"

#endif /* LED_AND_SWITCH_CONTROL*/
