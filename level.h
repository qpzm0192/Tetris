#ifndef __LEVEL_H__
#define __LEVEL_H__
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include "block.h"


class Level {
 public:
  virtual Block *createBlock() = 0;
  virtual ~Level();

};

class Level0: public Level{
  char type;
 public:

  Level0(char t):type(t) {
  }

  Block *createBlock() {
    Block *b;
    if (type == 'I') b = new Block('I',0);
    if (type == 'J') b = new Block('J',0);
    if (type == 'L') b = new Block('L',0);
    if (type == 'O') b = new Block('O',0);
    if (type == 'S') b = new Block('S',0);
    if (type == 'Z') b = new Block('Z',0);
    if (type == 'T') b = new Block('T',0);
    return b;
  }
};

class Level1: public Level{
  int randNum;
  int seed;
 public:
  Level1(int s):seed(s) {}
  Block *createBlock() {
    Block *b;
    if(seed >=0) srand (seed);
    else srand (time(NULL));
    randNum = rand() % 12 + 1;
    if (randNum == 1) b = new Block('S',1);
    if (randNum == 2) b = new Block('Z',1);
    if (randNum == 3 || randNum == 4) b = new Block('I',1);
    if (randNum == 5 || randNum == 6) b = new Block('J',1);
    if (randNum == 7 || randNum == 8) b = new Block('L',1);
    if (randNum == 9 || randNum == 10) b = new Block('O',1);
    return b;
  }
};

class Level2: public Level{
  int randNum;
  int seed;
 public:
  Level2(int s):seed(s) {}
  Block * createBlock() {
    Block *b;
    if(seed >=0) srand (seed);
    else srand (time(NULL));
    randNum = rand() % 7 + 1;
    if (randNum == 1) b = new Block('I',2);
    if (randNum == 2) b = new Block('J',2);
    if (randNum == 3) b = new Block('L',2);
    if (randNum == 4) b = new Block('O',2);
    if (randNum == 5) b = new Block('S',2);
    if (randNum == 6) b = new Block('Z',2);
    if (randNum == 7) b = new Block('T',2);
    return b;
  }
};

class Level3: public Level{
  int randNum;
  int seed;
 public:
  Level3(int s):seed(s) {}

  Block * createBlock() {
    Block *b;
    if(seed >=0) srand (seed);
    else srand (time(NULL));
    randNum = rand() % 9 + 1;
    if (randNum == 1 || randNum == 2) return new Block('S',3);
    if (randNum == 3 || randNum == 4) return new Block('Z',3);
    if (randNum == 5) b = new Block('I',3);
    if (randNum == 6) b = new Block('J',3);
    if (randNum == 7) b = new Block('L',3);
    if (randNum == 8) b = new Block('O',3);
    if (randNum == 9) b = new Block('T',3);
    return b;
  }
};

#endif
