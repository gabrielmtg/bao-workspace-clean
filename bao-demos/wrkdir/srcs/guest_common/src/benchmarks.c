// #include "../inc/benchmarks.h"
// #include "../inc/regulation.h" // for TASK_QUANTITY
// //
// // #include "../../benchmarks/bandwidth/inc/bandwidth.h"
// // #include "../../benchmarks/dijkstra/inc/dijkstra.h"
// // #include "../../benchmarks/disparity/inc/disparity.h"
// // #include "../../benchmarks/fft/inc/fft.h"
// // #include "../../benchmarks/mser/inc/mser.h"
// // #include "../../benchmarks/qsort/inc/qsort.h"
// // #include "../../benchmarks/sha/inc/sha.h"
// // #include "../../benchmarks/sorting/inc/sorting.h"
// // //
// #include <stdbool.h>
// #include <stdint.h>

// // #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
// // local helpers and variables

// #define MAX_TASKS 8

// int _get_info_index(int vm_num, int task_num);
// Function _local_function_table[NUM_BENCHMARKS];
// void initialize_all_benchmark_contexts();
// void free_all_benchmark_contexts();
// bool _context_initialized = false;

// // #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#

// Benchmark *benchmark_create() {
//   if (!_context_initialized) {
//     printf("\t initialize_all_benchmark_contexts has not been called.\n");
//     return NULL;
//   }

//   Benchmark *b = (Benchmark *)malloc(sizeof(Benchmark));
//   return b;
// }

// void benchmark_init(Benchmark *b) {
//   b->formula = 0;
//   b->info_size = 0;
// }

// void benchmark_destroy(Benchmark *b) { free(b); }

// const char *benchmark_get_formula_name(Benchmark *b) {
//   switch (b->formula) {
//   case EWMA_FORMULA:
//     return "EWMA";
//     break;
//   case SW_FORMULA:
//     return "SW";
//     break;
//   case AFC_FORMULA:
//     return "AFC";
//     break;
//   case AMBP_FORMULA:
//     return "AMBP";
//     break;
//   case PIC_FORMULA:
//     return "PIC";
//     break;
//   // case LR_FORMULA:
//   //   return "LR";
//   //   break;
//   case EWMA_V2_FORMULA:
//     return "EWMA_v2";
//     break;
//   case SW_V2_FORMULA:
//     return "SW_v2";
//     break;
//   case AFC_V2_FORMULA:
//     return "AFC_v2";
//     break;
//   case AMBP_V2_FORMULA:
//     return "AMBP_v2";
//     break;
//   case LR_V2_FORMULA:
//     return "LR_v2";
//     break;
//   case PIC_V2_FORMULA:
//     return "PIC_v2";
//     break;
//   default:
//     printf("\tinvalid formula name %d, returning UNDEFINED\n", b->formula);
//     return "UNDEFINED";
//     break;
//   }
// }

// formula_t benchmark_get_formula(Benchmark *b) {
//   //
//   return b->formula;
// }

// void benchmark_set_formula(Benchmark *b, formula_t formula) {
//   if (formula < 0 || formula >= FORMULA_COUNT) {
//     printf("\tInvalid set_benchmark_formula call %d\n", formula);
//     return;
//   }
//   b->formula = formula;
// }

// info_t *benchmark_get_info(Benchmark *b, int vm_num, int task_num) {
//   int index = _get_info_index(vm_num, task_num);

//   // Check if a benchmark has been added at this slot.
//   // This is reliable because benchmark_init() zeroed the whole array.
//   if (b->info[index].function.pointer == NULL) {
//     printf("\tError: benchmark_get_info called for an unconfigured task (vm: "
//            "%d, task: %d, index: %d)\n",
//            vm_num, task_num, index);
//     return NULL;
//   }

//   info_t *info = &b->info[index];
//   return info;
// }

// info_t *benchmark_add_info(Benchmark *b, int vm_num, int task_num,
//                            int periodicity) {
//   int index = _get_info_index(vm_num, task_num);
//   info_t info;
//   info.function = _local_function_table[index];
//   info.task_num = task_num;
//   info.periodicity = periodicity;
//   info.task_overruns = 0;
//   info.task_underruns = 0;

//   b->info[index] = info;
//   b->info_size += 1;

//   return &b->info[index];
// }

// // #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#

