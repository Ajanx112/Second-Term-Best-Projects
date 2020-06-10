#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COUNT 1000002

int strSearch(char *str,int size,char *search);

int main(){
	FILE *fp;
	char *search;
	char *str;
	//allocate a string array
	str=malloc(sizeof(char)*COUNT);
	if(str==NULL)
		return -2;
	//read from the file
	fp=fopen("pi1000000.txt","r");
	if(fp==NULL)
		return -3;
	fread(str,sizeof(char),COUNT,fp);
	fclose(fp);
	//allocate the search string
	search=malloc(100*sizeof(char));
	if(str==NULL)
			return -4;

	printf("Please enter the search term: ");
	fflush(stdout);
	scanf(" %s",search);
	//reallocate for smaller size
	search = realloc(search,sizeof(char)*(strlen(search)+1));
	printf("\n%d",strSearch(str,COUNT,search));
	//free
	free(search);
	free(str);
	return 0;
}

int strSearch(char *str,int size,char *search){
	int i,j,done_bool=0;
	int length=strlen(search);
	for(i=0;i<size;i++){
		if(str[i]==search[0]){
			done_bool=1;
			for(j=1;j<length;j++){
				if(str[i+j]!=search[j])
					done_bool=0;
				else if(done_bool==1&&j==length-1)
					return i-1;
			}
		}
	}
	return -1;
}
