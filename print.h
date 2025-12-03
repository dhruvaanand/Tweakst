#ifndef PRINT_H
#define PRINT_H

#include "board.h"
char*** createCharr(board* bord);
char* decodeNode(nod* node);
char*** printNode(char*** printer, board* bord);
void printBoard(char*** printer, board* bord);
char*** drawAll(char*** printer, board* bord);
char*** drawLink(nod* node1, nod* node2, char*** printer);


#endif // PRINT_H
