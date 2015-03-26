#include "block.h"
#include <vector>

void Block:: setBlock() {
	phase = 1;
	if(type == 'I') {
		p1r = 3;
		p1c = 0;
		p2r = 3;
		p2c = 1;
		p3r = 3;
		p3c = 2;
		p4r = 3;
		p4c = 3;
	} else if(type == 'J') {
		p1r = 3;
		p1c = 0;
		p2r = 4;
		p2c = 0;
		p3r = 4;
		p3c = 1;
		p4r = 4;
		p4c = 2;
	} else if(type == 'L') {
		p1r = 3;
		p1c = 2;
		p2r = 4;
		p2c = 2;
		p3r = 4;
		p3c = 1;
		p4r = 4;
		p4c = 0;
	} else if(type == 'O') {
		p1r = 3;
		p1c = 0;
		p2r = 3;
		p2c = 1;
		p3r = 4;
		p3c = 0;
		p4r = 4;
		p4c = 1;
	} else if(type == 'S') {
		p1r = 3;
		p1c = 1;
		p2r = 3;
		p2c = 2;
		p3r = 4;
		p3c = 0;
		p4r = 4;
		p4c = 1;
	} else if(type == 'Z') {
		p1r = 3;
		p1c = 0;
		p2r = 3;
		p2c = 1;
		p3r = 4;
		p3c = 1;
		p4r = 4;
		p4c = 2;
	} else {
		p1r = 3;
		p1c = 0;
		p2r = 3;
		p2c = 1;
		p3r = 3;
		p3c = 2;
		p4r = 4;
		p4c = 1;
	}
}

void Block:: left() {
	p1c -= 1;
	p2c -= 1;
	p3c -= 1;
	p4c -= 1;
}

void Block:: right() {
	p1c += 1;
	p2c += 1;
	p3c += 1;
	p4c += 1;
}

void Block:: down() {
	p1r+=1;
	p2r+=1;
	p3r+=1;
	p4r+=1;
}

void Block:: clockwise() {
	if(type == 'I') {


		if(phase == 1) {
			p2r -= 1;
			p2c -= 1;
			p3r -= 2;
			p3c -= 2;
			p4r -= 3;
			p4c -= 3;
			phase++;
		} else {
			p2r += 1;
			p2c += 1;
			p3r += 2;
			p3c += 2;
			p4r += 3;
			p4c += 3;
			phase--;
		}
	} else if(type == 'J') {
		if(phase == 1) {
			p1r -= 1;
			p1c += 1;
			p2r -= 2;
			p3r -= 1;
			p3c -= 1;
			p4c -= 2;
			phase++;
		} else if(phase == 2) {
			p1r += 2;
			p1c += 1;
			p2r += 1;
			p2c += 2;
			p3c += 1;
			p4r -= 1;
			phase++;
		} else if(phase == 3) {
			p1c -= 2;
			p2r += 1;
			p2c -= 1;
			p4r -= 1;
			p4c += 1;
			phase++;
		} else{
			p1r -= 1;
			p2c -= 1;
			p3r += 1;
			p4r += 2;
			p4c += 1;
			phase = 1;
		}
	} else if(type == 'L') {
		if(phase == 1) {
			p1r += 1;
			p1c -= 1;
			p2c -= 2;
			p3r -= 1;
			p3c -= 1;
			p4r -= 2;
			phase++;
		} else if(phase == 2) {
			p1c -= 1;
			p2r -= 1;
			p3c += 1;
			p4r += 1;
			p4c += 2;
			phase++;
		} else if(phase == 3) {
			p1r -= 2;
			p2r -= 1;
			p2c += 1;
			p4r += 1;
			p4c -= 1;
			phase++;
		} else{
			p1r += 1;
			p1c += 2;
			p2r += 2;
			p2c += 1;
			p3r += 1;
			p4c -= 1;
			phase = 1;
		}
	} else if(type == 'O') {
	} else if(type == 'S') {
		if(phase == 1) {
			p2r += 1;
			p2c -= 1;
			p3r -= 2;
			p4r -= 1;
			p4c -= 1;
			phase++;
		} else if(phase == 2) {
			p2r -= 1;
			p2c += 1;
			p3r += 2;
			p4r += 1;
			p4c += 1;
			phase--;
		}
	} else if(type == 'Z') {
		if(phase == 1) {
			p1r -= 1;
			p1c += 1;
			p3r -= 1;
			p3c -= 1;
			p4c -= 2;
			phase++;
		} else {
			p1r += 1;
			p1c -= 1;
			p3r += 1;
			p3c += 1;
			p4c += 2;
			phase--;
		}
	} else {
		if(phase == 1) {
			p1r -= 1;
			p1c += 1;
			p3r += 1;
			p3c -= 1;
			p4r -= 1;
			p4c -= 1;
			phase++;
		} else if(phase == 2) {
			p1r += 2;
			p1c += 1;
			p2r += 1;
			p3c -= 1;
			p4c += 1;
			phase++;
		} else if(phase == 3) {
			p1c -= 2;
			p2r -= 1;
			p2c -= 1;
			p3r -= 2;
			phase++;
		} else {
			p1r -= 1;
			p2c += 1;
			p3r += 1;
			p3c += 2;
			p4r += 1;
			phase = 1;
		}
	}
}

