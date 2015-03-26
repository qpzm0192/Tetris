 #ifndef __CELL_H__
#define __CELL_H__

#include <iostream>
#include "textdisplay.h"

const int maxNeighbours = 4;

class Cell {
	char type;
	int level;
	int index;
	bool has;
	bool fix;
	bool blockCleared;

	int numNeighbours;
	Cell *neighbours[maxNeighbours];

	int r, c;


 public:
	Cell();
/*
	Cell &operator=(const Cell &other) {
		if(this == &other) return *this;
		type = other.type;
		level = other.level;
		index = other.index;
		has = other.has;
		fix = other.fix;
		blockCleared = other.blockCleared;
		numNeighbours = other.numNeighbours;
		delete [] neighbours;
		for(int i=0; i<numNeighbours; i++) {
			neighbours[i] = other.neighbours[i];
		}
		return *this;
	}	
*/
	void setCoord(int row, int column);


	int getLevel();
	int getIndex(); //return index
	bool hasBlock(); //return true is cell has block, false other wise
	bool isFix(); //return true is block in this cell is fixed
	bool isBlockCleared();



	void setCell(char c);
	void clearCell();
	void setFix(int l, int n); //set the cell to be fixed with index n



	void notifyDisplay(TextDisplay &t);
	


	void resetNeighbour();
	void addNeighbour(Cell *neighbour);
	void deleteNeighbours(int n);
	void notifyNeighbours(int n);




};

#endif