// // Generating scenarios...
// // Generated 480 chaotic mix scenarios.
// // Generation complete.
// // Function _local_function_table[NUM_BENCHMARKS] = {
// //     // Scenario 1
// //     {0, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {2, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {3, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {4, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {5, disparity_wrapper, "disparity_wrapper", NULL},
// //     {6, sha_wrapper, "sha_wrapper", NULL},
// //     {7, mser_wrapper, "mser_wrapper", NULL},
// //     // Scenario 2
// //     {8, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {9, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {10, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {11, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {12, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {13, fft_wrapper, "fft_wrapper", NULL},
// //     {14, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {15, fft_wrapper, "fft_wrapper", NULL},
// //     // Scenario 3
// //     {16, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {17, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {18, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {19, mser_wrapper, "mser_wrapper", NULL},
// //     {20, disparity_wrapper, "disparity_wrapper", NULL},
// //     {21, mser_wrapper, "mser_wrapper", NULL},
// //     {22, disparity_wrapper, "disparity_wrapper", NULL},
// //     {23, disparity_wrapper, "disparity_wrapper", NULL},
// //     // Scenario 4
// //     {24, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {25, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {26, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {27, sorting_wrapper, "sorting_wrapper", NULL},
// //     {28, mser_wrapper, "mser_wrapper", NULL},
// //     {29, fft_wrapper, "fft_wrapper", NULL},
// //     {30, fft_wrapper, "fft_wrapper", NULL},
// //     {31, fft_wrapper, "fft_wrapper", NULL},
// //     // Scenario 5
// //     {32, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {33, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {34, fft_wrapper, "fft_wrapper", NULL},
// //     {35, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {36, sorting_wrapper, "sorting_wrapper", NULL},
// //     {37, disparity_wrapper, "disparity_wrapper", NULL},
// //     {38, fft_wrapper, "fft_wrapper", NULL},
// //     {39, disparity_wrapper, "disparity_wrapper", NULL},
// //     // Scenario 6
// //     {40, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {41, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {42, mser_wrapper, "mser_wrapper", NULL},
// //     {43, sha_wrapper, "sha_wrapper", NULL},
// //     {44, fft_wrapper, "fft_wrapper", NULL},
// //     {45, mser_wrapper, "mser_wrapper", NULL},
// //     {46, fft_wrapper, "fft_wrapper", NULL},
// //     {47, fft_wrapper, "fft_wrapper", NULL},
// //     // Scenario 7
// //     {48, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {49, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {50, mser_wrapper, "mser_wrapper", NULL},
// //     {51, sha_wrapper, "sha_wrapper", NULL},
// //     {52, sha_wrapper, "sha_wrapper", NULL},
// //     {53, sha_wrapper, "sha_wrapper", NULL},
// //     {54, disparity_wrapper, "disparity_wrapper", NULL},
// //     {55, disparity_wrapper, "disparity_wrapper", NULL},
// //     // Scenario 8
// //     {56, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {57, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {58, mser_wrapper, "mser_wrapper", NULL},
// //     {59, sha_wrapper, "sha_wrapper", NULL},
// //     {60, sorting_wrapper, "sorting_wrapper", NULL},
// //     {61, sorting_wrapper, "sorting_wrapper", NULL},
// //     {62, sorting_wrapper, "sorting_wrapper", NULL},
// //     {63, sorting_wrapper, "sorting_wrapper", NULL},
// //     // Scenario 9
// //     {64, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {65, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {66, sorting_wrapper, "sorting_wrapper", NULL},
// //     {67, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {68, mser_wrapper, "mser_wrapper", NULL},
// //     {69, mser_wrapper, "mser_wrapper", NULL},
// //     {70, sha_wrapper, "sha_wrapper", NULL},
// //     {71, mser_wrapper, "mser_wrapper", NULL},
// //     // Scenario 10
// //     {72, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {73, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {74, sorting_wrapper, "sorting_wrapper", NULL},
// //     {75, fft_wrapper, "fft_wrapper", NULL},
// //     {76, fft_wrapper, "fft_wrapper", NULL},
// //     {77, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {78, disparity_wrapper, "disparity_wrapper", NULL},
// //     {79, sorting_wrapper, "sorting_wrapper", NULL},
// //     // Scenario 11
// //     {80, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {81, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {82, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {83, sorting_wrapper, "sorting_wrapper", NULL},
// //     {84, mser_wrapper, "mser_wrapper", NULL},
// //     {85, disparity_wrapper, "disparity_wrapper", NULL},
// //     {86, sorting_wrapper, "sorting_wrapper", NULL},
// //     {87, sorting_wrapper, "sorting_wrapper", NULL},
// //     // Scenario 12
// //     {88, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {89, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {90, disparity_wrapper, "disparity_wrapper", NULL},
// //     {91, mser_wrapper, "mser_wrapper", NULL},
// //     {92, disparity_wrapper, "disparity_wrapper", NULL},
// //     {93, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {94, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {95, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     // Scenario 13
// //     {96, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {97, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {98, mser_wrapper, "mser_wrapper", NULL},
// //     {99, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {100, sorting_wrapper, "sorting_wrapper", NULL},
// //     {101, mser_wrapper, "mser_wrapper", NULL},
// //     {102, mser_wrapper, "mser_wrapper", NULL},
// //     {103, mser_wrapper, "mser_wrapper", NULL},
// //     // Scenario 14
// //     {104, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {105, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {106, sha_wrapper, "sha_wrapper", NULL},
// //     {107, disparity_wrapper, "disparity_wrapper", NULL},
// //     {108, sha_wrapper, "sha_wrapper", NULL},
// //     {109, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {110, mser_wrapper, "mser_wrapper", NULL},
// //     {111, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     // Scenario 15
// //     {112, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {113, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {114, sha_wrapper, "sha_wrapper", NULL},
// //     {115, sha_wrapper, "sha_wrapper", NULL},
// //     {116, sorting_wrapper, "sorting_wrapper", NULL},
// //     {117, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {118, fft_wrapper, "fft_wrapper", NULL},
// //     {119, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     // Scenario 16
// //     {120, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {121, disparity_wrapper, "disparity_wrapper", NULL},
// //     {122, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {123, fft_wrapper, "fft_wrapper", NULL},
// //     {124, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {125, disparity_wrapper, "disparity_wrapper", NULL},
// //     {126, sha_wrapper, "sha_wrapper", NULL},
// //     {127, disparity_wrapper, "disparity_wrapper", NULL},
// //     // Scenario 17
// //     {128, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {129, disparity_wrapper, "disparity_wrapper", NULL},
// //     {130, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {131, sha_wrapper, "sha_wrapper", NULL},
// //     {132, mser_wrapper, "mser_wrapper", NULL},
// //     {133, fft_wrapper, "fft_wrapper", NULL},
// //     {134, sha_wrapper, "sha_wrapper", NULL},
// //     {135, mser_wrapper, "mser_wrapper", NULL},
// //     // Scenario 18
// //     {136, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {137, disparity_wrapper, "disparity_wrapper", NULL},
// //     {138, fft_wrapper, "fft_wrapper", NULL},
// //     {139, fft_wrapper, "fft_wrapper", NULL},
// //     {140, disparity_wrapper, "disparity_wrapper", NULL},
// //     {141, sorting_wrapper, "sorting_wrapper", NULL},
// //     {142, mser_wrapper, "mser_wrapper", NULL},
// //     {143, sorting_wrapper, "sorting_wrapper", NULL},
// //     // Scenario 19
// //     {144, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {145, disparity_wrapper, "disparity_wrapper", NULL},
// //     {146, mser_wrapper, "mser_wrapper", NULL},
// //     {147, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {148, disparity_wrapper, "disparity_wrapper", NULL},
// //     {149, sha_wrapper, "sha_wrapper", NULL},
// //     {150, sha_wrapper, "sha_wrapper", NULL},
// //     {151, fft_wrapper, "fft_wrapper", NULL},
// //     // Scenario 20
// //     {152, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {153, disparity_wrapper, "disparity_wrapper", NULL},
// //     {154, mser_wrapper, "mser_wrapper", NULL},
// //     {155, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {156, fft_wrapper, "fft_wrapper", NULL},
// //     {157, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {158, sorting_wrapper, "sorting_wrapper", NULL},
// //     {159, fft_wrapper, "fft_wrapper", NULL},
// //     // Scenario 21
// //     {160, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {161, disparity_wrapper, "disparity_wrapper", NULL},
// //     {162, sha_wrapper, "sha_wrapper", NULL},
// //     {163, disparity_wrapper, "disparity_wrapper", NULL},
// //     {164, disparity_wrapper, "disparity_wrapper", NULL},
// //     {165, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {166, sha_wrapper, "sha_wrapper", NULL},
// //     {167, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     // Scenario 22
// //     {168, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {169, disparity_wrapper, "disparity_wrapper", NULL},
// //     {170, sha_wrapper, "sha_wrapper", NULL},
// //     {171, fft_wrapper, "fft_wrapper", NULL},
// //     {172, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {173, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {174, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {175, disparity_wrapper, "disparity_wrapper", NULL},
// //     // Scenario 23
// //     {176, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {177, disparity_wrapper, "disparity_wrapper", NULL},
// //     {178, sha_wrapper, "sha_wrapper", NULL},
// //     {179, mser_wrapper, "mser_wrapper", NULL},
// //     {180, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {181, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {182, mser_wrapper, "mser_wrapper", NULL},
// //     {183, sorting_wrapper, "sorting_wrapper", NULL},
// //     // Scenario 24
// //     {184, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {185, disparity_wrapper, "disparity_wrapper", NULL},
// //     {186, sorting_wrapper, "sorting_wrapper", NULL},
// //     {187, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {188, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {189, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {190, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {191, sorting_wrapper, "sorting_wrapper", NULL},
// //     // Scenario 25
// //     {192, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {193, disparity_wrapper, "disparity_wrapper", NULL},
// //     {194, sorting_wrapper, "sorting_wrapper", NULL},
// //     {195, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {196, sha_wrapper, "sha_wrapper", NULL},
// //     {197, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {198, fft_wrapper, "fft_wrapper", NULL},
// //     {199, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     // Scenario 26
// //     {200, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {201, fft_wrapper, "fft_wrapper", NULL},
// //     {202, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {203, sha_wrapper, "sha_wrapper", NULL},
// //     {204, sorting_wrapper, "sorting_wrapper", NULL},
// //     {205, fft_wrapper, "fft_wrapper", NULL},
// //     {206, disparity_wrapper, "disparity_wrapper", NULL},
// //     {207, sorting_wrapper, "sorting_wrapper", NULL},
// //     // Scenario 27
// //     {208, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {209, fft_wrapper, "fft_wrapper", NULL},
// //     {210, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {211, sha_wrapper, "sha_wrapper", NULL},
// //     {212, sorting_wrapper, "sorting_wrapper", NULL},
// //     {213, mser_wrapper, "mser_wrapper", NULL},
// //     {214, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {215, sha_wrapper, "sha_wrapper", NULL},
// //     // Scenario 28
// //     {216, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {217, fft_wrapper, "fft_wrapper", NULL},
// //     {218, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {219, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {220, sha_wrapper, "sha_wrapper", NULL},
// //     {221, disparity_wrapper, "disparity_wrapper", NULL},
// //     {222, disparity_wrapper, "disparity_wrapper", NULL},
// //     {223, mser_wrapper, "mser_wrapper", NULL},
// //     // Scenario 29
// //     {224, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {225, fft_wrapper, "fft_wrapper", NULL},
// //     {226, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {227, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {228, sha_wrapper, "sha_wrapper", NULL},
// //     {229, mser_wrapper, "mser_wrapper", NULL},
// //     {230, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {231, disparity_wrapper, "disparity_wrapper", NULL},
// //     // Scenario 30
// //     {232, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {233, fft_wrapper, "fft_wrapper", NULL},
// //     {234, fft_wrapper, "fft_wrapper", NULL},
// //     {235, disparity_wrapper, "disparity_wrapper", NULL},
// //     {236, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {237, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {238, sha_wrapper, "sha_wrapper", NULL},
// //     {239, fft_wrapper, "fft_wrapper", NULL},
// //     // Scenario 31
// //     {240, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {241, fft_wrapper, "fft_wrapper", NULL},
// //     {242, fft_wrapper, "fft_wrapper", NULL},
// //     {243, mser_wrapper, "mser_wrapper", NULL},
// //     {244, mser_wrapper, "mser_wrapper", NULL},
// //     {245, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {246, disparity_wrapper, "disparity_wrapper", NULL},
// //     {247, mser_wrapper, "mser_wrapper", NULL},
// //     // Scenario 32
// //     {248, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {249, fft_wrapper, "fft_wrapper", NULL},
// //     {250, sha_wrapper, "sha_wrapper", NULL},
// //     {251, disparity_wrapper, "disparity_wrapper", NULL},
// //     {252, sha_wrapper, "sha_wrapper", NULL},
// //     {253, disparity_wrapper, "disparity_wrapper", NULL},
// //     {254, sha_wrapper, "sha_wrapper", NULL},
// //     {255, disparity_wrapper, "disparity_wrapper", NULL},
// //     // Scenario 33
// //     {256, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {257, fft_wrapper, "fft_wrapper", NULL},
// //     {258, sorting_wrapper, "sorting_wrapper", NULL},
// //     {259, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {260, sorting_wrapper, "sorting_wrapper", NULL},
// //     {261, disparity_wrapper, "disparity_wrapper", NULL},
// //     {262, mser_wrapper, "mser_wrapper", NULL},
// //     {263, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     // Scenario 34
// //     {264, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {265, mser_wrapper, "mser_wrapper", NULL},
// //     {266, disparity_wrapper, "disparity_wrapper", NULL},
// //     {267, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {268, sorting_wrapper, "sorting_wrapper", NULL},
// //     {269, mser_wrapper, "mser_wrapper", NULL},
// //     {270, fft_wrapper, "fft_wrapper", NULL},
// //     {271, fft_wrapper, "fft_wrapper", NULL},
// //     // Scenario 35
// //     {272, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {273, mser_wrapper, "mser_wrapper", NULL},
// //     {274, disparity_wrapper, "disparity_wrapper", NULL},
// //     {275, disparity_wrapper, "disparity_wrapper", NULL},
// //     {276, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {277, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {278, sorting_wrapper, "sorting_wrapper", NULL},
// //     {279, disparity_wrapper, "disparity_wrapper", NULL},
// //     // Scenario 36
// //     {280, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {281, mser_wrapper, "mser_wrapper", NULL},
// //     {282, disparity_wrapper, "disparity_wrapper", NULL},
// //     {283, fft_wrapper, "fft_wrapper", NULL},
// //     {284, sha_wrapper, "sha_wrapper", NULL},
// //     {285, sha_wrapper, "sha_wrapper", NULL},
// //     {286, disparity_wrapper, "disparity_wrapper", NULL},
// //     {287, sha_wrapper, "sha_wrapper", NULL},
// //     // Scenario 37
// //     {288, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {289, mser_wrapper, "mser_wrapper", NULL},
// //     {290, disparity_wrapper, "disparity_wrapper", NULL},
// //     {291, mser_wrapper, "mser_wrapper", NULL},
// //     {292, fft_wrapper, "fft_wrapper", NULL},
// //     {293, sha_wrapper, "sha_wrapper", NULL},
// //     {294, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {295, sorting_wrapper, "sorting_wrapper", NULL},
// //     // Scenario 38
// //     {296, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {297, mser_wrapper, "mser_wrapper", NULL},
// //     {298, fft_wrapper, "fft_wrapper", NULL},
// //     {299, disparity_wrapper, "disparity_wrapper", NULL},
// //     {300, fft_wrapper, "fft_wrapper", NULL},
// //     {301, mser_wrapper, "mser_wrapper", NULL},
// //     {302, disparity_wrapper, "disparity_wrapper", NULL},
// //     {303, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     // Scenario 39
// //     {304, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {305, mser_wrapper, "mser_wrapper", NULL},
// //     {306, fft_wrapper, "fft_wrapper", NULL},
// //     {307, disparity_wrapper, "disparity_wrapper", NULL},
// //     {308, sorting_wrapper, "sorting_wrapper", NULL},
// //     {309, disparity_wrapper, "disparity_wrapper", NULL},
// //     {310, disparity_wrapper, "disparity_wrapper", NULL},
// //     {311, sha_wrapper, "sha_wrapper", NULL},
// //     // Scenario 40
// //     {312, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {313, mser_wrapper, "mser_wrapper", NULL},
// //     {314, fft_wrapper, "fft_wrapper", NULL},
// //     {315, sha_wrapper, "sha_wrapper", NULL},
// //     {316, fft_wrapper, "fft_wrapper", NULL},
// //     {317, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {318, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {319, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     // Scenario 41
// //     {320, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {321, mser_wrapper, "mser_wrapper", NULL},
// //     {322, sha_wrapper, "sha_wrapper", NULL},
// //     {323, sha_wrapper, "sha_wrapper", NULL},
// //     {324, disparity_wrapper, "disparity_wrapper", NULL},
// //     {325, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {326, sorting_wrapper, "sorting_wrapper", NULL},
// //     {327, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     // Scenario 42
// //     {328, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {329, mser_wrapper, "mser_wrapper", NULL},
// //     {330, sorting_wrapper, "sorting_wrapper", NULL},
// //     {331, sha_wrapper, "sha_wrapper", NULL},
// //     {332, mser_wrapper, "mser_wrapper", NULL},
// //     {333, fft_wrapper, "fft_wrapper", NULL},
// //     {334, disparity_wrapper, "disparity_wrapper", NULL},
// //     {335, disparity_wrapper, "disparity_wrapper", NULL},
// //     // Scenario 43
// //     {336, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {337, mser_wrapper, "mser_wrapper", NULL},
// //     {338, sorting_wrapper, "sorting_wrapper", NULL},
// //     {339, sorting_wrapper, "sorting_wrapper", NULL},
// //     {340, disparity_wrapper, "disparity_wrapper", NULL},
// //     {341, sha_wrapper, "sha_wrapper", NULL},
// //     {342, disparity_wrapper, "disparity_wrapper", NULL},
// //     {343, sha_wrapper, "sha_wrapper", NULL},
// //     // Scenario 44
// //     {344, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {345, sha_wrapper, "sha_wrapper", NULL},
// //     {346, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {347, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {348, disparity_wrapper, "disparity_wrapper", NULL},
// //     {349, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {350, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {351, sorting_wrapper, "sorting_wrapper", NULL},
// //     // Scenario 45
// //     {352, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {353, sha_wrapper, "sha_wrapper", NULL},
// //     {354, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {355, sha_wrapper, "sha_wrapper", NULL},
// //     {356, disparity_wrapper, "disparity_wrapper", NULL},
// //     {357, sha_wrapper, "sha_wrapper", NULL},
// //     {358, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {359, sha_wrapper, "sha_wrapper", NULL},
// //     // Scenario 46
// //     {360, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {361, sha_wrapper, "sha_wrapper", NULL},
// //     {362, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {363, sha_wrapper, "sha_wrapper", NULL},
// //     {364, sorting_wrapper, "sorting_wrapper", NULL},
// //     {365, fft_wrapper, "fft_wrapper", NULL},
// //     {366, fft_wrapper, "fft_wrapper", NULL},
// //     {367, disparity_wrapper, "disparity_wrapper", NULL},
// //     // Scenario 47
// //     {368, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {369, sha_wrapper, "sha_wrapper", NULL},
// //     {370, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {371, fft_wrapper, "fft_wrapper", NULL},
// //     {372, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {373, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {374, mser_wrapper, "mser_wrapper", NULL},
// //     {375, sha_wrapper, "sha_wrapper", NULL},
// //     // Scenario 48
// //     {376, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {377, sha_wrapper, "sha_wrapper", NULL},
// //     {378, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {379, fft_wrapper, "fft_wrapper", NULL},
// //     {380, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {381, fft_wrapper, "fft_wrapper", NULL},
// //     {382, sorting_wrapper, "sorting_wrapper", NULL},
// //     {383, mser_wrapper, "mser_wrapper", NULL},
// //     // Scenario 49
// //     {384, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {385, sha_wrapper, "sha_wrapper", NULL},
// //     {386, disparity_wrapper, "disparity_wrapper", NULL},
// //     {387, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {388, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {389, disparity_wrapper, "disparity_wrapper", NULL},
// //     {390, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {391, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     // Scenario 50
// //     {392, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {393, sha_wrapper, "sha_wrapper", NULL},
// //     {394, disparity_wrapper, "disparity_wrapper", NULL},
// //     {395, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {396, fft_wrapper, "fft_wrapper", NULL},
// //     {397, disparity_wrapper, "disparity_wrapper", NULL},
// //     {398, fft_wrapper, "fft_wrapper", NULL},
// //     {399, sorting_wrapper, "sorting_wrapper", NULL},
// //     // Scenario 51
// //     {400, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {401, sha_wrapper, "sha_wrapper", NULL},
// //     {402, disparity_wrapper, "disparity_wrapper", NULL},
// //     {403, fft_wrapper, "fft_wrapper", NULL},
// //     {404, sorting_wrapper, "sorting_wrapper", NULL},
// //     {405, mser_wrapper, "mser_wrapper", NULL},
// //     {406, fft_wrapper, "fft_wrapper", NULL},
// //     {407, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     // Scenario 52
// //     {408, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {409, sha_wrapper, "sha_wrapper", NULL},
// //     {410, disparity_wrapper, "disparity_wrapper", NULL},
// //     {411, sorting_wrapper, "sorting_wrapper", NULL},
// //     {412, fft_wrapper, "fft_wrapper", NULL},
// //     {413, mser_wrapper, "mser_wrapper", NULL},
// //     {414, mser_wrapper, "mser_wrapper", NULL},
// //     {415, sorting_wrapper, "sorting_wrapper", NULL},
// //     // Scenario 53
// //     {416, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {417, sha_wrapper, "sha_wrapper", NULL},
// //     {418, disparity_wrapper, "disparity_wrapper", NULL},
// //     {419, sorting_wrapper, "sorting_wrapper", NULL},
// //     {420, sha_wrapper, "sha_wrapper", NULL},
// //     {421, fft_wrapper, "fft_wrapper", NULL},
// //     {422, fft_wrapper, "fft_wrapper", NULL},
// //     {423, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     // Scenario 54
// //     {424, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {425, sha_wrapper, "sha_wrapper", NULL},
// //     {426, mser_wrapper, "mser_wrapper", NULL},
// //     {427, mser_wrapper, "mser_wrapper", NULL},
// //     {428, disparity_wrapper, "disparity_wrapper", NULL},
// //     {429, fft_wrapper, "fft_wrapper", NULL},
// //     {430, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {431, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     // Scenario 55
// //     {432, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {433, sha_wrapper, "sha_wrapper", NULL},
// //     {434, mser_wrapper, "mser_wrapper", NULL},
// //     {435, mser_wrapper, "mser_wrapper", NULL},
// //     {436, sorting_wrapper, "sorting_wrapper", NULL},
// //     {437, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {438, mser_wrapper, "mser_wrapper", NULL},
// //     {439, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     // Scenario 56
// //     {440, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {441, sha_wrapper, "sha_wrapper", NULL},
// //     {442, mser_wrapper, "mser_wrapper", NULL},
// //     {443, sorting_wrapper, "sorting_wrapper", NULL},
// //     {444, sorting_wrapper, "sorting_wrapper", NULL},
// //     {445, sha_wrapper, "sha_wrapper", NULL},
// //     {446, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {447, sha_wrapper, "sha_wrapper", NULL},
// //     // Scenario 57
// //     {448, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {449, sha_wrapper, "sha_wrapper", NULL},
// //     {450, sha_wrapper, "sha_wrapper", NULL},
// //     {451, sha_wrapper, "sha_wrapper", NULL},
// //     {452, disparity_wrapper, "disparity_wrapper", NULL},
// //     {453, sorting_wrapper, "sorting_wrapper", NULL},
// //     {454, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {455, disparity_wrapper, "disparity_wrapper", NULL},
// //     // Scenario 58
// //     {456, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {457, sorting_wrapper, "sorting_wrapper", NULL},
// //     {458, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {459, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {460, disparity_wrapper, "disparity_wrapper", NULL},
// //     {461, disparity_wrapper, "disparity_wrapper", NULL},
// //     {462, disparity_wrapper, "disparity_wrapper", NULL},
// //     {463, sha_wrapper, "sha_wrapper", NULL},
// //     // Scenario 59
// //     {464, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {465, sorting_wrapper, "sorting_wrapper", NULL},
// //     {466, disparity_wrapper, "disparity_wrapper", NULL},
// //     {467, fft_wrapper, "fft_wrapper", NULL},
// //     {468, mser_wrapper, "mser_wrapper", NULL},
// //     {469, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {470, fft_wrapper, "fft_wrapper", NULL},
// //     {471, disparity_wrapper, "disparity_wrapper", NULL},
// //     // Scenario 60
// //     {472, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {473, sorting_wrapper, "sorting_wrapper", NULL},
// //     {474, disparity_wrapper, "disparity_wrapper", NULL},
// //     {475, mser_wrapper, "mser_wrapper", NULL},
// //     {476, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {477, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {478, sha_wrapper, "sha_wrapper", NULL},
// //     {479, fft_wrapper, "fft_wrapper", NULL},
// //     // Scenario 61
// //     {480, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {481, sorting_wrapper, "sorting_wrapper", NULL},
// //     {482, disparity_wrapper, "disparity_wrapper", NULL},
// //     {483, sha_wrapper, "sha_wrapper", NULL},
// //     {484, fft_wrapper, "fft_wrapper", NULL},
// //     {485, mser_wrapper, "mser_wrapper", NULL},
// //     {486, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {487, mser_wrapper, "mser_wrapper", NULL},
// //     // Scenario 62
// //     {488, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {489, sorting_wrapper, "sorting_wrapper", NULL},
// //     {490, fft_wrapper, "fft_wrapper", NULL},
// //     {491, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {492, fft_wrapper, "fft_wrapper", NULL},
// //     {493, mser_wrapper, "mser_wrapper", NULL},
// //     {494, disparity_wrapper, "disparity_wrapper", NULL},
// //     {495, sorting_wrapper, "sorting_wrapper", NULL},
// //     // Scenario 63
// //     {496, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {497, sorting_wrapper, "sorting_wrapper", NULL},
// //     {498, mser_wrapper, "mser_wrapper", NULL},
// //     {499, fft_wrapper, "fft_wrapper", NULL},
// //     {500, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {501, disparity_wrapper, "disparity_wrapper", NULL},
// //     {502, fft_wrapper, "fft_wrapper", NULL},
// //     {503, sorting_wrapper, "sorting_wrapper", NULL},
// //     // Scenario 64
// //     {504, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {505, sorting_wrapper, "sorting_wrapper", NULL},
// //     {506, sha_wrapper, "sha_wrapper", NULL},
// //     {507, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {508, fft_wrapper, "fft_wrapper", NULL},
// //     {509, sorting_wrapper, "sorting_wrapper", NULL},
// //     {510, sha_wrapper, "sha_wrapper", NULL},
// //     {511, fft_wrapper, "fft_wrapper", NULL},
// //     // Scenario 65
// //     {512, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {513, sorting_wrapper, "sorting_wrapper", NULL},
// //     {514, sha_wrapper, "sha_wrapper", NULL},
// //     {515, disparity_wrapper, "disparity_wrapper", NULL},
// //     {516, fft_wrapper, "fft_wrapper", NULL},
// //     {517, sha_wrapper, "sha_wrapper", NULL},
// //     {518, fft_wrapper, "fft_wrapper", NULL},
// //     {519, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     // Scenario 66
// //     {520, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {521, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {522, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {523, fft_wrapper, "fft_wrapper", NULL},
// //     {524, fft_wrapper, "fft_wrapper", NULL},
// //     {525, fft_wrapper, "fft_wrapper", NULL},
// //     {526, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {527, sha_wrapper, "sha_wrapper", NULL},
// //     // Scenario 67
// //     {528, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {529, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {530, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {531, sorting_wrapper, "sorting_wrapper", NULL},
// //     {532, sha_wrapper, "sha_wrapper", NULL},
// //     {533, sorting_wrapper, "sorting_wrapper", NULL},
// //     {534, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {535, mser_wrapper, "mser_wrapper", NULL},
// //     // Scenario 68
// //     {536, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {537, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {538, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {539, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {540, disparity_wrapper, "disparity_wrapper", NULL},
// //     {541, disparity_wrapper, "disparity_wrapper", NULL},
// //     {542, disparity_wrapper, "disparity_wrapper", NULL},
// //     {543, mser_wrapper, "mser_wrapper", NULL},
// //     // Scenario 69
// //     {544, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {545, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {546, disparity_wrapper, "disparity_wrapper", NULL},
// //     {547, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {548, fft_wrapper, "fft_wrapper", NULL},
// //     {549, mser_wrapper, "mser_wrapper", NULL},
// //     {550, sorting_wrapper, "sorting_wrapper", NULL},
// //     {551, fft_wrapper, "fft_wrapper", NULL},
// //     // Scenario 70
// //     {552, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {553, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {554, disparity_wrapper, "disparity_wrapper", NULL},
// //     {555, fft_wrapper, "fft_wrapper", NULL},
// //     {556, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {557, disparity_wrapper, "disparity_wrapper", NULL},
// //     {558, fft_wrapper, "fft_wrapper", NULL},
// //     {559, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     // Scenario 71
// //     {560, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {561, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {562, disparity_wrapper, "disparity_wrapper", NULL},
// //     {563, sha_wrapper, "sha_wrapper", NULL},
// //     {564, fft_wrapper, "fft_wrapper", NULL},
// //     {565, sorting_wrapper, "sorting_wrapper", NULL},
// //     {566, sha_wrapper, "sha_wrapper", NULL},
// //     {567, mser_wrapper, "mser_wrapper", NULL},
// //     // Scenario 72
// //     {568, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {569, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {570, disparity_wrapper, "disparity_wrapper", NULL},
// //     {571, sha_wrapper, "sha_wrapper", NULL},
// //     {572, sorting_wrapper, "sorting_wrapper", NULL},
// //     {573, sorting_wrapper, "sorting_wrapper", NULL},
// //     {574, disparity_wrapper, "disparity_wrapper", NULL},
// //     {575, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     // Scenario 73
// //     {576, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {577, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {578, fft_wrapper, "fft_wrapper", NULL},
// //     {579, mser_wrapper, "mser_wrapper", NULL},
// //     {580, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {581, sorting_wrapper, "sorting_wrapper", NULL},
// //     {582, disparity_wrapper, "disparity_wrapper", NULL},
// //     {583, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     // Scenario 74
// //     {584, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {585, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {586, sha_wrapper, "sha_wrapper", NULL},
// //     {587, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {588, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {589, fft_wrapper, "fft_wrapper", NULL},
// //     {590, sha_wrapper, "sha_wrapper", NULL},
// //     {591, fft_wrapper, "fft_wrapper", NULL},
// //     // Scenario 75
// //     {592, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {593, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {594, sha_wrapper, "sha_wrapper", NULL},
// //     {595, mser_wrapper, "mser_wrapper", NULL},
// //     {596, mser_wrapper, "mser_wrapper", NULL},
// //     {597, fft_wrapper, "fft_wrapper", NULL},
// //     {598, sorting_wrapper, "sorting_wrapper", NULL},
// //     {599, mser_wrapper, "mser_wrapper", NULL},
// //     // Scenario 76
// //     {600, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {601, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {602, sorting_wrapper, "sorting_wrapper", NULL},
// //     {603, fft_wrapper, "fft_wrapper", NULL},
// //     {604, fft_wrapper, "fft_wrapper", NULL},
// //     {605, sorting_wrapper, "sorting_wrapper", NULL},
// //     {606, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {607, fft_wrapper, "fft_wrapper", NULL},
// //     // Scenario 77
// //     {608, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {609, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {610, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {611, disparity_wrapper, "disparity_wrapper", NULL},
// //     {612, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {613, disparity_wrapper, "disparity_wrapper", NULL},
// //     {614, fft_wrapper, "fft_wrapper", NULL},
// //     {615, sha_wrapper, "sha_wrapper", NULL},
// //     // Scenario 78
// //     {616, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {617, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {618, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {619, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {620, sorting_wrapper, "sorting_wrapper", NULL},
// //     {621, fft_wrapper, "fft_wrapper", NULL},
// //     {622, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {623, sorting_wrapper, "sorting_wrapper", NULL},
// //     // Scenario 79
// //     {624, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {625, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {626, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {627, mser_wrapper, "mser_wrapper", NULL},
// //     {628, disparity_wrapper, "disparity_wrapper", NULL},
// //     {629, disparity_wrapper, "disparity_wrapper", NULL},
// //     {630, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {631, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     // Scenario 80
// //     {632, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {633, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {634, disparity_wrapper, "disparity_wrapper", NULL},
// //     {635, disparity_wrapper, "disparity_wrapper", NULL},
// //     {636, fft_wrapper, "fft_wrapper", NULL},
// //     {637, sha_wrapper, "sha_wrapper", NULL},
// //     {638, sha_wrapper, "sha_wrapper", NULL},
// //     {639, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     // Scenario 81
// //     {640, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {641, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {642, disparity_wrapper, "disparity_wrapper", NULL},
// //     {643, sha_wrapper, "sha_wrapper", NULL},
// //     {644, disparity_wrapper, "disparity_wrapper", NULL},
// //     {645, disparity_wrapper, "disparity_wrapper", NULL},
// //     {646, mser_wrapper, "mser_wrapper", NULL},
// //     {647, disparity_wrapper, "disparity_wrapper", NULL},
// //     // Scenario 82
// //     {648, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {649, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {650, fft_wrapper, "fft_wrapper", NULL},
// //     {651, fft_wrapper, "fft_wrapper", NULL},
// //     {652, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {653, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {654, sorting_wrapper, "sorting_wrapper", NULL},
// //     {655, sorting_wrapper, "sorting_wrapper", NULL},
// //     // Scenario 83
// //     {656, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {657, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {658, sha_wrapper, "sha_wrapper", NULL},
// //     {659, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {660, fft_wrapper, "fft_wrapper", NULL},
// //     {661, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {662, sorting_wrapper, "sorting_wrapper", NULL},
// //     {663, sorting_wrapper, "sorting_wrapper", NULL},
// //     // Scenario 84
// //     {664, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {665, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {666, sha_wrapper, "sha_wrapper", NULL},
// //     {667, disparity_wrapper, "disparity_wrapper", NULL},
// //     {668, sorting_wrapper, "sorting_wrapper", NULL},
// //     {669, fft_wrapper, "fft_wrapper", NULL},
// //     {670, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {671, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     // Scenario 85
// //     {672, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {673, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {674, sorting_wrapper, "sorting_wrapper", NULL},
// //     {675, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {676, mser_wrapper, "mser_wrapper", NULL},
// //     {677, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {678, mser_wrapper, "mser_wrapper", NULL},
// //     {679, sha_wrapper, "sha_wrapper", NULL},
// //     // Scenario 86
// //     {680, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {681, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {682, sorting_wrapper, "sorting_wrapper", NULL},
// //     {683, sha_wrapper, "sha_wrapper", NULL},
// //     {684, fft_wrapper, "fft_wrapper", NULL},
// //     {685, sorting_wrapper, "sorting_wrapper", NULL},
// //     {686, sorting_wrapper, "sorting_wrapper", NULL},
// //     {687, sha_wrapper, "sha_wrapper", NULL},
// //     // Scenario 87
// //     {688, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {689, disparity_wrapper, "disparity_wrapper", NULL},
// //     {690, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {691, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {692, mser_wrapper, "mser_wrapper", NULL},
// //     {693, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {694, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {695, mser_wrapper, "mser_wrapper", NULL},
// //     // Scenario 88
// //     {696, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {697, disparity_wrapper, "disparity_wrapper", NULL},
// //     {698, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {699, fft_wrapper, "fft_wrapper", NULL},
// //     {700, disparity_wrapper, "disparity_wrapper", NULL},
// //     {701, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {702, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {703, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     // Scenario 89
// //     {704, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {705, disparity_wrapper, "disparity_wrapper", NULL},
// //     {706, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {707, mser_wrapper, "mser_wrapper", NULL},
// //     {708, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {709, sha_wrapper, "sha_wrapper", NULL},
// //     {710, disparity_wrapper, "disparity_wrapper", NULL},
// //     {711, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     // Scenario 90
// //     {712, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {713, disparity_wrapper, "disparity_wrapper", NULL},
// //     {714, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {715, sha_wrapper, "sha_wrapper", NULL},
// //     {716, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {717, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {718, mser_wrapper, "mser_wrapper", NULL},
// //     {719, sha_wrapper, "sha_wrapper", NULL},
// //     // Scenario 91
// //     {720, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {721, disparity_wrapper, "disparity_wrapper", NULL},
// //     {722, disparity_wrapper, "disparity_wrapper", NULL},
// //     {723, disparity_wrapper, "disparity_wrapper", NULL},
// //     {724, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {725, sha_wrapper, "sha_wrapper", NULL},
// //     {726, fft_wrapper, "fft_wrapper", NULL},
// //     {727, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     // Scenario 92
// //     {728, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {729, disparity_wrapper, "disparity_wrapper", NULL},
// //     {730, disparity_wrapper, "disparity_wrapper", NULL},
// //     {731, sha_wrapper, "sha_wrapper", NULL},
// //     {732, disparity_wrapper, "disparity_wrapper", NULL},
// //     {733, mser_wrapper, "mser_wrapper", NULL},
// //     {734, mser_wrapper, "mser_wrapper", NULL},
// //     {735, sha_wrapper, "sha_wrapper", NULL},
// //     // Scenario 93
// //     {736, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {737, disparity_wrapper, "disparity_wrapper", NULL},
// //     {738, fft_wrapper, "fft_wrapper", NULL},
// //     {739, mser_wrapper, "mser_wrapper", NULL},
// //     {740, disparity_wrapper, "disparity_wrapper", NULL},
// //     {741, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {742, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {743, fft_wrapper, "fft_wrapper", NULL},
// //     // Scenario 94
// //     {744, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {745, disparity_wrapper, "disparity_wrapper", NULL},
// //     {746, mser_wrapper, "mser_wrapper", NULL},
// //     {747, fft_wrapper, "fft_wrapper", NULL},
// //     {748, sha_wrapper, "sha_wrapper", NULL},
// //     {749, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {750, sha_wrapper, "sha_wrapper", NULL},
// //     {751, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     // Scenario 95
// //     {752, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {753, disparity_wrapper, "disparity_wrapper", NULL},
// //     {754, mser_wrapper, "mser_wrapper", NULL},
// //     {755, sorting_wrapper, "sorting_wrapper", NULL},
// //     {756, sha_wrapper, "sha_wrapper", NULL},
// //     {757, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {758, mser_wrapper, "mser_wrapper", NULL},
// //     {759, fft_wrapper, "fft_wrapper", NULL},
// //     // Scenario 96
// //     {760, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {761, disparity_wrapper, "disparity_wrapper", NULL},
// //     {762, mser_wrapper, "mser_wrapper", NULL},
// //     {763, sorting_wrapper, "sorting_wrapper", NULL},
// //     {764, sha_wrapper, "sha_wrapper", NULL},
// //     {765, sorting_wrapper, "sorting_wrapper", NULL},
// //     {766, sorting_wrapper, "sorting_wrapper", NULL},
// //     {767, fft_wrapper, "fft_wrapper", NULL},
// //     // Scenario 97
// //     {768, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {769, disparity_wrapper, "disparity_wrapper", NULL},
// //     {770, sha_wrapper, "sha_wrapper", NULL},
// //     {771, fft_wrapper, "fft_wrapper", NULL},
// //     {772, mser_wrapper, "mser_wrapper", NULL},
// //     {773, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {774, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {775, fft_wrapper, "fft_wrapper", NULL},
// //     // Scenario 98
// //     {776, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {777, disparity_wrapper, "disparity_wrapper", NULL},
// //     {778, sha_wrapper, "sha_wrapper", NULL},
// //     {779, mser_wrapper, "mser_wrapper", NULL},
// //     {780, sha_wrapper, "sha_wrapper", NULL},
// //     {781, mser_wrapper, "mser_wrapper", NULL},
// //     {782, sha_wrapper, "sha_wrapper", NULL},
// //     {783, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     // Scenario 99
// //     {784, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {785, disparity_wrapper, "disparity_wrapper", NULL},
// //     {786, sorting_wrapper, "sorting_wrapper", NULL},
// //     {787, disparity_wrapper, "disparity_wrapper", NULL},
// //     {788, disparity_wrapper, "disparity_wrapper", NULL},
// //     {789, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {790, disparity_wrapper, "disparity_wrapper", NULL},
// //     {791, sorting_wrapper, "sorting_wrapper", NULL},
// //     // Scenario 100
// //     {792, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {793, fft_wrapper, "fft_wrapper", NULL},
// //     {794, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {795, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {796, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {797, disparity_wrapper, "disparity_wrapper", NULL},
// //     {798, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {799, disparity_wrapper, "disparity_wrapper", NULL},
// //     // Scenario 101
// //     {800, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {801, fft_wrapper, "fft_wrapper", NULL},
// //     {802, disparity_wrapper, "disparity_wrapper", NULL},
// //     {803, mser_wrapper, "mser_wrapper", NULL},
// //     {804, disparity_wrapper, "disparity_wrapper", NULL},
// //     {805, mser_wrapper, "mser_wrapper", NULL},
// //     {806, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {807, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     // Scenario 102
// //     {808, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {809, fft_wrapper, "fft_wrapper", NULL},
// //     {810, fft_wrapper, "fft_wrapper", NULL},
// //     {811, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {812, mser_wrapper, "mser_wrapper", NULL},
// //     {813, fft_wrapper, "fft_wrapper", NULL},
// //     {814, fft_wrapper, "fft_wrapper", NULL},
// //     {815, sorting_wrapper, "sorting_wrapper", NULL},
// //     // Scenario 103
// //     {816, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {817, fft_wrapper, "fft_wrapper", NULL},
// //     {818, fft_wrapper, "fft_wrapper", NULL},
// //     {819, fft_wrapper, "fft_wrapper", NULL},
// //     {820, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {821, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {822, disparity_wrapper, "disparity_wrapper", NULL},
// //     {823, mser_wrapper, "mser_wrapper", NULL},
// //     // Scenario 104
// //     {824, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {825, fft_wrapper, "fft_wrapper", NULL},
// //     {826, fft_wrapper, "fft_wrapper", NULL},
// //     {827, fft_wrapper, "fft_wrapper", NULL},
// //     {828, sha_wrapper, "sha_wrapper", NULL},
// //     {829, sorting_wrapper, "sorting_wrapper", NULL},
// //     {830, fft_wrapper, "fft_wrapper", NULL},
// //     {831, fft_wrapper, "fft_wrapper", NULL},
// //     // Scenario 105
// //     {832, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {833, fft_wrapper, "fft_wrapper", NULL},
// //     {834, fft_wrapper, "fft_wrapper", NULL},
// //     {835, mser_wrapper, "mser_wrapper", NULL},
// //     {836, fft_wrapper, "fft_wrapper", NULL},
// //     {837, mser_wrapper, "mser_wrapper", NULL},
// //     {838, sha_wrapper, "sha_wrapper", NULL},
// //     {839, disparity_wrapper, "disparity_wrapper", NULL},
// //     // Scenario 106
// //     {840, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {841, fft_wrapper, "fft_wrapper", NULL},
// //     {842, mser_wrapper, "mser_wrapper", NULL},
// //     {843, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {844, sha_wrapper, "sha_wrapper", NULL},
// //     {845, sha_wrapper, "sha_wrapper", NULL},
// //     {846, sha_wrapper, "sha_wrapper", NULL},
// //     {847, sorting_wrapper, "sorting_wrapper", NULL},
// //     // Scenario 107
// //     {848, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {849, fft_wrapper, "fft_wrapper", NULL},
// //     {850, mser_wrapper, "mser_wrapper", NULL},
// //     {851, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {852, sorting_wrapper, "sorting_wrapper", NULL},
// //     {853, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {854, disparity_wrapper, "disparity_wrapper", NULL},
// //     {855, sha_wrapper, "sha_wrapper", NULL},
// //     // Scenario 108
// //     {856, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {857, fft_wrapper, "fft_wrapper", NULL},
// //     {858, mser_wrapper, "mser_wrapper", NULL},
// //     {859, disparity_wrapper, "disparity_wrapper", NULL},
// //     {860, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {861, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {862, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {863, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     // Scenario 109
// //     {864, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {865, fft_wrapper, "fft_wrapper", NULL},
// //     {866, sha_wrapper, "sha_wrapper", NULL},
// //     {867, sha_wrapper, "sha_wrapper", NULL},
// //     {868, disparity_wrapper, "disparity_wrapper", NULL},
// //     {869, sorting_wrapper, "sorting_wrapper", NULL},
// //     {870, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {871, disparity_wrapper, "disparity_wrapper", NULL},
// //     // Scenario 110
// //     {872, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {873, fft_wrapper, "fft_wrapper", NULL},
// //     {874, sorting_wrapper, "sorting_wrapper", NULL},
// //     {875, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {876, mser_wrapper, "mser_wrapper", NULL},
// //     {877, mser_wrapper, "mser_wrapper", NULL},
// //     {878, mser_wrapper, "mser_wrapper", NULL},
// //     {879, mser_wrapper, "mser_wrapper", NULL},
// //     // Scenario 111
// //     {880, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {881, mser_wrapper, "mser_wrapper", NULL},
// //     {882, disparity_wrapper, "disparity_wrapper", NULL},
// //     {883, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {884, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {885, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {886, sha_wrapper, "sha_wrapper", NULL},
// //     {887, mser_wrapper, "mser_wrapper", NULL},
// //     // Scenario 112
// //     {888, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {889, mser_wrapper, "mser_wrapper", NULL},
// //     {890, disparity_wrapper, "disparity_wrapper", NULL},
// //     {891, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {892, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {893, sorting_wrapper, "sorting_wrapper", NULL},
// //     {894, fft_wrapper, "fft_wrapper", NULL},
// //     {895, sha_wrapper, "sha_wrapper", NULL},
// //     // Scenario 113
// //     {896, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {897, mser_wrapper, "mser_wrapper", NULL},
// //     {898, disparity_wrapper, "disparity_wrapper", NULL},
// //     {899, fft_wrapper, "fft_wrapper", NULL},
// //     {900, sorting_wrapper, "sorting_wrapper", NULL},
// //     {901, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {902, sorting_wrapper, "sorting_wrapper", NULL},
// //     {903, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     // Scenario 114
// //     {904, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {905, mser_wrapper, "mser_wrapper", NULL},
// //     {906, disparity_wrapper, "disparity_wrapper", NULL},
// //     {907, mser_wrapper, "mser_wrapper", NULL},
// //     {908, fft_wrapper, "fft_wrapper", NULL},
// //     {909, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {910, sorting_wrapper, "sorting_wrapper", NULL},
// //     {911, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     // Scenario 115
// //     {912, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {913, mser_wrapper, "mser_wrapper", NULL},
// //     {914, fft_wrapper, "fft_wrapper", NULL},
// //     {915, disparity_wrapper, "disparity_wrapper", NULL},
// //     {916, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {917, mser_wrapper, "mser_wrapper", NULL},
// //     {918, disparity_wrapper, "disparity_wrapper", NULL},
// //     {919, mser_wrapper, "mser_wrapper", NULL},
// //     // Scenario 116
// //     {920, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {921, mser_wrapper, "mser_wrapper", NULL},
// //     {922, mser_wrapper, "mser_wrapper", NULL},
// //     {923, disparity_wrapper, "disparity_wrapper", NULL},
// //     {924, sorting_wrapper, "sorting_wrapper", NULL},
// //     {925, disparity_wrapper, "disparity_wrapper", NULL},
// //     {926, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {927, disparity_wrapper, "disparity_wrapper", NULL},
// //     // Scenario 117
// //     {928, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {929, mser_wrapper, "mser_wrapper", NULL},
// //     {930, sha_wrapper, "sha_wrapper", NULL},
// //     {931, disparity_wrapper, "disparity_wrapper", NULL},
// //     {932, sha_wrapper, "sha_wrapper", NULL},
// //     {933, sha_wrapper, "sha_wrapper", NULL},
// //     {934, sha_wrapper, "sha_wrapper", NULL},
// //     {935, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     // Scenario 118
// //     {936, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {937, mser_wrapper, "mser_wrapper", NULL},
// //     {938, sha_wrapper, "sha_wrapper", NULL},
// //     {939, mser_wrapper, "mser_wrapper", NULL},
// //     {940, sha_wrapper, "sha_wrapper", NULL},
// //     {941, fft_wrapper, "fft_wrapper", NULL},
// //     {942, sha_wrapper, "sha_wrapper", NULL},
// //     {943, sha_wrapper, "sha_wrapper", NULL},
// //     // Scenario 119
// //     {944, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {945, mser_wrapper, "mser_wrapper", NULL},
// //     {946, sorting_wrapper, "sorting_wrapper", NULL},
// //     {947, fft_wrapper, "fft_wrapper", NULL},
// //     {948, sha_wrapper, "sha_wrapper", NULL},
// //     {949, mser_wrapper, "mser_wrapper", NULL},
// //     {950, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {951, sha_wrapper, "sha_wrapper", NULL},
// //     // Scenario 120
// //     {952, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {953, sha_wrapper, "sha_wrapper", NULL},
// //     {954, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {955, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {956, mser_wrapper, "mser_wrapper", NULL},
// //     {957, disparity_wrapper, "disparity_wrapper", NULL},
// //     {958, mser_wrapper, "mser_wrapper", NULL},
// //     {959, sha_wrapper, "sha_wrapper", NULL},
// //     // Scenario 121
// //     {960, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {961, sha_wrapper, "sha_wrapper", NULL},
// //     {962, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {963, sha_wrapper, "sha_wrapper", NULL},
// //     {964, fft_wrapper, "fft_wrapper", NULL},
// //     {965, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {966, sorting_wrapper, "sorting_wrapper", NULL},
// //     {967, disparity_wrapper, "disparity_wrapper", NULL},
// //     // Scenario 122
// //     {968, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {969, sha_wrapper, "sha_wrapper", NULL},
// //     {970, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {971, sorting_wrapper, "sorting_wrapper", NULL},
// //     {972, mser_wrapper, "mser_wrapper", NULL},
// //     {973, disparity_wrapper, "disparity_wrapper", NULL},
// //     {974, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {975, disparity_wrapper, "disparity_wrapper", NULL},
// //     // Scenario 123
// //     {976, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {977, sha_wrapper, "sha_wrapper", NULL},
// //     {978, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {979, sorting_wrapper, "sorting_wrapper", NULL},
// //     {980, mser_wrapper, "mser_wrapper", NULL},
// //     {981, fft_wrapper, "fft_wrapper", NULL},
// //     {982, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {983, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     // Scenario 124
// //     {984, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {985, sha_wrapper, "sha_wrapper", NULL},
// //     {986, disparity_wrapper, "disparity_wrapper", NULL},
// //     {987, disparity_wrapper, "disparity_wrapper", NULL},
// //     {988, sorting_wrapper, "sorting_wrapper", NULL},
// //     {989, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {990, disparity_wrapper, "disparity_wrapper", NULL},
// //     {991, disparity_wrapper, "disparity_wrapper", NULL},
// //     // Scenario 125
// //     {992, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {993, sha_wrapper, "sha_wrapper", NULL},
// //     {994, disparity_wrapper, "disparity_wrapper", NULL},
// //     {995, sha_wrapper, "sha_wrapper", NULL},
// //     {996, fft_wrapper, "fft_wrapper", NULL},
// //     {997, sorting_wrapper, "sorting_wrapper", NULL},
// //     {998, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {999, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     // Scenario 126
// //     {1000, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1001, sha_wrapper, "sha_wrapper", NULL},
// //     {1002, fft_wrapper, "fft_wrapper", NULL},
// //     {1003, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1004, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1005, sha_wrapper, "sha_wrapper", NULL},
// //     {1006, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1007, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     // Scenario 127
// //     {1008, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1009, sha_wrapper, "sha_wrapper", NULL},
// //     {1010, fft_wrapper, "fft_wrapper", NULL},
// //     {1011, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1012, sha_wrapper, "sha_wrapper", NULL},
// //     {1013, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1014, fft_wrapper, "fft_wrapper", NULL},
// //     {1015, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     // Scenario 128
// //     {1016, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1017, sha_wrapper, "sha_wrapper", NULL},
// //     {1018, fft_wrapper, "fft_wrapper", NULL},
// //     {1019, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1020, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1021, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1022, fft_wrapper, "fft_wrapper", NULL},
// //     {1023, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     // Scenario 129
// //     {1024, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1025, sha_wrapper, "sha_wrapper", NULL},
// //     {1026, fft_wrapper, "fft_wrapper", NULL},
// //     {1027, fft_wrapper, "fft_wrapper", NULL},
// //     {1028, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1029, mser_wrapper, "mser_wrapper", NULL},
// //     {1030, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1031, sha_wrapper, "sha_wrapper", NULL},
// //     // Scenario 130
// //     {1032, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1033, sha_wrapper, "sha_wrapper", NULL},
// //     {1034, fft_wrapper, "fft_wrapper", NULL},
// //     {1035, mser_wrapper, "mser_wrapper", NULL},
// //     {1036, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1037, sha_wrapper, "sha_wrapper", NULL},
// //     {1038, sha_wrapper, "sha_wrapper", NULL},
// //     {1039, mser_wrapper, "mser_wrapper", NULL},
// //     // Scenario 131
// //     {1040, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1041, sha_wrapper, "sha_wrapper", NULL},
// //     {1042, mser_wrapper, "mser_wrapper", NULL},
// //     {1043, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1044, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1045, mser_wrapper, "mser_wrapper", NULL},
// //     {1046, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1047, disparity_wrapper, "disparity_wrapper", NULL},
// //     // Scenario 132
// //     {1048, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1049, sha_wrapper, "sha_wrapper", NULL},
// //     {1050, sha_wrapper, "sha_wrapper", NULL},
// //     {1051, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1052, mser_wrapper, "mser_wrapper", NULL},
// //     {1053, fft_wrapper, "fft_wrapper", NULL},
// //     {1054, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1055, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     // Scenario 133
// //     {1056, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1057, sha_wrapper, "sha_wrapper", NULL},
// //     {1058, sha_wrapper, "sha_wrapper", NULL},
// //     {1059, fft_wrapper, "fft_wrapper", NULL},
// //     {1060, fft_wrapper, "fft_wrapper", NULL},
// //     {1061, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1062, fft_wrapper, "fft_wrapper", NULL},
// //     {1063, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     // Scenario 134
// //     {1064, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1065, sha_wrapper, "sha_wrapper", NULL},
// //     {1066, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1067, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1068, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1069, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1070, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1071, sha_wrapper, "sha_wrapper", NULL},
// //     // Scenario 135
// //     {1072, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1073, sha_wrapper, "sha_wrapper", NULL},
// //     {1074, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1075, fft_wrapper, "fft_wrapper", NULL},
// //     {1076, sha_wrapper, "sha_wrapper", NULL},
// //     {1077, fft_wrapper, "fft_wrapper", NULL},
// //     {1078, sha_wrapper, "sha_wrapper", NULL},
// //     {1079, sha_wrapper, "sha_wrapper", NULL},
// //     // Scenario 136
// //     {1080, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1081, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1082, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1083, fft_wrapper, "fft_wrapper", NULL},
// //     {1084, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1085, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1086, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1087, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     // Scenario 137
// //     {1088, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1089, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1090, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1091, mser_wrapper, "mser_wrapper", NULL},
// //     {1092, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1093, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1094, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1095, mser_wrapper, "mser_wrapper", NULL},
// //     // Scenario 138
// //     {1096, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1097, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1098, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1099, sha_wrapper, "sha_wrapper", NULL},
// //     {1100, mser_wrapper, "mser_wrapper", NULL},
// //     {1101, mser_wrapper, "mser_wrapper", NULL},
// //     {1102, mser_wrapper, "mser_wrapper", NULL},
// //     {1103, mser_wrapper, "mser_wrapper", NULL},
// //     // Scenario 139
// //     {1104, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1105, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1106, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1107, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1108, fft_wrapper, "fft_wrapper", NULL},
// //     {1109, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1110, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1111, fft_wrapper, "fft_wrapper", NULL},
// //     // Scenario 140
// //     {1112, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1113, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1114, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1115, fft_wrapper, "fft_wrapper", NULL},
// //     {1116, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1117, fft_wrapper, "fft_wrapper", NULL},
// //     {1118, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1119, disparity_wrapper, "disparity_wrapper", NULL},
// //     // Scenario 141
// //     {1120, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1121, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1122, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1123, fft_wrapper, "fft_wrapper", NULL},
// //     {1124, sha_wrapper, "sha_wrapper", NULL},
// //     {1125, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1126, mser_wrapper, "mser_wrapper", NULL},
// //     {1127, mser_wrapper, "mser_wrapper", NULL},
// //     // Scenario 142
// //     {1128, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1129, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1130, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1131, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1132, fft_wrapper, "fft_wrapper", NULL},
// //     {1133, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1134, mser_wrapper, "mser_wrapper", NULL},
// //     {1135, fft_wrapper, "fft_wrapper", NULL},
// //     // Scenario 143
// //     {1136, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1137, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1138, fft_wrapper, "fft_wrapper", NULL},
// //     {1139, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1140, fft_wrapper, "fft_wrapper", NULL},
// //     {1141, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1142, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1143, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     // Scenario 144
// //     {1144, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1145, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1146, mser_wrapper, "mser_wrapper", NULL},
// //     {1147, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1148, fft_wrapper, "fft_wrapper", NULL},
// //     {1149, fft_wrapper, "fft_wrapper", NULL},
// //     {1150, fft_wrapper, "fft_wrapper", NULL},
// //     {1151, mser_wrapper, "mser_wrapper", NULL},
// //     // Scenario 145
// //     {1152, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1153, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1154, sha_wrapper, "sha_wrapper", NULL},
// //     {1155, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1156, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1157, mser_wrapper, "mser_wrapper", NULL},
// //     {1158, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1159, disparity_wrapper, "disparity_wrapper", NULL},
// //     // Scenario 146
// //     {1160, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1161, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1162, sha_wrapper, "sha_wrapper", NULL},
// //     {1163, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1164, mser_wrapper, "mser_wrapper", NULL},
// //     {1165, mser_wrapper, "mser_wrapper", NULL},
// //     {1166, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1167, disparity_wrapper, "disparity_wrapper", NULL},
// //     // Scenario 147
// //     {1168, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1169, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1170, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1171, fft_wrapper, "fft_wrapper", NULL},
// //     {1172, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1173, fft_wrapper, "fft_wrapper", NULL},
// //     {1174, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1175, mser_wrapper, "mser_wrapper", NULL},
// //     // Scenario 148
// //     {1176, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1177, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1178, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1179, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1180, sha_wrapper, "sha_wrapper", NULL},
// //     {1181, mser_wrapper, "mser_wrapper", NULL},
// //     {1182, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1183, sha_wrapper, "sha_wrapper", NULL},
// //     // Scenario 149
// //     {1184, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1185, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1186, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1187, mser_wrapper, "mser_wrapper", NULL},
// //     {1188, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1189, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1190, fft_wrapper, "fft_wrapper", NULL},
// //     {1191, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     // Scenario 150
// //     {1192, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1193, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1194, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1195, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1196, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1197, fft_wrapper, "fft_wrapper", NULL},
// //     {1198, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1199, mser_wrapper, "mser_wrapper", NULL},
// //     // Scenario 151
// //     {1200, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1201, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1202, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1203, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1204, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1205, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1206, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1207, sha_wrapper, "sha_wrapper", NULL},
// //     // Scenario 152
// //     {1208, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1209, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1210, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1211, fft_wrapper, "fft_wrapper", NULL},
// //     {1212, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1213, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1214, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1215, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     // Scenario 153
// //     {1216, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1217, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1218, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1219, mser_wrapper, "mser_wrapper", NULL},
// //     {1220, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1221, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1222, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1223, sorting_wrapper, "sorting_wrapper", NULL},
// //     // Scenario 154
// //     {1224, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1225, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1226, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1227, mser_wrapper, "mser_wrapper", NULL},
// //     {1228, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1229, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1230, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1231, fft_wrapper, "fft_wrapper", NULL},
// //     // Scenario 155
// //     {1232, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1233, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1234, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1235, sha_wrapper, "sha_wrapper", NULL},
// //     {1236, mser_wrapper, "mser_wrapper", NULL},
// //     {1237, fft_wrapper, "fft_wrapper", NULL},
// //     {1238, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1239, disparity_wrapper, "disparity_wrapper", NULL},
// //     // Scenario 156
// //     {1240, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1241, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1242, fft_wrapper, "fft_wrapper", NULL},
// //     {1243, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1244, fft_wrapper, "fft_wrapper", NULL},
// //     {1245, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1246, sha_wrapper, "sha_wrapper", NULL},
// //     {1247, sha_wrapper, "sha_wrapper", NULL},
// //     // Scenario 157
// //     {1248, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1249, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1250, sha_wrapper, "sha_wrapper", NULL},
// //     {1251, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1252, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1253, sha_wrapper, "sha_wrapper", NULL},
// //     {1254, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1255, sorting_wrapper, "sorting_wrapper", NULL},
// //     // Scenario 158
// //     {1256, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1257, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1258, sha_wrapper, "sha_wrapper", NULL},
// //     {1259, mser_wrapper, "mser_wrapper", NULL},
// //     {1260, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1261, fft_wrapper, "fft_wrapper", NULL},
// //     {1262, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1263, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     // Scenario 159
// //     {1264, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1265, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1266, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1267, sha_wrapper, "sha_wrapper", NULL},
// //     {1268, fft_wrapper, "fft_wrapper", NULL},
// //     {1269, sha_wrapper, "sha_wrapper", NULL},
// //     {1270, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1271, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     // Scenario 160
// //     {1272, disparity_wrapper, "disparity_wrapper", NULL},
// //     {1273, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1274, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1275, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1276, bandwidth_wrapper, "bandwidth_wrapper", NULL},
// //     {1277, dijkstra_wrapper, "dijkstra_wrapper", NULL},
// //     {1278, sorting_wrapper, "sorting_wrapper", NULL},
// //     {1279, sha_wrapper, "sha_wrapper", NULL},
// // };

