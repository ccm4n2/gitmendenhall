#include <stdio.h>
#include <stdlib.h> 
int main()
{
    char* fileName;
    fileName = malloc(50);
    printf("Specify file name you would like to print to: \n");
    scanf("%s", fileName);
 

    FILE* file1 = fopen(fileName, "a+");
 
    char c;
    while ((c=getchar()) !='1');
    {
        fprintf(file1, &c);
    }
 
    fclose(file1);
 
    printf("CTRL+d is a correct ending");
    free(fileName);  	
    return 0;
}
