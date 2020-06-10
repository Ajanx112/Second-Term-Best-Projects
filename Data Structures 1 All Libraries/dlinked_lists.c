#include "dlinked_lists.h"
#include <stdlib.h>
#include <stdio.h>

DLINKED_LIST dlinked_list_init(){
	DLINKED_LIST list = malloc(sizeof(DLINKED_LIST_t)*1);
	if(list!=NULL)
		list->head = NULL;
	else{
		fprintf(stderr,"ERROR: DLINKED_LIST_INIT");
		exit(-99);
	}
	return list;
}


DLINKED_LIST_NODE dlinked_node_init(void *data) {
	DLINKED_LIST_NODE node;
	node = malloc(sizeof(DLINKED_LIST_NODE_t));
	if(node!=NULL){
		node->data = data;
		node->prev = NULL;
		node->next = NULL;
	}
	else{
		fprintf(stderr,"ERROR: DLINKED_NODE_INIT");
		exit(-101);
	}
	return node;
}


void dlinked_list_free(DLINKED_LIST list){
	if(list->head!=NULL)
		dlinked_list_removeall(list);
	free(list);
}


void dlinked_list_prepend(DLINKED_LIST list, void *data){
	DLINKED_LIST_NODE new = dlinked_node_init(data);
	new->next = list->head;
	new->prev = (DLINKED_LIST_NODE)list;
	if(new->next!=NULL)//without this check we may dereference a NULL
		new->next->prev = new;
	list->head = new;
}


void dlinked_list_append(DLINKED_LIST list, void *data){
	DLINKED_LIST_NODE node, new;

	new = dlinked_node_init(data);
	node = (DLINKED_LIST_NODE)list;

	while (node->next != NULL) {//go till the end
		node = node->next;
	}

	node->next = new;
	new->prev = node;
}

DLINKED_LIST_NODE goto_idx(DLINKED_LIST_NODE curr,int idx){
	int i;
	//if an invalid but positive index is entered, we go till the end
	for(i=0;i<=idx;i++){//equal sign is needed as we usually call goto_idx with the casted LINKED_LIST
		curr = curr->next;
	}
	return curr;
}

void dlinked_list_insert(DLINKED_LIST list, void *data, int idx){
	DLINKED_LIST_NODE new = dlinked_node_init(data),curr,next;

	curr = (DLINKED_LIST_NODE)list;

	curr = goto_idx(curr,idx-1);//we use -1 because there is an equal sign in the loop inside goto_idx
	//it is there to emit empty list checks in remove

	next = curr->next;
	//linking the right facing pointers
	new->next = next;
	curr->next = new;

	//linking the left facing pointers
	new->prev = next->prev;
	next->prev = new;
}


void dlinked_list_set(DLINKED_LIST list, void *data, int idx){
	DLINKED_LIST_NODE curr;

	curr = (DLINKED_LIST_NODE)list;
	curr = goto_idx(curr,idx);

	curr->data = data;
}


void *dlinked_list_get(DLINKED_LIST list, int idx){
	DLINKED_LIST_NODE curr;

	curr = (DLINKED_LIST_NODE)list;

	curr = goto_idx(curr,idx);

	return curr->data;
}


void *dlinked_list_remove(DLINKED_LIST list, int idx){
	DLINKED_LIST_NODE curr,after;
	void * data;

	curr = (DLINKED_LIST_NODE)list;

	curr = goto_idx(curr,idx-1);

	after = curr->next->next;
	data = curr->next->data;

	free(curr->next);//we are welcome to free because we are holding the next node's adress in "after"

	curr->next = after;
	if(after!=NULL)//without this check we may dereference a NULL
		after->prev = curr;
	return data;
}

int dlinked_list_size(DLINKED_LIST list) {
	DLINKED_LIST_NODE node = list->head;
	int size=0;
	while(node!=NULL){//goes till the end
		node = node->next;
		size++;
	}
	return size;
}

void dlinked_list_removeall(DLINKED_LIST list){
	int i, size;
	size = dlinked_list_size(list);
	for (i = 0; i < size; i++) {
		dlinked_list_remove(list,0);
	}
}


void integer_printer(FILE *fp, void *data) {
	fprintf(fp,"<- %d -> ",*(int *)data);
}

void char_printer(FILE *fp, void *data) {
	fprintf(fp,"<- %c ->",*(char *)data);
}

void dlinked_list_fprint(DLINKED_LIST list, FILE *fp, void (*print_type) (FILE*, void*)) {
	fprintf(fp,"DoubleLinked List with size %d: ",dlinked_list_size(list));
	if(list->head==NULL){
		fprintf(fp,"Empty List\n");
		return;
	}
	DLINKED_LIST_NODE crnt_node = list->head;
	while(1){
		if(crnt_node->data!=NULL)
			print_type(fp,crnt_node->data);

		if(crnt_node->next==NULL){
			break;
		}
		else
			crnt_node = crnt_node->next;
	}
	fprintf(fp,"\n");
	fflush(stdout);
}
