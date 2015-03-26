#include <iostream>
#include "board.h"

using namespace std;

//----------------------------------------------------------
//initialization
//----------------------------------------------------------

int Board:: hiScore = 0;

Board:: Board(int l): l(l) {
	row = 18;
	column = 10;
	initBoard();
}

void Board:: clearBoard() {
	if(score > hiScore) {
		hiScore = score;
		notifyScore();
	}
	delete theBoard;
}

Board:: ~Board() {
	delete td;
	for(int i=0; i<row; i++) {
		delete [] theBoard[i];
	}
	delete [] theBoard;
	delete [] coord;
	delete curBlock;
	delete td;
}

void Board:: initBoard() {	
	td = new TextDisplay();
	theBoard = new Cell*[row];
	for(int i=0; i<row; i++) {
		theBoard[i] = new Cell[column];
	}
	for(int j=0; j<row; j++) {
		for(int k=0; k<column; k++) {
			theBoard[j][k].setCoord(j, k);			
		}
	}
	score = 0;
}


void Board:: setCurNext(Block* c, Block* n) {
	curBlock = c;
	next = n;
	updateCoord();	
	setBlock();
}

void Board:: setLevel(int n) {
	l = n;
}
//----------------------------------------------------------





//----------------------------------------------------------
//interact with textdisplay
//----------------------------------------------------------
void Board:: setBlock() {
	theBoard[coord[0]][coord[1]].setCell(curBlock->getType());
	theBoard[coord[0]][coord[1]].notifyDisplay(*td);

	theBoard[coord[2]][coord[3]].setCell(curBlock->getType());
	theBoard[coord[2]][coord[3]].notifyDisplay(*td);

	theBoard[coord[4]][coord[5]].setCell(curBlock->getType());
	theBoard[coord[4]][coord[5]].notifyDisplay(*td);

	theBoard[coord[6]][coord[7]].setCell(curBlock->getType());
	theBoard[coord[6]][coord[7]].notifyDisplay(*td);
}

void Board:: clearBlock() {
	theBoard[coord[0]][coord[1]].clearCell();
	theBoard[coord[0]][coord[1]].notifyDisplay(*td);

	theBoard[coord[2]][coord[3]].clearCell();
	theBoard[coord[2]][coord[3]].notifyDisplay(*td);

	theBoard[coord[4]][coord[5]].clearCell();
	theBoard[coord[4]][coord[5]].notifyDisplay(*td);

	theBoard[coord[6]][coord[7]].clearCell();
	theBoard[coord[6]][coord[7]].notifyDisplay(*td);
}

void Board::  fixBlock() {
	int l = curBlock->getLevel();

	theBoard[coord[0]][coord[1]].setFix(l, 1);
	theBoard[coord[2]][coord[3]].setFix(l, 2);
	theBoard[coord[4]][coord[5]].setFix(l, 3);
	theBoard[coord[6]][coord[7]].setFix(l, 4);

	theBoard[coord[0]][coord[1]].notifyDisplay(*td);
	theBoard[coord[2]][coord[3]].notifyDisplay(*td);
	theBoard[coord[4]][coord[5]].notifyDisplay(*td);
	theBoard[coord[6]][coord[7]].notifyDisplay(*td);


	theBoard[coord[0]][coord[1]].addNeighbour(&theBoard[coord[2]][coord[3]]);
	theBoard[coord[0]][coord[1]].addNeighbour(&theBoard[coord[4]][coord[5]]);
	theBoard[coord[0]][coord[1]].addNeighbour(&theBoard[coord[6]][coord[7]]);


	theBoard[coord[2]][coord[3]].addNeighbour(&theBoard[coord[0]][coord[1]]);
	theBoard[coord[2]][coord[3]].addNeighbour(&theBoard[coord[4]][coord[5]]);
	theBoard[coord[2]][coord[3]].addNeighbour(&theBoard[coord[6]][coord[7]]);


	theBoard[coord[4]][coord[5]].addNeighbour(&theBoard[coord[2]][coord[3]]);
	theBoard[coord[4]][coord[5]].addNeighbour(&theBoard[coord[0]][coord[1]]);
	theBoard[coord[4]][coord[5]].addNeighbour(&theBoard[coord[6]][coord[7]]);


	theBoard[coord[6]][coord[7]].addNeighbour(&theBoard[coord[2]][coord[3]]);
	theBoard[coord[6]][coord[7]].addNeighbour(&theBoard[coord[4]][coord[5]]);
	theBoard[coord[6]][coord[7]].addNeighbour(&theBoard[coord[0]][coord[1]]);

	setBlock();
}


