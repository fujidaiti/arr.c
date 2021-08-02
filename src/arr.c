#ifndef __ARR_C
#define __ARR_C

#include "arr.h"
#include <assert.h>

typedef struct
{
  int len;
  size_t data_size;
  ARR_COMPARE compare_func;
  ARR_QUANTIFY quantify_func;
} __ARR;

#define HEADER(ARRAY) \
  ((__ARR *)((char *)ARRAY - sizeof(__ARR)))

#define ELEMENT(INDEX, ARRAY) \
  (((char *)ARRAY) + HEADER(ARRAY)->data_size * INDEX)

void *_arr_new(size_t data_size, int n)
{
  assert(n >= 0);
  __ARR *header = (__ARR *)malloc(
      data_size * n + sizeof(__ARR));
  header->data_size = data_size;
  header->len = n;
  header->compare_func = NULL;
  return ((char *)header) + sizeof(__ARR);
}

void arr_free(void *array)
{
  free(HEADER(array));
}

int arr_len(void *array)
{
  return HEADER(array)->len;
}

void arr_set_comparator(ARR_COMPARE func, void *array)
{
  HEADER(array)->compare_func = func;
}

void arr_set_quantifier(ARR_QUANTIFY func, void *array)
{
  HEADER(array)->quantify_func = func;
}

static int arg(void *array, int sign)
{

  __ARR *header = HEADER(array);
  ARR_COMPARE compare = header->compare_func;
  assert(compare != NULL);

  if (header->len == 0)
    return -1;

  int i_arg = 0;
  void *elm_arg = ELEMENT(0, array);
  for (int i = 1; i < header->len; ++i)
  {
    void *elm = ELEMENT(i, array);
    if (sign * compare(elm, elm_arg) > 0)
    {
      i_arg = i;
      elm_arg = elm;
    }
  }
  return i_arg;
}

int arr_argmin(void *array)
{
  return arg(array, -1);
}

void *_arr_min(void *array)
{
  return ELEMENT(arr_argmin(array), array);
}

int arr_argmax(void *array)
{
  return arg(array, 1);
}

void *_arr_max(void *array)
{
  return ELEMENT(arr_argmax(array), array);
}

int _arr_indexof(void *value, void *array)
{
  ARR_COMPARE compare = HEADER(array)->compare_func;
  assert(compare != NULL);
  for (int i = 0; i < arr_len(array); ++i)
  {
    void *elm = ELEMENT(i, array);
    if (compare(elm, value) == 0)
      return i;
  }
  return -1;
}

double arr_sum(void *array)
{
  ARR_QUANTIFY quantify = HEADER(array)->quantify_func;
  assert(quantify != NULL);
  double sum = 0;
  for (int i = 0; i < arr_len(array); ++i)
  {
    sum += quantify(ELEMENT(i, array));
  }
  return sum;
}

double arr_avg(void *array)
{
  return arr_sum(array) / arr_len(array);
}

#endif