#include <stdlib.h>
#include <stdio.h>
#include "bst.h"
#include "bst.c"
// method to print out the nodes/questions/guesses
struct node* create_game_tree()
{
    struct node* root = NULL;
    root = insert(root, 100, "Does it grow underground?", "");
    insert(root, 50, "Is it long in shape?", "");
    insert(root, 25, "Is it orange in color?", "");
    insert(root, 15, "", "It's a carrot!");
    insert(root, 35, "", "It's a parsnip!");
    insert(root, 75, "Is it red in color?", "");
    insert(root, 65, "", "It's a radish!");
    insert(root, 85, "", "It's a potato!");
    insert(root, 150, "Does it grow on a tree?", "");
    insert(root, 125, "Is it red in color?", "");
    insert(root, 115, "", "It's an apple!");
    insert(root, 135, "", "It's a peach!");
    insert(root, 175, "Is it red in color?", "");
    insert(root, 165, "", "It's a tomato!");
    insert(root, 185, "", "It's a pea!");
    return root;
}
// i set up the play_game method so it can play through the game
void play_game(struct node* root)
{
    char answer;

    while (root != NULL)
    {
        if (root->guess[0] != '\0')
        {
            printf("%s\n", root->guess);
            scanf(" %c", &answer);
            if (answer == 'y')
            {
                printf("I win!\n");
            }
            else
            {
                printf("You win!\n");
            }
            return;
        }

        printf("%s\n", root->question);
        scanf(" %c", &answer);

        // traverses through the binary search tree depending on the answer the user puts in
        if (answer == 'y')
        {
            root = root->left;
        }
        else if (answer == 'n')
        {
            root = root->right;
        }
        else
        {
            printf("Invalid input. Please answer 'y' or 'n'.\n");
        }
    }
    printf("You win!\n");
}

// main method which chooses whether to print the game or quit the game
int main()
{
    struct node* game_tree = create_game_tree();
    printf("Welcome! Press 'q' to quit or any other key to continue:\n");
    char c;
    scanf(" %c", &c);
    
    // will print out game until the user puts 'q'
    while (c != 'q') 
    {
        if (c != '\n') 
        {
            printf("You think of a fruit or vegetable, and I will try to guess it!\n");
            play_game(game_tree);
        }
        
        printf("Press 'q' to quit or any other key to continue:\n");
        scanf(" %c", &c);
    }
    // prints after the user quits the game
    printf("Bye Bye!\n");
    return 0;
}