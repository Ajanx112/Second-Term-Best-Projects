#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000                                        //Do not edit this macro.

typedef struct{
	int film_id;
	char title[255];
	char description[1023];
	unsigned int release_year;
	char rental_duration;
	float rental_rate;
	unsigned char length;
	float replacement_cost;
	char rating[10];
	char last_update[30];
} RECORD_t, *RECORD;                                    //Do not edit this struct.

/* DECLARE YOUR FUNCTION PROTOTYPES HERE */

//ADDITIONAL FUNCS
void print_film(RECORD *rec,int i);//(Prints by index not id)
//!!! As print_film takes a record * use print_film(&record_array,0); to print regular record arrays
void test_menu(int *selection);//menu funcs for a clearer main
void test_switch(RECORD *rec,int selection);
//additionals end

//for the bounded funcs lower index is included but upper is excluded
void find_by_year(int release_year, RECORD *film_array, int size, int start, int end, int *p_found_num, RECORD **p_found_films);
RECORD find_by_title(char *title, RECORD *film_array, int size, int start, int end);
int insert(RECORD film, RECORD **p_film_array, int *p_size);
RECORD delete(int film_id, RECORD *film_array, int *p_size);
//generic sort that is usable with char * comparison and void **swap funcs
//generic sort parameter 6 is strcmp
void swapasc_record(void **x,void **y);//generic sort parameter 7
void sort(RECORD *film_array, int start, int end, char *title, char *rating,int(*compare)(const char *,const char *), void (*swap)(void **,void **));

//



int main(){
	/* --- DO NOT EDIT THIS PART. --- */
	int num_records = MAX;
	int i;
	RECORD tmp;
	RECORD *rec = (RECORD *)malloc(sizeof(RECORD)*num_records);
	FILE *file = fopen("data.txt", "rb");
	if (file == NULL) {
		printf("Cannot open the file.\n");
		exit(0);
	}
	for(i=0; i<num_records; i++) {
		tmp = (RECORD)malloc(sizeof(RECORD_t));
		fread(tmp, sizeof(RECORD_t), 1, file);
		rec[i] = tmp;
	}
	fclose(file);
	/* --- --- */

	/**************************/
	/* Your code starts here. */
	/**************************/
	int selection;
	test_menu(&selection);
	test_switch(rec,selection);

	/**************************/
	/* Your code ends here.   */
	/**************************/

	/* --- DO NOT EDIT THIS PART. --- */
	file = fopen("data_out.txt", "wb");
	for(i=0; i<num_records; i++) {
		tmp = rec[i];
		fwrite(tmp, sizeof(RECORD_t), 1, file);
		free(tmp);
	}
	fclose(file);
	free(rec);
	return 1;
	/* --- DO NOT EDIT THIS PART. --- */
}




/* IMPLEMENT YOUR FUNCTIONS HERE */

void print_film(RECORD *rec,int i){//!!! As print_film takes a record * use print_film(&record_array,0); to print regular record arrays
	printf("ID: %d\n", rec[i]->film_id);
	printf("TITLE: %s\n", rec[i]->title);
	printf("DESCRIPTION: %s\n", rec[i]->description);
	printf("RELEASE YEAR: %d\n", rec[i]->release_year);
	printf("RENTAL DURATION: %d\n", rec[i]->rental_duration);
	printf("RENTAL RATE: %f\n", rec[i]->rental_rate);
	printf("REPLACEMENT COST: %f\n", rec[i]->replacement_cost);
	printf("RATING: %s\n", rec[i]->rating);
	printf("LAST UPDATE: %s\n", rec[i]->last_update);
	printf("\n\n");
}

void test_menu(int *selection){
	again://for goto. Its only a simple check so i think goto will be fine
	printf("Welcome to test lab! Please type the corresponding test number.\n");
	printf("(Oh also some test use find_by_year in them to allocate a basis array)\n");
	printf("1-Find By Year Test\n");
	printf("2-Find By Title Test\n");
	printf("3-Insert General Test\n");
	printf("4-Insert Duplicate Test\n");
	printf("5-Delete General Test\n");
	printf("6-Delete Not_Exist Test\n");
	printf("7-Sort Test\n");
	printf("0-Exit\n");
	fflush(stdout);
	scanf("%d",selection);
	if(*selection>7||*selection<0){
		printf("Unidentified input!!!\n\n\n");
		goto again;
	}
}

