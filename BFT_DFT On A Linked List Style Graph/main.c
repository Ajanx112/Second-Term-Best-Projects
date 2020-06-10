#include <stdio.h>
#include <stdlib.h>
#include "linked_list_library.h"
#include "bft_dft.h"
#include "stack.h"
#include "queue.h"
#define NODE_COUNT 9

//Used LINKED_NODE instead of a new PAIR_s struct as they seem to serve the same purpose with proper casting
//To hold a linked_list, i casted the newly initialized LINKED_LIST to LINKED_LIST_NODE and stored it
int *int_arr_init(int);//DATA array
void init_graph(LINKED_LIST,int,int *);//main graph initialization function
void init_nodes(LINKED_LIST,int);//creates the main nodes
LINKED_LIST_NODE init_pair_and_edgelist(LINKED_LIST,int,int *);//creates the pair struct and mallocs the needed edgeList LinkedList
//As edges are unique to this graph we need seperate functions as following:
void init_edges_for_node_0(LINKED_LIST,int *);
void init_edges_for_node_1(LINKED_LIST,int *);
void init_edges_for_node_2(LINKED_LIST,int *);
void init_edges_for_node_3(LINKED_LIST,int *);
void init_edges_for_node_4(LINKED_LIST,int *);
void init_edges_for_node_5(LINKED_LIST,int *);
void init_edges_for_node_6(LINKED_LIST,int *);
void init_edges_for_node_7(LINKED_LIST,int *);
void init_edges_for_node_8(LINKED_LIST,int *);
//pretty printer as asked in matter 3
void linked_graph_printer(LINKED_LIST list, FILE *fp, void (*print_type) (FILE*, void*));
void linked_graph_free(LINKED_LIST,int);







int main(void) {

	LINKED_LIST graph = linked_list_init();
	int * intarray = int_arr_init(NODE_COUNT);
	init_graph(graph,NODE_COUNT,intarray);
	linked_graph_printer(graph,stdout,integer_printer);

	//DONT MIND THE WARNINGS THEY ARE THERE BECAUSE OF THE GENERIC IMPLEMENTATION
	//THE PROGRAM STILL COMPILES AND WORKS

	//bft
	printf("bft node 0:\n");
	bft_dft_generic_linked_list(graph,NODE_COUNT,0,linked_queue_init,linked_queue_enqueue,linked_queue_dequeue,linked_queue_is_empty,linked_queue_free);
	printf("bft node 1:\n");
	bft_dft_generic_linked_list(graph,NODE_COUNT,1,linked_queue_init,linked_queue_enqueue,linked_queue_dequeue,linked_queue_is_empty,linked_queue_free);
	//dft
	printf("dft node 0:\n");
	bft_dft_generic_linked_list(graph,NODE_COUNT,0,linked_stack_init,linked_stack_push,linked_stack_pop,linked_stack_is_empty,linked_stack_free);
	printf("dft node 1:\n");
	bft_dft_generic_linked_list(graph,NODE_COUNT,1,linked_stack_init,linked_stack_push,linked_stack_pop,linked_stack_is_empty,linked_stack_free);

	linked_graph_free(graph,NODE_COUNT);
	free(intarray);
	return 0;
}









int *int_arr_init(int size){
	int i,*intarray = malloc(sizeof(int)*size);
	for(i=0;i<size;i++){
		intarray[i] = i;
	}
	return intarray;
}


void init_graph(LINKED_LIST list,int nodeCount,int *intarray){
	init_nodes(list,nodeCount);
	init_edges_for_node_0(list,intarray);
	init_edges_for_node_1(list,intarray);
	init_edges_for_node_2(list,intarray);
	init_edges_for_node_3(list,intarray);
	init_edges_for_node_4(list,intarray);
	init_edges_for_node_5(list,intarray);
	init_edges_for_node_6(list,intarray);
	init_edges_for_node_7(list,intarray);
	init_edges_for_node_8(list,intarray);
}


void init_nodes(LINKED_LIST list,int nodeCount){
	int i;
	for(i=0;i<nodeCount;i++){
		linked_list_append(list,NULL);
	}
}


LINKED_LIST_NODE init_pair_and_edgelist(LINKED_LIST list,int idx,int * intarray){
	//Used LINKED_NODE instead of a new PAIR struct
	//To hold a linked_list, i casted the newly initialized LINKED_LIST to LINKED_LIST_NODE and stored it
	//Thus we have to perform the proper casts

	LINKED_LIST_NODE pair,pNode;
	pair = linked_node_init(&intarray[idx]);

	pNode = goto_idx((LINKED_LIST_NODE)list,idx);
	pNode->data = pair;

	LINKED_LIST edgeList = linked_list_init();
	pair->next = (LINKED_LIST_NODE) edgeList;

	return pair;
}


