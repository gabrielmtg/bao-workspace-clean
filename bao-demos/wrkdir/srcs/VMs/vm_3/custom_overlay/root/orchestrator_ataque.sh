#!/bin/sh

# List of attacks we compiled
ATAQUES="spectre armageddon meltdown"


while true; do
    for ATAQUE in $ATAQUES; do
        
        
        /root/$ATAQUE &
        PID_ATAQUE=$!

        # Wait 15 seconds for the attack to run
        sleep 15

        kill -9 $PID_ATAQUE
        
        # Wait 2 seconds before requesting the dump
        sleep 2

        # Signal FreeRTOS to print the collected data
        /root/trigger_print

        # 5 second pause for FreeRTOS to transfer data via serial
        sleep 5
        
    done
done
