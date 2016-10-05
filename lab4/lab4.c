#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

//function declarations
void scale(double a, double b[],int length, FILE *fp_out);
void offset_function(double a, double b[], int length, FILE *fp_out);
double average(double b[], int length);
double maximum(double b[], int length);
double maximum_doubles(double a, double b);
void centered(double a[], int length, FILE *fp_out);
void normalized(double a[], int length, FILE *fp_out);

int main(int argc, char *argv[])
{
	//intial variables
	int file = 0;
	FILE *fp;
	FILE *fp_out;
	char str[15];
	double avg;
	double max;
	int length;
	char* new_name;
	double value;
	double scalar = 0;
	double offset = 0;
	int i;
	int help =0;
	int stats =0;
	int center =0;
	int rename;
	char command = 'j';
	int normal;
	int count = 1;
	
	if(argc == 1){
		printf("Error: not enough commands input\n");
		return 0;
	}
	
	i=1;
	while (i < argc){
		//reading commands
		if(strcmp(argv[i], "-n") == 0){
			command = 'a';
		}
		else if(strcmp(argv[i], "-o") == 0){
			command = 'b';
		}
		else if(strcmp(argv[i], "-s") == 0){
			command = 'c';
		}
		else if(strcmp(argv[i], "-S") == 0){
			command = 'd';
		}
		else if(strcmp(argv[i], "-C") == 0){
			command = 'e';
		}
		else if(strcmp(argv[i], "-N") == 0){
			command = 'f';
		}
		else if(strcmp(argv[i], "-r") == 0){
			command = 'g';
		}
		else if(strcmp(argv[i], "-h") == 0){
			command = 'h';
		}
		else{
			command = 'j';
		}
		
		//for errors if end of argv
		if(i==argc-1){
			if(command == 'b'){
				printf("Error not enough information need value for offset\n");
				break;
			}
			if(command == 'c'){
				printf("Error not enough information need value for scalar\n");
				break;
			}
		}
		i++;
		
		//performs right operations based on command
		switch(command){
			case 'a':
				file = atoi(argv[i]);
				i++;
				break;
			case 'b':
				offset = atof(argv[i]);
				//offset error
				if(offset == 0){
					printf("Error not enough information need value for offset\n");
					break;
				}
				i++;
				break;
			case 'c':
				scalar = atof(argv[i]);
				//scalar error
				if(scalar == 0){
					printf("Error not enough information need value for scalar\n");
					break;
				}
				i++;
				break;
			case 'd':
				stats = 1;
				break;
			case 'e':
				center = 1;
				break;
			case 'f':
				normal = 1;
				break;
			case 'g':
				rename =1;
				new_name = argv[i];
				i++;
				break;
			case 'h':
				help = 1;
				break;
			default:
				printf("Option %d is a non-valid input\n", count);
				break;
		}
		count ++;
	}
	
	//if no file number error
	if(file == 0){
		printf("Error: no file specified use -n (1-11)\n");
		return 0;
	}
	
	//help print and tells user to restart program
	if(help == 1){
		printf("Program should be called as follows: ./myprogram -n 5 -S -r newfile\n");
		return 0;
	}
	
	//opening correct file
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
	for(i=0;i<length; i++){
		fscanf(fp, "%lf", &value);
		data[i] = value;
	}
	
	//scaling file if supposed to
	if(scalar != 0){
		//create scalar output file
		if(file < 10){
			sprintf(str, "Scaled_Data_0%d.txt", file);
		}
		else sprintf(str, "Scaled_Data_%d.txt", file);
		fp_out = fopen(str, "w");
		
		//scale the file
		fprintf(fp_out, "%d %0.4lf\n", length, max*scalar);
		scale(scalar, data, length, fp_out);
		fclose(fp_out);
	}
	
	//offsetting file if suppossed to
	if(offset!=0){
		//create offset output file
		if(file < 10){
			sprintf(str, "Offset_Data_0%d.txt", file);
		}
		else sprintf(str, "Offset_Data_%d.txt", file);
		fp_out = fopen(str, "w");
		
		//offset the file and begin writing
		fprintf(fp_out, "%d %0.4lf\n", length, max+offset);
		offset_function(offset, data, length, fp_out);
		fclose(fp_out);
	}
	
	//stats of file if suppossed to
	if(stats ==1){
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
		fprintf(fp_out, "%.4lf %.4lf\n", avg, max);
	}
	
	//centering a file if suppossed to
	if(center ==1){
		//creating out center file
		if(file < 10){
			sprintf(str, "Centered_Data_0%d.txt", file);
		}
		else sprintf(str, "Centered_Data_%d.txt", file);
		fp_out = fopen(str, "w");
		
		//centering data
		centered(data, length, fp_out);
	}
	
	//normalizing a file if supposed to
	if(normal ==1){
		if(file < 10){
		sprintf(str, "Normalized_Data_0%d.txt", file);
		}
		else sprintf(str, "Normalized_Data_%d.txt", file);
		fp_out = fopen(str, "w");
	
		//normalizing data
		normalized(data, length, fp_out);
	}
	
	//renaming a file if supposed to
	if(rename ==1){
		//creating new name file and writing data to it
		sprintf(str, "%s.txt", new_name);
		fp_out = fopen(str, "w");
		fprintf(fp_out, "%d %d\n", length, (int)max);
		for(i=0;i<length;i++){
			fprintf(fp_out, "%.0lf\n", data[i]);
		}
		
		fclose(fp_out);
		
		//normal new file
		if(normal ==1){
		sprintf(str, "%s_Normalized.txt", new_name);
		fp_out = fopen(str, "w");
	
		//normalizing data
		normalized(data, length, fp_out);
		fclose(fp_out);
		}
		
		//center rename
		if(center ==1){
		//creating out center file
		sprintf(str, "%s_Centered.txt", new_name);
		fp_out = fopen(str, "w");
		
		//centering data
		centered(data, length, fp_out);
		fclose(fp_out);
		}
		
		//scalar rename
		if(scalar != 0){
		//create scalar output file
		sprintf(str, "%s_Scaled.txt", new_name);
		fp_out = fopen(str, "w");
		
		//scale the file
		fprintf(fp_out, "%d %0.4lf\n", length, max*scalar);
		scale(scalar, data, length, fp_out);
		fclose(fp_out);
		}
		
		//offset rename
		if(offset!=0){
		//create offset output file
		sprintf(str, "%s_Offset.txt", new_name);
		fp_out = fopen(str, "w");
		
		//offset the file and begin writing
		fprintf(fp_out, "%d %0.4lf\n", length, max+offset);
		offset_function(offset, data, length, fp_out);
		fclose(fp_out);
		}
		
		//stats rename
		if(stats ==1){
		//create new output file
		sprintf(str, "%s_Stats.txt", new_name);
		fp_out = fopen(str, "w");
		
		//get average and max of data
		avg = average(data, length);
		max = maximum(data, length);
		
		//writing to stats file
		fprintf(fp_out, "%.4lf %.4lf\n", avg, max);
		fclose(fp_out);
		}
	}
	
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



