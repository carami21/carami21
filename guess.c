#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// set it to only show the top 3 scores
#define TOPSCORE 3

// gets the guess from players
int GetGuess()
{
    int num;
    scanf("%d", &num);
    return num;
}

// this struct is so it can show a highscore
typedef struct ass5
{
    char name[50];
    int score;
} HIGHSCORE;

// this function displays the top 3 highscores
void displayHighScores()
{
    // I changed the file name so TAs can grade easier, previously used this "/Users/carlosramirez/Documents/CSE240/playerHighScore.txt"
    char fileName[] = "/Users/carlosramirez/Documents/CSE240/playerHighScore.txt";
    FILE *fp = NULL;
    HIGHSCORE highscore[TOPSCORE];

    // opens the highscores file for reading
    fp = fopen(fileName, "r");

    if (fp == NULL)
    {
        printf("Error displaying highscores file\n");
        return;
    }
    printf("Here are the current leaders\n");

    // reads and displays the top 3 highscores
    for (int i = 0; i < TOPSCORE; i++)
    {
        if (fscanf(fp, "%s %d", highscore[i].name, &highscore[i].score) != 2)
        {
            strcpy(highscore[i].name, "NoName");
            highscore[i].score = 0;
        }
        printf("%s made %d guesses%s\n", highscore[i].name, highscore[i].score, highscore[i].score == 1 ? "" : "es");
    }

    fclose(fp);
}

// this function not only gets the highscore, but also updates it
void getHighScore(const char *playerName, int score, HIGHSCORE *scores, int maxScores)
{
    char fileName[] = "/Users/carlosramirez/Documents/CSE240/playerHighScore.txt";
    FILE *fp = NULL;
    HIGHSCORE highscore[TOPSCORE];

    // I found the reading and writing function to be used best in order to update the highscores
    fp = fopen(fileName, "r+");

    if (fp == NULL)
    {
        printf("Error opening highscore file.\n");
        return;
    }

    // reads the existing high scores and puts it into the highscore array
    for (int i = 0; i < TOPSCORE; i++)
    {
        if (fscanf(fp, "%s %d", highscore[i].name, &highscore[i].score) != 2)
        {
            strcpy(highscore[i].name, "NoName");
            highscore[i].score = 0;
        }
    }

    // finds the index of the first equivalent or higher score
    int updateIndex = TOPSCORE;
    for (int i = 0; i < TOPSCORE; i++)
    {
        if (score >= highscore[i].score)
        {
            updateIndex = i;
            break;
        }
    }

    // if a higher score or an equal score is found, the move names down
    if (updateIndex < TOPSCORE)
    {
        // Shift scores and names down to make room for the new score
        for (int i = TOPSCORE - 1; i > updateIndex; i--)
        {
            strcpy(highscore[i].name, highscore[i - 1].name);
            highscore[i].score = highscore[i - 1].score;
        }

        // updates the new score
        strcpy(highscore[updateIndex].name, playerName);
        highscore[updateIndex].score = score;
    }

    // moves the file pointer to the beginning of the file
    fseek(fp, 0, SEEK_SET);

    // writes the top high scores back to the file
    for (int i = 0; i < TOPSCORE; i++)
    {
        fprintf(fp, "%s %d\n", highscore[i].name, highscore[i].score);
    }

    fclose(fp);
}

// the main function to play the guessing game
void PlayGuessingGame(const char *playerName)
{
    int randNum;
    int num;
    double sqrtNum;
    int attempts = 0;

    // this generates a random number and its square root
    randNum = rand() %91 + 10;
    sqrtNum = sqrt(randNum);
    // had to change to only show 8 decimals instead of 15 like last assignment
    printf("%.8lf is the square root of what number? Guess a value between 10 and 100: ", sqrtNum);
    // this loop will run until the correct number is guessed 
    // otherwise it will keep giving you hints whether it is too low or too high
    do
    {
        num = GetGuess();
        attempts++;
        if (num < randNum)
        {
            printf("Too low, guess again: ");
        }
        else if (num > randNum)
        {
            printf("Too high, guess again: ");
        }
        else
        {
            printf("You got it, baby!\n");
        }
    } while (num != randNum);

    printf("You made %d guess%s.\n", attempts, attempts == 1 ? "" : "es");

    // updates the high scores with the players name and score
    getHighScore(playerName, attempts, NULL, 0);
}

int main()
{
    char userInput;
    char playerName[50];
    printf("Please enter your name to start: ");
    scanf("%s", playerName);

    while (1)
    {
        PlayGuessingGame(playerName);
        displayHighScores();
        printf("Press 'q' to quit or any other key to continue: ");
        scanf(" %c", &userInput);
        if (userInput == 'q' || userInput == 'Q')
        {
            printf("Bye Bye!\n");
            exit(0);
        }
    }
}
