#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct LINKED_QUEUE_NODE_s *LINKED_QUEUE_NODE;
typedef  struct LINKED_QUEUE_NODE_s{
	LINKED_QUEUE_NODE next;
	void *data;
}LINKED_QUEUE_NODE_t[1];

typedef struct{
	LINKED_QUEUE_NODE head;
	LINKED_QUEUE_NODE tail;
}LINKED_QUEUE_t[1],*LINKED_QUEUE;

LINKED_QUEUE linked_queue_init(){
	LINKED_QUEUE queue=malloc(1*sizeof(LINKED_QUEUE_t));
	if(queue==NULL){
		fprintf(stderr,"ERROR WHILE ALLOCATING LINKED_QUEUE");
		exit(99);
	}
	queue->head=NULL;
	queue->tail=NULL;
	return queue;
}

int linked_queue_is_empty(LINKED_QUEUE queue){
	return queue->head==NULL ? 1:0;
}

void linked_queue_free(LINKED_QUEUE queue){
	if(!linked_queue_is_empty(queue))
		printf("Linked_queue was not empty but you freed it anyway\n");
	free(queue);
}

int linked_queue_size(LINKED_QUEUE queue){
	int size=0;
	LINKED_QUEUE_NODE temp_queue = NULL;
	if(queue->head==NULL)
		return 0;
	temp_queue=queue->head->next;
	while(temp_queue!=NULL){
		size++;
		temp_queue=temp_queue->next;
	}
	return size+1;
}

void linked_queue_enqueue(LINKED_QUEUE queue,void *data){
	LINKED_QUEUE_NODE node = malloc(1*sizeof(LINKED_QUEUE_NODE_t));
	if(node==NULL){
		fprintf(stderr,"ERROR WHILE ALLOCATING LINKED_QUEUE_NODE");
		return;
	}
	node->data = data;
	node->next = NULL;
	if(linked_queue_is_empty(queue)){
		queue->head = node;
	}
	else{
		queue->tail->next = node;
	}
	queue->tail = node;
}

void * linked_queue_dequeue(LINKED_QUEUE queue){
	void *data = NULL;
	LINKED_QUEUE_NODE keep=queue->head;
	if(linked_queue_is_empty(queue)){
		return data;
	}
	data = queue->head->data;
	queue->head = queue->head->next;
	free(keep);
	return data;
}


#endif /* QUEUE_H_ */
