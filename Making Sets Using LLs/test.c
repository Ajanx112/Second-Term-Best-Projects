#include <stdio.h>
#include <stdlib.h>
#include "time.h"//used in srand, for random case testing
#include "linked_list_library.h"

enum COMPARISON{SMALLER = -1, EQUAL = 0, BIGGER = 1};//trying to make the code more readable
//otherwise it's really confusing to trace searching algorithms

//comparison funcs
int int_compare(void *first,void *second);
int char_compare(void *first,void *second);
//helper func
int linked_linear_search(LINKED_LIST list,void *key,int low,int high,int (*compare) (void*, void*));//high is included
//assignment functions
LINKED_LIST set_make(LINKED_LIST list, int (*compare) (void*, void*));
LINKED_LIST set_union(LINKED_LIST list1, LINKED_LIST list2, int (*compare) (void*, void*));
LINKED_LIST set_intersection(LINKED_LIST list1, LINKED_LIST list2, int (*compare) (void*, void*));
LINKED_LIST insertion_sort(LINKED_LIST list, int (*compare) (void*, void*));
//test functions
void set_test();
void sort_test();






int main(int argc, char **argv) {
	printf("\n************************Set Test************************\n");
	set_test();
	printf("\n************************Sort Test************************\n");
	sort_test();
	return 0;
}






void set_test(){
	LINKED_LIST list1 = linked_list_init();//must be freed using regular free because of concatenation in set_union
	LINKED_LIST list2 = linked_list_init();//must be freed using regular free because of concatenation in set_union
	LINKED_LIST	union_set,intersection_set;
	int arr[] = {0,1,2,3,4,5,6,7,8,9};



	//initializations:
		//For L1:
	linked_list_append(list1,&arr[0]);
	linked_list_append(list1,&arr[0]);
	linked_list_append(list1,&arr[1]);
	linked_list_append(list1,&arr[2]);
	linked_list_append(list1,&arr[2]);
	linked_list_append(list1,&arr[3]);
	linked_list_append(list1,&arr[3]);
	linked_list_append(list1,&arr[3]);
		//For L2:
	linked_list_append(list2,&arr[3]);
	linked_list_append(list2,&arr[4]);
	linked_list_append(list2,&arr[5]);
	linked_list_append(list2,&arr[6]);
	linked_list_append(list2,&arr[7]);
	linked_list_append(list2,&arr[2]);
	linked_list_append(list2,&arr[8]);
	linked_list_append(list2,&arr[0]);
	/**********************************/



	//set make test on L1
	printf("L1 before set_make:\n");
	linked_list_fprint(list1,stdout,integer_printer);

	list1 = set_make(list1,int_compare);

	printf("L1 after set_make:\n");
	linked_list_fprint(list1,stdout,integer_printer);
	/****************************************************/



	//set make test on L2
	printf("\nL2 before set_make:\n");
	linked_list_fprint(list2,stdout,integer_printer);

	list2 = set_make(list2,int_compare);

	printf("L2 after set_make:\n");
	linked_list_fprint(list2,stdout,integer_printer);
	/****************************************************/



	//set_intersection test
	intersection_set = set_intersection(list1,list2,int_compare);

	printf("\nIntersection Set of L1 and L2 after set_intersection:\n");

	linked_list_fprint(intersection_set,stdout,integer_printer);
	/****************************************************/



	//set_union test
	union_set = set_union(list1,list2,int_compare);

	printf("\nUnion Set of L1 and L2 after set_union:\n");

	linked_list_fprint(union_set,stdout,integer_printer);
	/****************************************************/




	free(list1);//using normal free because linked_list_free will try to free all the elements inside
	free(list2);//using normal free because linked_list_free will try to free all the elements inside
	free(intersection_set);//using normal free because linked_list_free will try to free all the elements inside
	//but we want the elements to live inside the union_set
	linked_list_free(union_set);
}



