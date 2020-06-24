#include "LinkedListApi.h"
#include <stdlib.h>
#include <assert.h>

struct _ll_node { /* ll_node */
  void* data;
  struct _ll_node *next;
};

struct _ll_{    /* ll_t */
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

int 
add_node_by_val(ll_t *ll , void *data){
  ll_node *node = calloc(1, sizeof(ll_node));
  node->data = data;
  if(!ll->head){
    ll->head = node;
    ll->node_count++;
    return 0;
  }
  node->next = ll->head;
  ll->node_count++;
  return 0;
}
