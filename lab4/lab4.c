#include<stdio.h>
#include<math.h>

//function declarations
void scale(double a, double b[],int length, FILE *fp_out);
void offset_function(double a, double b[], int length, FILE *fp_out);
double average(double b[], int length);
double maximum(double b[], int length);
double maximum_doubles(double a, double b);
void centered(double a[], int length, FILE *fp_out);
void normalized(double a[], int length, FILE *fp_out);

int main()
{
	//intial variables
	int file;
	FILE *fp;
	FILE *fp_out;
	char str[15];
	double avg;
	double max;
	int length;
	double value;
	double scalar;
	double offset;
	char c;
	
	//getting specified file from user
	printf("Which file would you like to open? (1-11)\n");
	scanf("%d", &file);
	if(file < 10){
		sprintf(str, "Raw_Data_0%d.txt", file);
	}
	else sprintf(str, "Raw_Data_%d.txt", file);
	
	//opening specified file for reading
	fp = fopen(str, "r");
	//read length and max of file
	fscanf(fp, "%d %lf", &length, &max);
	
	//read data into array
	double data[length];
	int i;
	for(i=0;i<length; i++){
		fscanf(fp, "%lf", &value);
		data[i] = value;
	}
	
	printf("Offset or Scalar? (o or s)\n");
	scanf(" %c", &c);
	
	switch(c){
	case 's':
		//create scalar output file
		if(file < 10){
			sprintf(str, "Scaled_Data_0%d.txt", file);
		}
		else sprintf(str, "Scaled_Data_%d.txt", file);
		fp_out = fopen(str, "w");
		
		//scale the file
		printf("Enter scalar: \n");
		scanf("%lf", &scalar);
		fprintf(fp_out, "%d %0.4lf\n", length, max*scalar);
		scale(scalar, data, length, fp_out);
		fclose(fp_out);
		break;
	
	case 'o':
		//create offset output file
		if(file < 10){
			sprintf(str, "Offset_Data_0%d.txt", file);
		}
		else sprintf(str, "Offset_Data_%d.txt", file);
		fp_out = fopen(str, "w");
		
		//offset the file and begin writing
		printf("Enter offset: \n");
		scanf("%lf", &offset);
		fprintf(fp_out, "%d %0.4lf\n", length, max+offset);
		offset_function(offset, data, length, fp_out);
		fclose(fp_out);
		break;
	default:
		printf("Not a Valid selection\n");
		break;
	}
	
	//create new output file
	if(file < 10){
		sprintf(str, "Statistics_Data_0%d.txt", file);
	}
	else sprintf(str, "Statistics_Data_%d.txt", file);
	fp_out = fopen(str, "w");
	
	//get average and max of data
	avg = average(data, length);
	max = maximum(data, length);
	
	//writing to stats file
	fprintf(fp_out, "%.4lf $.4lf\n", avg, max);
	
	//creating out center file
	if(file < 10){
		sprintf(str, "Centered_Data_0%d.txt", file);
	}
	else sprintf(str, "Centered_Data_%d.txt", file);
	fp_out = fopen(str, "w");
	
	//centering data
	centered(data, length, fp_out);
	
	//create normalized output file
	if(file < 10){
		sprintf(str, "Normalized_Data_0%d.txt", file);
	}
	else sprintf(str, "Normalized_Data_%d.txt", file);
	fp_out = fopen(str, "w");
	
	//normalizing data
	normalized(data, length, fp_out);
	
	fclose(fp_out);
	fclose(fp);
	return 0;
};

//function to scale numbers in file and save in new file
void scale(double a, double b[], int length, FILE *fp_out){
	double scaled_value;
	double scalar =a;
	
	//scaling values in file
	int i;
	for(i=0;i<length; i++){
		scaled_value = b[i]*scalar;
		fprintf(fp_out, "%.4lf \n", scaled_value);
	}
	
}

//function to offset numbers in file and save in new file
void offset_function(double a, double b[], int length, FILE *fp_out){
	double offset_value;
	double c = a;
	
	//offsetting values and printing to new file
	int i;
	for(i=0;i<length;i++){
		offset_value = b[i] + c;
		fprintf(fp_out, "%.4lf\n", offset_value);	
	}
}

//finds and returns average of numbers in array
double average(double b[], int length){
	double sum = 0;
	double avg;
	int i;
	for(i=0;i<length;i++){
		sum += b[i];
	}
	avg = sum/(double)length;
	return avg;
}

//finds the maximum number of array
double maximum(double b[], int length){
	double max = 0;
	int i;
	for(i=0;i<length;i++){
		max = maximum_doubles(b[i], max);
	}
	return max;
}

//finds the maximum between two doubles
double maximum_doubles(double a, double b){
	if(a>b){
		return a;
	}
	else return b;
}

//centering the signal and printing in new file
void centered(double a[], int length, FILE *fp_out){
	double avg = average(a, length);
	offset_function(-avg, a, length, fp_out);
}

//normalizing a signal and printing in a new file
void normalized(double a[], int length, FILE *fp_out){
	double max = maximum(a,length);
	scale(1/max, a, length, fp_out);
}



