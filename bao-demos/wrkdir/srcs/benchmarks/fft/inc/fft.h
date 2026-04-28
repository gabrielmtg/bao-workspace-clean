#ifndef FFT_H
#define FFT_H

#include <stdio.h>
#include <stdint.h>


#define NUM_POINTS 64 /* 1MB */

/************************************************************************************/

void init_array(int n, uint32_t *A_re, uint32_t *A_im); 
void compute_W(int n, uint32_t *W_re, uint32_t *W_im); 
//void output_array(int n, uint32_t *A_re, uint32_t *A_im, char *outfile); 
void permute_bitrev(int n, uint32_t *A_re, uint32_t *A_im); 
int bitrev(int inp, int numbits); 
int log_2(int n);
void fft(int n, uint32_t *A_re, uint32_t *A_im, uint32_t *W_re, uint32_t *W_im);

/************************************************************************************/



#endif
