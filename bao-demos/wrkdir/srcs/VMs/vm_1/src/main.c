/*
 * FreeRTOS Kernel V10.2.1
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/* FreeRTOS kernel includes. */
#include <stdio.h>
#include <sys/time.h>

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

#include "globals.h"
#include "tasks.h"

QueueHandle_t xPmuQueue = NULL;
volatile float g_label_atual = 0.0f;

int _gettimeofday(struct timeval *tv, void *tz) {
  if (tv) {
    tv->tv_sec = 0;
    tv->tv_usec = 0;
  }
  return 0;
}

int _open(const char *name, int flags, int mode) { return -1; }

// void _init(void) {}
void _fini(void) {}

int main(void) {

  // Create queue for PMU -> FANN communication
  xPmuQueue = xQueueCreate(100, sizeof(FANN_sample));
  if (xPmuQueue == NULL) {
    printf("Error: queue not created\n");
    while (1)
      ;
  }

  // Create orchestrator task
  xTaskCreate(task_orchestrator, "taskOrquestradora", TASK_STACK_SIZE, NULL,
              OTHER_TASK_PRIORITY, NULL);

  vTaskStartScheduler();
  while (1) {
    //
  }
  return 0;
}

/*-----------------------------------------------------------*/
void vApplicationDaemonTaskStartupHook(void) {
  printf("vApplicationDaemonTaskStartupHook(void)\n");
}

void vApplicationMallocFailedHook(void) {
  printf("vApplicationMallocFailedHook(void)\n");
  taskDISABLE_INTERRUPTS();
  for (;;)
    ;
}

void vApplicationIdleHook(void) { printf("void vApplicationIdleHook(void)\n"); }

void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName) {
  (void)pcTaskName;
  (void)pxTask;
  printf(
      "vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)\n");
  taskDISABLE_INTERRUPTS();
  for (;;)
    ;
}

void vApplicationTickHook(void) {
  printf("vApplicationTickHook(void)\n");
  for (;;)
    ;
}

void vAssertCalled(void) {
  printf("vAssertCalled(void)\n");
  volatile uint32_t ulSetTo1ToExitFunction = 0;

  taskDISABLE_INTERRUPTS();
  while (ulSetTo1ToExitFunction != 1) {
    __asm volatile("NOP");
  }
}

void vApplicationAssert(const char *pcFileName, uint32_t ulLine) {
  printf("vApplicationAssert( const char *pcFileName, uint32_t ulLine )\n");
  volatile uint32_t ul = 0;
  volatile const char *pcLocalFileName = pcFileName;
  volatile uint32_t ulLocalLine = ulLine;

  (void)pcLocalFileName;
  (void)ulLocalLine;

  printf("Assert failed in file %s, line %lu\r\n", pcLocalFileName,
         ulLocalLine);

  taskENTER_CRITICAL();
  {
    while (ul == 0) {
      __asm volatile("NOP");
    }
  }
  taskEXIT_CRITICAL();
}