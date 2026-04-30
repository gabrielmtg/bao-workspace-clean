// Filename: regulation.h
// Author: Everaldo Pereira Gomes
//         João Almeida (https://github.com/nynepebbles/)

#ifndef REGULATOR_H
#define REGULATOR_H

#include <stdint.h>
#include <printk.h>
#include <vm.h>
#include <pmu.h>


#define NO 0
#define YES 1

#define UNUSED_ARG 0

#define MAX_INT 4294967295U
#define UNKNOWN_VALUE MAX_INT

#define MAX_QNT_CORE 4

#define PMU_COUNT 6
#define PMU_0_OVERFLOWED_ID 0
#define PMU_1_OVERFLOWED_ID 1

#define READ 0
#define WRITE 1

#define OVERFLOWED 1

// #define GUEST_RESUME_TASK_0_ID 0
// #define GUEST_SUSPEND_TASK_0_BUDGET_ID 1
//
// #define GUEST_RESUME_TASK_1_ID 2
// #define GUEST_SUSPEND_TASK_1_BUDGET_ID 3

#define TASK_0 0
#define TASK_1 1

#define MARGIN 1000000000

struct VM {
    uint32_t depleated_op_type;
    uint32_t defined_pmu_read_val;
    uint32_t defined_pmu_write_val;
    uint64_t current_used_read_budget;
    uint64_t current_used_write_budget;
    uint32_t new_read_budget;
    uint32_t new_write_budget;
    uint64_t total_used_read_budget;
    uint64_t total_used_write_budget;
    uint64_t total_calculated_new_read_budget;
    uint64_t total_calculated_new_write_budget;
    //
    uint64_t cycles;
    uint64_t instructions;
    uint64_t cache_misses;
    uint64_t mispredicts;
};

struct EWMA {
    uint32_t previous_predicted_read_budget;
    uint32_t previous_predicted_write_budget;
    uint32_t new_read_budget;
    uint32_t new_write_budget;
    uint16_t alpha;
    uint16_t scaling_factor;
};

struct SW {
#define SW_MAX_ARRAY_SIZE 10
#define SW_MAX_WINDOW_SIZE 3

    uint32_t read_usage[SW_MAX_ARRAY_SIZE];
    uint32_t write_usage[SW_MAX_ARRAY_SIZE];
    uint8_t current_read_array_size;
    uint8_t current_write_array_size;
    uint16_t read_index;
    uint16_t write_index;
};

struct AMBP {
    uint32_t budget_read_limit;
    uint32_t budget_write_limit;
    uint32_t qnt_budget_read_limit_reached;
    uint32_t qnt_budget_write_limit_reached;
    uint32_t penalty_by_reaching_budget_read_limit;
    uint32_t penalty_by_reaching_budget_write_limit;
    uint16_t alpha;
    uint16_t scaling_factor;

    // Represents a percentage, e.g., 90 for a 10% penalty
    uint16_t penalty_factor;
};

struct AFC {
    uint32_t previous_read_budget;
    uint32_t previous_write_budget;
    uint16_t proportional_gain;
    uint16_t scaling_factor;
};

struct LR {
#define LR_MAX_QNT_ACCESS 9
    uint32_t t_vector[LR_MAX_QNT_ACCESS];
    uint32_t read_usage[LR_MAX_QNT_ACCESS];
    uint32_t write_usage[LR_MAX_QNT_ACCESS];
    uint8_t current_read_array_size;
    uint8_t current_write_array_size;
    uint8_t total_read_exec;
    uint8_t total_write_exec;

    // FIX: Added missing members required by lr_budget_v2
    uint32_t previous_read_usage;
    uint32_t previous_write_usage;
};

struct PIC {
    uint32_t accumulated_read_error;
    uint32_t accumulated_write_error;
    uint32_t kp;
    uint32_t ki;
    uint32_t scaling_factor;

    // FIX: Added missing members required by pic_budget_v2
    uint32_t previous_read_budget;
    uint32_t previous_write_budget;
};

struct Regulation_config {
#define VM_QNT 4
    // #define TASK_QNT 2

    // WARN: defined in <budget_function.h>
    // #define EWMA_FORMULA        0
    // #define SW_FORMULA          1
    // #define AMBP_FORMULA        2
    // #define AFC_FORMULA         3
    // #define LR_FORMULA          4
    // #define PIC_FORMULA         5
    // #define USED_BUDGET_FORMULA PIC_FORMULA

    struct VM vm;      //[TASK_QNT];
    struct EWMA ewma;  //[TASK_QNT];
    struct SW sw;      //[TASK_QNT];
    struct AMBP ambp;  //[TASK_QNT];
    //
    struct AFC afc;  //[TASK_QNT];
    struct LR lr;    //[TASK_QNT];
    struct PIC pic;  //[TASK_QNT];
};

extern struct Regulation_config reg_conf[VM_QNT];

void init_regulation_config();
// void regulator_budget_depleted(const uint8_t task_num, formula_t formula);
uint32_t regulator_get_new_budget(const uint8_t task_num,
                                  const uint8_t op_type);

//===
uint32_t regulator_fetch_new_budget(const uint8_t task_num,
                                    const uint8_t op_type);
uint32_t regulator_get_total_calculated_new_budget(const uint8_t task_num,
                                                   const uint8_t op_type);
uint32_t regulator_get_current_used_budget(const uint8_t task_num,
                                           const uint8_t op_type);
uint32_t regulator_get_total_used_budget(const uint8_t task_num,
                                         const uint8_t op_type);

uint32_t regulator_get_pmu_counter_value(const uint8_t pmu_index);

#endif

#if 0
#define PRINT(fmt, ...) printk("[BAO] " fmt "\n", ##__VA_ARGS__)
#else
#define PRINT(fmt, ...) ((void)0)
#endif

void print_VM(const struct VM *vm, bool before);
void print_EWMA(const struct EWMA *e, bool before);
void print_SW(const struct SW *s, bool before);
void print_AMBP(const struct AMBP *a, bool before);
void print_AFC(const struct AFC *c, bool before);
void print_LR(const struct LR *l, bool before);
void print_PIC(const struct PIC *p, bool before);
void print_Regulation_config(const struct Regulation_config *rc,
                             const char *message);
