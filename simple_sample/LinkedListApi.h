#ifndef LINKEDLISTAPI_H
#define LINKEDLISTAPI_H

typedef struct _ll_node ll_node;  /* opeque structure */
typedef struct _ll_ ll_t;         /* opeque structure */
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

#endif
