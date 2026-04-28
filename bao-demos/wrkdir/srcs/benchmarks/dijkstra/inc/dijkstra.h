#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <stdio.h>
#include <stdlib.h>

#define NUM_NODES 100
#define NONE 9999

typedef struct {
    int iDist;
    int iPrev;
} NODE;

typedef struct _QITEM {
    int iNode;
    int iDist;
    int iPrev;
    struct _QITEM *qNext;
} QITEM;

/* variáveis globais */
extern int g_qCount;
extern QITEM *qHead;
extern NODE rgnNodes[NUM_NODES];
extern int AdjMatrix[NUM_NODES][NUM_NODES];

/* funções */
void print_path(NODE *rgnNodes, int chNode);
void enqueue(int iNode, int iDist, int iPrev);
void dequeue(int *piNode, int *piDist, int *piPrev);
int qcount(void);
int dijkstra(int chStart, int chEnd);

#endif