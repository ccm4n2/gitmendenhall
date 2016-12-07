
#include <iostream>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;

//Sudoku_Board class, holds information on sudoku board
//blank values of the boards aka values user has to solve will be input as zeros


class Sudoku_Board{
	public: 
		int board[9][9]; //board holds the numbers relevant to this board
		Sudoku_Board(); //default board constructor
		Sudoku_Board(int n); //user specified board constructor, takes board number
		~Sudoku_Board(); //destructor
		void print_board(); //prints board
		void game_print_board(); //to do (have an idea for this)
};

//default constructor
Sudoku_Board::Sudoku_Board(){
	//reading in data to board
	ifstream in_file;
	in_file.open("board_default.txt", std::ifstream::in);
	
	int i, j;
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			in_file>>board[i][j];
		}
	}
	
	//closing file stream
	in_file.close();
}

//user specified board constructor
Sudoku_Board::Sudoku_Board(int n){
	//reading in data to board
	//ifstream in_file;
    char str[15];
	sprintf(str, "board%d.txt", n);
	std::ifstream in_file (str, std::ifstream::in);
	
	//if board doesnt exist throw error
	if(in_file.is_open()==false){
		cout<<"Error opening file not a valid board number"<<endl;
		throw 20;
	}
    else{ 
		//reading in data
		int i, j;
		for(i=0;i<9;i++){
			for(j=0;j<9;j++){
				in_file>>board[i][j];
				if(board[i][j] > 9 || board[i][j] < 0){
					cout<<"Error: Board has invalid arguments did not open correctly"<<endl;
					throw 20;
					i = 9; j = 9;
				} 
			}
		}
	}
	//closing file stream
	in_file.close();
}



//Sudoku_Board destructor
Sudoku_Board::~Sudoku_Board(){
	//no memory allocated
}

//prints sudoku board
void Sudoku_Board::print_board(){
	int i;
	for(i=0;i<9;i++){
		cout<<board[i][0]<< " " << board[i][1]<< " " << board[i][2]<< " " << board[i][3]
				<< " " << board[i][4]<< " " << board[i][5]<< " " << board[i][6]<< " " <<
				board[i][7]<< " " << board[i][8]<< endl;
	}
}

//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------

//Sudoku Solver Class and functions below
//this class is for the solving algorithims for solving the unfilled spaces on sudoku boards

class Sudoku_Solver{
	public:
		Sudoku_Board board;
		Sudoku_Solver(Sudoku_Board Board);
		~Sudoku_Solver();
		bool solve(unsigned pos);
	private:
		bool check(unsigned x,unsigned y);
		bool isEmpty(int row, int col);
};

//returns true is specified square of board is empty
bool Sudoku_Solver::isEmpty(int row, int col){
	if(board.board[row][col] == 0) return true;
	else return false;
}

//Sudoku_Solver constructor
Sudoku_Solver::Sudoku_Solver(Sudoku_Board Board){
	board = Board;
	
	//now solve board
	solve(0);
}

//destructor
Sudoku_Solver::~Sudoku_Solver(){
	//deletes memory
}

//checks for conflicts based on sudoku rules
bool Sudoku_Solver::check(unsigned x,unsigned y){
	unsigned char val=board.board[x][y];
	for (unsigned a=0;a<x;a++)
		if (board.board[a][y]==val)
			return false;
	for (unsigned a=x+1;a<9;a++)
		if (board.board[a][y]==val)
			return false;
	for (unsigned a=0;a<y;a++)
		if (board.board[x][a]==val)
			return false;
	for (unsigned a=y+1;a<9;a++)
		if (board.board[x][a]==val)
			return false;
	unsigned startx=x/(9/3)*3,
		starty=y/(9/3)*3,
		endx=startx+9/3,
		endy=starty+9/3;
	for (unsigned a=startx;a<endx;a++){
		for (unsigned b=starty;b<endy;b++){
			if (a!=x && b!=y && board.board[a][b]==val)
				return false;
		}
	}
	return true;
}		

//solves board
bool Sudoku_Solver::solve(unsigned pos){
	unsigned x=pos%9,
		y=pos/9;
	if (y>=9)
		return true;
	if (board.board[x][y])
		return solve(pos+1);
	for (unsigned a=1;a<=9;a++){
		board.board[x][y]=a;
		if (check(x,y) && solve(pos+1))
			return true;
	}
	board.board[x][y]=0;
	return 0;
}	

