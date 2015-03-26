#include <iostream>
#include "textdisplay.h"
using namespace std;


TextDisplay::TextDisplay() {
	theDisplay = new char*[r];
	for(int i=0; i<r; i++){
		theDisplay[i] = new char[c];
	}

	for(int j=0; j<r; j++){
		for(int k=0; k<c; k++){
			theDisplay[j][k]=' ';

		}
	}
}

void TextDisplay::notify(int r, int c, char ch){
	theDisplay[r][c]=ch;
}


void TextDisplay::notifyScore(int s, int hiS){
	score = s;
	hiScore = hiS;
}


TextDisplay::~TextDisplay(){
	for(int i=0; i<r; i++){
		delete [] theDisplay[i];
	}
	delete [] theDisplay;
}

ostream& operator<<(ostream &out, const TextDisplay &td){

	out<<"Score:    "<<td.score<<endl;
	out<<"Hi Score: "<<td.hiScore<<endl;
	out<<"----------"<<endl;  
	for(int i=0; i<r; i++){
	for(int j=0; j<c; j++){
		out<<td.theDisplay[i][j];
	}
		out<<endl;
	}
	out<<"----------"<<endl;
	out<<"Next:     "<<endl;

	return out;
}
