#ifndef __ARR_H
#define __ARR_H

#include <stdlib.h>

/**
 * Returns:
 * a positive number if a > b;
 * 0 if a == b;
 * a negative number if a < b;
 */
typedef int (*ARR_COMPARE)(void *a, void *b);

/**
 * Returns a quantity of the element
 */
typedef double (*ARR_QUANTIFY)(void *a);

void *_arr_new(size_t data_size, int n);
void arr_resize(int n);
void arr_free(void *array);

int arr_len(void *array);
void arr_set_comparator(ARR_COMPARE func, void *array);
void arr_set_quantifier(ARR_QUANTIFY func, void *array);

int arr_argmin(void *array);
int arr_argmax(void *array);
void *_arr_min(void *array);
void *_arr_max(void *array);
int _arr_indexof(void *value, void *array);
double arr_sum(void *array);
double arr_avg(void *array);

#define arr_new(TYPE, N) \
  ((TYPE *)_arr_new(sizeof(TYPE), N))
#define arr_min(ARRAY) *((typeof(ARRAY))_arr_min(ARRAY))
#define arr_max(ARRAY) *((typeof(ARRAY))_arr_max(ARRAY))
#define arr_indexof(VALUE, ARRAY) _arr_indexof(&VALUE, ARRAY)

#define arr_swap(ARRAY, I, J)      \
  {                                \
    typeof(*ARRAY) tmp = ARRAY[I]; \
    ARRAY[I] = ARRAY[J];           \
    ARRAY[J] = tmp;                \
  }

#define arr_fill(ARRAY, VALUE)             \
  for (int i = 0; i < arr_len(ARRAY); ++i) \
    ARRAY[i] = VALUE;

#endif