void Board:: drop() {


	clearBlock();

	int d = 17;
	if(coord[0] == 17 || coord[2] == 17 || coord[4] == 17 || coord[6] == 17) {
		fixBlock();
	} else {
		for(int i = coord[0] + 1; i < 18; i++) {
			if(i != coord[0] && i != coord[2] && i != coord[4] && i != coord[6]) {
				if(theBoard[i][coord[1]].hasBlock()) {
					if(d > i-coord[0]-1) d = i-coord[0]-1;
				} else if(i == 17) {
					if(d > i-coord[0]) d = i-coord[0];

				}								
			}
		}
			
		for(int i = coord[2] + 1; i < 18; i++) {
			if(i != coord[0] || i != coord[2] || i != coord[4] || i != coord[6]) {
				if(theBoard[i][coord[3]].hasBlock()) {
					if(d > i-coord[2]-1) d = i-coord[2]-1;
				} else if(i == 17) {
					if(d > i-coord[2]) d = i-coord[2];
				}								
			}
		}

		for(int i = coord[4] + 1; i < 18; i++) {
			if(i != coord[0] || i != coord[2] || i != coord[4] || i != coord[6]) {
				if(theBoard[i][coord[5]].hasBlock()) {
					if(d > i-coord[4]-1) d = i-coord[4]-1;
				} else if(i == 17) {
					if(d > i-coord[4]) d = i-coord[4];
				}								
			}
		}

		for(int i = coord[6] + 1; i < 18; i++) {
			if(i != coord[0] || i != coord[2] || i != coord[4] || i != coord[6]) {
				if(theBoard[i][coord[7]].hasBlock()) {
					if(d > i-coord[6]-1) d = i-coord[6]-1;
				} else if(i == 17) {
					if(d > i-coord[6]) d = i-coord[6];
				}								
			}
		}

		for(int k=0; k<8; k += 2) {
			coord[k] += d;
		}


		fixBlock();
		canClear();
	}
}


void Board:: notifyScore() {
	td->notifyScore(score, hiScore);
}
//----------------------------------------------------------

//----------------------------------------------------------
//methods about clear lines
//----------------------------------------------------------
void Board:: canClear() {
	int numLine = 0;	
	for(int i=0; i<18; i++) {
		for(int j=0; j<10; j++) {
			if(!theBoard[i][j].hasBlock()) break;
			if(j == 9) {

				clearLine(i);
				numLine++;

			}
		}
		
	}
	if(numLine != 0) {
		score += (l + numLine) * (l + numLine);
		notifyScore();
	}

}

void Board:: clearLine(int n) {



	for(int i=0; i<column; i++) {
		theBoard[n][i].clearCell();
		theBoard[n][i].notifyDisplay(*td);
		if(theBoard[n][i].isBlockCleared()) {
			int l = theBoard[n][i].getLevel();
			score += (l+1)*(l+1);
			notifyScore();
		}
	}

	delete [] theBoard[n];
	for(int j=n; j>0; j--) {
		theBoard[j] = theBoard[j-1];
	}
	theBoard[0] = new Cell[10];
	for(int k=0; k<18; k++) {
		for(int l=0; l<10; l++) {
			theBoard[k][l].setCoord(k,l);
			theBoard[k][l].notifyDisplay(*td);
		}
	}
}

bool Board:: checkLose() {
	int *a = next->getPos();
	for(int i=0; i<8; i+=2) {
		if(theBoard[a[i]][a[i+1]].hasBlock()) {
			return true;
		}
	}
	return false;
}
//----------------------------------------------------------




