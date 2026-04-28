#ifndef FANNCODE_H
#define FANNCODE_H

#include <stdio.h>

typedef struct {
    void (*func)(void *args);
    FILE* file;
} Fann;

#endif