// int _get_info_index(int vm_num, int task_num) {
//   int index =
//       (vm_num * TASK_QUANTITY + task_num) + (MAX_TASKS * BENCH_ARRAY_INDEX);
//   if (index < 0 || index >= NUM_BENCHMARKS) {
//     printf("Invalid get_benchmark_index call %d\n", index);
//     return -1;
//   }
//   return index;
// }

// // #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#

// #include "../inc/data.h"

// ///////////////////
// // int *g_mem_ptr = NULL; // bandwidth
// // I2D *It = NULL;
// //
// // void init_data() {
// //   // bandwitdh
// //   g_mem_ptr = (int *)malloc(BW_DEFAULT_ALLOC_SIZE);
// //   memset((char *)g_mem_ptr, 1, BW_DEFAULT_ALLOC_SIZE);
// //   for (uint64_t i = 0; i < BW_DEFAULT_ALLOC_SIZE / sizeof(int); i++) {
// //     g_mem_ptr[i] = i;
// //   }
// //
// //   // mser
// //   int i, j, k;
// //   I2D *I;
// //   // I2D *It;
// //   int rows = 196, cols = 98;
// //
// //   I = (I2D *)mserb;
// //   rows = I->height;
// //   cols = I->width;
// //
// //   It = (I2D *)mserb1;
// //
// //   k = 0;
// //   for (i = 0; i < cols; i++) {
// //     for (j = 0; j < rows; j++) {
// //       asubsref(It, k++) = subsref(I, j, i);
// //     }
// //   }
// // }
// //
// // void free_data() {
// //   // bandwitdh
// //   free(g_mem_ptr);
// // }

