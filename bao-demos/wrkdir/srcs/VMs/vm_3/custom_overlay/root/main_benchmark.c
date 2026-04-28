/*
 * main_benchmark.c
 *
 * Wrapper Linux para os benchmarks do projeto.
 * Recebe o nome do benchmark como argumento e executa em loop infinito.
 *
 * Uso: ./benchmark <nome>
 *   nome: bandwidth | dijkstra | disparity | fft | qsort | sha | sorting
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

/* Includes dos benchmarks — os -I flags são fornecidos pelo Makefile */
#include "bandwidth.h"
#include "benchmarks_wrappers.h"

/* g_bw_memory e qsort_input_data são definidos em benchmarks_wrappers.c */
extern int g_bw_memory[];

static void init_qsort_data(void) {
    srand(42);
    for (int i = 0; i < 164; i++) {
        qsort_input_data[i][0] = rand() % 1000;
        qsort_input_data[i][1] = rand() % 1000;
        qsort_input_data[i][2] = rand() % 1000;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <benchmark>\n", argv[0]);
        fprintf(stderr, "  Benchmarks: bandwidth dijkstra disparity fft qsort sha sorting\n");
        return 1;
    }

    const char *bench = argv[1];

    /* Inicializa dados do qsort */
    init_qsort_data();

    /* Executa o benchmark em loop infinito */
    while (1) {
        if (strcmp(bench, "bandwidth") == 0) {
            bandwidth_context_fann_t ctx;
            ctx.mem_ptr = g_bw_memory;
            ctx.sum = 0;
            bandwidth_wrapper_fann(&ctx);
        } else if (strcmp(bench, "dijkstra") == 0) {
            dijkstra_wrapper_fann();
        } else if (strcmp(bench, "disparity") == 0) {
            disparity_wrapper_fann();
        } else if (strcmp(bench, "fft") == 0) {
            fft_wrapper_fann();
        } else if (strcmp(bench, "qsort") == 0) {
            qsort_wrapper_fann();
        } else if (strcmp(bench, "sha") == 0) {
            sha_wrapper_fann();
        } else if (strcmp(bench, "sorting") == 0) {
            sorting_wrapper_fann();
        } else {
            fprintf(stderr, "Benchmark '%s' desconhecido!\n", bench);
            return 1;
        }

        /* Pequena pausa para não saturar completamente a CPU */
        usleep(1000);  /* 1ms */
    }

    return 0;
}
