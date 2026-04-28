// Filename: regulation.c
// Author: Everaldo Pereira Gomes
//         João Almeida (https://github.com/nynepebbles/)

#include <regulator.h>

struct Regulation_config reg_conf[VM_QNT];

void print_VM(const struct VM *vm, bool before)
{
    PRINT("VM: %s", (before ? "BEFORE" : "AFTER"));
    PRINT("  depleated_op_type               = %u", vm->depleated_op_type);
    PRINT("  defined_pmu_read_val            = %u", vm->defined_pmu_read_val);
    PRINT("  defined_pmu_write_val           = %u", vm->defined_pmu_write_val);
    PRINT("  current_used_read_budget        = %u",
          vm->current_used_read_budget);
    PRINT("  current_used_write_budget       = %u",
          vm->current_used_write_budget);
    PRINT("  new_read_budget                 = %u", vm->new_read_budget);
    PRINT("  new_write_budget                = %u", vm->new_write_budget);
    PRINT("  total_used_read_budget          = %u", vm->total_used_read_budget);
    PRINT("  total_used_write_budget         = %u",
          vm->total_used_write_budget);
    PRINT("  total_calculated_new_read_budget = %u",
          vm->total_calculated_new_read_budget);
    PRINT("  total_calculated_new_write_budget= %u",
          vm->total_calculated_new_write_budget);
}

void print_EWMA(const struct EWMA *e, bool before)
{
    PRINT("EWMA: %s", (before ? "BEFORE" : "AFTER"));
    PRINT("  previous_predicted_read_budget  = %u",
          e->previous_predicted_read_budget);
    PRINT("  previous_predicted_write_budget = %u",
          e->previous_predicted_write_budget);
    PRINT("  new_read_budget                 = %u", e->new_read_budget);
    PRINT("  new_write_budget                = %u", e->new_write_budget);
    PRINT("  alpha                           = %u", e->alpha);
    PRINT("  scaling_factor                  = %u", e->scaling_factor);
}

void print_SW(const struct SW *s, bool before)
{
    PRINT("SW: %s", (before ? "BEFORE" : "AFTER"));
    size_t i;
    PRINT("  current_read_array_size = %u", s->current_read_array_size);
    for (i = 0; i < s->current_read_array_size && i < SW_MAX_ARRAY_SIZE; ++i) {
        PRINT("    read_usage[%zu]       = %u", i, s->read_usage[i]);
    }
    PRINT("  current_write_array_size = %u", s->current_write_array_size);
    for (i = 0; i < s->current_write_array_size && i < SW_MAX_ARRAY_SIZE; ++i) {
        PRINT("    write_usage[%zu]      = %u", i, s->write_usage[i]);
    }
    PRINT("  read_index              = %u", s->read_index);
    PRINT("  write_index             = %u", s->write_index);
}

void print_AMBP(const struct AMBP *a, bool before)
{
    PRINT("AMBP: %s", (before ? "BEFORE" : "AFTER"));
    PRINT("  budget_read_limit               = %u", a->budget_read_limit);
    PRINT("  budget_write_limit              = %u", a->budget_write_limit);
    PRINT("  qnt_budget_read_limit_reached   = %u",
          a->qnt_budget_read_limit_reached);
    PRINT("  qnt_budget_write_limit_reached  = %u",
          a->qnt_budget_write_limit_reached);
    PRINT("  alpha                           = %u", a->alpha);
    PRINT("  scaling_factor                  = %u", a->scaling_factor);
    PRINT("  penalty_factor                  = %u%%", a->penalty_factor);
}

void print_AFC(const struct AFC *c, bool before)
{
    PRINT("AFC: %s", (before ? "BEFORE" : "AFTER"));
    PRINT("  previous_read_budget   = %u", c->previous_read_budget);
    PRINT("  previous_write_budget  = %u", c->previous_write_budget);
    PRINT("  proportional_gain      = %u", c->proportional_gain);
    PRINT("  scaling_factor         = %u", c->scaling_factor);
}

void print_LR(const struct LR *l, bool before)
{
    PRINT("LR: %s", (before ? "BEFORE" : "AFTER"));
    size_t i;
    PRINT("  current_read_array_size  = %u", l->current_read_array_size);
    for (i = 0; i < l->current_read_array_size && i < LR_MAX_QNT_ACCESS; ++i) {
        PRINT("    t_vector[%zu]    = %u", i, l->t_vector[i]);
        PRINT("    read_usage[%zu]  = %u", i, l->read_usage[i]);
    }
    PRINT("  current_write_array_size = %u", l->current_write_array_size);
    for (i = 0; i < l->current_write_array_size && i < LR_MAX_QNT_ACCESS; ++i) {
        PRINT("    write_usage[%zu] = %u", i, l->write_usage[i]);
    }
    PRINT("  total_read_exec          = %u", l->total_read_exec);
    PRINT("  total_write_exec         = %u", l->total_write_exec);
}

void print_PIC(const struct PIC *p, bool before)
{
    PRINT("PIC: %s", (before ? "BEFORE" : "AFTER"));
    // PMU_print_all_counters();
    PRINT("  accumulated_read_error  = %u", p->accumulated_read_error);
    PRINT("  accumulated_write_error = %u", p->accumulated_write_error);
    PRINT("  kp                      = %u", p->kp);
    PRINT("  ki                      = %u", p->ki);
    PRINT("  scaling_factor          = %u", p->scaling_factor);
}

void print_Regulation_config(const struct Regulation_config *rc,
                             const char *message)
{
    PRINT("=== RegulationConfig ===", message);
    // print_VM(&rc->vm);
    // print_EWMA(&rc->ewma);
    // print_SW(&rc->sw);
    // print_AMBP(&rc->ambp);
    // print_AFC(&rc->afc);
    // print_LR(&rc->lr);
    // print_PIC(&rc->pic);
    PRINT("========================");
}

void reset_vm(cpuid_t vm_num)
{
    // VM
    reg_conf[vm_num].vm.depleated_op_type = UNKNOWN_VALUE;
    reg_conf[vm_num].vm.current_used_read_budget = 0;
    reg_conf[vm_num].vm.current_used_write_budget = 0;
    reg_conf[vm_num].vm.total_used_read_budget = 0;
    reg_conf[vm_num].vm.total_used_write_budget = 0;
    reg_conf[vm_num].vm.total_calculated_new_read_budget = 0;
    reg_conf[vm_num].vm.total_calculated_new_write_budget = 0;
    reg_conf[vm_num].vm.defined_pmu_read_val = 250000;
    reg_conf[vm_num].vm.defined_pmu_write_val = 250000;
    reg_conf[vm_num].vm.new_read_budget = 0;
    reg_conf[vm_num].vm.new_write_budget = 0;
}