// typedef struct {
//   int *mem_ptr;
//   uint64_t sum;
// } bandwidth_context_t;

// typedef struct {
//   I2D *It;
// } mser_context_t;

// void empty_wrapper(void *context) {
//   while (1) {
//     printf("\t(empty_wrapper) this should never happen.\n");
//   }
// }

// void bandwidth_wrapper(void *context) {
//   // bandwidth_context_t *c = (bandwidth_context_t *)context;

//   // c->sum += bench_read(c->mem_ptr);
//   // c->sum += bench_write(c->mem_ptr);

//   return;
// }

// void dijkstra_wrapper(void *context) {
//   // int i, j, k;

//   // for (i = 0, j = NUM_NODES / 2; i < 100; i++, j++) {
//   //   j = j % NUM_NODES;
//   //   dijkstra(i, j);
//   // }

//   return;
// }

// void disparity_wrapper(void *context) {
//   // I2D *imleft = (I2D *)img1;
//   // I2D *imright = (I2D *)img2;
//   // int WIN_SZ = 8, SHIFT = 64;
//   // char signature[2] = {66, 77};
//   // short int bits_per_pixel = 24;

//   // // Check if images are valid BMP images.
//   // if (imleft->height <= 0 || imleft->width <= 0 || signature[0] != 'B' ||
//   //     signature[1] != 'M' || (bits_per_pixel != 24 && bits_per_pixel != 8)) {
//   //   return;
//   // }

