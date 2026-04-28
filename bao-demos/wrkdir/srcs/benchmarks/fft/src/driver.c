#include "../inc/fft.h"


void init_array(int n, uint32_t *A_re, uint32_t *A_im) 
{
	int NumPoints, i;
	NumPoints     = 0;

#ifdef COMMENT_ONLY
	for(i=0; i < n*2 ; i+=2)
	{
		A_re[NumPoints] = (uint32_t)input_buf[i];
		A_im[NumPoints] = (uint32_t)input_buf[i+1];
		NumPoints++;
	}
#endif
	for (i=0; i<n; i++)
	{
		if (i==1)
		{
			A_re[i]=1;
			A_im[i]=0;
		}
		else
		{
			A_re[i]=0;
			A_im[i]=0;
		}

	}
} 


void compute_W(int n, uint32_t *W_re, uint32_t *W_im)
{
	int i, br;
	int log2n = n;//nlog_2(n);

	for (i=0; i<(n/2); i++)
	{
		br = bitrev(i,log2n-1); 
		//W_re[br] = cos(((uint32_t)i*2*M_PI)/((uint32_t)n));  
		//W_im[br] = sin(((uint32_t)i*2*M_PI)/((uint32_t)n));
		W_re[br] = ((uint32_t)i * 2 * 31416) / ((uint32_t)n * 10000);
		W_im[br] = ((uint32_t)i * 2 * 31416) / ((uint32_t)n * 10000);

	}

#ifdef COMMENT_ONLY 
	for (i=0;i<(n/2);i++)
	{ 
		br = i; //bitrev(i,log2n-1); 
		printf("(%g\t%g)\n", W_re[br], W_im[br]);
	}  
#endif 
}


/* permutes the array using a bit-reversal permutation */ 
void permute_bitrev(int n, uint32_t *A_re, uint32_t *A_im) 
{ 
	int i, bri, log2n;
	uint32_t t_re, t_im;

	log2n = log_2(n); 
  
	for (i=0; i<n; i++)
	{
		bri = bitrev(i, log2n);

		/* skip already swapped elements */
		if (bri <= i) continue;

		t_re = A_re[i];
		t_im = A_im[i];
		A_re[i]= A_re[bri];
		A_im[i]= A_im[bri];
		A_re[bri]= t_re;
		A_im[bri]= t_im;
	}  
} 


/* treats inp as a numbits number and bitreverses it. 
 * inp < 2^(numbits) for meaningful bit-reversal
 */ 
int bitrev(int inp, int numbits)
{
	int i, rev=0;
	for (i=0; i < numbits; i++)
	{
		rev = (rev << 1) | (inp & 1);
		inp >>= 1;
	}
	return rev;
}


/* returns log n (to the base 2), if n is positive and power of 2 */ 
int log_2(int n) 
{
	int res; 
	for (res=0; n >= 2; res++) 
		n = n >> 1; 
	return res; 
}
 
