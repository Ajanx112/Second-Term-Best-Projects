#include <stdio.h>
#include "stack.h"
#include "functions.h"//HOMEWORK FUNCTIONS ARE HERE
#include <string.h>

#define READ_CHARS 24

int main(int argc, char **argv) {
	/*Remainder never forget to change READ_CHARS if the input is changed*/
	char *strfrom=file_read("input.txt",READ_CHARS);//file io just to practice
	char *strto=malloc((sizeof(char))*READ_CHARS);

	/*POSTFIX CONVERSION*/
	printf("Inputted form: %s\n",strfrom);
	toPostfix(strto,strfrom);//postfix conversion test
	file_write("output.txt","w",strto);//file io just to practice
	printf("Outputted form: %s\n",strto);
	/********************/

	/*POSTFIX EVALUATION*/
	int res;
	char s_f_w_i_f_c_m_f_o_s_s[50];//str_for_writing_into_file_cause_my_filewrite()_only_supports_string
	printf("Postfix to be evaluated: %s\n",strto);
	file_write("output.txt","a","\nRESULT OF EVALUATION: ");
	res=calc_postfix(strto);
	sprintf(s_f_w_i_f_c_m_f_o_s_s,"%d",res);
	file_write("output.txt","a",s_f_w_i_f_c_m_f_o_s_s);//file io just to practice
	printf("RESULT OF EVALUATION: %d\n",res);
	/*******************/



	free(strto);
	free(strfrom);
	return 0;
}


