
#ifndef LINK_H
#define LINK_H

#include <stdbool.h>
#include "board.h"
bool isLinked(nod* from, nod* to);
nod* addLink(nod* from, nod* to);
bool rmvLink(nod* from, nod* to);
bool canLink(nod* from, nod* to, board* bord);
bool place(int r, int c, int colour, board* bord);

#endif // LINK_H