//   // if (imright->height <= 0 || imright->width <= 0 || signature[0] != 'B' ||
//   //     signature[1] != 'M' || (bits_per_pixel != 24 && bits_per_pixel != 8)) {
//   //   return;
//   // }

//   // I2D *retDisparity = getDisparity(imleft, imright, WIN_SZ, SHIFT);
//   return;
// }

// void fft_wrapper(void *context) {
//   // uint32_t A_re[NUM_POINTS];
//   // uint32_t A_im[NUM_POINTS];
//   // uint32_t W_re[NUM_POINTS / 2];
//   // uint32_t W_im[NUM_POINTS / 2];

//   // int n = NUM_POINTS;
//   // init_array(n, A_re, A_im);
//   // compute_W(n, W_re, W_im);
//   // fft(n, A_re, A_im, W_re, W_im);
//   // permute_bitrev(n, A_re, A_im);

//   return;
// }

// void mser_wrapper(void *context) {
//   // mser_context_t *c = (mser_context_t *)context;
//   // mser(c->It, 2);
//   return;
// }

// void qsort_wrapper(void *context) {
//   // struct my3DVertexStruct array[QSORT_MAXARRAY];

//   // int numRows = sizeof(qsort_input_data) / sizeof(qsort_input_data[0]);
//   // int count = 0;