void reset_budget_formulas(cpuid_t vm_num)
{
    // EWMA
    reg_conf[vm_num].ewma.previous_predicted_read_budget = 0;
    reg_conf[vm_num].ewma.previous_predicted_write_budget = 0;
    reg_conf[vm_num].ewma.new_read_budget = 0;
    reg_conf[vm_num].ewma.new_write_budget = 0;
    reg_conf[vm_num].ewma.alpha = 2;
    reg_conf[vm_num].ewma.scaling_factor = 10;

    // SW
    for (uint8_t i_sw = 0; i_sw < SW_MAX_ARRAY_SIZE; i_sw++) {
        reg_conf[vm_num].sw.read_usage[i_sw] = 0;
        reg_conf[vm_num].sw.write_usage[i_sw] = 0;
    }

    reg_conf[vm_num].sw.current_read_array_size = 0;
    reg_conf[vm_num].sw.current_write_array_size = 0;
    reg_conf[vm_num].sw.read_index = 0;
    reg_conf[vm_num].sw.write_index = 0;

    // AMBP
    reg_conf[vm_num].ambp.budget_read_limit = 100;
    reg_conf[vm_num].ambp.budget_write_limit = 100;
    reg_conf[vm_num].ambp.qnt_budget_read_limit_reached = 0;
    reg_conf[vm_num].ambp.qnt_budget_write_limit_reached = 0;
    reg_conf[vm_num].ambp.penalty_by_reaching_budget_read_limit = 0;
    reg_conf[vm_num].ambp.penalty_by_reaching_budget_write_limit = 0;
    reg_conf[vm_num].ambp.alpha = 2;
    reg_conf[vm_num].ambp.scaling_factor = 10;
    //
    // Default: 90%, representing a 10% penalty
    reg_conf[vm_num].ambp.penalty_factor = 90;

    // AFC
    reg_conf[vm_num].afc.previous_read_budget = 0;
    reg_conf[vm_num].afc.previous_write_budget = 0;
    reg_conf[vm_num].afc.proportional_gain = 2;
    reg_conf[vm_num].afc.scaling_factor = 10;

    // LR
    for (uint8_t i_lr = 0; i_lr < LR_MAX_QNT_ACCESS; i_lr++) {
        reg_conf[vm_num].lr.t_vector[i_lr] = i_lr;
        reg_conf[vm_num].lr.read_usage[i_lr] = 0;
        reg_conf[vm_num].lr.write_usage[i_lr] = 0;
        reg_conf[vm_num].lr.total_read_exec = 0;
        reg_conf[vm_num].lr.total_write_exec = 0;
    }
    reg_conf[vm_num].lr.current_read_array_size = 0;
    reg_conf[vm_num].lr.current_write_array_size = 0;
    // FIX: Initialize the new members
    reg_conf[vm_num].lr.previous_read_usage = 0;
    reg_conf[vm_num].lr.previous_write_usage = 0;

    // PIC
    reg_conf[vm_num].pic.accumulated_read_error = 0;
    reg_conf[vm_num].pic.accumulated_write_error = 0;
    reg_conf[vm_num].pic.kp = 2;
    reg_conf[vm_num].pic.ki = 1;
    reg_conf[vm_num].pic.scaling_factor = 10;
    // FIX: Initialize the new members
    reg_conf[vm_num].pic.previous_read_budget = 0;
    reg_conf[vm_num].pic.previous_write_budget = 0;
}

void init_regulation_config()
{
    for (uint8_t vm_num = 0; vm_num < VM_QNT; vm_num++) {
        reset_vm(vm_num);
        reset_budget_formulas(vm_num);
    }
}

inline static uint32_t get_operation_usage_v2(uint8_t pmu_index,
                                              uint32_t defined_budget,
                                              bool overflowed)
{
    PRINT("get_operation_usage_v2(pmu_index, defined_budget, overflowed)(%d, "
          "%d, %d)",
          pmu_index, defined_budget, overflowed);
    uint32_t pmu_counter = PMU_get_counter_value(pmu_index);
    uint32_t result = 0;

    if (overflowed) {
        // return the defined budget + leftover.
        // (since that what was used)
        result = defined_budget + pmu_counter;
    } else {
        // return the (partial) used budget.
        // the total was not met and there was no overflow
        result = defined_budget - (MAX_INT - pmu_counter);  // end - (start)
    }

    return result;
}

// ...
inline static uint32_t get_operation_usage(const uint8_t cpu_id,
                                           const uint8_t task_num,
                                           uint8_t op_type)
{
    uint32_t r_reg = 0;
    uint32_t w_reg = 0;
    uint32_t counter_t_a;
    uint32_t counter_t_b;
    counter_t_a = PMU_get_counter_value(0);
    counter_t_b = PMU_get_counter_value(1);
    r_reg = MAX_INT - counter_t_a;
    w_reg = MAX_INT - counter_t_b;
    counter_t_a = counter_t_b = 0;
    if (op_type == READ) {
        PRINT("get_operation_usage READ MAX_INT %d - r_reg %d == %d", MAX_INT,
              r_reg, MAX_INT - r_reg);
    } else {
        PRINT("get_operation_usage WRITE MAX_INT %d - w_reg %d == %d", MAX_INT,
              w_reg, MAX_INT - w_reg);
    }

    return op_type == READ ? (MAX_INT - r_reg) : (MAX_INT - w_reg);
}

inline static void ewma(const uint8_t cpu_id, const uint8_t _unused_)
{
    print_EWMA(&reg_conf[cpu_id].ewma, true);

    // printk("[BAO] ewma, cpu %d, task %d\n", cpu_id, task_num_);
    // PMU_print_all_counters();

    const uint32_t current_read_usage =
        get_operation_usage(cpu_id, UNUSED_ARG, READ);

    if (current_read_usage == 0) {
        PRINT("[BAO] current_read_usage == 0");
    }

    if (current_read_usage != 0 && current_read_usage < MARGIN) {
        PRINT("[BAO] OK current_read_usage != 0");
        reg_conf[cpu_id].vm.current_used_read_budget = current_read_usage;
        reg_conf[cpu_id].vm.total_used_read_budget += current_read_usage;
        reg_conf[cpu_id].ewma.previous_predicted_read_budget =
            reg_conf[cpu_id].ewma.new_read_budget;

        reg_conf[cpu_id].ewma.new_read_budget =
            (reg_conf[cpu_id].ewma.alpha * current_read_usage +
             ((reg_conf[cpu_id].ewma.scaling_factor -
               reg_conf[cpu_id].ewma.alpha) *
              reg_conf[cpu_id].ewma.previous_predicted_read_budget)) /
            reg_conf[cpu_id].ewma.scaling_factor;

        reg_conf[cpu_id].vm.new_read_budget =
            reg_conf[cpu_id].ewma.new_read_budget;
    }

    // WRITE
    const uint32_t current_write_usage =
        get_operation_usage(cpu_id, UNUSED_ARG, WRITE);

    if (current_write_usage == 0) {
        PRINT("[BAO] current_write_usage == 0");
    }

    if (current_write_usage != 0 && current_write_usage < MARGIN) {
        PRINT("[BAO] OK current_write_usage != 0");
        reg_conf[cpu_id].vm.current_used_write_budget = current_write_usage;
        reg_conf[cpu_id].vm.total_used_write_budget += current_write_usage;
        reg_conf[cpu_id].ewma.previous_predicted_write_budget =
            reg_conf[cpu_id].ewma.new_write_budget;

        reg_conf[cpu_id].ewma.new_write_budget =
            (reg_conf[cpu_id].ewma.alpha * current_write_usage +
             ((reg_conf[cpu_id].ewma.scaling_factor -
               reg_conf[cpu_id].ewma.alpha) *
              reg_conf[cpu_id].ewma.previous_predicted_write_budget)) /
            reg_conf[cpu_id].ewma.scaling_factor;

        reg_conf[cpu_id].vm.new_write_budget =
            reg_conf[cpu_id].ewma.new_write_budget;
    }

    print_EWMA(&reg_conf[cpu_id].ewma, false);
}

