#ifndef __BOARD_H__
#define __BOARD_H__
#include <iostream>
#include "cell.h"
#include "textdisplay.h"

class Block;



class Board {

	TextDisplay *td;
	int l;    //level
	int score;
	static int hiScore;
	int row,column;


	Block *curBlock;
	int *coord;
	Block *next;

 public:

	Cell **theBoard;
	Board(int l);
	~Board();
	void initBoard();
	void clearBoard();

	void setCurNext(Block* c, Block* n);
	void setLevel(int n);

	
	bool canLeft(); //check if curBlock can be moved to left
	bool canRight(); //check if curBlock can be moved to right
	bool canDown(); //check if curBlock can be moved downward
	bool canCW(); //check if curBlock can be rotated clockwise
	bool canCCW(); //check if curBlock can be rotated counterclockwise


	void left(); //left
	void right(); //right
	void down(); //downs
	void cw(); //clockwise
	void ccw(); //counter clockwise
	void updateCoord(); //after move operation, update the coordinates

	void setBlock(); 
	void clearBlock();
	void fixBlock();


	void drop(); //drop curBlock, nextBlock becomes curBlock, creat new nextBlock 



	void canClear(); //after dropped curBlock,
			   //check if there is any line can be cleared
	void clearLine(int n); //clear the line at row n

	void notifyScore();

	bool checkLose();


	friend std::ostream &operator<<(std::ostream &out, const Board &b);

};

#endif
