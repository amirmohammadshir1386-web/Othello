#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define BOARD_SIZE 8
#define BLACK 'B'
#define WHITE 'W'
#define EMPTY '.'
#define VALID_BLACK 'b'
#define VALID_WHITE 'w'

// Colors for the terminal
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE_COLOR "\033[37m"
#define BOLD "\033[1m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"

// Structure to store game data
typedef struct {
    char board[BOARD_SIZE][BOARD_SIZE];
    char player1[50];
    char player2[50];
    char currentPlayer;
    int blackScore;
    int whiteScore;
} Game;

//Declaration of functions
void clearScreen();
void showMenu();
void showInstructions();
void initializeGame(Game *game);
void printBoard(Game *game, bool showValid);
bool isValidMove(Game *game, int row, int col, char player);
void getValidMoves(Game *game, char player);
bool makeMove(Game *game, int row, int col, char player);
void flipDiscs(Game *game, int row, int col, char player);
bool hasValidMoves(Game *game, char player);
void calculateScore(Game *game);
void playGame();
void announceWinner(Game *game);

// Screen clear function
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

//Menu display function
void showMenu() {
    clearScreen();
    printf("\n");
    printf(BOLD CYAN "╔════════════════════════════════════════════════════════════════╗\n" RESET);
    printf(BOLD CYAN "║" RESET "                        " BOLD YELLOW "  OTHELLO GAME  " RESET "                        " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "╟────────────────────────────────────────────────────────────────╢\n" RESET);
    printf(BOLD CYAN "║" RESET "                                                                " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "║" RESET GREEN "  1. " RESET "Start Game                                                 " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "║" RESET "                                                                " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "║" RESET GREEN "  2. " RESET "Game Instructions                                          " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "║" RESET "                                                                " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "║" RESET GREEN "  3. " RESET "Exit                                                       " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "║" RESET "                                                                " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "╚════════════════════════════════════════════════════════════════╝\n\n" RESET);
    printf(YELLOW " Your choice: " RESET);  
}

// Function to display game guide
void showInstructions() {
    clearScreen();
    printf("\n");
    printf(BOLD CYAN "╔════════════════════════════════════════════════════════════════╗\n" RESET);
    printf(BOLD CYAN "║" RESET "                       " BOLD YELLOW "GAME INSTRUCTIONS " RESET "                       " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "╟────────────────────────────────────────────────────────────────╢\n" RESET);
    printf(BOLD CYAN "║" RESET "                                                                " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "║" RESET GREEN " Game Rules:                                                    " RESET BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "║" RESET " ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "║" RESET "                                                                " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "║" RESET " • The game is played on an 8×8 board                           " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "║" RESET " • Two players play with black and white discs                  " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "║" RESET " • The game starts with 4 discs in the center (2 black, 2 white)" BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "║" RESET " • Black player makes the first move                            " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "║" RESET "                                                                " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "║" RESET YELLOW " How to Play:                                                   " RESET BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "║" RESET " ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "║" RESET " • Each move must trap at least one opponent's disc             " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "║" RESET " • Trapping is possible in 8 directions (horizontal, vertical,  " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "║" RESET "   diagonal)                                                    " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "║" RESET " • All trapped opponent discs are flipped to your color         " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "║" RESET " • Valid squares are shown in yellow                            " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "║" RESET "                                                                " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "║" RESET MAGENTA " End of Game:                                                   " RESET BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "║" RESET " ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "║" RESET " • The game ends when:                                          " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "║" RESET "   - The board is full                                          " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "║" RESET "   - Neither player has any valid moves                         " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "║" RESET " • The winner is the player with more discs                     " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "║" RESET "                                                                " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "╚════════════════════════════════════════════════════════════════╝\n\n" RESET);
    printf(CYAN " Press Enter to return..." RESET);
    getchar();
    getchar();
}

// Game screen initialization function
void initializeGame(Game *game) {
    // Clear the board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            game->board[i][j] = EMPTY;
        }
    }
    
    // Initial beads in the center
    game->board[3][3] = WHITE;
    game->board[3][4] = BLACK;
    game->board[4][3] = BLACK;
    game->board[4][4] = WHITE;
    
    game->currentPlayer = BLACK;
    game->blackScore = 2;
    game->whiteScore = 2;
}

