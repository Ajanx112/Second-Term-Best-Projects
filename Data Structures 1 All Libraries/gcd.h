#ifndef LIB_H_
#define LIB_H_

#include <stdio.h>
typedef unsigned long long int ulld;

ulld gcd(ulld x,ulld y){
	ulld r;
	if(y>x){//if the input is wrong we do the switcheroo
	   r=x;
	   x=y;
	   y=r;
	}
	int steps=0;
	printf("Step:%d %I64u = %I64u * %I64u + %I64u\n",steps,x,y,x/y,x-y*(x/y));
	if(x==0||y==0)
	{
	    if(x==y)
	        return 0;//undefined
	    else if(x>y)
	        return x;
	    else
	        return y;
	}
	while(y!=0){
	    steps++;
		r=x%y;
		x=y;
		y=r;
		if(y!=0)
			printf("Step:%d %I64u = %I64u * %I64u + %I64u\n",steps,x,y,x/y,x-y*(x/y));
		fflush(stdout);
	}
	return x;
}


#endif /* LIB_H_ */
