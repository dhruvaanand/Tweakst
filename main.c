#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "board.h"
#include "link.h"
#include "cross.h"
#include "init.h"
#include "print.h"

#include "checkwin.h"
#include "utils.h"

// Declare missing helpers
int checkQuad(pos origin, pos rel);
bool addEdge(nod* link, board* bord);
bool inRegion(pos a, pos b, pos check);
bool isEdge(nod* node, int edge, board* bord);
bool isKnight(pos from, pos to);
nod* autoLink(nod* node, board* bord);
int convstr(char* string);

int main() {
    printf("WELCOME TO TWEAKST\ntype help to know more, add a space after every command\n");
    printf("Enter your preferred board size r c\n");
    int x, y;
    scanf("%d %d", &x, &y);
    pos dims;
    dims.c = x, dims.r = y;
    board* gameBoard = newbord(dims);
    bool gameOver = false;
    int colour = 1;
    char*** show = createCharr(gameBoard);
    printNode(show, gameBoard);
    drawAll(show, gameBoard);
    printBoard(show, gameBoard);
    while(gameOver != true) {
        fflush(stdin);
        bool invalid = false;
        if (colour == 1) {
            printf("Player RED's turn \n");
        } else {
            printf("Player BLUE's turn \n");
        }
        static int ch;
        static char* words[5];
        int ind=0, bind=0;
        static char buffer[30];
        static int r1, r2, c1, c2;
        while((ch = getchar()) != '\n' && ch != EOF) {
            if(ch == ' ') {
                if(bind > 0) {
                    words[ind] = malloc(bind+1);
                    buffer[bind] = '\0';
                    strcpy(words[ind++], buffer);
                    bind=0;
                }
            } else {
                if(bind < sizeof(buffer) - 1) buffer[bind++] = ch;
            }
        }
        if(ind == 0) continue;
        if(strcmp(words[0], "help") == 0) {
            printf("help : displays all constrols\nplace r c : places a peg at that specific row and column\n");
            printf("addlink r1 c1 r2 c2 : adds a link(if possible) between the two pegs at the mentioned coordinates\n");
           // printf("removelink r1 c1 r2 c1 : removes a link(if possible) between the two pegs at the mentioned coordinates\n");
            printf("resign : Forfeit the game\n");
            continue;
        } else if(strcmp(words[0], "place") == 0) {
            r1 = convstr(words[1]);
            c1 = convstr(words[2]);
            if(r1 == -3 || c1 == -3) {
                printf("Invalid Input\n");
                continue;
            } else if(r1 >= gameBoard->size.r || c1 >= gameBoard->size.c) {
                printf("Invalid Input\n");
                continue;
            }
            if(colour == 1) {
                if(c1 == 0 || c1 == gameBoard->size.c-1) {
                    printf("Peg cannot be place there\n");
                    continue;
                }
            } else if(colour == -1) {
                if(r1 == 0 || r1 == gameBoard->size.r-1) {
                    printf("Peg cannot be place there\n");
                    continue;
                }
            }
            if(place(r1, c1, colour, gameBoard)) {
                colour = colour * -1;
                autoLink(gameBoard->allnodes[r1][c1], gameBoard);
            } else printf("Invalid input\n");
        } else if(strcmp(words[0], "addlink") == 0) {
            r1 = convstr(words[1]);
            c1 = convstr(words[2]);
            r2 = convstr(words[3]);
            c2 = convstr(words[4]);
            if(r1 == -3 || c1 == -3) {
                printf("Invalid Input\n");
                continue;
            } else if(r1 >= gameBoard->size.r || c1 >= gameBoard->size.c) {
                printf("Invalid Input\n");
                continue;
            }
            if(r2 == -3 || c2 == -3) {
                printf("Invalid Input\n");
                continue;
            } else if(r2 >= gameBoard->size.r || c2 >= gameBoard->size.c) {
                printf("Invalid Input\n");
                continue;
            }
            if(canLink(gameBoard->allnodes[r1][c1], gameBoard->allnodes[r2][c2], gameBoard)) {
                if(addLink(gameBoard->allnodes[r1][c1], gameBoard->allnodes[r2][c2]) == NULL) printf("Invalid input");
            } else printf("Pegs Cannot Be Linked\n");}
        // } else if(strcmp(words[0], "removelink") == 0) {
        //     r1 = convstr(words[1]);
        //     c1 = convstr(words[2]);
        //     r2 = convstr(words[3]);
        //     c2 = convstr(words[4]);
        //     if(r1 == -3 || c1 == -3) {
        //         printf("Invalid Input\n");
        //         continue;
        //     } else if(r1 >= gameBoard->size.r || c1 >= gameBoard->size.c) {
        //         printf("Invalid Input\n");
        //         continue;
        //     }
        //     if(r2 == -3 || c2 == -3) {
        //         printf("Invalid Input\n");
        //         continue;
        //     } else if(r2 >= gameBoard->size.r || c2 >= gameBoard->size.c) {
        //         printf("Invalid Input\n");
        //         continue;
        //     }
        //     if(isLinked(gameBoard->allnodes[r1][c1], gameBoard->allnodes[r2][c2])) {
        //         rmvLink(gameBoard->allnodes[r1][c1], gameBoard->allnodes[r2][c2]);
        //     } else printf("Pegs Not Linked\n");
        // } 
        else if(strcmp(words[0], "resign") == 0) {
            gameOver = true;
            printf("PLAYER %s WINS by resignation\n", (colour == 1) ? "BLUE" : "RED");
            break;
        } else if(!strcmp(words[0], "islinked")) {
            r1 = convstr(words[1]);
            c1 = convstr(words[2]);
            r2 = convstr(words[3]);
            c2 = convstr(words[4]);
            printf("%s", (isLinked(gameBoard->allnodes[r1][c1], gameBoard->allnodes[r2][c2])) ? "YES" : "NO");
            printf("%s\n", cross(gameBoard->allnodes[r1][c1], gameBoard->allnodes[r2][c2], gameBoard) ? "CROSS" : "UNCROSSED");
            printf("%s", (canLink(gameBoard->allnodes[r1][c1], gameBoard->allnodes[r2][c2], gameBoard)) ? "CAN" : "CANNOT");
            continue;
        } else {
            invalid = true;
        }
        system("cls");
        if(invalid) printf("Invalid command, type help to know more\n");
        if(checkWin(colour, gameBoard)) {
            printf("PLAYER %s WINS\n", (colour == 1) ? "BLUE" : "RED");
            printf("Thank you for playing\n");
            gameOver = true;
        }
        printNode(show, gameBoard);
        drawAll(show, gameBoard);
        printBoard(show, gameBoard);
    }
    freeAll(gameBoard, show);
    return 0;
}
