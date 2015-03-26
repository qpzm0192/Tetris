#include <iostream>
#include "cell.h"
#include "textdisplay.h"
using namespace std;



Cell:: Cell() {
	type = ' ';
	level = -1;
	index = 0;
	has = false;
	fix = false;
	blockCleared = false;
	numNeighbours=3;
	for(int i=0; i<3; i++){
	neighbours[i]=NULL;
	}
}







void Cell:: setCoord(int row, int column) {
	r=row;
	c=column;
}








int Cell:: getLevel() {
	return level;
}

	
int Cell:: getIndex() {
	return index;
}

bool Cell:: hasBlock() {
	if(has) return true;
	else return false;
}

bool Cell:: isFix() {
	return fix;
}

bool Cell:: isBlockCleared() {
	return blockCleared;
}








void Cell:: setCell(char c) {
	type = c;
	has = true;
}


void Cell:: clearCell() {
	if(fix) {
//*********************
		cout << "fix" << endl;
//********************
		if(numNeighbours==0) {
			blockCleared = true;
		} else {
//*********************
		cout << 1 << endl;
//********************
			notifyNeighbours(index);
//*********************
		cout << 2 << endl;
//********************
		}
		type = ' ';
		level = -1;
		index = 0;
		has = false;
		fix = false;
		resetNeighbour();	
	} else {
		type = ' ';
		has = false;
		fix = false;
	}
}


void Cell:: setFix(int l, int n) {
	level = l;
	index = n;
	has = true;
	fix = true;
	blockCleared = false;
}






void Cell:: notifyDisplay(TextDisplay &t) {
	if(has) {
		t.notify(r,c,type);
	} else {
		t.notify(r,c,' ');
	}
}
	


void Cell:: resetNeighbour() {
	numNeighbours=0;
	for(int i=0; i<3; i++){
	neighbours[i]=NULL;
	}
}	

		
void Cell:: addNeighbour(Cell *neighbour) {
	for(int i=0; i<3; i++) {
		if(neighbours[i]==NULL) {
			neighbours[i] = neighbour;
			break;
		}
	}
}

/*	
void Cell:: deleteNeighbours(int n) {
	for(int i=0; i<numNeighbours; i++) {
		if(neighbours[i]->getIndex() == n) {
			numNeighbours--;
		}
	}
}
*/


void Cell:: notifyNeighbours(int n) {
/*
	for(int i=0; i<numNeighbours; i++) {

		neighbours[i]->deleteNeighbours(n);
*/	
	numNeighbours--;
}