//---------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
//Sudoku Game class to run a computer game version of the puzzle

class Sudoku_Game{
	private:
		Sudoku_Solver* solver;
	public:
		Sudoku_Board board;
		Sudoku_Game(Sudoku_Board Board);
		~Sudoku_Game();
		void print_game_board();
		bool check_answer(int p, int row, int col);
		void hint(int row, int col);
};

//Constructor
Sudoku_Game::Sudoku_Game(Sudoku_Board Board){
	board = Board;
	
	solver = new Sudoku_Solver(Board);
	
}

//Destructor
Sudoku_Game::~Sudoku_Game(){
	delete solver;
}

//fills in specified square for the user
void Sudoku_Game::hint(int row, int col){
	cout<<solver->board.board[row][col]<< " " <<board.board[row][col]<<endl;;
	board.board[row][col] = solver->board.board[row][col];
}

//Prints board in game mode
void Sudoku_Game::print_game_board(){
	int k = 1;
	cout<<"    ";
	for(k;k<=9;k++){
		cout<<k<<"  ";
	}
	
	//jump down two lines
	cout<<"\n"<<endl;
	
	//start printing board
	int i,j;
	for(i=1;i<=9;i++){
		cout<<i<<"   ";
		for(j=0;j<9;j++){
			cout<<board.board[i-1][j]<<"  ";
		}
		cout<<endl;
	}
}

//checks user specified answer with specified square against a solved board
bool Sudoku_Game::check_answer(int p, int row, int col){
	if(solver->board.board[row][col] == p) return true;
	else return false;
}

//gives the user the answer to specified square

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------	

//main running the program
int main(){
	cout<<"Hello! Welcome to our Sudoku Game would you like to enter your own board or use the default play board? (0 for default or enter board number)"<<endl;
	int n;
	cin>>n;
	Sudoku_Board* b1;
	
	//exception handling for invalid board
	if(n == 0) b1 = new Sudoku_Board();
	else{
		try {
				b1 = new Sudoku_Board(n);
		}	
		
		//exception for invalid input board
		catch(int e){
			cout<<"Invalid board program terminating"<<endl;
			return 0;
		}
	}
	
	//user decides what they want to do with board
	cout<<"Would you like to solve this board or play a game? (enter solve or game)"<<endl;
	string str;
	cin>>str;
	
	//solves input board
	if(str == "solve"){
		b1->print_board();
		Sudoku_Solver s1(*b1);
		cout<<"\n"<<endl;
		s1.board.print_board();
	}
	
	//user can play a game
	else if (str == "game"){
		int z = 0;
		char selection;
		Sudoku_Game game1(*b1);
		while(z==0){
			game1.print_game_board();
			cout<<"Enter p to play a square, enter h for a hint, or enter e to exit the game"<<endl;
			cin>>selection;
			
			switch(selection){
				case 'p':
							int num, row, col;
							cout<<"Enter your answer for a square in following format: Num Row Col (all have to be 1-9)"<<endl;
							cin>>num; cin>>row; cin>>col;
							
							//exceptions
							if(num <1 || num>9||row <1 || row >9 || col <1 || col>9){
								cout<<"Error invalid number and/or row and/or column these numbers must be between 1-9"<<endl;
							}
							
							//game checks their answer for that square
							else{
								if(game1.check_answer(num, row-1, col-1)){
									cout<<"Correct Answer"<<endl;
									game1.board.board[row-1][col-1] = num;
								}
								else{
										cout<<"Wrong Answer"<<endl;
								}
								
							
							break;
				
				case 'h':		
							int row, col;
							cout<<"Enter square on board that you want a hint for: row (1-9) col (1-9)"<<endl;
							cin>>row; cin>>col;
							
							//exceptions
							if(row <1 || row >9 || col <1 || col>9){
								cout<<"Error invalid row and/or column number these numbers must be between 1-9"<<endl;
							}
							else{
								game1.hint(row-1,col-1);								}
							}
							break;
				case 'e':			
							//exit game
							cout<<"Exiting Game and program"<<endl;
							z++;
							break;
				default:			
							//invalid input
							cout<<"Invalid input please try again"<<endl;
							break;	
			}
		}	
	}

	
	else{
		cout<<"Not a valid input program exiting"<<endl;
	}
	
	return 0;
}