#include "../inc/dijkstra.h"

QITEM *qHead = NULL;
int g_qCount = 0;

NODE rgnNodes[NUM_NODES];
int AdjMatrix[NUM_NODES][NUM_NODES];

void print_path(NODE *rgnNodes, int chNode) {

  if (rgnNodes[chNode].iPrev != NONE)
    print_path(rgnNodes, rgnNodes[chNode].iPrev);

  printf(" %d", chNode);
}

void enqueue(int iNode, int iDist, int iPrev) {

  QITEM *qNew = (QITEM *)malloc(sizeof(QITEM));
  QITEM *qLast = qHead;

  if (!qNew) {
    fprintf(stderr, "Out of memory\n");
    exit(1);
  }

  qNew->iNode = iNode;
  qNew->iDist = iDist;
  qNew->iPrev = iPrev;
  qNew->qNext = NULL;

  if (!qLast) {
    qHead = qNew;
  } else {
    while (qLast->qNext)
      qLast = qLast->qNext;

    qLast->qNext = qNew;
  }

  g_qCount++;
}

void dequeue(int *piNode, int *piDist, int *piPrev) {

  QITEM *qKill = qHead;

  if (qHead) {

    *piNode = qHead->iNode;
    *piDist = qHead->iDist;
    *piPrev = qHead->iPrev;

    qHead = qHead->qNext;

    free(qKill);
    g_qCount--;
  }
}

int qcount(void) { return g_qCount; }

int dijkstra(int chStart, int chEnd) {

  int ch, i;
  int iNode, iDist, iPrev, iCost;

  for (ch = 0; ch < NUM_NODES; ch++) {
    rgnNodes[ch].iDist = NONE;
    rgnNodes[ch].iPrev = NONE;
  }

  if (chStart == chEnd) {

    printf("Shortest path is 0. Stay where you are.\n");

  } else {

    rgnNodes[chStart].iDist = 0;
    rgnNodes[chStart].iPrev = NONE;

    enqueue(chStart, 0, NONE);

    while (qcount() > 0) {

      dequeue(&iNode, &iDist, &iPrev);

      for (i = 0; i < NUM_NODES; i++) {

        if ((iCost = AdjMatrix[iNode][i]) != NONE) {

          if (rgnNodes[i].iDist == NONE || rgnNodes[i].iDist > iCost + iDist) {

            rgnNodes[i].iDist = iDist + iCost;
            rgnNodes[i].iPrev = iNode;

            enqueue(i, iDist + iCost, iNode);
          }
        }
      }
    }

    // printf("Shortest path cost: %d\n", rgnNodes[chEnd].iDist);
    // printf("Path: ");
    // print_path(rgnNodes, chEnd);
    // printf("\n");
  }

  return 0;
}

// int main(int argc, char *argv[]) {

//     int i, j, k;
//     FILE *fp;

//     if (argc < 2) {
//         fprintf(stderr,"Usage: dijkstra <matrix_file>\n");
//         return 1;
//     }

//     fp = fopen(argv[1], "r");

//     if (!fp) {
//         fprintf(stderr,"Error opening file\n");
//         return 1;
//     }

//     for (i = 0; i < NUM_NODES; i++) {
//         for (j = 0; j < NUM_NODES; j++) {
//             fscanf(fp, "%d", &k);
//             AdjMatrix[i][j] = k;
//         }
//     }

//     fclose(fp);

//     for (i = 0, j = NUM_NODES/2; i < 100; i++, j++) {

//         j = j % NUM_NODES;
//         dijkstra(i, j);

//     }

//     return 0;
// }