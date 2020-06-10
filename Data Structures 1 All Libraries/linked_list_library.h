#ifndef LINKED_LIST_LIBRARY_H_
#define LINKED_LIST_LIBRARY_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct LINKED_LIST_NODE_s *LINKED_LIST_NODE;
typedef struct LINKED_LIST_NODE_s{
	LINKED_LIST_NODE next; /* Do not change order */
	void *data;
} LINKED_LIST_NODE_t[1];

typedef struct LINKED_LIST_s *LINKED_LIST;
typedef struct LINKED_LIST_s{
  	LINKED_LIST_NODE head; /* May overlap with next. */
} LINKED_LIST_t[1], *LINKED_LIST;

typedef struct DATA_s{
	void *data;
} DATA_t[1], *DATA;

LINKED_LIST linked_list_init();
LINKED_LIST_NODE linked_node_init(void *data);
LINKED_LIST_NODE goto_idx(LINKED_LIST_NODE curr,int idx);
void linked_list_free(LINKED_LIST list);
void linked_list_prepend(LINKED_LIST list, void *data);
void linked_list_append(LINKED_LIST list, void *data);
void linked_list_insert(LINKED_LIST list, void *data, int idx);
void linked_list_set(LINKED_LIST list,void *data, int idx);
void *linked_list_get(LINKED_LIST list, int idx);
void *linked_list_remove(LINKED_LIST list, int idx);
int linked_list_size(LINKED_LIST list);
void linked_list_removeall(LINKED_LIST list);
void linked_list_concatenate(LINKED_LIST list, LINKED_LIST list2);
void linked_list_fprint(LINKED_LIST list, FILE *fp, void (*print_type) (FILE*, void*));
void integer_printer(FILE *fp, void *data);
void char_printer(FILE *fp, void *data);


DATA data_init(void *data);


#endif /* LINKED_LIST_LIBRARY_H_ */
