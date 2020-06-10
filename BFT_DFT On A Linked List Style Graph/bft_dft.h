#ifndef BFT_DFT_H_
#define BFT_DFT_H_
#include <stdio.h>
#include <stdlib.h>
#include "linked_list_library.h"

int create_map_and_aux(int**d_map,int **aux,int size){
	int i;
	int *a = malloc(size*sizeof(int));
	int *d = calloc(size,sizeof(int));//allocates and sets all elements to 0

	if(d==NULL||a==NULL)
		return -1;
	for(i=0;i<size;i++){
		a[i]=i;
	}

	*aux = a;
	*d_map = d;

	return 1;
}


//WARNINGS ARE CAUSED BY THE GENERIC IMPLEMENTATION BUT THE PROGRAM COMPILES AND WORKS
void bft_dft_generic_linked_list(LINKED_LIST g,int N,int s,void *(*init)(),void (*push)(void *,void *),void *(*pop)(void *),int (*isEmpty)(void *),void (*destroy)(void *)){
	//As bft and dft are two very alike algorithms why not combine them into 1
	void * DataStruct = init();
	int v=0,*d_map,*auxillary,tmp_data=0;
	LINKED_LIST pEdgelist;
	LINKED_LIST_NODE curr,temp;

	if(create_map_and_aux(&d_map,&auxillary,N)==-1)//Null Check inside
		exit(-101);

	push(DataStruct,&auxillary[s]);
	d_map[s]=1;

	while(!isEmpty(DataStruct)){
		v = *(int *)pop(DataStruct);
		printf("%d isVisited: %d\n",v,d_map[s]);
		fflush(stdout);

		//the new part:
		curr = goto_idx((LINKED_LIST_NODE)g,v);//goes to the proper vertex
		pEdgelist = (LINKED_LIST)((LINKED_LIST_NODE)curr->data)->next;//reaches the Edgelist structure
		temp = pEdgelist->head;//a placeholder for clear code

		while(temp!=NULL){//for each connection in the edgelist
			tmp_data = *(int *)temp->data;
			if(d_map[tmp_data]!=1){
				push(DataStruct,&auxillary[tmp_data]);
				d_map[tmp_data]=1;
			}
			temp = temp->next;
		}
	}
	free(auxillary);
	free(d_map);
	destroy(DataStruct);
}


#endif /* BFT_DFT_H_ */
