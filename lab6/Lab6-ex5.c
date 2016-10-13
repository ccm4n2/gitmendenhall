#include<stdio.h>
#include<malloc.h>
#include<string.h>
void main()
{
    char *a;
    a = (char*) malloc(15);
    strcpy(a, "hey");
    free( a );
    a = (char*) malloc(15);	
    strcpy(a, "hello");   
    printf("%s",a);
    free(a);
}
