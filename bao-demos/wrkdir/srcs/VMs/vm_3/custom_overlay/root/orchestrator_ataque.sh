#!/bin/sh

# Lista dos ataques que compilamos
ATAQUES="spectre armageddon meltdown"


while true; do
    for ATAQUE in $ATAQUES; do
        
        
        /root/$ATAQUE &
        PID_ATAQUE=$!

        # Aguarda 15 segundos de execucao do ataque
        sleep 15

        kill -9 $PID_ATAQUE
        
        # Aguarda 2 segundos antes de pedir o dump
        sleep 2

        # Avisa o FreeRTOS para printar os dados coletados
        /root/trigger_print

        # Pausa de 5 segundos para o FreeRTOS transferir os dados via serial
        sleep 5
        
    done
done
