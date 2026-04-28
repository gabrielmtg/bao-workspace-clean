// Filename: regulation.c
// Author: Everaldo Pereira Gomes

#include "../inc/regulation.h"

struct VM vm_conf[VM_QNT] = {
    {0,   5,   5,   0,   300000, 300000, 250000, 250000, 0, 0, {0}, {0}, {0},
     {0}, {0}, {0}, {0}, {0},    {0},    {0},    {0},    0, 0, 0,   0},
    {0,   5,   5,   0,   300000, 300000, 250000, 250000, 0, 0, {0}, {0}, {0},
     {0}, {0}, {0}, {0}, {0},    {0},    {0},    {0},    0, 0, 0,   0},
    {0,   5,   5,   0,   300000, 300000, 250000, 250000, 0, 0, {0}, {0}, {0},
     {0}, {0}, {0}, {0}, {0},    {0},    {0},    {0},    0, 0, 0,   0},
    {0,   5,   5,   0,   300000, 300000, 250000, 250000, 0, 0, {0}, {0}, {0},
     {0}, {0}, {0}, {0}, {0},    {0},    {0},    {0},    0, 0, 0,   0},
};

//
// TASK task_conf[TASK_QNT] =
// {
// 	{TASK_0, PMU_COUNTER0, PMU_COUNTER1, TASK_PRIORITY_2, PERIOD_MS_TASK_0,
// PMU_COUNTER4, 0, 0, DEADLINE_MS_TASK_0}, 	{TASK_1, PMU_COUNTER2,
// PMU_COUNTER3, TASK_PRIORITY_1, PERIOD_MS_TASK_1, PMU_COUNTER5, 0, 0,
// DEADLINE_MS_TASK_1}
// };