//   // // Process the array instead of reading from a file
//   // for (int i = 0; i < numRows && count < QSORT_MAXARRAY; i++) {
//   //   array[count].x = qsort_input_data[i][0];
//   //   array[count].y = qsort_input_data[i][1];
//   //   array[count].z = qsort_input_data[i][2];
//   //   array[count].distance = (array[count].x * array[count].x) +
//   //                           (array[count].y * array[count].y) +
//   //                           (array[count].z * array[count].z);
//   //   count++;
//   // }

//   // qsort(array, count, sizeof(struct my3DVertexStruct), qsort_compare);
//   return;
// }

// void sha_wrapper(void *context) {
//   // SHA_INFO sha_info;
//   // sha_stream(&sha_info);
//   return;
// }

// void sorting_wrapper(void *context) {
//   // int orig[MAX_SORTING], copy[MAX_SORTING], i;

//   // void *function[NUM_SORT] = {&selection_sort, &quick_sort,     &shell_sort,
//   //                             &stdlib_qsort,   &insertion_sort, &bubble_sort};
//   // char *sort_name[NUM_SORT] = {"Selection sort", "Quicksort",
//   //                              "Shellsort",      "Qsort",
//   //                              "Insertion sort", "Bubble sort"};

//   // fill_array(orig, MAX_SORTING);

