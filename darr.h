#ifndef DARR_H
#define DARR_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct darr {
  unsigned count;
  unsigned capacity;
  int (*append_func)(struct darr darr, void*);
  void** items;
  char pre_initialized;
} darr;

typedef enum darr_error_type {
  append_error = 0,
  ok = 1,
  delete_error = 2,
  init_error = 3,
  darr_empty = 4,
  darr_not_empty = 5,
  alloc_error = 6,
  darr_cap_empty = 7,
  index_out_of_range = 8,
} darr_error_type;

darr_error_type darr_alloc(darr* darr, unsigned count);
darr_error_type darr_realloc(darr* darr, unsigned count);
darr_error_type darr_init(darr* darr, unsigned capacity);
darr_error_type darr_over_cap(darr* darr);
darr_error_type darr_append_index(darr* darr, void* data, unsigned index);
darr_error_type darr_push(darr* darr, void* data);
darr_error_type darr_append(darr* darr, void* data);
darr_error_type darr_delete_index(darr* darr, unsigned arr[], unsigned count);
void darr_delete(darr* darr);
unsigned is_darr_empty(darr darr);
unsigned is_darr_full(darr darr);

#endif