ostream &operator<<(std::ostream &out, const Board &b){
  out<<*(b.td);
  return out;
}



//----------------------------------------------------------
//methos that make block move
//----------------------------------------------------------

void Board:: left() {
	if(canLeft()) {
		clearBlock();
		curBlock->left();
		updateCoord();
		setBlock();
	}
}

void Board:: right() {
	if(canRight()) {
		clearBlock();
		curBlock->right();
		updateCoord();
		setBlock();
	} else {}

}

void Board:: down() {
	if(canDown()) {
		clearBlock();
		curBlock->down();
		updateCoord();
		setBlock();
	} else {}

}

void Board:: cw() {
	if(canCW()) {
		clearBlock();
		curBlock->clockwise();
		updateCoord();
		setBlock();
	} else {}
}

void Board:: ccw() {
	if(canCCW()) {
		clearBlock();
		curBlock->counter_clockwise();
		updateCoord();
		setBlock();
	} else {}
}

void Board:: updateCoord() {
	coord = curBlock->getPos();
}
//----------------------------------------------------------


//----------------------------------------------------------
//methods that check if movement can be made
//----------------------------------------------------------
bool Board::canLeft() {
  int *a = new int[8];
  for(int i=0; i<8; i++) {
    a[i] = coord[i];
  } // copy array of coord of curBlock.

  for(int r=0,c=1; c<8; r+=2,c+=2) {
    if(coord[c]==0) return false; 
    else {
      a[c] -=1;
      if(theBoard[a[r]][a[c]].isFix()) return false;
    }
  }


  delete [] a;
  return true;
}

bool Board::canRight() {
  int *a = new int[8];
  for(int i=0; i<8; i++) {
    a[i] = coord[i];
  } // copy array of coord of curBlock.

  for(int r=0,c=1; c<8; r+=2,c+=2) {
    if(coord[c]==9) return false; 
    else {
      a[c] +=1;
      if(theBoard[a[r]][a[c]].isFix()) return false;
    }
  }

  delete [] a;
  return true;
}

bool Board::canDown() {
  int *a = new int[8];
  for(int i=0; i<8; i++) {
    a[i] = coord[i];
  } // copy array of coord of curBlock.

  for(int r=0,c=1; c<8; r+=2,c+=2) {
    if(coord[r]==17) return false; 
    else {
      a[r] +=1;
      if(theBoard[a[r]][a[c]].isFix()) return false;
    }
  }

  delete [] a;
  return true;
}