// Print game screen function
void printBoard(Game *game, bool showValid) {
    char tempBoard[BOARD_SIZE][BOARD_SIZE];
    
    // Copy the board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            tempBoard[i][j] = game->board[i][j];
        }
    }
    
    // Show valid gestures
    if (showValid) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (tempBoard[i][j] == EMPTY && isValidMove(game, i, j, game->currentPlayer)) {
                    tempBoard[i][j] = (game->currentPlayer == BLACK) ? VALID_BLACK : VALID_WHITE;
                }
            }
        }
    }
    printf("\n");
    printf(BOLD "                   0   1   2   3   4   5   6   7  \n" RESET);
    printf(BOLD "                 ┌───┬───┬───┬───┬───┬───┬───┬───┐\n" RESET);
    
    for(int i = 0; i < BOARD_SIZE; i++) {
        printf(BOLD "               %d │" RESET, i);
        for(int j = 0; j < BOARD_SIZE; j++) {
            if (tempBoard[i][j] == BLACK) {
                printf(BOLD " ○ " RESET);
            } else if (tempBoard[i][j] == WHITE) {
                printf(BOLD " ● " RESET);
            } else if (tempBoard[i][j] == VALID_BLACK) {
                printf(" " BOLD YELLOW "*" RESET " ");
            } else if (tempBoard[i][j] == VALID_WHITE) {
                printf(" " BOLD YELLOW "*" RESET " ");
            } else {
                printf("   ");
            }
            printf(BOLD "│" RESET);
        }
        if (i < BOARD_SIZE - 1)
        {
            printf(BOLD "\n                 ├───┼───┼───┼───┼───┼───┼───┼───┤\n" RESET);
        }
    }
    printf(BOLD "\n                 └───┴───┴───┴───┴───┴───┴───┴───┘\n" RESET);
}

// Function to check the legality of the move
bool isValidMove(Game *game, int row, int col, char player) {
   // Check for the existence of the house
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return false;
    }
    
    // Check if the house is empty
    if (game->board[row][col] != EMPTY) {
        return false;
    }
    
    char opponent = (player == BLACK) ? WHITE : BLACK;
    // Check 8 directions
    int directions[8][2] = {{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}};
    
    for (int d = 0; d < 8; d++) {
        int dr = directions[d][0];
        int dc = directions[d][1];
        int r = row + dr;
        int c = col + dc;
        bool foundOpponent = false;

        // Continue in the direction until reaching the player's piece
        while (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE) {
            if (game->board[r][c] == EMPTY) {
                break;
            }
            if (game->board[r][c] == opponent) {
                foundOpponent = true;
            } else if (game->board[r][c] == player) {
                if (foundOpponent) {
                    return true;
                }
                break;
            }
            r += dr;
            c += dc;
        }
    }
    
    return false;
}

// Function to rotate the dice
void flipDiscs(Game *game, int row, int col, char player) {
    char opponent = (player == BLACK) ? WHITE : BLACK;
    // Rotate the beads in 8 directions
    int directions[8][2] = {{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}};
    
    for (int d = 0; d < 8; d++) {
        int dr = directions[d][0];
        int dc = directions[d][1];
        int r = row + dr;
        int c = col + dc;
        bool foundOpponent = false;
        int flips[64][2];
        int flipCount = 0;
        
        while (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE) {
            if (game->board[r][c] == EMPTY) {
                break;
            }
            if (game->board[r][c] == opponent) {
                foundOpponent = true;
                flips[flipCount][0] = r;
                flips[flipCount][1] = c;
                flipCount++;
            } else if (game->board[r][c] == player) {
                if (foundOpponent) {
                    for (int i = 0; i < flipCount; i++) {
                        game->board[flips[i][0]][flips[i][1]] = player;
                    }
                }
                break;
            }
            r += dr;
            c += dc;
        }
    }
}

// Function to place the piece and rotate the opponent's pieces
bool makeMove(Game *game, int row, int col, char player) {
    if (!isValidMove(game, row, col, player)) {
        return false;
    }
    
    game->board[row][col] = player;
    flipDiscs(game, row, col, player);
    return true;
}

// Function to check if the player has movement
bool hasValidMoves(Game *game, char player) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (isValidMove(game, i, j, player)) {
                return true;
            }
        }
    }
    return false;
}

// Points counting function
void calculateScore(Game *game) {
    game->blackScore = 0;
    game->whiteScore = 0;
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (game->board[i][j] == BLACK) {
                game->blackScore++;
            } else if (game->board[i][j] == WHITE) {
                game->whiteScore++;
            }
        }
    }
}

