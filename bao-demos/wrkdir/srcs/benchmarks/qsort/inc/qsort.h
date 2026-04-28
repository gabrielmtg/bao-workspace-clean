#ifndef QSORT_H
#define QSORT_H

#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#define UNLIMIT
/* this number, if too large, will cause a seg. fault!! */
#define QSORT_MAXARRAY 1000

struct my3DVertexStruct {
  int x, y, z;
  uint32_t distance;
};

int qsort_compare(const void *elem1, const void *elem2);

#endif
