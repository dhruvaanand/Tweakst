
#include <stdlib.h>
#include "link.h"
#include "board.h"
#include "utils.h"
#include "cross.h"
#include "init.h"
bool isLinked(nod* from, nod* to) {
    if(!from || !to) return false;
    for(int i = 0; i < from->links; i++){
        nod* cur = from->linked[i];
        if(cur == to) return true;
        if(SAMEPOS(cur->data, to->data)) return true;
    }
    return false;
}

nod* addLink(nod* from, nod* to) {
    from->links++;
    to->links++;
    from->linked = realloc(from->linked,from->links*sizeof(nod*));
    to->linked = realloc(to->linked,to->links*sizeof(nod*));
    from->linked[from->links-1] = to;
    to->linked[to->links-1] = from;
    return to;
}

bool rmvLink(nod* from, nod* to) {
    if(!from || !to || from == to) return false;
    if(from->links == 0 || to->links == 0) return false;
    int fi = -1, ti = -1;
    for(int i = 0; i < from->links; i++) {
        nod* cur = from->linked[i];
        if(cur == to || SAMEPOS(cur->data, to->data)) { fi = i; break; }
    }
    for(int i = 0; i < to->links; i++) {
        nod* cur = to->linked[i];
        if(cur == from || SAMEPOS(cur->data, from->data)) { ti = i; break; }
    }
    if(fi < 0 || ti < 0) return false;

    from->links--;
    if(from->links == 0) {
        free(from->linked);
        from->linked = NULL;
    } else {
        for(int j = fi; j < from->links; j++) {
            from->linked[j] = from->linked[j+1];
        }
        from->linked = realloc(from->linked, from->links * sizeof(nod*));
    }

    to->links--;
    if(to->links == 0) {
        free(to->linked);
        to->linked = NULL;
    } else {
        for(int j = ti; j < to->links; j++) {
            to->linked[j] = to->linked[j+1];
        }
        to->linked = realloc(to->linked, to->links * sizeof(nod*));
    }
    return true;
}

bool canLink(nod* from, nod* to, board* bord) {
    return isKnight(from->data,to->data) && !cross(from,to,bord);
}
bool place(int r,int c,int colour,board* bord){
    if(bord->allnodes[r][c]!= NULL){
        return false;
    }
    nod* newnode = create(colour,r,c);
    bord->allnodes[r][c] = newnode;
    if(isEdge(newnode,0,bord)){
        addEdge(newnode,bord);
    }
    return true;
}
