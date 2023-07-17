#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define NEWLINES for(int i = 1; i <= 5; ++i) {puts("");}

int validity(int);
int antiStuck(int);
void grid();
void move(int, int, int);
int checker();
void computerMove();
int inputCheck();
void game();

char row1[12] = "   |   |   ";
char row2[12] = "   |   |   ";
char row3[12] = "   |   |   ";
const char row_separator[12] = "---|---|---";

int gameState[3][3] = {
                       {0, 0, 0},
                       {0, 0, 0},
                       {0, 0, 0}
                       }; // cross (X) will be represented as 1, circle (O) as 2

const char validInput[3] = {1,2,3};

int validity(int x) { // checks for validity of user input (row/column)
    for(int j = 0; j <= 2; ++j) {
        if(x == validInput[j]) {
            return 1;
        }
    }
    return 0;
}

int antiStuck(int x) {
    for(int j = 0; j <= 2; ++j) {
        if(gameState[x-1][j] == 0) {
            return 1;
        }
    }
    return 0;
}

void grid() {  // prints the grid
    printf("\n%s", row1);
    printf("\n%s", row_separator);
    printf("\n%s", row2);
    printf("\n%s", row_separator);
    printf("\n%s\n\n\n", row3);
}

void move(int x, int y, int z) { // places an X/O to a space on the grid
    gameState[x-1][y-1] = z;
    
    switch(x) { // checks for which row to place into
        
        case 1: switch(y) { // checks for which column to place into
            case 1: switch(z) { // checks whether X or O should be placed
                case 1: row1[1] = 'X'; break;
                case 2: row1[1] = 'O'; break;
            }
            break;
            case 2: switch(z) {
                case 1: row1[5] = 'X'; break;
                case 2: row1[5] = 'O'; break;
            }
            break;
            case 3: switch(z) {
                case 1: row1[9] = 'X'; break;
                case 2: row1[9] = 'O'; break;
            }
        }
        break;

        case 2: switch(y) {
            case 1: switch(z) {
                case 1: row2[1] = 'X'; break;
                case 2: row2[1] = 'O'; break;
            }
            break;
            case 2: switch(z) {
                case 1: row2[5] = 'X'; break;
                case 2: row2[5] = 'O'; break;
            }
            break;
            case 3: switch(z) {
                case 1: row2[9] = 'X'; break;
                case 2: row2[9] = 'O'; break;
            }
        }
        break;

        case 3: switch(y) {
            case 1: switch(z) {
                case 1: row3[1] = 'X'; break;
                case 2: row3[1] = 'O'; break;
            }
            break;
            case 2: switch(z) {
                case 1: row3[5] = 'X'; break;
                case 2: row3[5] = 'O'; break;
            }
            break;
            case 3: switch(z) {
                case 1: row3[9] = 'X'; break;
                case 2: row3[9] = 'O'; break;
            }
        }
        break;
    }
}


int checker() { // verifies whether a solution has occured
    // rows
    for(int i = 0; i <= 2; ++i) {
        if(gameState[i][0] == gameState[i][1] && gameState[i][0] == gameState[i][2]) {
            if(gameState[i][0] == 1) { return 1; } // X's win
            else if(gameState[i][0] == 2) { return 2; } // O's win
        }
    }

    // columns
    for(int j = 0; j <= 2; ++j) {
        if(gameState[0][j] == gameState[1][j] && gameState[0][j] == gameState[2][j]) {
            if(gameState[0][j] == 1) { return 1; } // X's win
            else if(gameState[0][j] == 2) { return 2; } // O's win
        }
    }

    // diag 1
    if(gameState[0][0] == gameState[1][1] && gameState[0][0] == gameState[2][2]) {
        if(gameState[0][0] == 1) { return 1; } // X's win
        else if(gameState[0][0] == 2) { return 2; } // O's win
    }

    // diag 2
    if(gameState[0][2] == gameState[1][1] && gameState[0][2] == gameState[2][0]) {
        if(gameState[0][2] == 1) { return 1; } // X's win
        else if(gameState[0][2] == 2) { return 2; } // O's win
    }
    return 0;
}

void computerMove() { // generates a position, and then performs a move (with the move function)
    int i = 4, j = 4; // can be any number apart from 0, 1, 2, and also 3 for some reason (!)
    
    do {
        srand(time(0));
        i = rand() % 3;
        j = rand() % 3;
    } while(gameState[i][j] != 0);

    move(i+1,j+1,2);
}

int inputCheck() { // enables decimal input, which would otherwise result in unexpected behavior
    char input[100];
    int x;

    fgets(input, 100, stdin);
    input[strlen(input)-1] = '\0';
    x = atoi(input);

    return x;
}

void game() {
    int a = 0;
    int r, col;
    int moveCount = 0;

    grid();

    do {
        printf("\nEnter row #(1-3): ");
        r = inputCheck();

        while(validity(r) == 0 || antiStuck(r) == 0) {
            printf("\nThat was an incorrect value.");
            printf("\nEnter row #(1-3): ");
            r = inputCheck();
        }

        printf("Enter column #(1-3): ");
        col = inputCheck();

        while(validity(col) == 0) {
            printf("\nThat was an incorrect value.");
            printf("\nEnter column #(1-3): ");
            col = inputCheck();
        }

        printf("\n\n\n");

        if(gameState[r-1][col-1] == 0) {
            move(r, col, 1);
            moveCount++;


        } else {
            printf("\nThat space is already taken.\n");
            NEWLINES
            continue;
            }
        a = checker();
        if(a == 1) {
            grid();
            printf("\nYOU WIN!");
            break;
        }
        
        if(moveCount == 9) {
            break;
        }

        computerMove();
        moveCount++;
        a = checker(); // verification happens both after player's move and the computer's move
        grid();
        if(a == 2) {
            printf("\nCOMPUTER WINS. :(");
            break;
        }
    } while(moveCount < 9);

    if(a == 0) {
        grid();
        printf("\nTIE.");
    }
}

int main(void) {
    char cont;

    NEWLINES
    printf("HELLO, WELCOME TO TIC-TAC-TOE.\n\n");

    while(1) {
        game();

        for(int i = 0; i <= 2; ++i) {
            for(int j = 0; j <= 2; ++j) {
                gameState[i][j] = 0;
            }
        }
        strcpy(row1, "   |   |   ");
        strcpy(row2, "   |   |   ");
        strcpy(row3, "   |   |   ");

        printf("\nWOULD YOU LIKE TO PLAY AGAIN? (Y/N): ");
        scanf(" %c", &cont);
        cont = toupper(cont);

        if(cont != 'Y') {
            NEWLINES
            printf("\nThank you for playing! :)");
            NEWLINES
            break;
        }
        NEWLINES
        getchar(); // ! VERY IMPORTANT, otherwise we get unexpected output at game replay ("That was an incorrect value")
    }
    system("pause");
    return 0;
}