//   // for (i = 0; i < NUM_SORT; i++) {
//   //   execute_sort(orig, copy, MAX_SORTING, sort_name[i], function[i]);
//   // }

//   return;
// }

// //------------------------------------------//

// // NEW: Function to create and initialize a unique context for every task
// void initialize_all_benchmark_contexts() {
//   // Calculate the starting point of the active benchmark "window"
//   int start_index = (VM_QNT * TASK_QUANTITY) * BENCH_ARRAY_INDEX;
//   int num_active_benchmarks = VM_QNT * TASK_QUANTITY;
//   int end_index = start_index + num_active_benchmarks;

//   if (end_index > NUM_BENCHMARKS) {
//     printf("ERROR: Active benchmark range exceeds NUM_BENCHMARKS!\n");
//     return;
//   }

//   // Loop ONLY over the active benchmarks
//   for (int i = start_index; i < end_index; i++) {
//     Function *f = &_local_function_table[i];

//     if (strcmp(f->name, "bandwidth_wrapper") == 0) {
//       // This part was already correct and doesn't need changes.
//       // It correctly allocates memory within the task's private context.
//       bandwidth_context_t *ctx = malloc(sizeof(bandwidth_context_t));
//       ctx->mem_ptr = (int *)malloc(BW_DEFAULT_ALLOC_SIZE);
//       memset((char *)ctx->mem_ptr, 1, BW_DEFAULT_ALLOC_SIZE);
//       for (uint64_t j = 0; j < BW_DEFAULT_ALLOC_SIZE / sizeof(int); j++) {
//         ctx->mem_ptr[j] = j;
//       }
//       ctx->sum = 0;
//       f->context = ctx;
//     } else if (strcmp(f->name, "mser_wrapper") == 0) {
//       // NEW: MSER logic is now integrated here.
//       mser_context_t *ctx = malloc(sizeof(mser_context_t));

