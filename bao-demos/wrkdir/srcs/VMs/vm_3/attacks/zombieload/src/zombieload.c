#include "../inc/zombieload.h"
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

static inline uint64_t get_hardware_timer_count(void) {
  uint64_t val;
  asm volatile("mrs %0, cntvct_el0" : "=r"(val));
  return val;
}
static inline uint64_t get_hardware_timer_freq(void) {
  uint64_t val;
  asm volatile("mrs %0, cntfrq_el0" : "=r"(val));
  return val;
}

uint8_t zombie_noise_buffer[FILL_BUFFER_SIZE];
uint8_t array[256 * 512];

// simula a carga nos buffers de preenchimento
void generate_mds_traffic() {
  for (int i = 0; i < 100; i++) {
    int idx = rand() % FILL_BUFFER_SIZE;
    zombie_noise_buffer[idx] += 1;
    // força a escrita e invalidaçao para gerar trafego de barramento
    asm volatile("dc civac, %0" : : "r"(&zombie_noise_buffer[idx]) : "memory");
  }
  asm volatile("dsb sy");
}

void execute_zombieload_attack(uint8_t secret_val, int cache_hit_threshold,
                               uint32_t duration_ms) {
  uint64_t start_time = get_hardware_timer_count();
  uint64_t timer_freq = get_hardware_timer_freq();

  // Calcula quantos ciclos de hardware equivalem aos milissegundos desejados
  uint64_t duration_hardware_ticks = (timer_freq / 1000) * duration_ms;
  uint64_t end_time = start_time + duration_hardware_ticks;

  // Loop usa o relógio do hardware nativo
  while (get_hardware_timer_count() < end_time) {

    generate_mds_traffic();

    for (int i = 0; i < 256; i++) {
      asm volatile("dc civac, %0" : : "r"(&array[i * 512]) : "memory");
    }
    asm volatile("dsb sy \n isb");

    // acesso especulativo simulado
    volatile uint8_t dummy = array[secret_val * 512];
    (void)dummy;

    int mix_i;
    uint64_t start, end;
    volatile uint8_t *addr;

    for (int i = 0; i < 256; i++) {
      // multiplicacao por numero primo (167) ajuda a embaralhar o acesso e
      // evitar prefetcher de hardware
      mix_i = ((i * 167) + 13) & 255;
      addr = &array[mix_i * 512];

      // mede o tempo de leitura usando o timer
      asm volatile("isb \n mrs %0, cntvct_el0" : "=r"(start));
      volatile uint8_t junk = *addr;
      (void)junk;
      asm volatile("isb \n mrs %0, cntvct_el0" : "=r"(end));

      if ((end - start) <= cache_hit_threshold) {
        // hit
      }
    }
  }
}

int main(void) {
  int cache_hit_threshold = 80;
  uint8_t secret_val = 42;
  while (1) {
    execute_zombieload_attack(secret_val, cache_hit_threshold, 100);
    usleep(5000);
  }
  return 0;
}