inline static void sw(const uint8_t cpu_id, const uint8_t task_num_)
{
    print_SW(&reg_conf[cpu_id].sw, true);

    // READ
    const uint32_t current_read_usage =
        get_operation_usage(cpu_id, UNUSED_ARG, READ);

    if (current_read_usage != 0 && current_read_usage < MARGIN) {
        // Insert the new usage into the circular buffer
        reg_conf[cpu_id].sw.read_usage[reg_conf[cpu_id].sw.read_index] =
            current_read_usage;
        reg_conf[cpu_id].sw.read_index =
            (reg_conf[cpu_id].sw.read_index + 1) % SW_MAX_ARRAY_SIZE;

        // Update the sample count (up to buffer size)
        if (reg_conf[cpu_id].sw.current_read_array_size < SW_MAX_ARRAY_SIZE)
            reg_conf[cpu_id].sw.current_read_array_size++;

        reg_conf[cpu_id].vm.current_used_read_budget = current_read_usage;

        // Only compute if enough samples exist
        if (reg_conf[cpu_id].sw.current_read_array_size >= SW_MAX_WINDOW_SIZE) {
            uint32_t lowest_avg = MAX_INT;

            // Total number of windows available
            uint8_t num_windows = reg_conf[cpu_id].sw.current_read_array_size -
                                  SW_MAX_WINDOW_SIZE + 1;

            for (uint8_t i = 0; i < num_windows; i++) {
                uint32_t sum = 0;

                for (uint8_t j = 0; j < SW_MAX_WINDOW_SIZE; j++) {
                    uint8_t index =
                        (reg_conf[cpu_id].sw.read_index + SW_MAX_ARRAY_SIZE +
                         i + j - reg_conf[cpu_id].sw.current_read_array_size) %
                        SW_MAX_ARRAY_SIZE;

                    sum += reg_conf[cpu_id].sw.read_usage[index];
                }

                const uint32_t avg =
                    (sum + (SW_MAX_WINDOW_SIZE / 2)) / SW_MAX_WINDOW_SIZE;
                reg_conf[cpu_id].vm.total_used_read_budget += avg;

                if (avg > 0 && avg < lowest_avg) lowest_avg = avg;
            }

            reg_conf[cpu_id].vm.new_read_budget = lowest_avg;
        }
    }

    /* const uint32_t current_read_usage = get_operation_usage(cpu_id, task_num,
     * READ); */

    /* if (current_read_usage != 0 && current_read_usage < MARGIN) */
    /* { */
    /* 	// Insert the new usage into the circular buffer */
    /* 	reg_conf[cpu_id].sw.read_usage[reg_conf[cpu_id].sw.read_index]
     * = current_read_usage; */
    /* 	reg_conf[cpu_id].sw.read_index =
     * (reg_conf[cpu_id].sw.read_index + 1) % SW_MAX_ARRAY_SIZE; */

    /* 	// Track the number of valid samples (max = SW_MAX_ARRAY_SIZE) */
    /* 	if (reg_conf[cpu_id].sw.current_read_array_size <
     * SW_MAX_ARRAY_SIZE) */
    /* 		reg_conf[cpu_id].sw.current_read_array_size++; */

    /* 	reg_conf[cpu_id].vm.current_used_read_budget =
     * current_read_usage; */

    /* 	// If buffer is full, compute sliding window averages */
    /* 	if (reg_conf[cpu_id].sw.current_read_array_size ==
     * SW_MAX_ARRAY_SIZE) */
    /* 	{ */
    /* 		uint32_t lowest_avg = MAX_INT; */

    /* 		// Loop through all possible windows */
    /* 		for (uint8_t i = 0; i <= (SW_MAX_ARRAY_SIZE -
     * SW_MAX_WINDOW_SIZE); i++) */
    /* 		{ */
    /* 			uint32_t sum = 0; */

    /* 			for (uint8_t j = 0; j < SW_MAX_WINDOW_SIZE; j++) */
    /* 			{ */
    /* 				// Circular buffer access */
    /* 				uint8_t index =
     * (reg_conf[cpu_id].sw.read_index + i + j) % SW_MAX_ARRAY_SIZE;
     */
    /* 				sum +=
     * reg_conf[cpu_id].sw.read_usage[index]; */
    /* 			} */

    /* 			const uint32_t avg = (sum + (SW_MAX_WINDOW_SIZE / 2)) /
     * SW_MAX_WINDOW_SIZE; */
    /* 			reg_conf[cpu_id].vm.total_used_read_budget +=
     * avg; */

    /* 			if (avg < lowest_avg && avg > 0) */
    /* 				lowest_avg = avg; */
    /* 		} */

    /* 		reg_conf[cpu_id].vm.new_read_budget = lowest_avg; */
    /* 	} */
    /* } */

    // ORIGINAL
    /* const uint8_t current_read_array_size =
     * reg_conf[cpu_id].sw.current_read_array_size; */
    /* const uint32_t current_read_usage = get_operation_usage(cpu_id, task_num,
     * READ); */

    /* // Fill the array of size SW_MAX_ARRAY_SIZE */
    /* if (current_read_array_size < SW_MAX_ARRAY_SIZE) */
    /* { */
    /* 	if (current_read_usage != 0 && current_read_usage < MARGIN) */
    /* 	{	 */
    /* 		reg_conf[cpu_id].sw.read_usage[current_read_array_size]
     * = current_read_usage; */
    /* 		reg_conf[cpu_id].vm.current_used_read_budget =
     * current_read_usage; */
    /* 		reg_conf[cpu_id].sw.current_read_array_size++; */
    /* 	} */
    /* } */
    /* else */
    /* { */
    /* 	// Sliding the window and calculating the average */
    /* 	uint32_t lowest_avg = MAX_INT; */

    /* 	for (uint8_t array = 0; array <= (SW_MAX_ARRAY_SIZE -
     * SW_MAX_WINDOW_SIZE); array++) */
    /* 	{ */
    /* 		uint32_t sum = 0; */

    /* 		for (uint8_t window = array; window < (array +
     * SW_MAX_WINDOW_SIZE); window++) */
    /* 			sum += reg_conf[cpu_id].sw.read_usage[window];
     */

    /* 		const uint32_t avg = (sum + (SW_MAX_WINDOW_SIZE / 2)) /
     * SW_MAX_WINDOW_SIZE; */
    /* 		reg_conf[cpu_id].vm.total_used_read_budget += avg; */

    /* 		if (avg > 0 && avg < lowest_avg) */
    /* 			lowest_avg = avg; */
    /* 	} */

    /* 	reg_conf[cpu_id].vm.new_read_budget = lowest_avg; */
    /* 	reg_conf[cpu_id].sw.current_read_array_size = 0; */
    /* } */

    // WRITE
    const uint32_t current_write_usage =
        get_operation_usage(cpu_id, UNUSED_ARG, WRITE);

    if (current_write_usage != 0 && current_write_usage < MARGIN) {
        // Insert the new usage into the circular buffer
        reg_conf[cpu_id].sw.write_usage[reg_conf[cpu_id].sw.write_index] =
            current_write_usage;
        reg_conf[cpu_id].sw.write_index =
            (reg_conf[cpu_id].sw.write_index + 1) % SW_MAX_ARRAY_SIZE;

        // Update the sample count (up to buffer size)
        if (reg_conf[cpu_id].sw.current_write_array_size < SW_MAX_ARRAY_SIZE)
            reg_conf[cpu_id].sw.current_write_array_size++;

        reg_conf[cpu_id].vm.current_used_write_budget = current_write_usage;

        // Only compute if enough samples exist
        if (reg_conf[cpu_id].sw.current_write_array_size >=
            SW_MAX_WINDOW_SIZE) {
            uint32_t lowest_avg = MAX_INT;

            // Total number of windows available
            uint8_t num_windows = reg_conf[cpu_id].sw.current_write_array_size -
                                  SW_MAX_WINDOW_SIZE + 1;

            for (uint8_t i = 0; i < num_windows; i++) {
                uint32_t sum = 0;

                for (uint8_t j = 0; j < SW_MAX_WINDOW_SIZE; j++) {
                    uint8_t index =
                        (reg_conf[cpu_id].sw.write_index + SW_MAX_ARRAY_SIZE +
                         i + j - reg_conf[cpu_id].sw.current_write_array_size) %
                        SW_MAX_ARRAY_SIZE;

                    sum += reg_conf[cpu_id].sw.write_usage[index];
                }

                const uint32_t avg =
                    (sum + (SW_MAX_WINDOW_SIZE / 2)) / SW_MAX_WINDOW_SIZE;
                reg_conf[cpu_id].vm.total_used_write_budget += avg;

                if (avg > 0 && avg < lowest_avg) lowest_avg = avg;
            }

            reg_conf[cpu_id].vm.new_write_budget = lowest_avg;
        }
    }
    /* const uint32_t current_write_usage = get_operation_usage(cpu_id,
     * task_num, WRITE); */

    /* if (current_write_usage != 0 && current_write_usage < MARGIN) */
    /* { */
    /* 	// Insert the new usage into the circular buffer */
    /* 	reg_conf[cpu_id].sw.write_usage[reg_conf[cpu_id].sw.write_index]
     * = current_write_usage; */
    /* 	reg_conf[cpu_id].sw.write_index =
     * (reg_conf[cpu_id].sw.write_index + 1) % SW_MAX_ARRAY_SIZE; */

    /* 	// Track the number of valid samples (max = SW_MAX_ARRAY_SIZE) */
    /* 	if (reg_conf[cpu_id].sw.current_write_array_size <
     * SW_MAX_ARRAY_SIZE) */
    /* 		reg_conf[cpu_id].sw.current_write_array_size++; */

    /* 	reg_conf[cpu_id].vm.current_used_write_budget =
     * current_write_usage; */

    /* 	// If buffer is full, compute sliding window averages */
    /* 	if (reg_conf[cpu_id].sw.current_write_array_size ==
     * SW_MAX_ARRAY_SIZE) */
    /* 	{ */
    /* 		uint32_t lowest_avg = MAX_INT; */

    /* 		// Loop through all possible windows */
    /* 		for (uint8_t i = 0; i <= (SW_MAX_ARRAY_SIZE -
     * SW_MAX_WINDOW_SIZE); i++) */
    /* 		{ */
    /* 			uint32_t sum = 0; */

    /* 			for (uint8_t j = 0; j < SW_MAX_WINDOW_SIZE; j++) */
    /* 			{ */
    /* 				// Circular buffer access */
    /* 				uint8_t index =
     * (reg_conf[cpu_id].sw.write_index + i + j) % SW_MAX_ARRAY_SIZE;
     */
    /* 				sum +=
     * reg_conf[cpu_id].sw.write_usage[index]; */
    /* 			} */

    /* 			const uint32_t avg = (sum + (SW_MAX_WINDOW_SIZE / 2)) /
     * SW_MAX_WINDOW_SIZE; */
    /* 			reg_conf[cpu_id].vm.total_used_write_budget +=
     * avg; */

    /* 			if (avg < lowest_avg && avg > 0) */
    /* 				lowest_avg = avg; */
    /* 		} */

    /* 		reg_conf[cpu_id].vm.new_write_budget = lowest_avg; */
    /* 	} */
    /* } */

    // ORIGINAL
    /* const uint8_t current_write_array_size =
     * reg_conf[cpu_id].sw.current_write_array_size; */
    /* const uint32_t current_write_usage = get_operation_usage(cpu_id,
     * task_num, WRITE); */

    /* // Fill the array of size SW_MAX_ARRAY_SIZE */
    /* if (current_write_array_size < SW_MAX_ARRAY_SIZE) */
    /* { */
    /* 	if (current_write_usage != 0 && current_write_usage < MARGIN) */
    /* 	{	 */
    /* 		reg_conf[cpu_id].sw.write_usage[current_write_array_size]
     * = current_write_usage; */
    /* 		reg_conf[cpu_id].vm.current_used_write_budget =
     * current_write_usage; */
    /* 		reg_conf[cpu_id].sw.current_write_array_size++; */
    /* 	} */
    /* } */
    /* else */
    /* { */
    /* 	// Sliding the window and calculating the average */
    /* 	uint32_t lowest_avg = MAX_INT; */

    /* 	for (uint8_t array = 0; array <= (SW_MAX_ARRAY_SIZE -
     * SW_MAX_WINDOW_SIZE); array++) */
    /* 	{ */
    /* 		uint32_t sum = 0; */

    /* 		for (uint8_t window = array; window < (array +
     * SW_MAX_WINDOW_SIZE); window++) */
    /* 			sum +=
     * reg_conf[cpu_id].sw.write_usage[window]; */

    /* 		const uint32_t avg = (sum + (SW_MAX_WINDOW_SIZE / 2)) /
     * SW_MAX_WINDOW_SIZE; */
    /* 		reg_conf[cpu_id].vm.total_used_write_budget += avg; */

    /* 		if (avg > 0 && avg < lowest_avg) */
    /* 			lowest_avg = avg; */
    /* 	} */

    /* 	reg_conf[cpu_id].vm.new_write_budget = lowest_avg; */
    /* 	reg_conf[cpu_id].sw.current_write_array_size = 0; */
    /* } */

    print_SW(&reg_conf[cpu_id].sw, false);
}

