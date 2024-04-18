#include "./darr.h"

darr_error_type darr_alloc(darr* darr, unsigned count) {
  darr->items = calloc(1, count * sizeof(void*));
  if(darr->items == NULL) {
    darr->capacity = 0;
    return alloc_error;
  } else {
    darr->capacity = count;
    return ok;
  }
}

darr_error_type darr_realloc(darr* darr, unsigned count) {
  darr->items = realloc(darr->items, count * sizeof(void*));
  if(darr->items == NULL) {
    darr->capacity = 0;
    return alloc_error;
  } else {
    darr->capacity = count;
    return ok;
  }
}

darr_error_type darr_init(darr* darr, unsigned capacity) {
  darr->items = calloc(1, capacity * sizeof(darr->items));
  if(darr->items == NULL) {
    darr->capacity = 0;
    return init_error;
  }
  darr->capacity = capacity;
  darr->pre_initialized = 1;
  return ok;
}

darr_error_type darr_over_cap(darr* darr) {
  if(darr->capacity <= 0) {
    return darr_cap_empty;
  } else if(darr->count >= darr->capacity) {
    darr->capacity *= 2;
    darr->items = realloc(darr->items, darr->capacity * sizeof(void*));
  }
  if(darr->items == NULL) {
    return alloc_error;
  } else {
    return ok;
  }
}

unsigned darr_append_index(darr* darr, void* data, unsigned index) {
  if(is_darr_empty(*darr) == darr_empty) {
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

unsigned darr_push(darr* darr, void* data) {
  if(is_darr_empty(*darr) == darr_empty) {
    return darr_empty;
  }
  darr->items[darr->count] = data;
  darr->count += 1;
  darr->items[darr->count] = NULL;
  return ok;
}

unsigned darr_append(darr* darr, void* data) {
  if(darr->append_func) {
    if(darr->append_func(*darr, data) == ok) {
      return ok;
    } else {
      return append_error;
    }
  }
  if(darr->count == 0) {
    if(darr->pre_initialized == 0) {
      darr->capacity = 8;
    }
    darr_alloc(darr, darr->capacity);
  } else {
    if(darr->count >= darr->capacity) {
      darr_over_cap(darr);
    } else {
      darr_realloc(darr, darr->count + 1);
    }
  }
  if(darr->items == NULL) {
    return alloc_error;
  }
  darr_push(darr, data);
  return ok;
}

unsigned darr_delete_index(darr* darr, unsigned arr[], unsigned count) {
  if(is_darr_empty(*darr)) {
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

void darr_delete(darr* darr) {
  darr->count = 0;
  darr->capacity = 0;
  darr->items = NULL;
}

darr_error_type is_darr_empty(darr darr) {
  if(darr.capacity <= 0) {
    return darr_empty;
  } else {
    return darr_not_empty;
  }
}

unsigned is_darr_full(darr darr) {
  if(darr.count == darr.capacity) {
    return 1;
  } else {
    return darr_empty;
  }
}
