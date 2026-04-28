/********************************
Author: Sravanthi Kota Venkata
********************************/

#ifndef _MSER_
#define _MSER_

#include <string.h>
#include "sdvbs_common.h"

#define sref(a,i) a->data[i]


typedef int val_t;

typedef struct
{
    int width;
    int data[];
}iArray;

typedef struct
{
    int width;
    unsigned int data[];
}uiArray;

typedef struct
{
    int width;
    long long int unsigned data[];
}ulliArray;





#define magic_timing_begin(cycleLo, cycleHi) {					\
		cycleHi = 0;											\
		asm volatile("mrs %0, cntvct_el0" : "=r"(cycleLo) );	\
	}															\

#define min(a,b) (a<b)?a:b
#define max(a,b) (a>b)?a:b


#define MIN(a,b) (a<b)?a:b
#define MAX(a,b) (a>b)?a:b

typedef int  unsigned idx_t ;
typedef long long int unsigned acc_t ;

/* pairs are used to sort the pixels */
typedef struct 
{
	val_t value ; 
	idx_t  index ;
} pair_t ;

/* forest node */
typedef struct
{
	idx_t parent ;   /**< parent pixel         */
	idx_t shortcut ; /**< shortcut to the root */
	idx_t region ;   /**< index of the region  */
	int   area ;     /**< area of the region   */
#ifdef USE_RANK_UNION
	int   height ;    /**< node height         */
#endif
} node_t ;

/* extremal regions */
typedef struct
{
	idx_t parent ;     /**< parent region                           */
	idx_t index ;      /**< index of root pixel                     */
	val_t value ;      /**< value of root pixel                     */
	int   area ;       /**< area of the region                      */
	int   area_top ;   /**< area of the region DELTA levels above   */
	int   area_bot  ;  /**< area of the region DELTA levels below   */
	int variation ;  /**< variation           //float                    */
	int   maxstable ;  /**< max stable number (=0 if not maxstable) */
} region_t ;


//int script_mser();
void adv(iArray *dims, int ndims, iArray *subs_pt);
I2D* mser(I2D* I, int in_delta);

#endif


