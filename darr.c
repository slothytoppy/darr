#include <stdbool.h>

#include "./darr.h"

bool darr_alloc(darr* darr, unsigned count) {
  darr->items = calloc(1, (count + 1) * sizeof(void*));
  if(darr->items == NULL) {
    darr_reset(darr);
    return false;
  } else {
    darr_set_cap(darr, count);
    return true;
  }
}

bool darr_realloc(darr* darr, unsigned count) {
  darr->items = realloc(darr->items, (count + 1) * sizeof(void*));
  if(darr->items == NULL) {
    darr_reset(darr);
    return false;
  } else {
    darr_set_cap(darr, count);
    return true;
  }
}

bool darr_init(darr* darr, unsigned capacity) {
  if(darr_alloc(darr, capacity) != true) {
    return false;
  }
  darr_set_cap(darr, capacity);
  return true;
}

bool darr_over_cap(darr* darr) {
  if(darr->count >= darr->capacity) {
    return true;
  }
  return false;
}

bool darr_append(darr* darr, void* data) {
  if(darr->capacity == 0) {
    darr_init(darr, 255);
  } else {
    if(darr_over_cap(darr) == ok) {
      darr->capacity *= 2;
      darr_realloc(darr, darr->capacity);
    }
  }
  if(darr->items == NULL) {
    return false;
  }
  darr->items[darr->count] = data;
  darr->count += 1;
  darr->items[darr->count] = NULL;
  return false;
}

bool is_darr_empty(darr darr) {
  if(darr.capacity <= 0) {
    return true;
  } else {
    return false;
  }
}

bool is_darr_full(darr darr) {
  if(darr.count == darr.capacity) {
    return true;
  } else {
    return false;
  }
}

darr_error_type darr_append_index(darr* darr, void* data, unsigned index) {
  if(is_darr_empty(*darr) == true) {
    return darr_empty;
  }
  if(index > darr->capacity) {
    return index_out_of_range;
  }
  if(darr->count + 1 == darr->capacity) {
    if(darr_realloc(darr, darr->count + 2) != ok) {
      return alloc_error;
    }
    // darr->count+2 so that you have room for data + NULL
  }
  darr->items[index] = data;
  darr->count += 1;
  darr->items[index] = NULL;
  return ok;
}

darr_error_type darr_delete_index(darr* darr, unsigned arr[], unsigned count) {
  if(is_darr_empty(*darr) == true) {
    return darr_empty;
  }
  for(unsigned i = 0; i < darr->count; i++) {
    if(arr[i] > darr->count) {
      return delete_error;
    }
    darr->items[arr[i]] = NULL;
  }
  return ok;
}

void darr_push(darr* darr, void* data) {
  darr->items[darr->count] = data;
  darr->count += 1;
  darr->items[darr->count] = NULL;
}

void darr_delete(darr* darr) {
  darr->count = 0;
  darr->capacity = 0;
  darr->items = NULL;
}
void darr_reset_cap(darr* darr) {
  darr->capacity = 0;
}

void darr_reset_count(darr* darr) {
  darr->count = 0;
}

void darr_set_cap(darr* darr, unsigned capacity) {
  darr->capacity = capacity;
}

void darr_double_cap(darr* darr) {
  darr->capacity *= 2;
}

void darr_set_count(darr* darr, unsigned count) {
  darr->count = count;
}

void darr_inc_count(darr* darr) {
  darr->count += 1;
}

void darr_reset(darr* darr) {
  darr_reset_cap(darr);
  darr_reset_count(darr);
  free(darr->items);
}
