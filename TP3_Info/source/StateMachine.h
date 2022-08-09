/*
 * StateMachine.h
 *
 *  Máquina de llenado -> LED rojo
 *  Máquina de tapado  -> LED verde
 *  Sensor de llenado  -> SW3
 *  Sensor de tapado   -> SW1
 *
 */

#ifndef STATEMACHINE
#define STATEMACHINE

#include "Led_and_switch_control.h"

typedef enum
{
    INICIO_TAPADO,
    FIN_TAPADO,
    INICIO_LLENADO,
    FIN_LLENADO
} Evento;

typedef enum
{
    EN_MOVIMIENTO,
    TAPANDO,
    LLENANDO,
    TAPANDO_Y_LLENANDO
} Estado;

void encender_maquina_llenado() {
	RED_LED_ON;
}

void apagar_maquina_llenado() {
	RED_LED_OFF;
}

void encender_maquina_tapado() {
	GREEN_LED_ON;
}

void apagar_maquina_tapado() {
	GREEN_LED_OFF;
}

Evento tomar_evento_tapadora(){
	if(Sw1_get() == 1)
		return INICIO_TAPADO;
	else
		return FIN_TAPADO;
}

Evento tomar_evento_llenadora(){
	if(Sw3_get() == 1)
		return INICIO_LLENADO;
	else
		return FIN_LLENADO;
}

void Start_sistem()
{
	// Le damos clock a los puertos
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

	// Por seguridad, ponemos los de manera que las máquinas estén apagadas antes de declararlas como salidas
	apagar_maquina_llenado();
	apagar_maquina_tapado();

	// Declaramos los pines como salidas
	GPIOE->PDDR |= 1 << RED_PIN;
	GPIOD->PDDR |= 1 << GREEN_PIN;
}

Estado procesar_evento(Estado estado_actual, Evento evento)
{
    switch (estado_actual)
    {
    case EN_MOVIMIENTO:
        if (evento == INICIO_TAPADO)
        {
            encender_maquina_tapado();
            return TAPANDO;
        }
        if (evento == INICIO_LLENADO)
        {
            encender_maquina_llenado();
            return LLENANDO;
        }
        break;

    case TAPANDO:
        if (evento == FIN_TAPADO)
        {
            apagar_maquina_tapado();
            return EN_MOVIMIENTO;
        }
        if (evento == INICIO_LLENADO)
        {
            encender_maquina_llenado();
            return TAPANDO_Y_LLENANDO;
        }
        break;

    case LLENANDO:
        if (evento == FIN_LLENADO)
        {
            apagar_maquina_llenado();
            return EN_MOVIMIENTO;
        }
        if (evento == INICIO_TAPADO)
        {
            encender_maquina_tapado();
            return TAPANDO_Y_LLENANDO;
        }
        break;

    case TAPANDO_Y_LLENANDO:
        if (evento == FIN_LLENADO)
        {
            apagar_maquina_llenado();
            return TAPANDO;
        }
        if (evento == FIN_TAPADO)
        {
            apagar_maquina_tapado();
            return LLENANDO;
        }
        break;

    default:
        break;
    }

    return estado_actual;
}



#endif /* STATEMACHINE*/

