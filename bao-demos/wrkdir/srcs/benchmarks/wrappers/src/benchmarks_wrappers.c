#include "../inc/benchmarks_wrappers.h"

#include <stdio.h>

#include "../../bandwidth/inc/bandwidth.h"
#include "../../dijkstra/inc/dijkstra.h"
#include "../../disparity/inc/disparity.h"
#include "../../disparity/inc/ecrts2019_images_64_48.h"
#include "../../fft/inc/fft.h"
#include "../../mser/inc/mser.h"
#include "../../qsort/inc/qsort.h"
#include "../../sha/inc/sha.h"
#include "../../sorting/inc/sorting.h"


// Array global
int g_bw_memory[NUM_INTS] __attribute__((aligned(CACHE_LINE_SIZE)));
uint32_t qsort_input_data[164][3];

void bandwidth_wrapper_fann(void *context) {
  bandwidth_context_fann_t *c = (bandwidth_context_fann_t *)context;

  c->sum += bench_read(c->mem_ptr);
  c->sum += bench_write(c->mem_ptr);

  return;
}

//disparity benchmark

void disparity_wrapper_fann() {
  I2D *imleft = (I2D *)img1;
  I2D *imright = (I2D *)img2;
  int WIN_SZ = 8, SHIFT = 64;
  char signature[2] = {66, 77};
  short int bits_per_pixel = 24;

  // Check if images are valid BMP images.
  if (imleft->height <= 0 || imleft->width <= 0 || signature[0] != 'B' ||
      signature[1] != 'M' || (bits_per_pixel != 24 && bits_per_pixel != 8)) {
    return;
  }

  if (imright->height <= 0 || imright->width <= 0 || signature[0] != 'B' ||
      signature[1] != 'M' || (bits_per_pixel != 24 && bits_per_pixel != 8)) {
    return;
  }

  I2D *retDisparity = getDisparity(imleft, imright, WIN_SZ, SHIFT);
  return;
}

//qsort benchmark

void qsort_wrapper_fann() {
  struct my3DVertexStruct array[QSORT_MAXARRAY];

  int numRows = sizeof(qsort_input_data) / sizeof(qsort_input_data[0]);
  int count = 0;

  // Process the array instead of reading from a file
  for (int i = 0; i < numRows && count < QSORT_MAXARRAY; i++) {
    array[count].x = qsort_input_data[i][0];
    array[count].y = qsort_input_data[i][1];
    array[count].z = qsort_input_data[i][2];
    array[count].distance = (array[count].x * array[count].x) +
                            (array[count].y * array[count].y) +
                            (array[count].z * array[count].z);
    count++;
  }

  qsort(array, count, sizeof(struct my3DVertexStruct), qsort_compare);
  return;
}

//dijkstra benchmark

void dijkstra_wrapper_fann() {
  int i, j, k;

  for (i = 0, j = NUM_NODES / 2; i < 100; i++, j++) {
    j = j % NUM_NODES;
    dijkstra(i, j);
  }

  return;
}

//sha benchmark

void sha_wrapper_fann() {
  SHA_INFO sha_info;
  sha_stream(&sha_info);
  return;
}

//fft benchmark

void fft_wrapper_fann() {
  uint32_t A_re[NUM_POINTS];
  uint32_t A_im[NUM_POINTS];
  uint32_t W_re[NUM_POINTS / 2];
  uint32_t W_im[NUM_POINTS / 2];

  int n = NUM_POINTS;
  init_array(n, A_re, A_im);
  compute_W(n, W_re, W_im);
  fft(n, A_re, A_im, W_re, W_im);
  permute_bitrev(n, A_re, A_im);

  return;
}

//sorting benchmark
void sorting_wrapper_fann() {
  int orig[MAX_SORTING], copy[MAX_SORTING], i;

  void *function[NUM_SORT] = {&selection_sort, &quick_sort,     &shell_sort,
                              &stdlib_qsort,   &insertion_sort, &bubble_sort};
  char *sort_name[NUM_SORT] = {"Selection sort", "Quicksort",
                               "Shellsort",      "Qsort",
                               "Insertion sort", "Bubble sort"};

  fill_array(orig, MAX_SORTING);

  for (i = 0; i < NUM_SORT; i++) {
    execute_sort(orig, copy, MAX_SORTING, sort_name[i], function[i]);
  }

  return;
}