void test_switch(RECORD *rec,int selection){
	//some tests use find_by_year to allocate a basis array in them
	switch(selection){
		int i;
		default:
			break;
		case 1://Find By Year Test:
			{
				int size;
				RECORD *res_arr;
				find_by_year(2006,rec,MAX,100,110,&size,&res_arr);
				for(i=0;i<size;i++){
					print_film(&res_arr[i],0);
				}
				free(res_arr);
			}
			break;
		case 2://Find By Title Test:
			print_film(rec,130);
			RECORD record=find_by_title("CENTER DINOSAUR",rec,MAX,100,150);
			printf("%d",record->film_id);//expected 131
			break;
		case 3://insert normal test
			{
				int size;
				RECORD *res_arr;
				find_by_year(2006,rec,MAX,100,110,&size,&res_arr);
				for(i=0;i<size;i++){
					print_film(&res_arr[i],0);
				}
				printf("********************************************************\n");

				int indx=insert(rec[9],&res_arr,&size);
				printf("new size:%d  ",size);
				printf("new index:%d  ",indx);
				print_film(&res_arr[indx],0);
				printf("SUCCESS!!!");
				print_film(rec,9);
				free(res_arr);
			}
			break;
		case 4://insert duplicate test
			{
				int size;
				RECORD *res_arr;
				find_by_year(2006,rec,MAX,100,110,&size,&res_arr);
				for(i=0;i<size;i++){
					print_film(&res_arr[i],0);
				}
				int indx=insert(rec[102],&res_arr,&size);
				printf("%d  ",size);
				printf("%d  ",indx);
				if(indx<0)
					printf("SUCCESS!!!\n");
				free(res_arr);
			}
			break;
		case 5://delete normal test
			{
				int size;
				RECORD *res_arr;
				RECORD delete_test;
				find_by_year(2006,rec,MAX,100,110,&size,&res_arr);
				for(i=0;i<size;i++){
					print_film(&res_arr[i],0);
				}
				printf("********************************************************\n");
				delete_test=delete(103,res_arr,&size);
				printf("%d  ",size);
				print_film(&delete_test,0);
				printf("SUCCESS!!!\n");
				free(res_arr);
				break;
			}
		case 6://delete edge test
			{
				int size;
				RECORD *res_arr;
				RECORD delete_test;
				find_by_year(2006,rec,MAX,100,110,&size,&res_arr);
				for(i=0;i<size;i++){
					print_film(&res_arr[i],0);
				}
				printf("********************************************************\n");
				delete_test=delete(112,res_arr,&size);
				printf("%d  ",size);
				if(delete_test==NULL)
					printf("SUCCESS!!!\n");
				else
					print_film(&delete_test,0);//prints delete_test[0]
				free(res_arr);
				break;
			}
		case 7://Sort Test
			{
				RECORD *record_array=malloc(sizeof(RECORD_t)*5);
				if(record_array==NULL)
					exit(-5);
				record_array[0]=rec[9];
				record_array[1]=rec[10];
				record_array[2]=rec[11];
				record_array[3]=rec[301];
				record_array[4]=rec[690];
				print_film(record_array,0);
				print_film(record_array,1);
				print_film(record_array,2);
				print_film(record_array,3);
				print_film(record_array,4);
				printf("**************************************************************************\n");
				sort(record_array,0,5,"These arguments","are unnecessary",strcmp,swapasc_record);
				print_film(record_array,0);
				print_film(record_array,1);
				print_film(record_array,2);
				print_film(record_array,3);
				print_film(record_array,4);
				free(record_array);
			}
			break;
	};
}

