#include <stdio.h>   // Standard input-output library   
#include <stdlib.h>  // Standard library for functions 
#include <ctype.h>   // Testing or checking characters
#include <time.h>    // Used to work with date and time functions 

// Declaring global variables 
char board[3][3];
const char PLAYER = 'X';     // Character to play for the player
const char COMPUTER = 'O';   // Character to play for computer

// Function declarations
void resetBoard();
void printBoard();
int CheckFreeSpace();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char winner);

int main() {
    char winner;  // Empty space is replaced with whichever character wins X or O
    char response;  // To check if the player wants to play again
    
    do {
        winner = ' ';  // Reset winner for each new game
        resetBoard();
        
        while (winner == ' ' && CheckFreeSpace() != 0) {
            printBoard();
            
            // Player move
            playerMove();
            winner = checkWinner();
            if (winner != ' ' || CheckFreeSpace() == 0) {
                break;
            }
            
            // Computer move
            computerMove();
            winner = checkWinner();
            if (winner != ' ' || CheckFreeSpace() == 0) {
                break;
            }
        }
        
        printBoard();
        printWinner(winner);
        
        printf("\nWould you like to play again (Y/N)?: ");
        scanf(" %c", &response);  // Use space before %c to consume any trailing newline
        response = toupper(response);  // Convert to uppercase to handle both cases
    } while (response == 'Y');
    
    printf("Thanks for playing!!\n");
    return 0;
}

// Function definitions
void resetBoard() {
    for (int i = 0; i < 3; i++) { 
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

int CheckFreeSpace() {
    int freeSpace = 9;
    for (int i = 0; i < 3; i++) { 
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != ' ') {
                freeSpace--;
            }
        }
    }
    return freeSpace;
}

void playerMove() {
    int x, y;
    do {
        printf("Enter row #(1-3): ");
        scanf("%d", &x);
        x--;  // Array index starts at 0 and user doesn't know that, so decrement by 1 after user input
        printf("Enter column #(1-3): ");
        scanf("%d", &y);
        y--;

        if (board[x][y] != ' ') {
            printf("Invalid move!!\n");
        } else {
            board[x][y] = PLAYER;
            break;
        }
    } while (board[x][y] != ' ');
}

void computerMove() {
    srand(time(0));
    int x, y;
    if (CheckFreeSpace() > 0) {
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');

        board[x][y] = COMPUTER;
    }
}

char checkWinner() {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            return board[i][0];
        }
    }
    // Check columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
            return board[0][i];
        }
    }
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
        return board[0][2];
    }
    return ' ';  // Returning empty character if no winner
}

void printWinner(char winner) {
    if (winner == PLAYER) {
        printf("YOU WIN!\n");
    } else if (winner == COMPUTER) {
        printf("COMPUTER WINS!\n");
    } else {
        printf("IT'S A DRAW!\n");
    }
}
