#include<stdio.h>
#include<math.h>
#define PI 3.14159

int main()
{
	double circumference;
	int radius;
	
	printf("please enter the radius of a circle to calculate the circumference\n");
	scanf("%d", &radius);
	circumference = PI*2*radius;
	printf("circumference of circle = %lf", circumference);
	return 0;
};