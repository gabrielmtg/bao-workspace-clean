#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "tasks_project.h"
#include "queue.h"

#include "../inc/globals.h"

#include "pmu_monitor.h"
#include "neural_network.h"




//==============================================================================
//monitor
//==============================================================================

void task_monitor(void *arg) {
    const TickType_t xPeriod = pdMS_TO_TICKS(200);
    TickType_t xLastWakeTime = xTaskGetTickCount();
    
    printf("TIMESTAMP, CPU_CYCLES, INSTRUCTIONS, CACHE_MISSES, BRANCH_MISSES, LABEL, DET_STATUS, DET_PROB, BENCH_ID\n");
    fflush(stdout);

    // Inicializar IPC shared memory com zeros para evitar lixo nos labels
    ipc_init_channels();

    uint64_t timer_freq;
    asm volatile("mrs %0, cntfrq_el0" : "=r"(timer_freq));

    // PMU registers são inicializados pelo hypervisor (timer_arch_init)
    // NÃO chamar init_pmu_registers() aqui — conflita com a config do EL2

    while(1) {
        vTaskDelayUntil(&xLastWakeTime, xPeriod);

        collect_and_process_pmu_sample(timer_freq);

        // O envio via UART em dump_history_to_serial toma muito tempo, fazendo o vTaskDelayUntil
        // tentar "compensar" os delays perdidos rodando instantaneamente sem esperar.
        // Isso lê os dados cacheados do hypervisor, gerando dados 100% duplicados.
        // A lógica abaixo identifica se ocorreu um atraso grande e resincroniza o timer.
        TickType_t current_tick = xTaskGetTickCount();
        if ((current_tick - xLastWakeTime) > xPeriod) {
            xLastWakeTime = current_tick;
        }
    }
}

//==============================================================================
//fann
//==============================================================================

void task_fann(void *arg) {
    struct fann *ann = init_fann_model();
    int iteracao = 0;
    
    vTaskDelay(pdMS_TO_TICKS(500));
    const TickType_t xPeriod = pdMS_TO_TICKS(500);
    TickType_t xLastWakeTime = xTaskGetTickCount();
    
    while(1) {
        vTaskDelayUntil(&xLastWakeTime, xPeriod);
      
        int amostras = uxQueueMessagesWaiting(xPmuQueue);
      
        if (amostras > 0) {
            process_fann_batch(ann, amostras, &iteracao);
        }
    }
}