inline static void ambp(const uint8_t cpu_id, const uint8_t task_num)
{
    print_AMBP(&reg_conf[cpu_id].ambp, true);

    // READ
    const uint32_t current_read_usage =
        get_operation_usage(cpu_id, task_num, READ);
    if (current_read_usage != 0 && current_read_usage < MARGIN) {
        reg_conf[cpu_id].vm.total_used_read_budget += current_read_usage;
        reg_conf[cpu_id].vm.current_used_read_budget = current_read_usage;

        if (current_read_usage > reg_conf[cpu_id].ambp.budget_read_limit) {
            reg_conf[cpu_id].ambp.qnt_budget_read_limit_reached++;

            // Update penalty
            reg_conf[cpu_id].ambp.penalty_by_reaching_budget_read_limit *=
                reg_conf[cpu_id].ambp.qnt_budget_read_limit_reached;

            // Calculate the new budget_read_limit using integer arithmetic
            reg_conf[cpu_id].ambp.budget_read_limit =
                reg_conf[cpu_id].ambp.budget_read_limit +
                (reg_conf[cpu_id].ambp.alpha *
                 (current_read_usage -
                  reg_conf[cpu_id].ambp.budget_read_limit)) /
                    reg_conf[cpu_id].ambp.scaling_factor -
                reg_conf[cpu_id].ambp.penalty_by_reaching_budget_read_limit;

            reg_conf[cpu_id].vm.new_read_budget =
                reg_conf[cpu_id].ambp.budget_read_limit;
        } else {
            // Decrease the budget
            reg_conf[cpu_id].ambp.qnt_budget_read_limit_reached = 0;
            reg_conf[cpu_id].vm.new_read_budget =
                (950 * reg_conf[cpu_id].ambp.budget_read_limit +
                 50 * current_read_usage) /
                reg_conf[cpu_id].ambp.scaling_factor;
        }
    }

    // WRITE
    const uint32_t current_write_usage =
        get_operation_usage(cpu_id, task_num, WRITE);
    if (current_write_usage != 0 && current_write_usage < MARGIN) {
        reg_conf[cpu_id].vm.total_used_write_budget += current_write_usage;
        reg_conf[cpu_id].vm.current_used_write_budget = current_write_usage;
        if (current_write_usage > reg_conf[cpu_id].ambp.budget_write_limit) {
            reg_conf[cpu_id].ambp.qnt_budget_write_limit_reached++;

            // Update penalty
            reg_conf[cpu_id].ambp.penalty_by_reaching_budget_write_limit *=
                reg_conf[cpu_id].ambp.qnt_budget_write_limit_reached;

            // Calculate the new budget_write_limit using integer arithmetic
            reg_conf[cpu_id].ambp.budget_write_limit =
                reg_conf[cpu_id].ambp.budget_write_limit +
                (reg_conf[cpu_id].ambp.alpha *
                 (current_write_usage -
                  reg_conf[cpu_id].ambp.budget_write_limit)) /
                    reg_conf[cpu_id].ambp.scaling_factor -
                reg_conf[cpu_id].ambp.penalty_by_reaching_budget_write_limit;

            reg_conf[cpu_id].vm.new_write_budget =
                reg_conf[cpu_id].ambp.budget_write_limit;
        } else {
            // Decrease the budget
            reg_conf[cpu_id].ambp.qnt_budget_write_limit_reached = 0;
            reg_conf[cpu_id].vm.new_write_budget =
                (950 * reg_conf[cpu_id].ambp.budget_write_limit +
                 50 * current_write_usage) /
                reg_conf[cpu_id].ambp.scaling_factor;
        }
    }

    print_AMBP(&reg_conf[cpu_id].ambp, false);
}

