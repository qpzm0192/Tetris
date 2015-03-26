#ifndef __BLOCK_H__
#define __BLOCK_H__
#include <vector>
#include <iostream>
using namespace std;

class Block {	
	char type;
	int level;
	int p1r, p1c, p2r, p2c, p3r, p3c, p4r, p4c;
	int phase;
 public:
	Block(char t, int l): type(t), level(l) {
		setBlock();
	}

	char getType();;
	int getLevel();
	int getPhase();
	int *getPos(); 

	void setBlock();
	void left();
	void right();
	void down();
	void clockwise();
	void counter_clockwise();

//	void phasePlus();
//	void phaseMinus();

	~Block();
};
	
#endif