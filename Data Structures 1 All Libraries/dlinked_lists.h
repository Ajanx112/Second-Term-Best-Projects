#ifndef DLINKED_LISTS_H_
#define DLINKED_LISTS_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct DLINKED_LIST_NODE_s *DLINKED_LIST_NODE;
typedef struct DLINKED_LIST_NODE_s
{
 DLINKED_LIST_NODE next; /*Do not change the order.*/
 DLINKED_LIST_NODE prev;
 void *data;
} DLINKED_LIST_NODE_t[1];


typedef struct DLINKED_LIST_s *DLINKED_LIST;
typedef struct DLINKED_LIST_s
{
 DLINKED_LIST_NODE head; /*May overlap with next.*/
} DLINKED_LIST_t[1];


DLINKED_LIST dlinked_list_init();
DLINKED_LIST_NODE dlinked_node_init(void *data);//HELPER FUNC
void dlinked_list_free(DLINKED_LIST list);
DLINKED_LIST_NODE goto_idx(DLINKED_LIST_NODE curr,int idx);//HELPER FUNC
void dlinked_list_prepend(DLINKED_LIST list, void *data);
void dlinked_list_append(DLINKED_LIST list, void *data);
void dlinked_list_insert(DLINKED_LIST list, void *data, int idx);
int dlinked_list_size(DLINKED_LIST list);
void dlinked_list_set(DLINKED_LIST list, void *data, int idx);
void *dlinked_list_get(DLINKED_LIST list, int idx);
void *dlinked_list_remove(DLINKED_LIST list, int idx);
void dlinked_list_removeall(DLINKED_LIST list);
void integer_printer(FILE *fp, void *data);
void char_printer(FILE *fp, void *data);
void dlinked_list_fprint(DLINKED_LIST list, FILE *fp, void (*print_type) (FILE*, void*));

#endif /* DLINKED_LISTS_H_ */
