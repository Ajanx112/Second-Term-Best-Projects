#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *binarypatternsearch(char *string,const char *pattern){
	char *leftover;//our leftover pointer
	int found_any=0,found=0;//found_any used in recursive base case
	int i,count=0,start=0;//loop index , substring search pattern size index thing , where the leftover begins


	//int sizestr=(int)(sizeof(string)/sizeof(char)-1);
	//int sizeptrn=(int)(sizeof(pattern)/sizeof(char)-1);

	int sizestr=strlen(string);
	int sizeptrn=strlen(pattern);


	//special case
	if(sizestr<sizeptrn)
		return string;
	//
	for (i = 0; string[i]!='\0'&&found==0; ++i) {
		if(pattern[count]==string[i]){
			count++;
		}
		else{
			if(count!=0)//if the first element is true but the second one is false we won't skip to the next index
				i--;
			count=0;
		}
		//substring search until now

		if(count==sizeptrn){//if found we store the starting index
			found=1;
			start=i+1-sizeptrn;
		}
	}

	if(found==1){//we use starting index and manipulate our input string
		found_any=1;
		leftover=(string+start+sizeptrn);//our leftover is assigned to be an adress which is string + start of the pattern index + pattern size
		for(i=0;leftover[i]!='\0';i++){//reassigning for loop
			string[start]=leftover[i];
			start++;
		}
		string[start]='\0';//end of our new sting is now assigned to null
	}

	if(found_any==0)
		return string;
	else
		return binarypatternsearch(string,pattern);

}


int main(){
	//char arr[]={'1','1','1','0','0','1','1','0','1','\0'};
	char arr[]={"111001101"};
	//char pattern[]={'0','1','\0'};
	char pattern[]={"01"};

	//printf("%d  %d  %d  %d\n",strlen(arr),strlen(pattern),sizeof(arr)/sizeof(char)-1,(sizeof(pattern)/sizeof(char)-1));
	printf("%s",binarypatternsearch(arr,pattern));
	return 0;
}
