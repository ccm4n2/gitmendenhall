
#include <iostream>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>


using namespace std;

class Signal{
	private:
		void set_average();
	public:
		int length;
		double max_value, average;
		vector<double> data;
		void operator+(double a);
		void offset(double a);
		void operator*(double a);
		void scale(double a);
		void statistics();
		void normalize();
		void center();
		void sig_info();
		void save_file(string str);
		Signal();
		Signal(int n);
		Signal(string str);
		~Signal();
};

//Signal functions
void Signal::sig_info(){
	std::cout<<"Length: "<< length <<" Maximum value: "<< max_value << " Average value: " << average << "\n"<<std::endl;
}

void Signal::save_file(string str){
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

void Signal::operator+(double a){
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

void Signal::operator*(double a){
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
	this->operator+(-average);
	max_value -= average;
}

void Signal::center(){
	double b = 1/max_value;
	this->operator*(b);
	max_value = 1;
}

Signal operator+(const Signal &s1, const Signal &s2){
	Signal s3;
	if(s1.length == s2.length){
		s3.length = s1.length;
		int i = 0;
		for(i;i<s1.length;i++){
			s3.data[i] = s1.data[i] + s2.data[i];
		}
		
		if(s1.max_value>s2.max_value) s3.max_value = s1.max_value;
		else s3.max_value = s2.max_value;
		
		s3.average = (s1.average+s2.average)/2;
	}
	else{
		//s3 remains empty
	}
	return s3;
}

Signal::Signal(){
	length = 0;
	average = 0;
	max_value = 0;
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
		double j;
		for(i=0;i<length;i++){
			in_file>>j;
			data.push_back(j);
		}
		set_average();
		in_file.close();
	}
	else{
		std::cout<<"Error opening file: "<< str << " file number not valid"<< std::endl;
		length = 0;
		average = 0;
		max_value = 0;
	}
}

Signal::Signal(string str){
	//checking for specified signal file and reading length and max if available
	std::ifstream in_file(str, std::ifstream::in);
	if(in_file.is_open()==true){
		in_file>>length;
		in_file>>max_value;
				
		//reading data into array
		//reading data into array	
		int i;
		double j;
		for(i=0;i<length;i++){
			in_file>>j;
			data.push_back(j);
		}
		set_average();
		in_file.close();
	}
	else{
		std::cout<<"Error opening file: "<< str << " file number not valid"<< std::endl;
		length = 0;
		average = 0;
		max_value = 0;
	}
}

Signal::~Signal(){

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
	string c;
	char file_name[50];
	int n;
	Signal* s1;
	Signal* s2 = new Signal(5);
	if(argc == 1){
		//no command line inputs
		std::cout<<"Would you like to Enter a file name (name) or file number (num)?\n";
		std::cin>>c;
		
		//name
		if(c == "name"){
			std::cout<<"Please enter filename\n";
			std::cin>>file_name;
			s1= new Signal(file_name);
		}
		
		//number
		else if(c=="num"){
			std::cout<<"Please enter file number\n";
			std::cin>>n;
			//std::cout<<n;
			s1 = new Signal(n);
		}
		
		//default file
		else{
			std::cout<<"Signal will be empty Signal"<<std::endl;
		}
	}
	
	//command line inputs
	else{
		//number
		if(strcmp(argv[1], "-n") == 0){
			n = atoi(argv[2]);
			s1 = new Signal(n);
		}
		
		//name
		else if(strcmp(argv[1], "-f") == 0){
			string file(argv[2]);
			s1 = new Signal(file);
		}
			
		//default
		else{
			std::cout<<"Signal will be empty Signal"<<std::endl;
		}
	}
	
	
	//while loop so user can do what they want with the signal
	int w = 0;
	char operation;
	//Signal s3 = operator+(*s1,*s2);
	while(w==0){
		std::cout<<"What would you like to do with the following Signal? \nCenter(C) Normalize(N) Offset(O) Scale(S) Stats(s) Write to file(W) Info(I) End(E)\n"<<std::endl;
		std::cin>>operation;
		
		switch(operation){
			case 'C':
				s1->center();
				break;
			case 'N':
				s1->normalize();
				break;
			case 'S':
				double scalar;
				std::cout<<"Scale by what number? \n"<<std::endl;
				std:cin>>scalar;
				s1->scale(scalar);
				break;
			case 'O':
				double offset;
				std::cout<<"Offset by what number? \n"<<std::endl;
				std::cin>>offset;
				s1->offset(offset);
				break;
			case 's':
				s1->statistics();
				break;
			case 'W':{
				string name2;
				std::cout<<"Enter new file name \n"<<std::endl;
				std::cin>>name2;
				s1->save_file(name2);}
				break;
			case 'I':
				s1->sig_info();
				break;
			case 'E':
				w++;
				break;
			default:
				std::cout<<"Invalid action entered please try again"<<std::endl;
				break;
		}
	}

	delete s1;
	return 0;
}
