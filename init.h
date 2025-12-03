#ifndef INIT_H
#define INIT_H

#include "board.h"
board* newbord(pos siz);
nod* create(int col, int r, int c);
void freeAll(board* bord, char*** printer);
#endif // INIT_H
