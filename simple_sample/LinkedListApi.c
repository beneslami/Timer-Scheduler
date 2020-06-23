#include "LinkedListApi.h"
#include <stdlib.h>

struct _ll_node {
  void* data;
  struct _ll_ *next;
};

struct _ll_{
  ll_node *head;
  unsigned int node_count;
  int (*comparison_fn)(void*, void*);
  int (*order_comparison_fn)(void*, void*);
};

ll_t*
init_singly_ll(){
  ll_t *head = calloc(1, sizeof(ll_t));
  return head;
}