bool Board::canCW() {
  int *a = new int[8];
  for(int i=0; i<8; i++) {
    a[i] = coord[i];
  } // copy array of coord of curBlock.

  if(curBlock->getType() == 'I') {
	if(curBlock->getPhase() == 1) {
		a[2] -= 1;
		a[3] -= 1;
		a[4] -= 2;
		a[5] -= 2;
		a[6] -= 3;
		a[7] -= 3;
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	} else {
		if(a[1]==9) {
			delete [] a;
			return false;
		} else {
			a[2] += 1;
			a[3] += 1;
			a[4] += 2;
			a[5] += 2;
			a[6] += 3;
			a[7] += 3;
		}
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
		
	}

  } else if(curBlock->getType() == 'J') {
	if(curBlock->getPhase() == 1) {
		a[0] -= 1;
		a[1] += 1;
		a[2] -= 2;
		a[4] -= 1;
		a[5] -= 1;
		a[7] -= 2;
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	} else if(curBlock->getPhase()==2) {
		if(a[1]==9) {
			delete [] a;
			return false;
		} else {
			a[0] += 2;
			a[1] += 1;
			a[2] += 1;
			a[3] += 2;
			a[5] += 1;
			a[6] -= 1;
		}
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
		
	} else if(curBlock->getPhase()==3) {
		a[2] -= 2;
		a[3] += 1;
		a[4] -= 1;
		a[7] -= 1;
		a[8] -= 1;
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	} else if(curBlock->getPhase()==4) {
		if(a[7]==9) {
			delete [] a;
			return false;
		} else {
			a[0] -= 1;
			a[3] -= 1;
			a[4] += 1;
			a[6] += 2;
			a[7] += 1;
		}
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	}
  } else if(curBlock->getType() == 'L') {
	if(curBlock->getPhase() == 1) {
		a[0] += 1;
		a[1] -= 1;
		a[3] -= 2;
		a[4] -= 1;
		a[5] -= 1;
		a[6] -= 2;
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	} else if(curBlock->getPhase()==2) {
		if(a[1]==9) {
			delete [] a;
			return false;
		} else {
			a[1] -= 1;
			a[2] -= 1;
			a[5] += 1;
			a[6] += 1;
			a[7] += 2;
		}
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	} else if(curBlock->getPhase()==3) {
		a[0] -= 2;
		a[2] -= 1;
		a[3] += 1;
		a[6] += 1;
		a[7] -= 1;
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	} else if(curBlock->getPhase()==4) {
		if(a[7]==9) {
			delete [] a;
			return false;
		} else {
			a[0] += 1;
			a[1] += 2;
			a[2] += 2;
			a[3] += 1;
			a[4] += 1;
			a[7] -= 1;
		}
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	}
  } else if(curBlock->getType() == 'S') {
	if(curBlock->getPhase() == 1) {
		a[2] += 1;
		a[3] -= 1;
		a[4] -= 2;
		a[6] -= 1;
		a[7] -= 1;
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	} else if(curBlock->getPhase()==2) {
		if(a[1]==9) {
			delete [] a;
			return false;
		} else {
			a[2] -= 1;
			a[3] += 1;
			a[4] += 2;
			a[6] += 1;
			a[7] += 1;
		}
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	}
  } else if(curBlock->getType() == 'Z') {
	if(curBlock->getPhase() == 1) {
		a[0] -= 1;
		a[1] += 1;
		a[4] -= 1;
		a[5] -= 1;
		a[7] -= 2;
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	} else if(curBlock->getPhase()==2) {
		if(a[1]==9) {
			delete [] a;
			return false;
		} else {
			a[0] += 1;
			a[1] -= 1;
			a[4] += 1;
			a[5] += 1;
			a[7] += 2;
		}
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	}
  } else if(curBlock->getType() == 'T') {
	if(curBlock->getPhase() == 1) {
		a[0] -= 1;
		a[1] += 1;
		a[4] += 1;
		a[5] -= 1;
		a[6] -= 1;
		a[7] -= 1;
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	} else if(curBlock->getPhase()==2) {
		if(a[1]==9) {
			delete [] a;
			return false;
		} else {
			a[0] += 2;
			a[1] += 1;
			a[2] += 1;
			a[5] -= 1;
			a[7] += 1;
		}
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	} else if(curBlock->getPhase()==3) {
		a[1] -= 2;
		a[2] -= 1;
		a[3] -= 1;
		a[4] -= 2;
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	} else if(curBlock->getPhase()==4) {
		if(a[7]==9) {
			delete [] a;
			return false;
		} else {
			a[0] -= 1;
			a[3] += 1;
			a[4] += 1;
			a[5] += 2;
			a[6] += 1;
		}
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	}
  }
  delete [] a;
  return true;

}


