#include <iostream>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;

class Message{
	protected:
		char message[50];
	public:
		Message();
		Message(char str[]);
		~Message();
		void print();
};

//constructor prompts user for input
Message::Message(){
	//message = new char[50];
	cout<<"What would you like the message to be?\n"<<endl;
	cin>>message;
}

//constructor user input parameter
Message::Message(char str[]){
	//message = new char[strlen(str)];
	stpcpy(message, str);
}

//destructor deallocates memory pointed to by message
Message:: ~Message(){
	//cout<<"Message deleted"<<endl;
	//delete message;
}

//print method
void Message::print(){
	cout<< message << "\n"<<endl;
}

//----------------------------------------------------------------------------
//morsecodeMessage class and functions below

class morseCodeMessage : public Message{
	private:
		string morse_message;
	public:
		void print();
		void translate();
		morseCodeMessage();
		morseCodeMessage(char str[]);
		~morseCodeMessage();
};

//translates and prints message into morse code
void morseCodeMessage::translate(){
	
	//array used for the translation
	string morseCode[] = {".-", "-...", "-.-.", "-..", ".", "..-.", 
							"--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", 
							".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", 
							"-.--", "--.."};
	
	char ch;
	morse_message = "";
	
	//translates into morse code and input into morse_message string
	for(int i = 0; i<strlen(message);i++){
		ch = toupper(message[i]);
		morse_message += morseCode[ch - 'A'];
		morse_message += " ";
	}
}

morseCodeMessage::morseCodeMessage() : Message(){
	//cout<<"\n"<<endl;
	translate();
}

morseCodeMessage::morseCodeMessage(char str[]) : Message(str){
	//cout<<"\n"<<endl;
	translate();
}

void morseCodeMessage::print(){
	cout<<message<<"\n"<<morse_message<<endl;
}

morseCodeMessage::~morseCodeMessage(){
	
}

//--------------------------------------------------------------
///Message stack class and functions below

class messageStack{
	public:
		messageStack(const Message m);
		~messageStack();
		void push(const Message m);
		Message pop();
		void print_stack();
		bool isEmpty();
	
	private:
		//stack node with reference to next element
		struct StackNode{
			Message m;
			StackNode *next;
			
			//stack node constructor
			StackNode(Message element, StackNode *nextNode): m(element), next(nextNode){}
		};
		
		StackNode *top;
};

//stack constructor
messageStack::messageStack(const Message m){
	//cout<<"in stack constructor"<<endl;
	top = NULL;
	push(m);
	//cout<<"exiting constructor"<<endl;
}

//stack destructor
messageStack::~messageStack(){
	//cout<<"in stack destructor"<<endl;
	while(!isEmpty()){
		pop();
	}
}

//push element onto stack and have next node be previous top of stack
void messageStack::push(const Message m){
	//cout<<"in push operation"<<endl;
	top = new StackNode(m, top);
	//cout<<"exiting push operation"<<endl;
}
//pop element from stack
Message messageStack::pop(){
	if(!isEmpty()){
		StackNode *topNode = top;
		//top = top->next;
		Message m1 = top->m;
		top = top->next;
		delete topNode;
		return m1;
	}
	return NULL;
}

//is empty boolean
bool messageStack::isEmpty(){
	if(top==NULL){
		return true;
	}
	else return false;
}

//prints all elements in stack
void messageStack::print_stack(){
	cout<<"printing stack"<<endl;
	StackNode *topNode = top;
	while(topNode != NULL){
		topNode->m.print();
		topNode = topNode->next;
	}
}

int main(){
	//create messages
	Message m1;
	Message m2("message2");
	morseCodeMessage m3("hello");
	
	//print morse code print
	m3.print();
	
	//print message print
	m2.print();
	
	//push to stack
	messageStack stack(m1);
	stack.push(m2);
	stack.push(m3);
	
	//print stack
	stack.print_stack();
}