void Block:: counter_clockwise() {
	if(type == 'I') {
		if(phase == 1) {
			p2r -= 1;
			p2c -= 1;
			p3r -= 2;
			p3c -= 2;
			p4r -= 3;
			p4c -= 3;
			phase++;
		} else {
			p2r += 1;
			p2c += 1;
			p3r += 2;
			p3c += 2;
			p4r += 3;
			p4c += 3;
			phase--;
		}
	}else if(type == 'J') {
		if(phase == 1) {
			p1r += 1;
			p2c += 1;
			p3r -= 1;
			p4r -= 2;
			p4c -= 1;
			phase = 4;
		} else if(phase == 2) {
			p1r += 1;
			p1c -= 1;
			p2r += 2;
			p3r += 1;
			p3c += 1;
			p4c += 2;
			phase--;
		} else if(phase == 3) {
			p1r -= 2;
			p1c -= 1;
			p2r -= 1;
			p2c -= 2;
			p3c -= 1;
			p4r += 1;
			phase--;
		} else{
			p1c += 2;
			p2r -= 1;
			p2c += 1;
			p4r += 1;
			p4c -= 1;
			phase--;
		}
	} else if(type == 'L') {
		if(phase == 1) {
			p1r -= 1;
			p1c -= 2;
			p2r -= 2;
			p2c -= 1;
			p3r -= 1;
			p4c += 1;
			phase = 4;
		} else if(phase == 2) {

			p1r -= 1;
			p1c += 1;
			p2c += 2;
			p3r += 1;
			p3c += 1;
			p4r += 2;
			phase--;
		} else if(phase == 3) {
			p1c += 1;
			p2r += 1;
			p3c -= 1;
			p4r -= 1;
			p4c -= 2;
			phase--;
		} else{
			p1r += 2;
			p2r += 1;
			p2c -= 1;
			p4r -= 1;
			p4c += 1;
			phase--;
		}
	} else if(type == 'O') {
	} else if(type == 'S') {
		if(phase == 1) {
			p2r += 1;
			p2c -= 1;
			p3r -= 2;
			p4r -= 1;
			p4c -= 1;
			phase++;
		} else {
			p2r -= 1;
			p2c += 1;
			p3r += 2;
			p4r += 1;
			p4c += 1;
			phase--;
		}
	} else if(type == 'Z') {
		if(phase == 1) {
			p1r -= 1;
			p1c += 1;
			p3r -= 1;
			p3c -= 1;
			p4c -= 2;
			phase++;
		} else {
			p1r += 1;
			p1c -= 1;
			p3r += 1;
			p3c += 1;
			p4c += 2;
			phase--;
		}
	} else {
		if(phase == 1) {
			p1r += 1;
			p2c -= 1;
			p3r -= 1;
			p3c -= 2;
			p4r -= 1;
			phase=4;
		} else if(phase == 2) {
			p1r += 1;
			p1c -= 1;
			p3r -= 1;
			p3c += 1;
			p4r += 1;
			p4c += 1;
			phase--;
		} else if(phase == 3) {
			p1r -= 2;
			p1c -= 1;
			p2r -= 1;
			p3c += 1;
			p4c -= 1;
			phase--;
		} else {
			p1c += 2;
			p2r += 1;
			p2c += 1;
			p3r += 2;
			phase--;
		}
	}
}
		
char Block:: getType() {
	return type;
}

int Block:: getLevel() {
	return level;
}

int Block:: getPhase() {
	return phase;
}

int* Block:: getPos() {
	int *pos = new int[8];
	pos[0] = p1r;
	pos[1] = p1c;
	pos[2] = p2r;
	pos[3] = p2c;
	pos[4] = p3r;
	pos[5] = p3c;
	pos[6] = p4r;
	pos[7] = p4c;
	return pos;
}
/*
void Block:: phasePlus() {
	phase++;
}


void Block:: phaseMinus() {
	phase--;
}
*/


Block:: ~Block() { }
