#ifndef SORTING_H
#define SORTING_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*--------------------
 Preprocessor Section
 ---------------------*/
#define MAX_SORTING 128//65535
#define NUM_SORT   6


void fill_array( int arr[], int array_size );
void bubble_sort( int a[], int array_size );
void selection_sort(int numbers[], int array_size);
void shell_sort(int numbers[], int array_size);
void insertion_sort(int numbers[], int array_size);
void q_sort(int numbers[], int left, int right);
void quick_sort(int numbers[], int array_size);
int compare(const void *m, const void *n);
void stdlib_qsort( int numbers[], int array_size );
void execute_sort( int const orig[], int copy[], int array_size, char* sort_name,
				   void (*sort_function)(int[], int) ) ;


#endif