//       // Perform MSER-specific data preparation (image transposition)
//       I2D *I = (I2D *)mserb;   // Source image from global data
//       I2D *It = (I2D *)mserb1; // Destination buffer from global data

//       int rows = I->height;
//       int cols = I->width;
//       int k = 0;

//       for (int col_idx = 0; col_idx < cols; col_idx++) {
//         for (int row_idx = 0; row_idx < rows; row_idx++) {
//           asubsref(It, k++) = subsref(I, row_idx, col_idx);
//         }
//       }

//       // Assign the prepared (transposed) image buffer to the context
//       ctx->It = It;
//       f->context = ctx;
//     }
//     // ... add other 'else if' blocks as needed ...
//     else {
//       f->context = NULL;
//     }
//   }
//   _context_initialized = true;
// }

// // NEW: Function to clean up all allocated contexts
// void free_all_benchmark_contexts() {
//   // Calculate the exact same "window" of active benchmarks as the init function
//   int start_index = (VM_QNT * TASK_QUANTITY) * BENCH_ARRAY_INDEX;
//   int num_active_benchmarks = VM_QNT * TASK_QUANTITY;
//   int end_index = start_index + num_active_benchmarks;

//   // Safety check
//   if (end_index > NUM_BENCHMARKS)
//     return;

//   // Loop ONLY over the active benchmarks that were initialized
//   for (int i = start_index; i < end_index; i++) {
//     Function *f = &_local_function_table[i];

//     // Only try to free contexts that were actually allocated
//     if (f->context != NULL) {

//       // Perform a "deep free" for contexts that contain their own malloc'd
//       // pointers. This correctly replaces the old "free(g_mem_ptr)".
//       if (strcmp(f->name, "bandwidth_wrapper") == 0) {
//         bandwidth_context_t *ctx = (bandwidth_context_t *)f->context;
//         free(ctx->mem_ptr); // First, free the memory INSIDE the context
//       } else if (strcmp(f->name, "mser_wrapper") == 0) {
//         // Currently, mser_context->It points to a global buffer (mserb1),
//         // so we don't need to free it. If you change the init logic to
//         // malloc memory for It, you would add a free() call here.
//       }

//       // Finally, free the context struct itself. This is done for ALL
//       // contexts that were allocated (bandwidth, mser, etc.).
//       free(f->context);
//     }
//   }
// }