void announceWinner(Game *game) {
    clearScreen();
    calculateScore(game);
    
    printf("\n");
    printf(BOLD CYAN "╔════════════════════════════════════════════════════════════════╗\n" RESET);
    printf(BOLD CYAN "║" RESET "                          " BOLD YELLOW " GAME OVER  " RESET "                          " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "╚════════════════════════════════════════════════════════════════╝\n" RESET);
    printf("\n");
    
    printf(BOLD "  Final Results:\n" RESET);
    printf("  ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    printf("  " BOLD "○ %s (Black):" RESET " %d points\n", game->player1, game->blackScore);
    printf("  " BOLD "● %s (White):" RESET " %d points\n\n", game->player2, game->whiteScore);
    printf("  ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    
    if (game->blackScore > game->whiteScore) {
        printf(BOLD GREEN "   Winner: %s (Black) \n" RESET, game->player1);
    } else if (game->whiteScore > game->blackScore) {
        printf(BOLD GREEN "   Winner: %s (White) \n" RESET, game->player2);
    } else {
        printf(BOLD YELLOW "   It's a Tie! \n" RESET);
    }
    
    printf("\n");
}

void playGame() {
    Game game;
    clearScreen();
    
    printf(BOLD CYAN "╔════════════════════════════════════════════════════════════════╗\n" RESET);
    printf(BOLD CYAN "║" RESET "                         " BOLD YELLOW "Start New Game" RESET "                         " BOLD CYAN "║\n" RESET);
    printf(BOLD CYAN "╚════════════════════════════════════════════════════════════════╝\n" RESET);
    printf("\n");
    
    printf(GREEN " Player 1 name (Black disc): " RESET);
    scanf(" %[^\n]", game.player1);
    
    printf(GREEN " Player 2 name (White disc): " RESET);
    scanf(" %[^\n]", game.player2);
    
    initializeGame(&game);
    
    bool gameRunning = true;
    bool blackPassed = false;
    bool whitePassed = false;
    
    while (gameRunning) {
        clearScreen();
        calculateScore(&game);
        
        printf("\n");
        printf(BOLD CYAN "╔════════════════════════════════════════════════════════════════╗\n" RESET);
        printf(BOLD CYAN "║" RESET "                        " BOLD YELLOW "  OTHELLO GAME  " RESET "                        " BOLD CYAN "║\n" RESET);
        printf(BOLD CYAN "╚════════════════════════════════════════════════════════════════╝\n" RESET);
        
        printf("\n  " BOLD "Scores: " RESET);
        printf(BOLD "○ %s: %d" RESET "  |  " BOLD "● %s: %d\n" RESET, 
               game.player1, game.blackScore, game.player2, game.whiteScore);
        
        if (game.currentPlayer == BLACK) {
            printf("\n  " BOLD GREEN "Turn: %s (○ Black)\n" RESET, game.player1);
        } else {
            printf("\n  " BOLD BLUE "Turn: %s (● White)\n" RESET, game.player2);
        }
        
        printBoard(&game, true);
        
        // Check for movement for the current player
        if (!hasValidMoves(&game, game.currentPlayer)) {
            printf("\n" YELLOW "    No valid moves available! Turn passed.\n" RESET);
            printf(CYAN "  Press Enter to continue..." RESET);
            getchar();
            getchar();
            
            if (game.currentPlayer == BLACK) {
                blackPassed = true;
            } else {
                whitePassed = true;
            }
            
            if (blackPassed && whitePassed) {
                gameRunning = false;
                continue;
            }
            
            game.currentPlayer = (game.currentPlayer == BLACK) ? WHITE : BLACK;
            continue;
        }
        
        if (game.currentPlayer == BLACK) {
            blackPassed = false;
        } else {
            whitePassed = false;
        }
        
        printf("\n" YELLOW "   Yellow squares: valid moves\n" RESET);
        printf(GREEN "  Enter coordinates (row column): " RESET);
        
        int row, col;
        if (scanf("%d %d", &row, &col) != 2) {
            printf(RED "\n   Invalid input!\n" RESET);
            while (getchar() != '\n'); // پاک کردن بافر
            printf(CYAN "  Press Enter to continue..." RESET);
            getchar();
            continue;
        }
        
        // Perform the move
        if (!makeMove(&game, row, col, game.currentPlayer)) {
            printf(RED "\n   Invalid move! Please try again.\n" RESET);
            printf(CYAN "  Press Enter to continue..." RESET);
            while (getchar() != '\n'); // پاک کردن بافر
            getchar();
            continue;
        }
        
        // Count points
        calculateScore(&game);
        
        // Check if the game is over (all cells are filled)
        if (game.blackScore + game.whiteScore == BOARD_SIZE * BOARD_SIZE) {
            gameRunning = false;
            continue;
        }
        
        game.currentPlayer = (game.currentPlayer == BLACK) ? WHITE : BLACK;
    }
    
    announceWinner(&game);
    printf(CYAN "\n  Press Enter to return to menu..." RESET);
    // Clear the input buffer
    while (getchar() != '\n');
    getchar();
}

int main() {
    int choice;
    bool running = true;
    while (running) {
        showMenu();
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }
        
        switch (choice) {
            case 1:
                playGame();
                break;
            case 2:
                showInstructions();
                break;
            case 3:
                clearScreen();
                printf("\n" BOLD GREEN "   Goodbye! Enjoy playing!\n\n" RESET);
                running = false;
                break;
            default:
                printf(RED "\n   Invalid choice!\n" RESET);
                printf(CYAN "  Press Enter to continue..." RESET);
                while (getchar() != '\n');
                getchar();
        }
    }
    
    return 0;
}