void find_by_year(int release_year, RECORD *film_array, int size, int start, int end, int *p_found_num, RECORD **p_found_films) {
	int i,count=0,just_to_be_safe_found_bool=0;
	RECORD *found_arr=malloc(sizeof(RECORD)*(end-start));//max possible size
	RECORD *test_realloc;
	for(i=0;i<size;i++){
		if(film_array[i]->film_id>=start&&film_array[i]->film_id<end)//start end check
			if(film_array[i]->release_year==release_year){//id check
				found_arr[count]=film_array[i];//we are using * because we pass by value :(
				count++;
				just_to_be_safe_found_bool=1;
			}
	}
	test_realloc=realloc(found_arr,sizeof(RECORD)*count);//reallocating for a smaller size

	if(test_realloc==NULL)//if it doesn't work we will return the unedited size
		*p_found_films=found_arr;
	else
		*p_found_films=test_realloc;//if it works we will return it with the smaller size

	*p_found_num=count;
	if(just_to_be_safe_found_bool==0){
		*p_found_num=0;
		*p_found_films=NULL;
	}
}


RECORD find_by_title(char *title, RECORD *film_array, int size, int start, int end) {
	int i,found=0;
	RECORD p_found=NULL;
	for(i=0;i<size&&!found;i++){
		if(film_array[i]->film_id>start&&film_array[i]->film_id<end)
			if(strcmp(title,film_array[i]->title)==0){
				p_found=film_array[i];
				found=1;
			}
	}
	i--;
	return p_found;
}


int insert(RECORD film, RECORD **p_film_array, int *p_size) {
	//Parentheses are required in (*p_film_array) because it turns out that c evaluates [] earlier than *
	int i,isFull=1,noDuplicate=1,return_val=0;
	int sfilm_id=film->film_id;//searched film id
	RECORD *n_array;
	for(i=0;i<*p_size&&isFull!=0&&noDuplicate!=0;i++){
		if((*p_film_array)[i]==NULL)//if there is an empty space
			isFull=0;
		if(sfilm_id==(*p_film_array)[i]->film_id)
			noDuplicate=0;
	}
	i--;//back at our index value, this might become handy


	if(noDuplicate==0)//there is a duplicate size is not incremented
		return_val=-1;
	else if(isFull==0){//there is an empty space
		//size is not incremented
		(*p_film_array)[i]=film;
		return_val=i;
	}
	else{//array is full
		n_array=realloc(*p_film_array,((*p_size)+1)*sizeof(RECORD));
		if(n_array==NULL)
			return_val=-2;
		else{
			*p_film_array=n_array;
			(*p_film_array)[i+1]=film;
			return_val=*p_size;//keeps the index
			*p_size=*p_size+1;//increments the size
		}
	}
	return return_val;
}


RECORD delete(int film_id, RECORD *film_array, int *p_size) {
	int i,found=0;
	RECORD return_rec=NULL;//if we couldn't find any we will return NULL
	for(i=0;i<*p_size&&!found;i++){
		if(film_id==film_array[i]->film_id)
			found=1;
	}
	i--;//back at our index

	if(found==1){
		return_rec=(film_array[i]);
		film_array[i]=NULL;
	}

	return return_rec;
}


void swapasc_record(void **x,void **y){
	void *tmp;
	tmp=*x;
	*x=*y;
	*y=tmp;
}


//generic sort that is usuable with char * comparison and void **swap funcs
void sort(RECORD *film_array, int start, int end, char *rating, char *title,int (*compare)(const char *,const char *),void (*swap)(void **,void **)) {
	int high;
	int i,x=end+1;
	while(x!=start){
		high=start;
		for (i = start; i < x-2; i++) {
			if(compare(film_array[i]->rating,film_array[i+1]->rating)>0){//rating sort
				swap((void **)&film_array[i],(void **)&film_array[i+1]);
			}
			else if(compare(film_array[i]->rating,film_array[i+1]->rating)==0){//if equal, then...
				if(compare(film_array[i]->title,film_array[i+1]->title)>0)//...title sort
					swap((void **)&film_array[i],(void **)&film_array[i+1]);
			}
			high=i+1;
		}
		x=high;
	}
}

//FUNCS END
