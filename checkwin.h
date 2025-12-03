#ifndef CHECKWIN_H
#define CHECKWIN_H

#include "board.h"
nod* trace(nod* head, board* bord);
nod* checkWin(int col, board* bord);
bool reset(board* bord);

#endif // CHECKWIN_H