void init_edges_for_node_0(LINKED_LIST list,int * intarray){
	LINKED_LIST_NODE pair;
	pair = init_pair_and_edgelist(list,0,intarray);

	LINKED_LIST_NODE edge1 = linked_node_init(&intarray[1]),edge2 = linked_node_init(&intarray[3]),edge3 = linked_node_init(&intarray[4]);
	((LINKED_LIST_NODE)pair->next)->next = edge1;
	edge1->next = edge2;
	edge2->next = edge3;
}


void init_edges_for_node_1(LINKED_LIST list,int * intarray){
	LINKED_LIST_NODE pair;
	pair = init_pair_and_edgelist(list,1,intarray);

	LINKED_LIST_NODE edge1 = linked_node_init(&intarray[2]),edge2 = linked_node_init(&intarray[4]);
	pair->next->next = edge1;
	edge1->next = edge2;
}


void init_edges_for_node_2(LINKED_LIST list,int * intarray){
	LINKED_LIST_NODE pair;
	pair = init_pair_and_edgelist(list,2,intarray);

	LINKED_LIST_NODE edge1 = linked_node_init(&intarray[5]);
	pair->next->next = edge1;
}


void init_edges_for_node_3(LINKED_LIST list,int * intarray){
	LINKED_LIST_NODE pair;
	pair = init_pair_and_edgelist(list,3,intarray);

	LINKED_LIST_NODE edge1 = linked_node_init(&intarray[4]),edge2 = linked_node_init(&intarray[6]);
	pair->next->next = edge1;
	edge1->next = edge2;
}


void init_edges_for_node_4(LINKED_LIST list,int * intarray){
	LINKED_LIST_NODE pair;
	pair = init_pair_and_edgelist(list,4,intarray);

	LINKED_LIST_NODE edge1 = linked_node_init(&intarray[5]);
	pair->next->next = edge1;
}


void init_edges_for_node_5(LINKED_LIST list,int * intarray){
	LINKED_LIST_NODE pair;
	pair = init_pair_and_edgelist(list,5,intarray);

	pair->next->next = NULL;
}


void init_edges_for_node_6(LINKED_LIST list,int * intarray){
	LINKED_LIST_NODE pair;
	pair = init_pair_and_edgelist(list,6,intarray);

	LINKED_LIST_NODE edge1 = linked_node_init(&intarray[4]),edge2 = linked_node_init(&intarray[7]);
	pair->next->next = edge1;
	edge1->next = edge2;
}


void init_edges_for_node_7(LINKED_LIST list,int * intarray){
	LINKED_LIST_NODE pair;
	pair = init_pair_and_edgelist(list,7,intarray);

	LINKED_LIST_NODE edge1 = linked_node_init(&intarray[5]),edge2 = linked_node_init(&intarray[8]);
	pair->next->next = edge1;
	edge1->next = edge2;
}


void init_edges_for_node_8(LINKED_LIST list,int * intarray){
	LINKED_LIST_NODE pair;
	pair = init_pair_and_edgelist(list,8,intarray);

	pair->next->next = NULL;
}


void linked_graph_printer(LINKED_LIST list, FILE *fp, void (*print_type) (FILE*, void*)){
	//Used LINKED_NODE instead of a new PAIR struct
	//To hold a linked_list, i casted the newly initialized LINKED_LIST to LINKED_LIST_NODE and stored it
	//Thus we have to perform the proper casts


	//quick exit
	if(list->head==NULL){
		fprintf(fp,"Empty Graph");
		return;
	}

	fprintf(fp,"Graph:");
	fprintf(fp,"\n********************************************\n");
	LINKED_LIST_NODE pPair,crnt_node = list->head;
	LINKED_LIST pEdgelist;

	while(1){

		pPair = ((LINKED_LIST_NODE)crnt_node->data);
		pEdgelist = (LINKED_LIST)(pPair->next);

		fprintf(fp,"Node %d is connected to ",*(int *)(pPair->data));
		fflush(stdout);
		linked_list_fprint(pEdgelist,fp,print_type);


		if(crnt_node->next==NULL){
			break;
		}
		else
			crnt_node = crnt_node->next;

	}

	fprintf(fp,"********************************************\n");
	fflush(stdout);
}


void linked_graph_free(LINKED_LIST list,int nodeCount){
	//Used LINKED_NODE instead of a new PAIR struct
	//To hold a linked_list, i casted the newly initialized LINKED_LIST to LINKED_LIST_NODE and stored it
	//Thus we have to perform the proper casts
	int i;
	LINKED_LIST_NODE curr,pPair;
	LINKED_LIST pEdgelist;

	for(i=0;i<nodeCount;i++){
		curr = goto_idx((LINKED_LIST_NODE)list,i);

		pPair = ((LINKED_LIST_NODE)curr->data);//our pair

		pEdgelist = (LINKED_LIST)(pPair->next);//the edgelist to be deleted

		linked_list_removeall(pEdgelist);//remove everything in the edgelist
		free(pEdgelist);//free the edgelist
		free(pPair);//free the PAIR
	}

	linked_list_removeall(list);//remove all the nodes
	free(list);//free the graph
}


