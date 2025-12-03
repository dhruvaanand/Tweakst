#include "init.h"
#include "board.h"
#include "utils.h"
#include <stdlib.h>

board* newbord(pos siz) {
    board* newb = malloc(sizeof(board));
    newb->size = siz;
    newb->allnodes = malloc(newb->size.r*sizeof(nod**));
    newb->blinks = NULL;newb->rlinks=NULL;
    newb->numblinks = 0;newb->numrlinks = 0;
    for(int i = 0; i<newb->size.r;i++){
        newb->allnodes[i] = malloc(newb->size.c*sizeof(nod*));
        for(int j = 0;j<newb->size.c;j++){
            newb->allnodes[i][j] = NULL;
        }
    }
    return newb;
}

nod* create(int col,int r,int c) {
    nod* newh = malloc(sizeof(nod));
    newh->color = col;
    newh->data.r = r;
    newh->data.c = c;
    newh->linked = NULL;
    newh->links = 0;
    newh->visit = false;
    return newh;
}

void freeAll(board* bord, char*** printer) {
    if(!bord) return;
    for(int i = 0; i < bord->size.r; i++) {
        for(int j = 0; j < bord->size.c; j++) {
            nod* node = bord->allnodes[i][j];
            if(node) {
                if(node->linked) free(node->linked);
                free(node);
            }
        }
        free(bord->allnodes[i]);
    }
    free(bord->allnodes);
    if(bord->rlinks) free(bord->rlinks);
    if(bord->blinks) free(bord->blinks);
    if(printer) {
        for(int i = 0; i < 5 * bord->size.r; i++) {
            if(printer[i]) free(printer[i]);
        }
        free(printer);
    }
    free(bord);
}
