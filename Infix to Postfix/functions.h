#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>//for pow()
#include <string.h>//for strlen()
#include "stack.h"

char *file_read(char *path,int read_this_many_chars){//additional read from file function
	FILE *fp;
	int i;
	char ch,*return_arr=malloc(sizeof(char)*(read_this_many_chars));

	if(return_arr==NULL){
		fprintf(stderr,"file_read():char * malloc error");
		exit(-1);
	}

	fp=fopen(path,"r");
	if(fp==NULL){
		fprintf(stderr,"file_read():fopen() error");
		exit(-2);
	}

	for(i=0;i<read_this_many_chars;i++){
		if((ch=fgetc(fp))!=EOF){
			return_arr[i]=ch;
		}
	}

	fclose(fp);
	return return_arr;
}

void file_write(char *path,char *mode,char *str){//additional write to file function
	FILE *fp;
	fp=fopen(path,mode);
	if(fp==NULL){
		fprintf(stderr,"file_write():fopen() error");
		exit(-2);
	}
	fprintf(fp,str);
	fclose(fp);
}

int isOperand(char ch){//helper func
	if(ch>47&&ch<58)
		return 1;
	return 0;
}

int priority(char ch){//helper func
	switch(ch){
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case '^':
		return 3;
	case '(':
	case ')':
		return 4;
	default:
		return -1;
	};
}

void toPostfix(char *to,char *from){//infix to postfix assignment function
	LINKED_STACK LinkS=linked_stack_init();
	int i=0,indx=0;
	char ch;

	while(from[i]!='\0'){//reading until the string ends
			ch=from[i];
			//When an operand is read, it is placed onto the output.
			if(isOperand(ch)){
				to[indx]=ch;
				indx++;
			}
			//Left parenthesis are pushed to the stack.
			else if(ch=='('){
				linked_stack_push(LinkS,(void *)&from[i]);
			}
			//If we see a right parenthesis, then we pop the stack, until a left parenthesis is seen
			else if(ch==')'){
				while(!linked_stack_is_empty(LinkS)&&*(char *)linked_stack_top(LinkS)!='('){
					to[indx]=*(char *)linked_stack_pop(LinkS);
					indx++;
				}
				if(!linked_stack_is_empty(LinkS)){//for popping the left parenthesis
					linked_stack_pop(LinkS);
				}
			}
			//we pop entries from the stack until we find an entry of higher priority
			else if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='^'){
				while(!linked_stack_is_empty(LinkS)&&priority(ch)<=priority(*(char *)linked_stack_top(LinkS))){
					if(*(char *)linked_stack_top(LinkS)!='('){//One exception is that we never remove a ’(’
						to[indx]=*(char *)linked_stack_pop(LinkS);
						indx++;
					}
					else
						break;
				}
				linked_stack_push(LinkS,(void *)&from[i]);//When the popping is done, we push the operand onto the stack.
			}

			i++;
	}//endofbigwhile

	//If we read the end of input, we pop the stack until it is empty
	while(!linked_stack_is_empty(LinkS)){
			if(*(char *)linked_stack_top(LinkS)!='('){
				to[indx]=*(char *)linked_stack_pop(LinkS);
				indx++;
			}
			else{
				linked_stack_pop(LinkS);
			}
		}

	linked_stack_free(LinkS);
}

int operator_switch(char ch,char cx,char cy){
	int x=cx-'0';
	int y=cy-'0';
	switch (ch){
	case '+':
		return x+y;
	case '-':
		return x-y;
	case '*':
		return x*y;
	case '/':
		return x/y;
	case '^':
		return pow(x,y);
	default:
		return -1;
	};
}

int calc_postfix(char *from){
	LINKED_STACK LinkS=linked_stack_init();
	int i=0,indx=0,res=0;
	char ch,*auxiliary=malloc(strlen(from)*sizeof(char));

	while(from[i]!='\0'){//reading until the string ends
		ch=from[i];
		if(isOperand(ch))//if it is an operand we push
			linked_stack_push(LinkS,(void *)&from[i]);
		else if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='^'){
			auxiliary[indx]='0'+operator_switch(ch,*(char *)linked_stack_pop(LinkS),*(char *)linked_stack_pop(LinkS));
			linked_stack_push(LinkS,&auxiliary[indx]);
			indx++;
		}
		i++;
	}

	res=*(char *)linked_stack_pop(LinkS)-'0';
	free(auxiliary);
	linked_stack_free(LinkS);
	return res;
}

#endif