bool Board::canCCW() {
  int *a = new int[8];
  for(int i=0; i<8; i++) {
    a[i] = coord[i];
  } // copy array of coord of curBlock.

  if(curBlock->getType() == 'I') {
	if(curBlock->getPhase() == 1) {
		a[2] -= 1;
		a[3] -= 1;
		a[4] -= 2;
		a[5] -= 2;
		a[6] -= 3;
		a[7] -= 3;
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	} else {
		if(a[1]==0) {
			delete [] a;
			return false;
		} else {
			a[2] += 1;
			a[3] += 1;
			a[4] += 2;
			a[5] += 2;
			a[6] += 3;
			a[7] += 3;
		}
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
		
	}

  } else if(curBlock->getType() == 'J') {
	if(curBlock->getPhase() == 1) {
		a[0] += 1;
		a[3] += 1;
		a[4] -= 1;
		a[6] -= 2;
		a[7] -= 1;
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	} else if(curBlock->getPhase()==2) {
		if(a[1]==9) {
			delete [] a;
			return false;
		} else {
			a[0] += 1;
			a[1] -= 1;
			a[2] += 2;
			a[4] += 1;
			a[5] += 1;
			a[7] += 2;
		}
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
		
	} else if(curBlock->getPhase()==3) {
		a[0] -= 2;
		a[1] -= 1;
		a[2] -= 1;
		a[3] -= 2;
		a[5] -= 1;
		a[6] += 1;
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	} else if(curBlock->getPhase()==4) {
		if(a[7]==9) {
			delete [] a;
			return false;
		} else {
			a[2] += 2;
			a[3] -= 1;
			a[4] += 1;
			a[6] += 1;
			a[7] -= 1;
		}
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	}
  } else if(curBlock->getType() == 'L') {
	if(curBlock->getPhase() == 1) {
		a[0] -= 1;
		a[1] -= 2;
		a[2] -= 2;
		a[3] -= 1;
		a[4] -= 1;
		a[7] += 1;
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	} else if(curBlock->getPhase()==2) {
		if(a[1]==9) {
			delete [] a;
			return false;
		} else {
			a[0] -= 1;
			a[1] += 1;
			a[3] += 2;
			a[4] += 1;
			a[5] += 1;
			a[6] += 2;
		}
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	} else if(curBlock->getPhase()==3) {
		a[1] += 1;
		a[2] += 1;
		a[5] -= 1;
		a[6] -= 1;
		a[7] -= 2;

		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	} else if(curBlock->getPhase()==4) {
		if(a[7]==9) {
			delete [] a;
			return false;
		} else {
			a[0] += 2;
			a[2] += 1;
			a[3] -= 1;
			a[6] -= 1;
			a[7] += 1;
		}
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	}
  } else if(curBlock->getType() == 'S') {
	if(curBlock->getPhase() == 1) {
		a[2] += 1;
		a[3] -= 1;
		a[4] -= 2;
		a[6] -= 1;
		a[7] -= 1;
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	} else if(curBlock->getPhase()==2) {
		if(a[1]==9) {
			delete [] a;
			return false;
		} else {
			a[2] -= 1;
			a[3] += 1;
			a[4] += 2;
			a[6] += 1;
			a[7] += 1;
		}
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	}
  } else if(curBlock->getType() == 'Z') {
	if(curBlock->getPhase() == 1) {
		a[0] -= 1;
		a[1] += 1;
		a[4] -= 1;
		a[5] -= 1;
		a[7] -= 2;
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	} else if(curBlock->getPhase()==2) {
		if(a[1]==9) {
			delete [] a;
			return false;
		} else {
			a[0] += 1;
			a[1] -= 1;
			a[4] += 1;
			a[5] += 1;
			a[7] += 2;
		}
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	}
  } else if(curBlock->getType() == 'T') {
	if(curBlock->getPhase() == 1) {
		a[0] += 1;
		a[3] -= 1;
		a[4] -= 1;
		a[5] -= 2;
		a[6] -= 1;

		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	} else if(curBlock->getPhase()==2) {
		if(a[1]==9) {
			delete [] a;
			return false;
		} else {
			a[0] += 1;
			a[1] -= 1;
			a[4] -= 1;
			a[5] += 1;
			a[6] += 1;
			a[7] += 1;

		}
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	} else if(curBlock->getPhase()==3) {
		a[0] -= 2;
		a[1] -= 1;
		a[2] -= 1;
		a[5] += 1;
		a[7] -= 1;

		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	} else if(curBlock->getPhase()==4) {
		if(a[7]==9) {
			delete [] a;
			return false;
		} else {
			a[1] += 2;
			a[2] += 1;
			a[3] += 1;
			a[4] += 2;

		}
		for(int r=0,c=1; c<8; r+=2,c+=2) {
      			if(theBoard[a[r]][a[c]].isFix()) {
        			delete [] a;
        			return false;
			}
      		}
	}
  }
  delete [] a;
  return true;

}


//----------------------------------------------------------
