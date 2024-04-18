#include "./darr.h"

int main(void) {
  darr darr = {0};
  darr_alloc(&darr, 10);
  darr_realloc(&darr, 100);
  darr_push(&darr, "hello");
  printf("%d\n", darr.capacity);
  printf("%s\n", darr.items[0]);
}
