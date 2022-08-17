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

void encender_maquina_llenado();

void apagar_maquina_llenado();

void encender_maquina_tapado();

void apagar_maquina_tapado();

Evento tomar_evento();

Estado procesar_evento(Estado estado_actual, Evento evento);

#endif /* MEF*/
