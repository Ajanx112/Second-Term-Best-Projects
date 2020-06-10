#include<stdlib.h>
#include"arraylist.h"
#include <string.h>

//additional menu funcs
int test_menu();//getting the switch parameter
void cap_and_student_size();//determining the capacity and student count
void test_switch(int selection);//applying the related test


//generic insert implementation
int insertArrayListGeneric(ArrayList l, void *e, int (*find)(ArrayList, void *))
{
	//as i understand we will return the minimum ascending index
	void **nlist;
	int ncapacity;

	int index = find(l,e);//basically all the work we had to implement

	if(index >= 0 && index <= l->size) {//if index is valid
		if(isArrayListFull(l)) {//if array is full(self explanatory)
			ncapacity = l->capacity * 2;
			nlist = realloc(l->list, ncapacity * sizeof(void *));
			if(nlist != NULL) {//realloc worked
				//shift elements between index and l->size-1 to right by 1
				memmove(&nlist[index]+1, &nlist[index], (l->size - index)*sizeof(void *));

				l->list = nlist;
				l->capacity = ncapacity;
				l->size++;
				l->list[index] = e;
			}
			else {//realloc didn't work
				nlist = (void **)malloc(ncapacity * sizeof(void *));
				if(nlist != NULL) {//malloc worked
					//copy elements while shifting elements between index and l->size-1 to right by 1
					memcpy(nlist, l->list, index * sizeof(void *));
					memcpy(&nlist[index]+1, &l->list[index], (l->size - index)*sizeof(void *));
					free(l->list);

					l->list = nlist;
					l->capacity = ncapacity;
					l->size++;
					l->list[index] = e;
				}
				else {//malloc didn't work exit
					index = -index;
				}
			}
		}
		else {//array is not full
			//shift elements between index and l->size-1 to right by 1
			memmove(&l->list[index]+1, &l->list[index], (l->size - index)*sizeof(void *));

			l->size++;
			l->list[index] = e;
		}
	}
	else {//index is not valid exit
		index = -index;
	}
	//if index>0 this should have worked
	return index;
}



#define NAME_SIZE 30

typedef struct Student_s {
	int id;
	char name[NAME_SIZE];
} STUDENT_t, *STUDENT;



int findInsertionIndex_STUDENT_ascending(ArrayList l, void *e)
{
	//NOTE TO SELF:If the e->name comes before l[i]->name we will return (i-1)th index then the following students will be memmoved
	int i,found=0;
	int size = l->size;//THE CASTING IS NECESSARY FOR WARNINGS
	for (i = 0; i <size && !found; i++) {
		char *given_name=((STUDENT) e)->name;
		char *array_name=((STUDENT)(l->list[i]))->name;
		if(strcmp(given_name,array_name)<0){
			found=1;
		}
	}
	if(!found){//if we didn't enter the loop but initialized i to 0
		i++;
	}
	return i-1;
}

int findInsertionIndex_STUDENT_descending(ArrayList l, void *e)
{
	int i,found=0;
	int size = l->size;//THE CASTING IS NECESSARY FOR WARNINGS
	for (i = 0; i <size && !found; i++) {
		char *given_name=((STUDENT) e)->name;
		char *array_name=((STUDENT)(l->list[i]))->name;
		if(strcmp(given_name,array_name)>0){
			found=1;
		}
	}
	if(!found){//if we didn't enter the loop but initialized i to 0
		i++;
	}
	return i-1;
}

void fprintf_STUDENT(FILE *fp, void *e)
{
	//this function is implemented.
	STUDENT s = (STUDENT)e;
	fprintf(fp, "%d, %s\n", s->id, s->name);
}

int compare_STUDENT_name_descending(void *e1, void *e2)//switching e1 and e2 in the strcmp takes care of the descending task
{
	return strcmp(((STUDENT)e2)->name,((STUDENT)e1)->name);
}






//init cap and student nums are also scanffed
//These don't have to be global but i think it looks more #define-like with this method
int init_cap;
int num_students;

int main()
{
	int selection=test_menu();
	test_switch(selection);

	return 0;
}






int test_menu(){
	int s;
	printf("Welcome to code testing menu please choose which example you want to test?\n");
	printf("1-Ascending arraylist fill\n");
	printf("2-Ascending arraylist fill with descending bubble sort\n");
	printf("3-Descending arraylist fill\n");
	printf("0-Exit\n");
	fflush(stdout);
	scanf("%d",&s);
	return s;
}


void test_switch(int selection){
	if(selection==0){
		printf("EXITING WITHOUT ALLOCATING AN ARRAY LIST");
		return;
	}

	ArrayList arr;
	STUDENT s;
	int i;

	cap_and_student_size();//The capacity and student counts are determined
	arr = createArrayList(init_cap);

	switch (selection){
	//start switch
		case 1://case 1 and 2 are combined as case 2 needs case 1 to work
		case 2:
			for(i=0; i<num_students; i++) {
				s = malloc(sizeof(STUDENT_t));
				printf("id:\n");
				fflush(stdout);
				scanf("%d",&(s->id));

				printf("name:\n");
				fflush(stdout);
				scanf(" %s",s->name);//may need "&" sign but i think this will work too

				insertArrayListGeneric(arr, (void *)s, findInsertionIndex_STUDENT_ascending); //this line will work after insertArrayListGeneric and findInsertionIndex_STUDENT_ascending are implemented.
			}
			printf("\n");
			fprintfArrayList(stdout, arr, fprintf_STUDENT);

			if(selection==1)//if we only want case 1 to work we break here
				break;
			else{
				printf("\nAFTER BUBBLE SORT:\n");
				bubbleSortArrayList(arr, compare_STUDENT_name_descending); //this line will work after compare_STUDENT_name_descending is implemented.
				fprintfArrayList(stdout, arr, fprintf_STUDENT);
				break;
			}

		case 3:
			for(i=num_students; i<2*num_students; i++) {
				s = malloc(sizeof(STUDENT_t));

				printf("id_ex2:\n");
				fflush(stdout);
				scanf("%d",&(s->id));

				printf("name_ex2:\n");
				fflush(stdout);
				scanf(" %s",s->name);

				insertArrayListGeneric(arr, (void *)s, findInsertionIndex_STUDENT_descending); //this line will work after insertArrayListGeneric and findInsertionIndex_STUDENT_descending are implemented.
			}
			printf("\n");
			fprintfArrayList(stdout, arr, fprintf_STUDENT);
			break;
	//end switch
	};
	//deleting elements 1 by 1
	while(!isArrayListEmpty(arr)) {
		s = deleteArrayList(arr, arr->size-1);
		free(s);
	}

	printf("\nAFTER FREEING:\n");
	fprintfArrayList(stdout, arr, fprintf_STUDENT);

	//destroy array list
	destroyArrayList(arr);
}

void cap_and_student_size(){
	negative_input_err:
	printf("INIT_CAP:\n");
	fflush(stdout);
	scanf("%d",&init_cap);

	printf("NUM_STUDENTS:\n");
	fflush(stdout);
	scanf("%d",&num_students);

	if(init_cap<=0||num_students<=0){
		printf("Invalid output please reenter");
		goto negative_input_err;
	}
}

