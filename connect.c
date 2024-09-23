#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define Rows 6
#define Columns 7

void printBoard(char *board);
int playerTurn(char *board, int currPlayer, const char *gamePiece);
int playerWin(char *board, int winCondition);
int horizontalWin(char *board, int winCondition);
int verticalWin(char *board, int winCondition);
int diagonalWin(char *board, int winCondition);

void getName(char *player1Name, char *player2Name)
{
    printf("Enter Player 1 Name: ");
    scanf("%s", player1Name);
    printf("Enter Player 2 Name: ");
    scanf("%s", player2Name);

    printf("Welcome %s and %s\n", player1Name, player2Name);
}

void assignPlayer(char *player1Name, char *player2Name)
{
    printf("%s will be assigned the color Red.\n", player1Name);
    printf("%s will be assigned the color Yellow.\n", player2Name);
}

int main()
{
    char player1Name[50], player2Name[50];
    char userChoice;
    int winCondition;

do 
{
        printf("Choose the winning condition (3, 4, or 5 tokens in a row): ");
        scanf("%d", &winCondition);

        if (winCondition != 3 && winCondition != 4 && winCondition != 5) 
        {
            printf("Invalid winning condition. Please choose 3, 4, or 5 tokens.\n");
        }
    } while (winCondition != 3 && winCondition != 4 && winCondition != 5);

    const char *gamePiece = "RY";
    char board[Rows * Columns];
    memset(board, ' ', Rows * Columns);

    int done = 0;

    getName(player1Name, player2Name);

do
{
        int turn;
    for (turn = 0; turn < Rows * Columns && !done; turn++)
    {
            printBoard(board);
            int currentPlayer = turn % 2;
    while (!playerTurn(board, currentPlayer, gamePiece))
    {
        printBoard(board);
        puts("**Cannot fill in, column full**\n");
    }
        done = playerWin(board, winCondition);
     }

printBoard(board);

if (done == 1)
    printf("%s wins!\n", player1Name);
    else if (done == 2)
            printf("%s wins!\n", player2Name);
        else
            printf("It's a draw!\n");

            printf("Play again? (C to continue, Q to quit, any other key to quit): ");
            scanf(" %c", &userChoice);

if (toupper(userChoice) == 'C')
    {
        memset(board, ' ', Rows * Columns);
        done = 0;

    do 
    {
        printf("Choose the winning condition (3, 4, or 5 tokens in a row): ");
        scanf("%d", &winCondition);

    if (winCondition != 3 && winCondition != 4 && winCondition != 5) 
    {
        printf("Invalid winning condition. Please choose 3, 4, or 5 tokens.\n");
    }
    } while (winCondition != 3 && winCondition != 4 && winCondition != 5);
    }
    else if (toupper(userChoice) == 'Q')
    {
        printf("Thank you for playing, come back again!\n");
        break; 
    }

} while (toupper(userChoice) == 'C');

    return 0;
}

void printBoard(char *board)
{
    int row;
    int column;

    for (row = Rows - 1; row >= 0; row--)
    {
        for (column = 0; column < Columns; column++)
        {
            printf("|%c|", board[row * Columns + column]);
        }
        printf("\n");
    }

    for (column = 0; column < Columns; column++)
    {
        printf(" %d ", column + 1);
    }
    printf("\n");

    for (column = 0; column < Columns; column++)
    {
        printf("----");
    }
    printf("-\n");

    if (playerWin(board, 0) == 0)
        printf("%s to play. Pick a column (1-%d): ", "Red", Columns);
    else
        printf("%s to play. Pick a column (1-%d): ", "Yellow", Columns);
}

int playerTurn(char *board, int currPlayer, const char *gamePiece)
{
    int column;

    char *currentPlayerName = (currPlayer == 0) ? "Red" : "Yellow";

    printf("%s's turn. Enter column (1-7): ", currentPlayerName);
    scanf("%d", &column);
    column--;

    if (column < 0 || column >= Columns || board[(Rows - 1) * Columns + column] != ' ')
    {
        return 0;
    }
    for (int row = 0; row < Rows; row++)
    {
        if (board[row * Columns + column] == ' ')
        {
            board[row * Columns + column] = gamePiece[currPlayer];
            break;
        }
    }

    return 1;
}

int playerWin(char *board, int winCondition)
{
    if (horizontalWin(board, winCondition) || verticalWin(board, winCondition) || diagonalWin(board, winCondition))
    {
        return 1;
    }
    else if (horizontalWin(board + 1, winCondition) || verticalWin(board + 1, winCondition) || diagonalWin(board + 1, winCondition))
    {
        return 2;
    }

    return 0;
}

int horizontalWin(char *board, int winCondition)
{
    for (int row = 0; row < Rows; row++)
    {
        for (int col = 0; col < Columns - winCondition + 1; col++)
        {
            char piece = board[row * Columns + col];
            if (piece != ' ')
            {
                int consecutive = 1;
                for (int i = 1; i < winCondition; i++)
                {
                    if (piece != board[row * Columns + col + i])
                    {
                        consecutive = 0;
                        break;
                    }
                }
                if (consecutive)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int verticalWin(char *board, int winCondition)
{
    for (int row = 0; row < Rows - winCondition + 1; row++)
    {
        for (int col = 0; col < Columns; col++)
        {
            char piece = board[row * Columns + col];
            if (piece != ' ')
            {
                int consecutive = 1;
                for (int i = 1; i < winCondition; i++)
                {
                    if (piece != board[(row + i) * Columns + col])
                    {
                        consecutive = 0;
                        break;
                    }
                }
                if (consecutive)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int diagonalWin(char *board, int winCondition)
{
for (int row = 0; row < Rows - winCondition + 1; row++)
{
    for (int col = 0; col < Columns - winCondition + 1; col++)
    {
        char piece = board[row * Columns + col];
    if (piece != ' ')
    {
        int consecutive = 1;
    for (int i = 1; i < winCondition; i++)
    {
        if (piece != board[(row + i) * Columns + col + i])
        {
            consecutive = 0;
            break;
        }
    }
    if (consecutive)
    {
        return 1;
    }
    }
    }
}

    for (int row = 0; row < Rows - winCondition + 1; row++)
    {
        for (int col = winCondition - 1; col < Columns; col++)
        {
            char piece = board[row * Columns + col];
            if (piece != ' ')
            {
                int consecutive = 1;
                for (int i = 1; i < winCondition; i++)
                {
                    if (piece != board[(row + i) * Columns + col - i])
                    {
                        consecutive = 0;
                        break;
                    }
                }
                if (consecutive)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}