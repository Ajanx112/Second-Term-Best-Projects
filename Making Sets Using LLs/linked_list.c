#include "linked_list_library.h"
#include <stdlib.h>
#include <stdio.h>

LINKED_LIST linked_list_init() {
	LINKED_LIST new;

	new = malloc(sizeof(LINKED_LIST_t));
	if (new != NULL){
		new->head = NULL;
	} else {
		printf("Error @linked_list_init");
	}

	return new;
}

void linked_list_free(LINKED_LIST list){
	if(list->head!=NULL)
		linked_list_removeall(list);
	free(list);
}

LINKED_LIST_NODE linked_node_init(void *data) {
	LINKED_LIST_NODE new;
	new = malloc(sizeof(LINKED_LIST_NODE_t));
	new->data = data;
	new->next = NULL;

	return new;
}

DATA data_init(void *data) {
	DATA new;

	new = malloc(sizeof(DATA_t));
	new->data = data;

	return new;
}

void linked_list_append(LINKED_LIST list, void *data) {
	LINKED_LIST_NODE node, new;

	new = linked_node_init(data);
	node = (LINKED_LIST_NODE)list;
	while (node->next != NULL) {
		node = node->next;
	}
	node->next = new;
}

void linked_list_prepend(LINKED_LIST list, void *data) {
	LINKED_LIST_NODE new =linked_node_init(data);
	new->next = list->head;
	list->head = new;
}

int linked_list_size(LINKED_LIST list) {
	LINKED_LIST_NODE node = list->head;
	int size=0;
	while(node!=NULL){
		node = node->next;
		size++;
	}
	return size;
}

//HELPER FUNC
LINKED_LIST_NODE goto_idx(LINKED_LIST_NODE curr,int idx){
	int i;
	for(i=0;i<=idx;i++){//equal sign is needed as we usually call goto_idx with the casted LINKED_LIST
		curr = curr->next;
	}
	return curr;
}

void linked_list_insert(LINKED_LIST list, void *data, int idx) {
	LINKED_LIST_NODE new = linked_node_init(data),curr,next;

	curr = (LINKED_LIST_NODE)list;

	curr = goto_idx(curr,idx-1);//because we use an equal sign in the loop inside goto_idx

	next = curr->next;
	new->next = next;
	curr->next = new;
}

void linked_list_set(LINKED_LIST list, void *data, int idx) {
	LINKED_LIST_NODE curr;

	curr = (LINKED_LIST_NODE)list;
	curr = goto_idx(curr,idx);

	curr->data = data;
}

void *linked_list_get(LINKED_LIST list, int idx) {
	LINKED_LIST_NODE curr;

	curr = (LINKED_LIST_NODE)list;

	curr = goto_idx(curr,idx);
	return curr->data;
}

void *linked_list_remove(LINKED_LIST list, int idx) {
	LINKED_LIST_NODE curr,after;
	void * data;

	curr = (LINKED_LIST_NODE)list;

	curr = goto_idx(curr,idx-1);

	after = curr->next->next;
	data = curr->next->data;

	free(curr->next);
	curr->next = after;

	return data;
}

void linked_list_removeall(LINKED_LIST list) {
	int i, size;

	size = linked_list_size(list);
	for (i = 0; i < size; i++) {
		linked_list_remove(list,0);
	}
}


void linked_list_concatenate(LINKED_LIST list, LINKED_LIST list2){
	LINKED_LIST_NODE crnt_node = (LINKED_LIST_NODE)list;
	int flag = 1;
	while(crnt_node!=NULL&&flag){

		if(crnt_node->next==NULL){
			crnt_node->next = list2->head;
			flag = 0;
		}

		crnt_node = crnt_node->next;
	}
}

void integer_printer(FILE *fp, void *data) {
	fprintf(fp,"%d->",*(int *)data);
}

void char_printer(FILE *fp, void *data) {
	fprintf(fp,"%c->",*(char *)data);
}

void linked_list_fprint(LINKED_LIST list, FILE *fp, void (*print_type) (FILE*, void*)) {
	fprintf(fp,"LINKED_LIST: ");
	if(list->head==NULL){
		fprintf(fp,"No Connection\n");
		return;
	}
	LINKED_LIST_NODE crnt_node = list->head;
	while(1){
		if(crnt_node->data!=NULL)
			print_type(fp,crnt_node->data);

		if(crnt_node->next==NULL){
			break;
		}
		else
			crnt_node = crnt_node->next;
	}
	fprintf(fp,"NULL\n");
	fflush(stdout);
}
