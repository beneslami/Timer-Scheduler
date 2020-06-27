#ifndef LINKEDLISTAPI_H
#define LINKEDLISTAPI_H

typedef struct _ll_node{
  void* data;
  struct _ll_node *next;
}ll_node;

typedef struct _ll_{
  ll_node *head;
  unsigned int node_count;
  int (*comparison_fn)(void*, void*);
  int (*order_comparison_fn)(void*, void*);
}ll_t;

typedef enum _bool_{
  LL_FALSE,
  LL_TRUE
} bool_t;       /* opeque structure */

/* function declarations */
ll_t*
init_singly_ll();
int
add_node_by_val(ll_t*, void*);
bool_t
is_ll_empty(ll_t*);
int
ll_remove_node(ll_t*, ll_node*);
int
ll_add_node(ll_t*, ll_node*);
int
ll_delete_node(ll_t*, ll_node*);

/* Macros */
#define ITERATE_LIST_BEGIN(list_ptr, node_ptr)      \
  {                                                 \
    ll_node *node = NULL;                           \
    node = list_ptr->head;                          \
    for(; node != NULL; node = node_ptr){           \
      node = node_ptr->next;

#define ITERATE_LIST_END(list_ptr, node_ptr) }}

#define ITERATE_LIST_BEGIN_ENHANCED(list_ptr, node_ptr, prev)   \
  {                                                             \
    ll_node *_node_ptr = NULL;                                  \
    ll_node *prev = NULL;                                       \
    node_ptr = list_ptr->head;                                  \
    for(;node_ptr != NULL; node_ptr = _node_ptr){               \
      _node_ptr = node_ptr->next;

#define ITERATE_LIST_CONTINUE_ENHANCED(list_ptr, node_ptr, prev)  \
  {                                                               \
    if(node_ptr) prev = node_ptr;                                 \
    continue;}

#define ITERATE_LIST_BREAK(list_ptr, node_ptr, prev)   break;

#define ITERATE_LIST_NODE_DELETE_ENHANCED(list_ptr, node_ptr, prev)   \
  {if(node_ptr && prev == NULL){                                      \
    list_ptr->head = node_ptr_next;                                   \
  }                                                                   \
  else if(node_ptr && prev){                                          \
      prev->next = node_ptr->next;                                    \
  }                                                                   \
  free(node_ptr);                                                     \
  list_ptr->node_count--;                                             \
  node_ptr = NULL;}

#define ITERATE_LIST_END_ENHANCED(list_ptr, node_ptr, prev)      \
  if(node_ptr) prev = node_ptr; }}


#endif
