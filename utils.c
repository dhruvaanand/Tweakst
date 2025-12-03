
#define RED 1
#define BLACK -1
#define SAMEPOS(a,b) ((a).r == (b).r && (a).c == (b).c)
#define max(a,b) ((a)>(b))?(a):(b)
#define min(a,b) ((a)>(b))?(b):(a)

const int moves[8][2] = {
    {1,2},{1,-2},{-1,2},{-1,-2},{2,1},{-2,1},{2,-1},{-2,-1}
};
const int crossfrom[6][2] = {
    {1,0},{0,3},{1,1},{1,2},{0,1},{0,2}
};
const int crossto[6][2] = {
    {-1,0},{0,-3},{-1,-1},{-1,-2},{0,-1},{0,-2}
};
#include "utils.h"
#include "board.h"
#include "link.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

int checkQuad(pos origin, pos rel) {
    if(rel.r - origin.r > 0) {
        if(rel.c - origin.c > 0) return 1;
        return 2;
    } else {
        if(rel.c - origin.c > 0) return 4;
        return 3;
    }
}
int checkType(pos origin, pos rel) {
    if(abs(origin.r - rel.r) == 2 && abs(origin.c - rel.c) == 1) return 2; // vertical
    else if(abs(origin.r - rel.r) == 1 && abs(origin.c - rel.c) == 2) return 1; // horizontal
    return 0;
}
bool addEdge(nod* link, board* bord) {
    if(link->color == -1) {
        bord->numblinks++;
        bord->blinks = realloc(bord->blinks, bord->numblinks * sizeof(nod*));
        bord->blinks[bord->numblinks-1] = link;
        return true;
    } else {
        bord->numrlinks++;
        bord->rlinks = realloc(bord->rlinks, bord->numrlinks * sizeof(nod*));
        bord->rlinks[bord->numrlinks-1] = link;
        return true;
    }
    return false;
}

bool inRegion(pos a, pos b, pos check) {
    for(int i = (a.r < b.r ? a.r : b.r); i <= (a.r > b.r ? a.r : b.r); i++) {
        for(int j = (a.c < b.c ? a.c : b.c); j <= (a.c > b.c ? a.c : b.c); j++) {
            if(i == check.r && j == check.c) return true;
        }
    }
    return false;
}

bool isEdge(nod* node, int edge, board* bord) {
    if(edge == 0) {
        if(node->color == 1 && node->data.r == 0) {
            return true;
        } else if(node->color == -1 && node->data.c == 0) {
            return true;
        } else return false;
    } else {
        if(node->color == 1 && node->data.r == bord->size.r-1) {
            return true;
        } else if(node->color == -1 && node->data.c == bord->size.c-1) {
            return true;
        } else return false;
    }
}

bool isKnight(pos from, pos to) {
    return ((abs(from.r - to.r) == 2 && abs(from.c - to.c) == 1) || (abs(from.r - to.r) == 1 && abs(from.c - to.c) == 2));
}

nod* autoLink(nod* node, board* bord) {
    extern const int moves[8][2];
    int r = node->data.r;
    int c = node->data.c;
    for(int i = 0; i < 8; i++) {
        int posr = r + moves[i][0];
        int posc = c + moves[i][1];
        if(posr < 0 || posc < 0 || posr >= bord->size.r || posc >= bord->size.c) continue;
        if(!bord->allnodes[posr][posc]) continue;
        nod* cand = bord->allnodes[posr][posc];
        if(cand->color != node->color) continue;
        if(!canLink(cand, node, bord)) continue;
        if(isLinked(cand, node)) continue;
        addLink(cand, node);
    }
    return node;
}

int convstr(char* string) {
    int num = 0;
    if(string[0] >= '0' && string[0] <= '9') {
        for(int i = 0; string[i] != '\0'; i++) {
            if(string[i] >= '0' && string[i] <= '9')
                num = num*10 + string[i] - '0';
            else return -3;
        }
        return num-1;
    } else if(string[0] >= 'A' && string[0] <= 'A'+50) {
        for(int i = 0; string[i] != '\0'; i++) {
            if(string[i] >= 'A' && string[i] <= 'A'+50)
                num = num*10 + string[i] - 'A';
            else return -3;
        }
        return num;
    } else return -3;
}