void sort_test(){
	LINKED_LIST list = linked_list_init();
	char letters[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	int i,rndm;
	srand(time(NULL));
	for(i=25;i>=0;i--){
		rndm = rand() % 26;
		linked_list_append(list,&letters[rndm]);
	}

	printf("Randomly Filled Linked List Before Insertion Sort:\n");
	linked_list_fprint(list,stdout,char_printer);

	list = insertion_sort(list,char_compare);

	printf("\nRandomly Filled Linked List After Insertion Sort:\n");
	linked_list_fprint(list,stdout,char_printer);

	printf("\nSet Version of the Sorted Linked List:\n");
	linked_list_fprint(set_make(list,char_compare),stdout,char_printer);


	linked_list_free(list);
}



int int_compare(void *first,void *second){
	int return_val;
	int diff = *(int *)first - *(int *)second;

	if(diff>0)
		return_val = BIGGER;
	else if(diff<0)
		return_val = SMALLER;
	else
		return_val = EQUAL;

	return return_val;
}



int char_compare(void *first,void *second){
	int return_val;
	int diff = *(char *)first - *(char *)second;

	if(diff>0)
		return_val = BIGGER;
	else if(diff<0)
		return_val = SMALLER;
	else
		return_val = EQUAL;

	return return_val;
}



int linked_linear_search(LINKED_LIST list,void *key,int low,int high,int (*compare) (void*, void*)){//includes high
	int return_val = -1;
	LINKED_LIST_NODE node;
	node = goto_idx((LINKED_LIST_NODE)list,low);//goes to the asked node

	while(low <= high && node != NULL && compare((node->data),key) != EQUAL){//goes till the end
		low++;
		node = node->next;
	}

	if(low > high)//if we couldn't find
		return_val = -1;
	else//if found
		return_val = low;

	return return_val;
}



LINKED_LIST set_make(LINKED_LIST list, int (*compare) (void*, void*)){
	int i,return_val;
	void *data;
	//It is better to calculate size in the loop head because size may change in each iter
	for(i = 0; i < (linked_list_size(list) - 1); i++){
		data = ((LINKED_LIST_NODE)goto_idx((LINKED_LIST_NODE)list,i))->data;//store the data of the related index

		//linear search the data starting from one higher than i
		return_val = linked_linear_search(list,data,i+1,(linked_list_size(list)-1),compare);

		if(return_val != -1){//if a duplicate exists, remove it.
			linked_list_remove(list,return_val);
			i--;//decrease the index by 1 because of the shift
		}
	}

	return list;
}



LINKED_LIST set_union(LINKED_LIST list1, LINKED_LIST list2, int (*compare) (void*, void*)){
	//As we already have a function to make a set by deleting duplicates (set_make)
	//Our only job is to allocate a new list and combine all 3
	//Then set_make will take care of the rest
	LINKED_LIST union_set = linked_list_init();
	if(union_set==NULL)
		return NULL;

	linked_list_concatenate(list1,list2);
	linked_list_concatenate(union_set,list1);
	union_set = set_make(union_set,compare);

	return union_set;
}



LINKED_LIST set_intersection(LINKED_LIST list1, LINKED_LIST list2, int (*compare) (void*, void*)){
	LINKED_LIST intersection_set = linked_list_init();
	void *data;
	int i,return_val,sizeL1 = linked_list_size(list1),sizeL2 = linked_list_size(list2);

	if(intersection_set==NULL)
		return NULL;

	for(i = 0; i < sizeL1 ; i++){//for each element in L1
		data = ((LINKED_LIST_NODE)goto_idx((LINKED_LIST_NODE)list1,i))->data;//goto_idx takes LLNODE and returns LLNODE

		return_val = linked_linear_search(list2,data,0,sizeL2-1,compare);//Linear search that element
		if(return_val != -1)//if it exists in L2, append it to intersection_set
			linked_list_append(intersection_set,data);
	}

	return intersection_set;
}



LINKED_LIST insertion_sort(LINKED_LIST list, int (*compare) (void*, void*)){//algorithm is morphed from the lecture slides
	int i,j,low = 0,size = linked_list_size(list);
	LINKED_LIST_NODE casted_list,prev_node;//
	void *x;
	casted_list = (LINKED_LIST_NODE)list;//to increase readability

	for(i=low;i<size;i++){
		x = ((LINKED_LIST_NODE)goto_idx(casted_list,i))->data;
		j = i;
		prev_node = goto_idx(casted_list,j-1);
		while(j > low && compare(prev_node->data,x) > EQUAL){
			prev_node->next->data = prev_node->data;
			j--;
			prev_node = goto_idx(casted_list,j-1);
		}
		prev_node->next->data = x;
	}
	return list;
}


