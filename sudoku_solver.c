/* 
 * File:   sudoku_solver.c
 * Author: Avishay
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>                     
#include <Math.h>

typedef unsigned char byte;
typedef enum {false, true} bool;
typedef struct {byte x; byte y;} point; // x for columns, y for rows

bool solveSudoku(byte board[9][9]);
bool checkBoard(byte board[9][9], point p);
void insertIntoMat(byte mat[9][9], byte arr[], int index);
bool checkSquare(byte board[9][9], point sqStart, point valPt);
void printBoard(byte board[9][9]);
    
int main(int argc, char** argv) {
    byte board[9][9] = { //edit the variable to whatever board you have, if you want it to be unfilled leave as 0
                         {0, 0, 0, 0, 6, 0, 5, 0, 0},
                         {0, 4, 0, 0, 0, 0, 3, 0, 2},
                         {5, 0, 0, 1, 0, 4, 0, 0, 0},
                         {2, 0, 6, 0, 0, 7, 8, 0, 0},
                         {0, 8, 0, 0, 0, 0, 0, 3, 0},
                         {0, 0, 5, 8, 0, 0, 2, 0, 6},
                         {0, 0, 0, 2, 0, 9, 0, 0, 4},
                         {7, 0, 4, 0, 0, 0, 0, 2, 0},
                         {0, 0, 8, 0, 5, 0, 0, 0, 0}
                                                    };
    printf("Board is %s\n", solveSudoku(board) ? "fine" : "not fine");
    printBoard(board);

    return EXIT_SUCCESS;
}

bool solveSudoku(byte board[9][9]) {
    int i, j, z;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (board[i][j] == 0) {
                for (z = 1; z <= 9; z++) {
                    board[i][j] = z;
                    point pt;
                    pt.x = j;
                    pt.y = i;
                    
                    if (checkBoard(board, pt) == false) {
                        board[i][j] = 0;
                        continue;
                    }
                        
                    if (solveSudoku(board) == false) {
                        board[i][j] = 0;
                        continue;
                    } else
                        break;
                }  
            }
            if (board[i][j] == 0) 
                return false;
        }
    }
    return true;
}
bool checkBoard(byte board[9][9], point p) {
    int i;
    for (i = 0; i < 9; i++) {                               // go over all the column numbered x
        if (board[i][p.x] == board[p.y][p.x] && i != p.y) // check if it is equal, which means it is corrupt 
            return false;
        
        if (board[p.y][i] == board[p.y][p.x] && i != p.x)   // same but just row numbered y
            return false;
        point sq;
        sq.x = p.x / 3 * 3;
        sq.y = p.y / 3 * 3;
        if (!checkSquare(board, sq, p))
            return false;
    }
    return true;
}

bool checkSquare(byte board[9][9], point sqStart, point valPt) {
    int i, j;
    for (i = sqStart.x; i < sqStart.x + 3; i++)
        for (j = sqStart.y; j < sqStart.y + 3; j++)
            if (board[j][i] == board[valPt.y][valPt.x] && (valPt.x != i && valPt.y != j)) {
                return false;
            }
    return true;
}

void printBoard(byte board[9][9]) {
    int i, j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            printf("%3d", board[i][j]);
        }
        printf("\n");
    }
}
