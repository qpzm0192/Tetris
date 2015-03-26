#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <sstream>
#include "block.h"

const int r = 18;
const int c = 10;

class TextDisplay {
	char **theDisplay;
	int score;
	int hiScore;
	Block* next;
	
 public:
	TextDisplay();

	void notify(int r, int c, char ch);
	void notifyScore(int s, int hiS);


	~TextDisplay();

	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
