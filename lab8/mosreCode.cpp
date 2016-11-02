#include <iostream>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;

class Message{
	private:
		char *message;
	public:
		Message();
		Message(char str[]);
		~Message();
		void print();
};

//constructor prompts user for input
Message::Message(){
	message = new char[50];
	cout<<"What would you like the message to be?\n"<<endl;
	cin>>message;
}

//constructor user input parameter
Message::Message(char str[]){
	message = new char[strlen(str)];
	stpcpy(message, str);
}

//destructor deallocates memory pointed to by message
Message::~Message(){
	delete message;
}

//print method
void Message::print(){
	cout<< message << "\n"<<endl;
}