inline static void afc(const uint8_t cpu_id, const uint8_t task_num)
{
    print_AFC(&reg_conf[cpu_id].afc, true);

    // READ
    const uint32_t current_read_usage =
        get_operation_usage(cpu_id, task_num, READ);
    if (current_read_usage != 0 && current_read_usage < MARGIN) {
        reg_conf[cpu_id].vm.total_used_read_budget += current_read_usage;
        reg_conf[cpu_id].vm.current_used_read_budget = current_read_usage;
        const int32_t read_error =
            current_read_usage - reg_conf[cpu_id].afc.previous_read_budget;

        const uint32_t new_read_budget =
            reg_conf[cpu_id].afc.previous_read_budget +
            ((reg_conf[cpu_id].afc.proportional_gain * read_error)) /
                reg_conf[cpu_id].afc.scaling_factor;

        reg_conf[cpu_id].afc.previous_read_budget = new_read_budget;
        reg_conf[cpu_id].vm.new_read_budget = new_read_budget;
    }

    // WRITE
    const uint32_t current_write_usage =
        get_operation_usage(cpu_id, task_num, WRITE);
    if (current_write_usage != 0 && current_write_usage < MARGIN) {
        reg_conf[cpu_id].vm.total_used_write_budget += current_write_usage;
        reg_conf[cpu_id].vm.current_used_write_budget = current_write_usage;

        const int32_t write_error =
            current_write_usage - reg_conf[cpu_id].afc.previous_write_budget;

        const uint32_t new_write_budget =
            reg_conf[cpu_id].afc.previous_write_budget +
            ((reg_conf[cpu_id].afc.proportional_gain * write_error)) /
                reg_conf[cpu_id].afc.scaling_factor;

        reg_conf[cpu_id].afc.previous_write_budget = new_write_budget;
        reg_conf[cpu_id].vm.new_write_budget = new_write_budget;
    }

    print_AFC(&reg_conf[cpu_id].afc, false);
}

// <not implemented>
inline static void lr(const uint8_t cpu_id, const uint8_t task_num)
{
    print_LR(&reg_conf[cpu_id].lr, true);

    uint32_t r = 0, w = 0;

    // READ
    const uint32_t current_read_usage =
        get_operation_usage(cpu_id, task_num, READ);

    if (current_read_usage != 0 && current_read_usage < MARGIN) {
        const uint8_t current_read_array_size =
            reg_conf[cpu_id].lr.current_read_array_size;
        if (current_read_array_size < LR_MAX_QNT_ACCESS) {
            reg_conf[cpu_id].lr.read_usage[current_read_array_size] =
                current_read_usage;
            reg_conf[cpu_id].lr.current_read_array_size++;
            reg_conf[cpu_id].vm.current_used_read_budget = current_read_usage;
        }
    }

    if (r && w) {
        for (uint8_t i = 0; i < LR_MAX_QNT_ACCESS; i++)
            reg_conf[cpu_id].lr.t_vector[i] += 1;
    }

    print_LR(&reg_conf[cpu_id].lr, false);
}

inline static void pic(const uint8_t cpu_id, const uint8_t task_num)
{
    print_PIC(&reg_conf[cpu_id].pic, true);

    // READ
    const uint32_t current_read_usage =
        get_operation_usage(cpu_id, task_num, READ);
    PRINT("(CURRENT READ USAGE) %u", current_read_usage);
    if (current_read_usage != 0 && current_read_usage < MARGIN) {
        const uint32_t read_error = MAX_INT - current_read_usage;
        PRINT("(READ ERROR) %u", read_error);
        reg_conf[cpu_id].pic.accumulated_read_error += read_error;
        reg_conf[cpu_id].vm.current_used_read_budget = current_read_usage;
        reg_conf[cpu_id].vm.total_used_read_budget += current_read_usage;

        uint32_t read_adjust = ((reg_conf[cpu_id].pic.kp * read_error) +
                                (reg_conf[cpu_id].pic.ki *
                                 reg_conf[cpu_id].pic.accumulated_read_error)) /
                               reg_conf[cpu_id].pic.scaling_factor;

        reg_conf[cpu_id].vm.new_read_budget = read_error + read_adjust;
    }

    // WRITE
    const uint32_t current_write_usage =
        get_operation_usage(cpu_id, task_num, WRITE);
    PRINT("(CURRENT WRITE USAGE) %u", current_write_usage);
    if (current_write_usage != 0 && current_write_usage < MARGIN) {
        uint32_t write_error = MAX_INT - current_write_usage;
        reg_conf[cpu_id].pic.accumulated_write_error += write_error;
        reg_conf[cpu_id].vm.current_used_write_budget = current_write_usage;
        reg_conf[cpu_id].vm.total_used_write_budget += current_write_usage;

        uint32_t write_adjust =
            ((reg_conf[cpu_id].pic.kp * write_error) +
             (reg_conf[cpu_id].pic.ki *
              reg_conf[cpu_id].pic.accumulated_write_error)) /
            reg_conf[cpu_id].pic.scaling_factor;

        reg_conf[cpu_id].vm.new_write_budget = write_error + write_adjust;
    }

    print_PIC(&reg_conf[cpu_id].pic, false);
}

//////////////

/**
 * @brief  Calculates the new EWMA value based on the current and previous
 * states.
 * @param  current_usage    The latest measured value.
 * @param  prev_prediction  The prediction from the previous time step.
 * @param  alpha            The weight given to the current value (smoothing
 * factor numerator).
 * @param  scaling_factor   The denominator for the smoothing factor.
 * @return The newly calculated EWMA prediction.
 */
