#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void *linked_stack_pop(LINKED_STACK stack)
{
	LINKED_STACK_NODE node;
	void *res = NULL;

	if(stack->head != NULL){//if not empty
		node = stack->head;
		res=node->data;
		stack->head=node->next;
		free(node);
	}
	else{
		fprintf(stderr,"Error! Popped an empty stack(Error_code:(We only have 1 predetermined error so 1 i guess))\n");
		fflush(stderr);
	}

	return res;
}

void linked_stack_push(LINKED_STACK stack, void *data)
{
	LINKED_STACK_NODE node=malloc(sizeof(LINKED_STACK_NODE_t));
	 node->data = data;
	 node->next = stack->head;
	 stack->head=node;
}

void *linked_stack_top(LINKED_STACK stack)
{
	void *res = NULL;

	if(stack->head != NULL)
		res = stack->head->data;

	return res;
}

int linked_stack_is_empty(LINKED_STACK stack)//there was a typo with the word empty
{
	int return_val=0;

	if(stack->head==NULL)
		return_val = 1;

	return return_val;
}

LINKED_STACK linked_stack_init()
{
	LINKED_STACK stack=malloc(sizeof(LINKED_STACK_t));
	stack->head = NULL;
	return stack;
}

void linked_stack_free(LINKED_STACK stack)
{
	if(stack->head!=NULL){//just to be safe(if this line breakes the code i will get mad)
		free(stack->head);
	}
	free(stack);
}

