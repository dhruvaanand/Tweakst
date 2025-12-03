
#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>
#include "board.h"

#define RED 1
#define BLACK -1
#define SAMEPOS(a,b) ((a).r == (b).r && (a).c == (b).c)
#define max(a,b) ((a)>(b))?(a):(b)
#define min(a,b) ((a)>(b))?(b):(a)

extern const int moves[8][2];
extern const int crossfrom[6][2];
extern const int crossto[6][2];

int checkQuad(pos origin, pos rel);
int checkType(pos origin, pos rel);
bool addEdge(nod* link, board* bord);
bool inRegion(pos a, pos b, pos check);
bool isEdge(nod* node, int edge, board* bord);
bool isKnight(pos from, pos to);
nod* autoLink(nod* node, board* bord);
int convstr(char* string);

#endif // UTILS_H
