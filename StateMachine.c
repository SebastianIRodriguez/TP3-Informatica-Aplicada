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
    //COMPLETAR
}

void apagar_maquina_llenado() {
    //COMPLETAR
}

void encender_maquina_tapado() {
    //COMPLETAR
}

void apagar_maquina_tapado() {
    //COMPLETAR
}

/*
Recibe el estado actual y el evento y en base a esto devuelve el nuevo estado.
*/
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

int main()
{

    // Inicializar esta plaquita de mierda

    Estado estado_actual = EN_MOVIMIENTO;
    while (1)
    {
        // Leer entradas y en base a eso determinar el valor de la variable evento
        Evento evento = INICIO_TAPADO;
        //Calculo el siguiente estado, y prendo/apago las lucecitas
        estado_actual = procesar_evento(estado_actual, evento);
    }
    return 0;
}