#ifndef LINKEDLISTAPI_H
#define LINKEDLISTAPI_H

typedef struct _ll_node ll_node;  /* opeque structure */
typedef struct _ll_ ll_t;         /* opeque structure */

ll_t*
init_singly_ll();
int 
add_node_by_val(ll_t*, void*);
#endif
