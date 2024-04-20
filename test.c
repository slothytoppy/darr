#include "./darr.h"

int main(void) {
  darr darr = {0};
  darr_init(&darr, 20);
  darr_append(&darr, "a");
  darr_append(&darr, "a");
  darr_append(&darr, "a");
  darr_append(&darr, "a");
  darr_append(&darr, "a");
  darr_append(&darr, "a");
  darr_append(&darr, "a");
  darr_append(&darr, "a");
  darr_append(&darr, "a");
  darr_append(&darr, "a");
  darr_append(&darr, "a");
  darr_append(&darr, "a");
  darr_append(&darr, "a");
  darr_append(&darr, "b");
  darr_append(&darr, "a");
  darr_append(&darr, "a");
  darr_append(&darr, "b");
  darr_append(&darr, "b");
  darr_append(&darr, "b");
  darr_append(&darr, "b");
  darr_append(&darr, "b");
  printf("cap %d\n", darr.capacity);
  printf("count %d\n", darr.count);
  printf("%s\n", darr.items[0]);
  printf("%s\n", darr.items[1]);
  darr_reset(&darr);
  printf("cap %d\n", darr.capacity);
  printf("count %d\n", darr.count);
}
