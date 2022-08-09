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

Evento tomar_evento_tapadora()
{
    return (Sw1_get() == 1) ? INICIO_TAPADO : FIN_TAPADO;
}

Evento tomar_evento_llenadora()
{
    return (Sw3_get() == 1) ? INICIO_LLENADO : FIN_LLENADO;
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

#endif /* MEF*/
