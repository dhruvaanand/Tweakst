#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

typedef struct pos{
    int r;
    int c;
}pos;

typedef struct nod{
    int color;
    pos data;
    struct nod** linked;
    int links;
    bool visit;
}nod;

typedef struct board{
    pos size;
    nod*** allnodes;
    nod** blinks;
    int numblinks;
    nod** rlinks;
    int numrlinks;
}board;

#endif // BOARD_H