static inline uint32_t calculate_ewma(const uint32_t current_usage,
                                      const uint32_t prev_prediction,
                                      const uint16_t alpha,
                                      const uint16_t scaling_factor)
{
    // --- Safety Check ---
    // Prevents a division-by-zero crash if the scaling_factor is misconfigured.
    if (scaling_factor == 0) {
        // Log this as a critical error in a real system.
        // Returning the previous prediction is a safe fallback.
        printk("\t\tinvalid usage of calculate_ewma, null scaling_factor\n");
        return prev_prediction;
    }

    // --- The EWMA Formula ---
    // NewPrediction = β * CurrentValue + (1 - β) * PreviousPrediction
    // where β = alpha / scaling_factor
    // The calculation uses 64-bit integers to prevent overflow before the final
    // division.
    return (uint32_t)(((uint64_t)alpha * current_usage +
                       (uint64_t)(scaling_factor - alpha) * prev_prediction) /
                      scaling_factor);
}

/**
 * @brief  Calculates the next EWMA budget based on provided usage values.
 *
 * This function is a pure calculation engine. It is the caller's
 * responsibility to provide the most accurate usage data for the period.
 *
 * @param  cpu_id              The CPU identifier for the configuration.
 * @param  actual_read_usage   The actual read usage for the completed period.
 * @param  actual_write_usage  The actual write usage for the completed period.
 */
void ewma_budget_v2(const uint32_t cpu_id, const uint32_t actual_read_usage,
                    const uint32_t actual_write_usage)
{
    struct VM *vm_conf = &reg_conf[cpu_id].vm;
    struct EWMA *ewma_conf = &reg_conf[cpu_id].ewma;

    print_EWMA(&reg_conf[cpu_id].ewma, true);

    // --- READ: Update stats and calculate next budget ---
    vm_conf->current_used_read_budget = actual_read_usage;
    vm_conf->total_used_read_budget += actual_read_usage;
    ewma_conf->previous_predicted_read_budget = ewma_conf->new_read_budget;
    ewma_conf->new_read_budget = calculate_ewma(
        (actual_read_usage < MARGIN) ? actual_read_usage : MARGIN,
        ewma_conf->previous_predicted_read_budget, ewma_conf->alpha,
        ewma_conf->scaling_factor);
    vm_conf->new_read_budget = ewma_conf->new_read_budget;
    // (FIX) Add update for total allocated budget statistic
    vm_conf->total_calculated_new_read_budget += vm_conf->new_read_budget;

    // --- WRITE: Update stats and calculate next budget ---
    vm_conf->current_used_write_budget = actual_write_usage;
    vm_conf->total_used_write_budget += actual_write_usage;
    ewma_conf->previous_predicted_write_budget = ewma_conf->new_write_budget;
    ewma_conf->new_write_budget = calculate_ewma(
        (actual_write_usage < MARGIN) ? actual_write_usage : MARGIN,
        ewma_conf->previous_predicted_write_budget, ewma_conf->alpha,
        ewma_conf->scaling_factor);
    vm_conf->new_write_budget = ewma_conf->new_write_budget;
    // (FIX) Add update for total allocated budget statistic
    vm_conf->total_calculated_new_write_budget += vm_conf->new_write_budget;

    print_EWMA(&reg_conf[cpu_id].ewma, false);
}

/**
 * @brief Calculates the next memory budget using a sliding window average.
 *
 * This function implements the "Average of Last Window" strategy. It maintains
 * a history of recent memory usage in a circular buffer. The new budget is set
 * to the simple average of the last 'SW_MAX_WINDOW_SIZE' periods. This provides
 * a balance of stability and responsiveness.
 *
 * This version has been updated to calculate a new budget on every call.
 * During the initial phase when the history buffer is not yet full, it will
 * average the number of samples currently available.
 *
 * @param cpu_id The ID of the CPU core for which the budget is being
 * calculated.
 * @param actual_read_usage The measured memory read operations for the last
 * period.
 * @param actual_write_usage The measured memory write operations for the last
 * period.
 */
inline static void sw_budget_v2(const uint8_t cpu_id,
                                const uint32_t actual_read_usage,
                                const uint32_t actual_write_usage)
{
    // Get pointers to the relevant configuration structs for cleaner code
    struct VM *vm_conf = &reg_conf[cpu_id].vm;
    struct SW *sw_conf = &reg_conf[cpu_id].sw;

    print_SW(sw_conf, true);

    // --- READ BUDGET CALCULATION ---

    // Update VM statistics with the actual measured usage for this period.
    vm_conf->current_used_read_budget = actual_read_usage;
    vm_conf->total_used_read_budget += actual_read_usage;

    // Add the new usage data to our historical circular buffer.
    sw_conf->read_usage[sw_conf->read_index] = actual_read_usage;
    sw_conf->read_index = (sw_conf->read_index + 1) % SW_MAX_ARRAY_SIZE;

    // Increment the count of historical samples, up to the maximum buffer size.
    if (sw_conf->current_read_array_size < SW_MAX_ARRAY_SIZE) {
        sw_conf->current_read_array_size++;
    }

    // NEW LOGIC: Determine how many samples to average. This ensures we always
    // calculate a budget, even before the window is full.
    uint8_t read_samples_to_average =
        (sw_conf->current_read_array_size < SW_MAX_WINDOW_SIZE)
            ? sw_conf->current_read_array_size
            : SW_MAX_WINDOW_SIZE;

    // Always calculate a new budget if we have at least one sample.
    if (read_samples_to_average > 0) {
        uint64_t sum_of_window = 0;

        // Calculate the sum of the last 'read_samples_to_average' samples.
        for (uint8_t i = 0; i < read_samples_to_average; i++) {
            uint16_t index =
                (sw_conf->read_index - (i + 1) + SW_MAX_ARRAY_SIZE) %
                SW_MAX_ARRAY_SIZE;
            sum_of_window += sw_conf->read_usage[index];
        }

        // Calculate the average and set it as the new budget.
        vm_conf->new_read_budget =
            (sum_of_window + (read_samples_to_average / 2)) /
            read_samples_to_average;
    }

    // --- WRITE BUDGET CALCULATION ---

    vm_conf->current_used_write_budget = actual_write_usage;
    vm_conf->total_used_write_budget += actual_write_usage;

    sw_conf->write_usage[sw_conf->write_index] = actual_write_usage;
    sw_conf->write_index = (sw_conf->write_index + 1) % SW_MAX_ARRAY_SIZE;

    if (sw_conf->current_write_array_size < SW_MAX_ARRAY_SIZE) {
        sw_conf->current_write_array_size++;
    }

    // NEW LOGIC: Determine how many samples to average for the write budget.
    uint8_t write_samples_to_average =
        (sw_conf->current_write_array_size < SW_MAX_WINDOW_SIZE)
            ? sw_conf->current_write_array_size
            : SW_MAX_WINDOW_SIZE;

    if (write_samples_to_average > 0) {
        uint64_t sum_of_window = 0;

        for (uint8_t i = 0; i < write_samples_to_average; i++) {
            uint16_t index =
                (sw_conf->write_index - (i + 1) + SW_MAX_ARRAY_SIZE) %
                SW_MAX_ARRAY_SIZE;
            sum_of_window += sw_conf->write_usage[index];
        }

        vm_conf->new_write_budget =
            (sum_of_window + (write_samples_to_average / 2)) /
            write_samples_to_average;
    }

    // Update total allocated budget statistic. This is now safe because a new
    // budget is calculated on every call (assuming at least one sample exists).
    vm_conf->total_calculated_new_read_budget += vm_conf->new_read_budget;
    vm_conf->total_calculated_new_write_budget += vm_conf->new_write_budget;

    print_SW(sw_conf, false);
}

// ================================================================================
//  Budget Formula Implementations (Corrected)
// ================================================================================

/**
 * @brief Adaptive Budget with Penalty (AMBP) v2 (Corrected)
 */
