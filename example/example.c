#include "../src/arr.h"

#include <stdio.h>

typedef int IntArr;

void print_a(IntArr *array)
{
  printf("[ ");
  for (int i = 0; i < arr_len(array); ++i)
  {
    printf("%d ", array[i]);
  }
  printf("]\n");
}

int comparator(void *a, void *b)
{
  return *(int *)a - *(int *)b;
}

double quantifier(void *a)
{
  return *(int *)a;
}

void main()
{
  IntArr *a = arr_new(int, 10);
  arr_set_comparator(comparator, a);
  arr_set_quantifier(quantifier, a);

  for (int i = 0; i < arr_len(a); ++i)
    a[i] = (i + 1) * 10;

  print_a(a);

  printf("argmin=%d\n", arr_argmin(a));
  printf("argmax=%d\n", arr_argmax(a));

  printf("min=%d\n", arr_min(a));
  printf("max=%d\n", arr_max(a));

  arr_swap(a, 0, 9);
  print_a(a);

  int x = 60;
  printf("index of %d=%d\n", x, arr_indexof(x, a));

  printf("sum=%lf\n", arr_sum(a));
  printf("avg=%lf\n", arr_avg(a));

  arr_fill(a, -1);
  print_a(a);

  arr_free(a);
}