#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include "../../fann/src/include/fann.h"
#include "../../VMs/vm_0/src/tasks/inc/globals.h"


#define NORM_BRANCH      100000000.0f
#define NORM_CACHE       50000000.0f 
#define NORM_INSTR       200000000.0f
#define NORM_CYCLES      400000000.0f
#define NORM_TIMESTAMP   1000000.0f

#define WINDOW_SIZE 5
#define METRICS 5
#define TOTAL_INPUTS (WINDOW_SIZE * METRICS)

#define NORM_DELTA_TIME  1000000.0f 

extern unsigned long last_hardware_timestamp;

extern FANN_sample window_buffer[WINDOW_SIZE];
extern int buffer_index;
extern int buffer_filled;

void update_window(FANN_sample new_sample);
void get_flattened_window(fann_type *input_vector);
struct fann_train_data* cria_dataset(unsigned int num_amostras);
struct fann* init_fann_model(void);
void process_fann_batch(struct fann *ann, int amostras, int *iteracao);
void task_fann(void *arg);

#endif