inline static void ambp_budget_v2(const uint8_t cpu_id,
                                  const uint32_t actual_read_usage,
                                  const uint32_t actual_write_usage)
{
    struct VM *vm_conf = &reg_conf[cpu_id].vm;
    struct AMBP *ambp_conf = &reg_conf[cpu_id].ambp;

    print_AMBP(ambp_conf, true);

    // --- READ BUDGET CALCULATION ---
    vm_conf->current_used_read_budget = actual_read_usage;
    vm_conf->total_used_read_budget += actual_read_usage;

    if (actual_read_usage > ambp_conf->budget_read_limit) {
        uint32_t new_limit =
            ambp_conf->budget_read_limit +
            (ambp_conf->alpha *
             (actual_read_usage - ambp_conf->budget_read_limit)) /
                ambp_conf->scaling_factor;
        ambp_conf->budget_read_limit =
            (new_limit * ambp_conf->penalty_factor) / 100;
    } else {
        ambp_conf->budget_read_limit =
            ((950 * ambp_conf->budget_read_limit) + (50 * actual_read_usage)) /
            1000;
    }
    vm_conf->new_read_budget = ambp_conf->budget_read_limit;

    // --- WRITE BUDGET CALCULATION ---
    vm_conf->current_used_write_budget = actual_write_usage;
    vm_conf->total_used_write_budget += actual_write_usage;

    if (actual_write_usage > ambp_conf->budget_write_limit) {
        uint32_t new_limit =
            ambp_conf->budget_write_limit +
            (ambp_conf->alpha *
             (actual_write_usage - ambp_conf->budget_write_limit)) /
                ambp_conf->scaling_factor;
        ambp_conf->budget_write_limit =
            (new_limit * ambp_conf->penalty_factor) / 100;
    } else {
        ambp_conf->budget_write_limit = ((950 * ambp_conf->budget_write_limit) +
                                         (50 * actual_write_usage)) /
                                        1000;
    }
    vm_conf->new_write_budget = ambp_conf->budget_write_limit;

    vm_conf->total_calculated_new_read_budget += vm_conf->new_read_budget;
    vm_conf->total_calculated_new_write_budget += vm_conf->new_write_budget;

    print_AMBP(ambp_conf, false);
}

/**
 * @brief Proportional Control (AFC) v2 (No bugs found)
 */
inline static void afc_budget_v2(const uint8_t cpu_id,
                                 const uint32_t actual_read_usage,
                                 const uint32_t actual_write_usage)
{
    struct VM *vm_conf = &reg_conf[cpu_id].vm;
    struct AFC *afc_conf = &reg_conf[cpu_id].afc;

    print_AFC(afc_conf, true);

    // --- READ BUDGET CALCULATION ---
    vm_conf->current_used_read_budget = actual_read_usage;
    vm_conf->total_used_read_budget += actual_read_usage;

    const int32_t read_error =
        actual_read_usage - afc_conf->previous_read_budget;
    const uint32_t new_read_budget =
        afc_conf->previous_read_budget +
        (afc_conf->proportional_gain * read_error) / afc_conf->scaling_factor;

    afc_conf->previous_read_budget = new_read_budget;
    vm_conf->new_read_budget = new_read_budget;

    // --- WRITE BUDGET CALCULATION ---
    vm_conf->current_used_write_budget = actual_write_usage;
    vm_conf->total_used_write_budget += actual_write_usage;

    const int32_t write_error =
        actual_write_usage - afc_conf->previous_write_budget;
    const uint32_t new_write_budget =
        afc_conf->previous_write_budget +
        (afc_conf->proportional_gain * write_error) / afc_conf->scaling_factor;

    afc_conf->previous_write_budget = new_write_budget;
    vm_conf->new_write_budget = new_write_budget;

    vm_conf->total_calculated_new_read_budget += vm_conf->new_read_budget;
    vm_conf->total_calculated_new_write_budget += vm_conf->new_write_budget;

    print_AFC(afc_conf, false);
}

/**
 * @brief Linear Regression (LR) v2 - Simplified (Corrected)
 */
inline static void lr_budget_v2(const uint8_t cpu_id,
                                const uint32_t actual_read_usage,
                                const uint32_t actual_write_usage)
{
    struct VM *vm_conf = &reg_conf[cpu_id].vm;
    struct LR *lr_conf = &reg_conf[cpu_id].lr;

    print_LR(lr_conf, true);

    // --- READ BUDGET CALCULATION ---
    vm_conf->current_used_read_budget = actual_read_usage;
    vm_conf->total_used_read_budget += actual_read_usage;

    int32_t read_trend = actual_read_usage - lr_conf->previous_read_usage;
    // Dampen the trend by half to prevent instability and overflow.
    uint32_t new_read_budget = actual_read_usage + (read_trend / 2);

    lr_conf->previous_read_usage = actual_read_usage;
    vm_conf->new_read_budget = new_read_budget;

    // --- WRITE BUDGET CALCULATION ---
    vm_conf->current_used_write_budget = actual_write_usage;
    vm_conf->total_used_write_budget += actual_write_usage;

    int32_t write_trend = actual_write_usage - lr_conf->previous_write_usage;
    // Dampen the trend.
    uint32_t new_write_budget = actual_write_usage + (write_trend / 2);

    lr_conf->previous_write_usage = actual_write_usage;
    vm_conf->new_write_budget = new_write_budget;

    vm_conf->total_calculated_new_read_budget += vm_conf->new_read_budget;
    vm_conf->total_calculated_new_write_budget += vm_conf->new_write_budget;

    print_LR(lr_conf, false);
}

/**
 * @brief Proportional-Integral Controller (PIC) v2 (Corrected)
 */
#define MAX_ACCUMULATED_ERROR 5000000  // Example value, tune as needed
#define MIN_ACCUMULATED_ERROR -5000000

inline static void pic_budget_v2(const uint8_t cpu_id,
                                 const uint32_t actual_read_usage,
                                 const uint32_t actual_write_usage)
{
    struct VM *vm_conf = &reg_conf[cpu_id].vm;
    struct PIC *pic_conf = &reg_conf[cpu_id].pic;

    print_PIC(pic_conf, true);

    // --- READ BUDGET CALCULATION ---
    vm_conf->current_used_read_budget = actual_read_usage;
    vm_conf->total_used_read_budget += actual_read_usage;

    const int32_t read_error =
        actual_read_usage - pic_conf->previous_read_budget;
    pic_conf->accumulated_read_error += read_error;

    // Clamp the accumulated error to prevent integral windup.
    if (pic_conf->accumulated_read_error > MAX_ACCUMULATED_ERROR) {
        pic_conf->accumulated_read_error = MAX_ACCUMULATED_ERROR;
    } else if (pic_conf->accumulated_read_error < MIN_ACCUMULATED_ERROR) {
        pic_conf->accumulated_read_error = MIN_ACCUMULATED_ERROR;
    }

    const int32_t read_adjust =
        (pic_conf->kp * read_error +
         pic_conf->ki * pic_conf->accumulated_read_error) /
        pic_conf->scaling_factor;

    const uint32_t new_read_budget =
        pic_conf->previous_read_budget + read_adjust;
    pic_conf->previous_read_budget = new_read_budget;
    vm_conf->new_read_budget = new_read_budget;

    // --- WRITE BUDGET CALCULATION ---
    vm_conf->current_used_write_budget = actual_write_usage;
    vm_conf->total_used_write_budget += actual_write_usage;

    const int32_t write_error =
        actual_write_usage - pic_conf->previous_write_budget;
    pic_conf->accumulated_write_error += write_error;

    // Clamp the accumulated error.
    if (pic_conf->accumulated_write_error > MAX_ACCUMULATED_ERROR) {
        pic_conf->accumulated_write_error = MAX_ACCUMULATED_ERROR;
    } else if (pic_conf->accumulated_write_error < MIN_ACCUMULATED_ERROR) {
        pic_conf->accumulated_write_error = MIN_ACCUMULATED_ERROR;
    }

    const int32_t write_adjust =
        (pic_conf->kp * write_error +
         pic_conf->ki * pic_conf->accumulated_write_error) /
        pic_conf->scaling_factor;

    const uint32_t new_write_budget =
        pic_conf->previous_write_budget + write_adjust;
    pic_conf->previous_write_budget = new_write_budget;
    vm_conf->new_write_budget = new_write_budget;

    vm_conf->total_calculated_new_read_budget += vm_conf->new_read_budget;
    vm_conf->total_calculated_new_write_budget += vm_conf->new_write_budget;

    print_PIC(pic_conf, false);
}

