#include "checkwin.h"
#include "board.h"
#include "utils.h"
#include <stdlib.h>
#include <stdbool.h>
bool reset(board* bord){
    for(int i = 0;i<bord->size.r;i++){
        for(int j = 0;j<bord->size.c;j++){
            if(bord->allnodes[i][j]!= NULL){
                bord->allnodes[i][j]->visit = false;
            }
        }
    }
    return true;
}
nod* trace(nod* head,board* bord){
    nod** lifo = malloc(sizeof(nod*)*(bord->size.r*bord->size.c)*4);
    int top = 0;
    
    lifo[top++] =head;
    while(top>0){
        top--;
        nod* temp = lifo[top];
        if(temp== NULL ||temp->visit == true)continue;
        temp->visit = true;
        if(isEdge(temp,1,bord)){
        free(lifo);
        return temp;}
        for(int i = 0;i<temp->links;i++){
            nod* next = temp->linked[i];
            if(!next->visit){
                lifo[top++] = next;
            }
        }
    }
    free(lifo);
    return NULL;
}
nod* checkWin(int col,board* bord) {
    if(!reset(bord))return NULL;
    col--;
    int numcol = col ? bord->numrlinks : bord->numblinks;
    if(numcol ==0) return NULL;
    nod** collink = col? bord->rlinks : bord->blinks;
    nod* x;
    for(int i = 0; i<numcol;i++){
        x = trace(collink[i],bord);
        if(x!= NULL) break;
    }
    return x;
}
