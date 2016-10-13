#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
int main(void)
{
	char *s, *dyn_s;
	int ln;
	s = malloc(50);
	printf("Enter the input string\n");
	scanf("%s",s);
	ln = strlen(s);
	dyn_s = (char*)malloc(strlen(s)+1);
	dyn_s = s;
	dyn_s[strlen(s)]='\0';
	printf(dyn_s);
	return 0;
}