//////////////

void print_counters(bool before)
{
    PMU_print_all_counters(before ? "BEFORE" : "AFTER");
}

void print_bool_array(const bool arr[], int size)
{
    PRINT("Boolean Array State:");
    for (int i = 0; i < size; i++) {
        // Use %s for the string and the ternary operator to choose the output
        PRINT("  Flag[%d] = %s", i, arr[i] ? "true" : "false");
    }
}

/**
 * @brief  Populates a boolean array based on the bits set in an integer mask.
 *
 * This function iterates from bit 0 to 'size - 1' of the input bitmask.
 * For each position 'i', it sets arr[i] to true if the bit is set,
 * and false otherwise.
 *
 * @param  bitmask The input integer to read the bits from.
 * @param  arr     The output boolean array to populate.
 * @param  size    The number of bits/array elements to process.
 */
// void convert_bitmask_to_array(uint8_t bitmask, bool arr[], int size)
// {
//     print_bool_array(arr, size);
//
//     for (int i = 0; i < size; i++) {
//         // Check if the i-th bit is set in the bitmask.
//         if (bitmask & (1U << i)) {
//             arr[i] = true;
//         } else {
//             arr[i] = false;
//         }
//     }
//
//     print_bool_array(arr, size);
// }

// void reset_state_on_new_formula(formula_t const formula)
// {
//     // HACK:
//     static int last_formula = -1;
//     if (last_formula != formula) {
//         last_formula = formula;
//         reset_vm(cpu()->id);
//         reset_budget_formulas(cpu()->id);
//         PRINT("CHANGED FORMULA, NULL-oed VM struct");
//     }
// }

// void regulator_budget_depleted(const uint8_t pmu_id, formula_t formula)
// {
//     PRINT("regulator_budget_depleted\t formula %d", formula);
//     print_VM(&reg_conf[cpu()->id].vm, true);
//     print_counters(true);

//     reg_conf[cpu()->id].vm.cycles = PMU_get_counter_value(2);
//     reg_conf[cpu()->id].vm.instructions = PMU_get_counter_value(3);
//     reg_conf[cpu()->id].vm.cache_misses = PMU_get_counter_value(4);
//     reg_conf[cpu()->id].vm.mispredicts = PMU_get_counter_value(5);

//     reset_state_on_new_formula(formula);

//     cpuid_t cpu_id = cpu()->id;
//     bool new_read = (pmu_id == READ);
//     bool new_write = (pmu_id == WRITE);

//     // This part is now correct
//     uint32_t actual_read_usage = get_operation_usage_v2(
//         READ, reg_conf[cpu_id].vm.defined_pmu_read_val, new_read);
//     uint32_t actual_write_usage = get_operation_usage_v2(
//         WRITE, reg_conf[cpu_id].vm.defined_pmu_write_val, new_write);

//     switch (formula) {
//         case EWMA_FORMULA:
//             ewma(cpu_id, UNUSED_ARG);
//             break;
//         case EWMA_V2_FORMULA:
//             ewma_budget_v2(cpu_id, actual_read_usage, actual_write_usage);
//             break;
//         case SW_FORMULA:
//             sw(cpu_id, UNUSED_ARG);
//             break;
//         case SW_V2_FORMULA:
//             sw_budget_v2(cpu_id, actual_read_usage, actual_write_usage);
//             break;
//         case AFC_FORMULA:
//             afc(cpu_id, UNUSED_ARG);
//             break;
//         case AFC_V2_FORMULA:
//             afc_budget_v2(cpu_id, actual_read_usage, actual_write_usage);
//             break;
//         case AMBP_FORMULA:
//             ambp(cpu()->id, UNUSED_ARG);
//             break;
//         case AMBP_V2_FORMULA:
//             ambp_budget_v2(cpu_id, actual_read_usage, actual_write_usage);
//             break;
//         // case LR_FORMULA:
//         //     lr(cpu()->id, UNUSED_ARG);
//         //     break;
//         case LR_V2_FORMULA:
//             lr_budget_v2(cpu_id, actual_read_usage, actual_write_usage);
//             break;
//         case PIC_FORMULA:
//             pic(cpu()->id, UNUSED_ARG);
//             break;
//         case PIC_V2_FORMULA:
//             pic_budget_v2(cpu_id, actual_read_usage, actual_write_usage);
//             break;
//         default:
//             printk("something has gone very wrong!\n");
//             break;
//     }

//     // --- BUG FIX: Update the defined budget for the NEXT period ---
//     // This ensures the next call to get_operation_usage_v2 has the correct
//     // starting value.
//     reg_conf[cpu_id].vm.defined_pmu_read_val =
//         reg_conf[cpu_id].vm.new_read_budget;
//     reg_conf[cpu_id].vm.defined_pmu_write_val =
//         reg_conf[cpu_id].vm.new_write_budget;

//     reg_conf[cpu()->id].vm.depleated_op_type = UNKNOWN_VALUE;
//     PMU_reset_all_counters();
//     // for (int i = 0; i < PMU_COUNT; ++i) {
//     //     PMU_reset_counter(i);
//     // }

//     print_VM(&reg_conf[cpu()->id].vm, false);
//     print_counters(false);
// }

uint32_t regulator_get_new_budget(const uint8_t task_num, const uint8_t op_type)
{
    return op_type == READ ? reg_conf[cpu()->id].vm.new_read_budget
                           : reg_conf[cpu()->id].vm.new_write_budget;
}

uint32_t regulator_get_current_used_budget(const uint8_t task_num,
                                           const uint8_t op_type)
{
    return op_type == READ ? reg_conf[cpu()->id].vm.current_used_read_budget
                           : reg_conf[cpu()->id].vm.current_used_write_budget;
}

uint32_t regulator_get_pmu_counter_value(const uint8_t pmu_index)
{
    switch (pmu_index) {
        case 0:
        return PMU_get_counter_value(0);
        case 1:
        return PMU_get_counter_value(1);
        case 2:
        return PMU_get_counter_value(2);
        case 3:
        return PMU_get_counter_value(3);
        case 4:
        return PMU_get_counter_value(4);
        case 5:
        return PMU_get_counter_value(5);
        case 6:
            return PMU_secure_monitor();
        default:
            printk("\n\n\ninvalid regulator call \n\n\n");
            break;
    }

    return -1;

    // return op_type == READ ? reg_conf[cpu()->id].vm.total_used_read_budget
    //                        : reg_conf[cpu()->id].vm.total_used_write_budget;
}

uint32_t regulator_get_total_used_budget(const uint8_t value1,
                                         const uint8_t value2)
{
    printk("\n\n\nUndefined function\n\n\n");
    return 0;
}
