
#include <iostream>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;

class Signal{
	private:
		int length;
		double max_value, average;
		double* data;
		void set_average();
	public:
		void offset(double a);
		void scale(double a);
		void statistics();
		void normalize();
		void center();
		void sig_info();
		void save_file(char* str);
		Signal();
		Signal(int n);
		Signal(const char* str);
		~Signal();
};

//Signal functions
void Signal::sig_info(){
	std::cout<<"Length: "<< length <<" Maximum value: "<< max_value << " Average value: " << average << "\n"<<std::endl;
}

void Signal::save_file(char* str){
	ofstream output_file;
	output_file.open(str);
	output_file<<length<<" "<<max_value<<"\n";
	int i;
	for(i=0;i<length;i++){
		output_file<< data[i]<< "\n";
	}
	output_file.close();
}

void Signal::offset(double a){
	max_value += a;
	int i;
	for(i=0;i<length;i++){
		data[i] += a;
	}
	set_average();
}

void Signal::scale(double a){
	max_value *= a;
	int i;
	for(i=0;i<length;i++){
		data[i] *= a;
	}
	set_average();
}

void Signal::statistics(){
	std::cout<<"Maximum value: "<< max_value << " Average value: " << average << "\n" <<std::endl;
}

void Signal::normalize(){
	offset(-average);
}

void Signal::center(){
	scale(1/max_value);
}

Signal::Signal(){
	std::ifstream in_file;
	in_file.open("Raw_Data_01.txt", std::ifstream::in);
	in_file>>length;
	in_file>>max_value;
	
	//reading data into array	
	int i;
	data = new double[length];
	for(i=0;i<length;i++){
		in_file>>data[i];
	}
	set_average();
	in_file.close();
}

Signal::Signal(int n){
	char str[15];
	if(n<10){
		sprintf(str, "Raw_Data_0%d.txt", n);
	}
	else{
		sprintf(str, "Raw_Data_%d.txt", n);
	}
	
	std::ifstream in_file (str, std::ifstream::in);
	if(in_file.is_open()==true){
		//in_file.open(str, std::ifstream::in);
		in_file>>length;
		in_file>>max_value;
		
		//reading data into array	
		int i;
		data = new double[length];
		for(i=0;i<length;i++){
			in_file>>data[i];
		}
		set_average();
		in_file.close();
	}
	else{
		std::cout<<"Error opening file: "<< str << " file number not valid opening default file"<< std::endl;
		std::ifstream in_file;
		in_file.open("Raw_Data_01.txt", std::ifstream::in);
		in_file>>length;
		in_file>>max_value;
		
		//reading data into array	
		int i;
		data = new double[length];
		for(i=0;i<length;i++){
			in_file>>data[i];
		}
		set_average();
		in_file.close();
	}
}

Signal::Signal(const char* str){
	//checking for specified signal file and reading length and max if available
	std::ifstream in_file(str, std::ifstream::in);
	if(in_file.is_open()==true){
		//in_file.open(*str, std::ifstream::in);
		in_file>>length;
		in_file>>max_value;
				
		//reading data into array
		//reading data into array	
		int i;
		data = new double [length];
		for(i=0;i<length;i++){
			in_file>>data[i];
		}
		set_average();
		in_file.close();
	}
	else{
		std::cout<<"Error opening file: "<< *str << " filename not valid default file being opened"<< std::endl;
		std::ifstream in_file;
		in_file.open("Raw_Data_01.txt", std::ifstream::in);
		in_file>>length;
		in_file>>max_value;
		
		//reading data into array	
		int i;
		data = new double [length];
		for(i=0;i<length;i++){
			in_file>>data[i];
		}
		set_average();
		in_file.close();
	}
}

Signal::~Signal(){
	delete[] data;
}

void Signal::set_average(){
	double total = 0;
	int i;
	for(i=0; i<length; i++){
		total += data[i];
	}
	average = total/length;
}

//main running functions
int main(int argc, char *argv[]){
	char* c;
	char file_name[50];
	int n;
	Signal *s2 = NULL;
	if(argc == 1){
		//no command line inputs
		std::cout<<"Would you like to Enter a file name (name) or file number (num)?\n";
		std::cin>>c;
		
		//name
		if(strcmp(c, "name")==0){
			std::cout<<"Please enter filename\n";
			std::cin>>file_name;
			Signal s1(file_name);
			s2 = &s1;
		}
		
		//number
		else if(strcmp(c, "num")==0){
			std::cout<<"Please enter file number\n";
			std::cin>>n;
			//std::cout<<n;
			Signal s1(n);
			s2 = &s1;
		}
		
		//default file
		else{
			std::cout<<"Default File being opening, proper command not input by user"<<std::endl;
			Signal s1;
			s2 = &s1;
		}
	}
	
	//command line inputs
	else{
		//number
		if(strcmp(argv[2], "-n") == 0){
			n = atoi(argv[3]);
			Signal s1(n);
			s2 = &s1;
		}
		
		//name
		else if(strcmp(argv[2], "-f") == 0){
			char* name;
			name = argv[3];
			Signal s1(name);
			s2 = &s1;
		}
		
		//default
		else{
			std::cout<<"Default File being opening, proper command not input by user"<<std::endl;
			Signal s1;
			s2 = &s1;
		}
	}
	
	//while loop so user can do what they want with the signal
	int w = 0;
	char operation;
	while(w==0){
		std::cout<<"What would you like to do with the following Signal? \nCenter(C) Normalize(N) Offset(O) Scale(S) Stats(s) Write to file(W) Info(I) End(E)\n"<<std::endl;
		std::cin>>operation;
		
		switch(operation){
			case 'C':
				s2->center();
				break;
			case 'N':
				s2->normalize();
				break;
			case 'S':
				double scalar;
				std::cout<<"Scale by what number? \n"<<std::endl;
				std:cin>>scalar;
				s2->scale(scalar);
				break;
			case 'O':
				double offset;
				std::cout<<"Offset by what number? \n"<<std::endl;
				std::cin>>offset;
				s2->offset(offset);
				break;
			case 's':
				s2->statistics();
				break;
			case 'W':
				char* name;
				std::cout<<"Enter new file name \n"<<std::endl;
				std::cin>>name;
				s2->save_file(name);
				break;
			case 'I':
				s2->sig_info();
				break;
			case 'E':
				w++;
				break;
			default:
				std::cout<<"Invalid action entered please try again"<<std::endl;
				break;
		}
	}
	
	delete s2;
	return 0;
}