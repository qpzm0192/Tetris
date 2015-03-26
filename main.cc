#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
using namespace std;

#include "block.h"
#include "cell.h"
#include "level.h"
#include "board.h"


//*****************************************************
//                 Helper Function
//*****************************************************

Level* newLevel(int n,char type,int s) {
	if(n == 0) return new Level0(type);
	else if(n == 1) return new Level1(s);
	else if(n == 2) return new Level2(s);
	else return new Level3(s);
}	

Block* newBlock(int level, Level* l, char type,int s) {
	if(level == 0) {
		l = new Level0(type);
		return l->createBlock();
	}	
	else if(level == 1) {
		l = new Level1(s);
		return l->createBlock();
	}
	else if(level == 2) {
		l = new Level2(s);
		return l->createBlock();
	}
	else {
		l = new Level3(s);
		return l->createBlock();
	}
}
	
void printBoard(Board* b, Block *next, int level) {
	cout<<"Level:    "<< level <<endl;

	cout << *b << endl;

	char **arr = new char*[2];
	for(int i=0; i<2; i++) {
		arr[i]= new char[4];
	}
	for(int j=0; j<2; j++) {
		for(int k=0; k<4; k++) {
			arr[j][k] = ' ';
		}
	}

	int *p = next->getPos();

	char type =next->getType();
	arr[p[0]-3][p[1]] = type;
	arr[p[2]-3][p[3]] = type;
	arr[p[4]-3][p[5]] = type;
	arr[p[6]-3][p[7]] = type;

	for(int j=0; j<2; j++) {
		for(int k=0; k<4; k++) {
			cout << arr[j][k];
		}
		cout << endl;
	}
	cout << endl;

}


//*****************************************************



int main(int argc, char *argv[]) {

	string s;
	string fname = "sequence.txt";
	int seed = -1;
	int level;
	Block *cur;
	Block *next;

	for(int i=1; i<argc; i++) {
		string cmd1 = argv[i];
		if(cmd1 == "-scriptfile") {
			fname = argv[i+1];
		} else if(cmd1 == "-seed") {
			istringstream iss(argv[i+1]);
			iss >> seed;
		} else if(cmd1 == "-startlevel") {
			if(i+1 < argc) {
				istringstream is(argv[i+1]);
				is >> level;
			} else level=0;
		} else if(cmd1 == "-text") {
		}
	}		



	Board *board = new Board(level);
	Level *l;

		
	//if level = 0, get list of type
	char type = ' ';
	string loType; //contains the list of types in the file
	int numOfType; //max num of the types
	int index = 0; 

	if(level == 0) {


		ifstream file(fname.c_str());
		getline(file,loType);
		numOfType = loType.size();
		type = loType[index];
		index+=2;


	}	
	cur = newBlock(level, l, type, seed);



	if(level == 0) {
		numOfType = loType.size();
		type = loType[index];
		index+=2;
	}		
	next = newBlock(level, l, type, seed);
	board->setCurNext(cur,next);
	printBoard(board, next, level);
		
	while(1) {
		int multiplier;
		string move;
		string cmd;
		char c = cin.peek();
		if (cin.fail()) break;

		if(c >= '1' && c <= '9') {
			getline(cin, cmd);
			istringstream iss(cmd);
			iss >> multiplier;
			iss >> move;
		} else {
			multiplier = 1;
			getline(cin, move);
		}

		if(move == "left" || cmd == "lef") {
			for(int i=0; i<multiplier; i++) {
				board->left();
			}

			printBoard(board, next, level);
		}
		else if(move == "right" || move == "ri" || move == "rig" ||
			 move == "righ") {
			for(int i=0; i<multiplier; i++) {
				board->right();
			}
			printBoard(board, next, level);
		}

		else if(move == "down" || move == "do" || move == "dow") {
			for(int i=0; i<multiplier; i++) {
				board->down();
			}
			printBoard(board, next, level);
		}

		else if(move == "drop" || move == "dr" || move == "dro") {
			board->drop();

			Block *tmp = cur;
			delete tmp;
			cur = next;
			board->setCurNext(cur, next);
			if(level == 0) {
				if(index >= numOfType) index = 0;
				type = loType[index];
				index+=2;
			}
			next = newBlock(level, l, type, seed);

/*
			if(board->checkLose()) {
				cout << "yes" << endl;
				cout << "You LOSE! Game is restarted." << endl;
				board->clearBoard();
				board->initBoard();

				Block *tmp = cur;
				delete tmp;
				cur = next;

				if(level == 0) {
					if(index >= numOfType) index = 0;
					type = loType[index];
					index+=2;
				}
				next = newBlock(level, l, type, seed);
				board->setCurNext(cur, next);
				printBoard(board, next, level);
			}
*/
			printBoard(board, next, level);
		}


		else if(move == "clockwise" || move == "cl" || move == "clo" ||
			 move == "cloc" || move == "clock" || move == "clockw" ||
			 move == "clockwi" || move == "clockwis" || move == "clockwise") {
			for(int i=0; i<multiplier; i++) {
				board->cw();
			}
			printBoard(board, next, level);
		}

		else if(move == "counterclockwise" || move == "co" || move == "cou" ||
			 move == "coun" || move == "count" || move == "counte" ||
			 move == "counter" || move == "counterc" || move == "countercl" ||
			 move == "counterclo" || move == "countercloc" ||
			 move == "counterclock" || move == "counterclockw" ||
			 move == "counterclockwi" || move == "counterclockwis" ||
			 move == "counterclockwise") {
			for(int i=0; i<multiplier; i++) {
				board->ccw();
			}
			printBoard(board, next, level);
		}

		else if(move == "levelup" || move == "lev" || move == "leve" ||
			 move == "level" || move == "levelu"){
			level++;
			l = newLevel(level,type, seed); 
			board->setLevel(level);
			cout << "Level is set to: " << level << endl;
		}

		else if(move == "leveldown" || move == "leveld" || move == "levedo" ||
			 move == "leveldow"){
			level--;
			if(level == 0) {
				if(index >= numOfType) index = 0;
				type = loType[index];
				index+=2;
			}
			l = newLevel(level,type, seed); 
			board->setLevel(level);
			cout << "Level is set to: " << level << endl;
		}
		else if(move == "restart" || move == "re" || move == "res" ||
			 move == "rest" || move == "resta" || move == "restar"){
			board->clearBoard();
			board->initBoard();

			Block *tmp = cur;
			delete tmp;
			cur = next;

			if(level == 0) {
				if(index >= numOfType) index = 0;
				type = loType[index];
				index+=2;
			}
			next = newBlock(level, l, type, seed);
			board->setCurNext(cur, next);
			printBoard(board, next, level);
		}
	}
}



