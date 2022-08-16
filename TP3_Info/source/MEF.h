/*
 *  Máquina de llenado -> LED rojo
 *  Máquina de tapado  -> LED verde
 *  Sensor de llenado  -> SW3
 *  Sensor de tapado   -> SW1
 */

#ifndef MEF
#define MEF

#include "Led_and_switch_control.h"

typedef enum
{
    TAPANDO_SI_LLENANDO_SI,
    TAPANDO_SI_LLENANDO_NO,
    TAPANDO_NO_LLENANDO_SI,
    TAPANDO_NO_LLENANDO_NO
} Evento;

typedef enum
{
    EN_MOVIMIENTO,
    TAPANDO,
    LLENANDO,
    TAPANDO_Y_LLENANDO
} Estado;

void encender_maquina_llenado()
{
    LED_ROJO_ON;
}

void apagar_maquina_llenado()
{
    LED_ROJO_OFF;
}

void encender_maquina_tapado()
{
    LED_VERDE_ON;
}

void apagar_maquina_tapado()
{
    LED_VERDE_OFF;
}


Evento tomar_evento()
{
	if(Sw1_get() == 1 && Sw3_get() == 1)
		return TAPANDO_SI_LLENANDO_SI;
	else if(Sw1_get() == 1 && Sw3_get() == 0)
		return TAPANDO_SI_LLENANDO_NO;
	else if(Sw1_get() == 0 && Sw3_get() == 1)
			return TAPANDO_NO_LLENANDO_SI;
	else return TAPANDO_NO_LLENANDO_NO;
}

Estado procesar_evento(Estado estado_actual, Evento evento)
{
    switch (estado_actual)
    {
    case EN_MOVIMIENTO:

    	switch (evento)
    	{
    		case TAPANDO_SI_LLENANDO_NO:
    			encender_maquina_tapado();
    			return TAPANDO;
    			break;

    		case TAPANDO_NO_LLENANDO_SI:
    			encender_maquina_llenado();
    			return LLENANDO;
    			break;

    		case TAPANDO_SI_LLENANDO_SI:
    			encender_maquina_llenado();
    			encender_maquina_tapado();
    			return TAPANDO_Y_LLENANDO;
    			break;

    		default:
    			break;
    	}
    	break;

    case TAPANDO:

    	switch (evento)
    	{
    		case TAPANDO_NO_LLENANDO_NO:
    			apagar_maquina_tapado();
    			return EN_MOVIMIENTO;
    			break;

    		case TAPANDO_NO_LLENANDO_SI:
    			apagar_maquina_tapado();
    			return EN_MOVIMIENTO;
    			break;

    		default:
    			break;
    	}
        break;

    case LLENANDO:

    	switch (evento)
    	{
    		case TAPANDO_NO_LLENANDO_NO:
    			apagar_maquina_llenado();
    			return EN_MOVIMIENTO;
    			break;

    		case TAPANDO_SI_LLENANDO_NO:
    			apagar_maquina_llenado();
    			return EN_MOVIMIENTO;
    			break;

    		default:
    			break;
    	}
    	break;

    case TAPANDO_Y_LLENANDO:

    	switch (evento)
        {
        	case TAPANDO_NO_LLENANDO_NO:
        		apagar_maquina_llenado();
        		apagar_maquina_tapado();
        		return EN_MOVIMIENTO;
        		break;

        	case TAPANDO_SI_LLENANDO_NO:
        		apagar_maquina_llenado();
        		return TAPANDO;
        		break;

        	case TAPANDO_NO_LLENANDO_SI:
        		apagar_maquina_tapado();
        		return LLENANDO;
        		break;

        	default:
        		break;
        }
        break;

    default:
        break;
    }

    return estado_actual;
}

#endif /* MEF*/
