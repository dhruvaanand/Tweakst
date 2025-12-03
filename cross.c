#include "cross.h"
#include "board.h"
#include "utils.h"
#include <stdlib.h>

bool cross(nod* from,nod*to,board*bord){
    if (from->data.c > to->data.c) {
        return cross(to, from, bord);
    }
    pos pos1,pos2;
    pos temp;
    int csig,rsig;
    switch (checkQuad(from->data,to->data))
    {
    case 1:
    csig=1,rsig=-1;
        break;
    case 2:
        csig=-1,rsig=-1;
        break;  
    case 3:
        csig=-1,rsig=1;
        break;
    case 4:
        csig=1,rsig=1;
        break;
    
    default:
        csig=0,rsig=0;
        break;
    }

    for(int i = 0;i<6;i++){
        if(checkType(from->data,to->data)==1){
            pos1.r = from->data.r + rsig*crossfrom[i][0];
            pos1.c = from->data.c + csig*crossfrom[i][1];
        }
        else if(checkType(from->data,to->data)==2){
            pos1.r = from->data.r - rsig*crossfrom[i][1];
            pos1.c = from->data.c - csig*crossfrom[i][0];
        }
        else continue;
        if(pos1.r<0||pos1.c<0||pos1.r>=bord->size.r||pos1.c>=bord->size.c)continue;
        if(bord->allnodes[pos1.r][pos1.c]== NULL) continue;
        for(int j =0;j<bord->allnodes[pos1.r][pos1.c]->links;j++){
            pos curr = bord->allnodes[pos1.r][pos1.c]->linked[j]->data;
            for(int k = 0;k<6;k++){
                if(checkType(from->data,to->data)==1){
                    pos2.r = to->data.r - rsig*crossfrom[k][0];
                    pos2.c = to->data.c - csig*crossfrom[k][1];
                }
                else if(checkType(from->data,to->data)==2){
                    pos2.r = to->data.r + rsig*crossfrom[k][1];
                    pos2.c = to->data.c + csig*crossfrom[k][0];
                }
                else continue;
                if(pos2.r<0||pos2.c<0||pos2.r>=bord->size.r||pos2.c>=bord->size.c)continue;
                if(SAMEPOS(curr,pos2)){
                    if((i==0||i==1)&&(k==0||k==1))continue;
                    return true;
                }
            }
        }
        
}
return false;
}