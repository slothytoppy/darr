#ifndef DARR_H
#define DARR_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct darr {
  unsigned count;
  unsigned capacity;
  void** items;
} darr;

typedef enum darr_return_type {
  ok = 1,
  delete_error = 2,
  darr_empty = 3,
  alloc_error = 4,
  index_out_of_range = 5,
} darr_error_type;

bool darr_alloc(darr* darr, unsigned count);
bool darr_realloc(darr* darr, unsigned count);
bool darr_init(darr* darr, unsigned capacity);
bool darr_over_cap(darr* darr);
bool darr_append(darr* darr, void* data);
bool is_darr_empty(darr darr);
bool is_darr_full(darr darr);
darr_error_type darr_append_index(darr* darr, void* data, unsigned index);
darr_error_type darr_delete_index(darr* darr, unsigned arr[], unsigned count);
void darr_push(darr* darr, void* data);
void darr_delete(darr* darr);
void darr_reset_cap(darr* darr);
void darr_reset_count(darr* darr);
void darr_set_cap(darr* darr, unsigned capacity);
void darr_double_cap(darr* darr);
void darr_set_count(darr* darr, unsigned count);
void darr_inc_count(darr* darr);
void darr_reset(darr* darr);

#endif
