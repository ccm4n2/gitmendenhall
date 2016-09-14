#include<stdio.h>
#include<math.h>
#define PI 3.14159

int main()
{
	double area;
	int radius;
	
	printf("please enter the radius of a circle to calculate the area\n");
	scanf("%d", &radius);
	area = PI*pow(radius, 2);
	printf("Area of circle = %lf", area);
	return 0;
};