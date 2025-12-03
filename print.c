#include "print.h"
#include "board.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

char*** createCharr(board* bord) {
    char*** printer = malloc(sizeof(char**)*5*bord->size.r);
    for(int i = 0;i<5*bord->size.r;i++){
        printer[i] = malloc(sizeof(char*)*8*bord->size.c);
    }
    for(int i=0;i<5*bord->size.r;i++){
        for(int j = 0;j<8*bord->size.c;j++){
            printer[i][j] = " ";
        }
    }
    return printer;
}

char* decodeNode(nod* node) {
    if(node == NULL){
        return ".";
    }
    else if(node->color == 1){
        return "\033[31mo\033[0m";
    }
    else if(node->color == -1){
        return "\033[34mo\033[0m";
    }
    return " ";
}

char*** printNode(char*** printer, board* bord) {
    for(int i = 0;i<bord->size.r;i++){
        for(int j = 0;j<bord->size.c;j++){
            printer[5*i][8*j] = decodeNode(bord->allnodes[i][j]);
        }
    }
    return NULL;
}

void printBoard(char*** printer,board* bord) {
    for(int i = -5;i<5*bord->size.r;i++){
        for(int j=-8;j<8*bord->size.c;j++){
            if(i==-5&&j==-8)printf(" ");
            else if(i==-5&&j%8==0) printf("%c",'A'+j/8);
            else if(j==-8&&i%5==0)printf("%d",1 + i/5);
            else if((i<0||j<0)&&(i!=-5||j!=-8))printf(" ");
            else printf("%s",printer[i][j]);
        }
        printf("\n");
    }
}

char*** drawAll(char*** printer,board* bord) {
    for(int i = 0;i<bord->size.r;i++){
        for(int j = 0;j<bord->size.c;j++){
            if(bord->allnodes[i][j]== NULL) continue;
            for(int k = 0;k<bord->allnodes[i][j]->links;k++){
                drawLink(bord->allnodes[i][j],bord->allnodes[i][j]->linked[k],printer);
            }
        }
    }
    printer[0][0] = "X";
    printer[-5 + bord->size.r*5][0] = "X";
    printer[-5 + bord->size.r*5][-8 + bord->size.c*8] = "X";
    printer[0][bord->size.c*8-8] = "X";
}

char*** drawLink(nod* node1,nod* node2,char*** printer) {
    int csig,rsig;
    int orgcoc=8*node1->data.c,orgcor = 5*node1->data.r;
    char* dash = "";
    char* pipe = "";
    if(node1->color==1){
        dash = "\033[31m_\033[0m";
        pipe = "\033[31m|\033[0m";
    }
    else if(node1->color==-1){
        pipe = "\033[34m|\033[0m";
        dash = "\033[34m_\033[0m";
    }
    if(checkQuad(node1->data,node2->data) == 1) csig=1,rsig=1;
    else if(checkQuad(node1->data,node2->data) == 2)csig=-1,rsig=1;
    else if(checkQuad(node1->data,node2->data) == 3)csig=-1,rsig=-1;
    else if(checkQuad(node1->data,node2->data) == 4)csig=1,rsig=-1;
    else csig=0,rsig=0;
    if(checkType(node1->data,node2->data)==1){
        printer[orgcor + rsig*1][orgcoc] = pipe;
        printer[orgcor + rsig*2][orgcoc] = pipe;
        for(int i = 1;i<16;i++){
            printer[orgcor + rsig*3][orgcoc + csig*i] = dash;
        }
        printer[orgcor+rsig*4][orgcoc+csig*16] = pipe;        
    }
    else if(checkType(node1->data,node2->data)==2){
        printer[orgcor][orgcoc+csig] = dash;
        printer[orgcor][orgcoc+2*csig] = dash;
        printer[orgcor][orgcoc+3*csig] = dash;
        for(int i = 0;i<8;i++){
            printer[orgcor+i*rsig][orgcoc+4*csig] = pipe;
        }
        printer[orgcor+10*rsig][orgcoc+5*csig] = dash;
        printer[orgcor+10*rsig][orgcoc+6*csig] = dash;
        printer[orgcor+10*rsig][orgcoc+6*csig] = dash;
    }
}


