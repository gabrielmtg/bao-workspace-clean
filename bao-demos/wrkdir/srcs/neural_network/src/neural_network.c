#include "../inc/neural_network.h"
#include "../inc/pesos_treinados.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FANN_sample window_buffer[WINDOW_SIZE];
int buffer_index = 0;
int buffer_filled = 0;

unsigned long last_hardware_timestamp = 0;

void update_window(FANN_sample new_sample) {
    unsigned long current_ts = new_sample.data.timestamp;
    
    unsigned long delta_cycles = (last_hardware_timestamp == 0) ? 0 : (current_ts - last_hardware_timestamp);
    last_hardware_timestamp = current_ts;

    float freq = (float)get_hardware_timer_freq();
    float delta_ms = (delta_cycles * 1000.0f) / freq;

    new_sample.data.timestamp = (unsigned long)delta_ms; 
    
    window_buffer[buffer_index] = new_sample;
    buffer_index = (buffer_index + 1) % WINDOW_SIZE;
    if (buffer_index == 0) buffer_filled = 1;
}

void get_flattened_window(fann_type *input_vector) {
    for (int i = 0; i < WINDOW_SIZE; i++) {
        int idx = (buffer_index + i) % WINDOW_SIZE; 
        int offset = i * METRICS;
        
        input_vector[offset + 0] = (fann_type)window_buffer[idx].data.branch_misses / NORM_BRANCH;
        input_vector[offset + 1] = (fann_type)window_buffer[idx].data.cache_misses / NORM_CACHE;
        input_vector[offset + 2] = (fann_type)window_buffer[idx].data.instructions / NORM_INSTR;
        input_vector[offset + 3] = (fann_type)window_buffer[idx].data.cpu_cycles / NORM_CYCLES;
        input_vector[offset + 4] = (fann_type)window_buffer[idx].data.timestamp / NORM_DELTA_TIME;
    }
}

struct fann_train_data* cria_dataset(unsigned int num_amostras) {
    struct fann_train_data *data = fann_create_train(num_amostras, TOTAL_INPUTS, 1);
    if (data == NULL) return NULL;

    FANN_sample buffer;
    unsigned int coletados = 0;
    unsigned int processados = 0;

    while(processados < num_amostras) {
        if(xQueueReceive(xPmuQueue, &buffer, 10)) {
            update_window(buffer);
            processados++;

            if (buffer_filled) {
                get_flattened_window(data->input[coletados]);
                data->output[coletados][0] = (fann_type)buffer.output;
                coletados++;
            }
        } else {
            break;
        }
    }
    
    data->num_data = coletados;
    if (coletados == 0) {
        fann_destroy_train(data);
        return NULL;
    }
    return data;
}

struct fann* init_fann_model(void) {
    const unsigned int num_input = TOTAL_INPUTS; //25
    const unsigned int num_output = 1;
    const unsigned int num_layers = 4; 
    const unsigned int num_neurons_hidden1 = 16;
    const unsigned int num_neurons_hidden2 = 8;
    
    struct fann *ann = fann_create_standard(num_layers, num_input, num_neurons_hidden1, num_neurons_hidden2, num_output);

    fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
    fann_set_activation_function_output(ann, FANN_SIGMOID);
    fann_set_training_algorithm(ann, FANN_TRAIN_INCREMENTAL);
    fann_set_learning_rate(ann, 0.01f); 

    #ifdef NUM_PESOS
    struct fann_connection *conexoes = (struct fann_connection *)malloc(NUM_PESOS * sizeof(struct fann_connection));
    if (conexoes) {
      fann_get_connection_array(ann, conexoes);
      if (NUM_PESOS == fann_get_total_connections(ann)) {
        for (int i=0; i<NUM_PESOS; i++) conexoes[i].weight = (fann_type)pesos_iniciais[i];
        fann_set_weight_array(ann, conexoes, NUM_PESOS);
        printf("[FANN] Pesos carregados com sucesso!\n");
      }
      free(conexoes);
    }
    #endif

    printf("[FANN] Rede inicializada. Aguardando dados...\n");
    return ann;
}

void process_fann_batch(struct fann *ann, int amostras, int *iteracao) {
    struct fann_train_data *train_data = cria_dataset(amostras);
          
    if (train_data) {
        float erro_medio_batch = 0.0f;
        float predicao_media = 0.0f;

        for(int k=0; k < train_data->num_data; k++) {
            fann_type *out = fann_run(ann, train_data->input[k]);
            predicao_media += out[0];
            
            float erro = fabsf(train_data->output[k][0] - out[0]);
            erro_medio_batch += erro;
        }
        predicao_media /= train_data->num_data;
        erro_medio_batch /= train_data->num_data;

        printf("FANN #%d: Real=%.0f Predito=%.2f (Erro Médio: %.4f)\n", 
               (*iteracao)++, train_data->output[0][0], predicao_media, erro_medio_batch);

        if (erro_medio_batch > 0.1f) {
             fann_train_epoch(ann, train_data);
        }

        fann_destroy_train(train_data);
    }
}