#include<stdio.h>
#include<stdlib.h>
int main()
{
	int x=1309;
	int *p = NULL;
	p = malloc(2);
	*p = 450;
	printf("\n The value of x is = %d",x);
	printf("\n The pointer points to the value = %d",*p);
        free(p);
	return 1;
}
