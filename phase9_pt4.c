// include stdio library header file
#include <stdio.h>
// include stdlib.h library header file
#include <stdlib.h>
// include time.h library header file
#include <time.h>
// include string.h library header file
#include <string.h>
// include ctype.h library header file
#include <ctype.h>


// macros / global constants
#define ZERO 0
#define ONE 1
#define TWO 2
#define FOURTEEN 14
#define NAME 20
#define PLAY 1
#define LEAD 2
#define EXIT 3
#define FALSE 0
#define TRUE 1
#define HAND 10
#define DECK 108
#define FOUR 4
#define EIGHT 8
#define TWELVE 12
#define WILD 13
#define SKIP 14
#define LINE 100
#define FIELDS 3
#define DATA 45
#define DISCARD 1
#define DRAW 2
#define THREE 3
#define FIVE 5
#define SIX 6
#define SEVEN 7
#define NINE 9
#define TEN 10
#define ELEVEN 11

// function prototypes
void welcomeScreen();
void playGame();
int displayMenu();
void displayLeaderboard();
void initializeDeck(int deck[DECK]);
void shuffleDeck(int deck[DECK]);
void displayDeck(int deck[DECK]);
void dealHand(int deck[DECK], int *deckIdx, int playerHand[HAND]);
void displayPlayerHand(char player[NAME], int playerHand[HAND]);
int dealDiscard(int deck[DECK], int *deckIdx);
void displaySingle(int discard);
int comp(const void *a, const void *b);
void readLeaderboardFile();
int playerOption(char player[NAME]);
int draw(int deck[DECK], int *deckIdx);
int discardCard(char player[NAME], int playerHand[HAND], int pickUp);
void updateHand(char player[NAME], int playerHand[HAND], int discardIdx, int *discard, int newCard);
char *trim(char *str);

// main function
int main() {
    // call function welcomeScreen
    welcomeScreen();
    // seed the random function
    srand ((unsigned int) time (NULL));
    // call function playGame
    playGame();

    return 0;
}

// welcomeScreen function displays the Phase 9 logo and phases of the game
void welcomeScreen() {
    printf("PPPP    H  H     A      SSSS  EEEE    9999  \n");
    printf("P   P   H  H    A A    SS     E      9    9 \n");
    printf("PPPP    HHHH   AA AA    SS    EEE     9999  \n");
    printf("P       H  H   A   A      SS  E         9   \n");
    printf("P       H  H  A     A  SSSS   EEEE    99    \n");
    printf("\n");
    printf("PHASE 9 PHASES\n\n");
    printf("1. 2 sets of 3\n");
    printf("2. 1 set of 3 + 1 run of 4\n");
    printf("3. 1 set of 4 + 1 run of 4\n");
    printf("4. 1 run of 7\n");
    printf("5. 1 run of 8\n");
    printf("6. 1 run of 9\n");
    printf("7. 2 sets of 4\n");
    printf("8. 1 set of 5 + 1 set of 2\n");
    printf("9. 1 set of 5 + 1 set of 3\n\n");
}
// function playGame controls the gameplay
void playGame() {
    char one[NAME];
    char two[NAME];
    int oneHand[HAND];
    int twoHand[HAND];
    int deck[DECK];
    int deckIdx = ZERO;
    int discardOrDraw = ZERO;
    int pickUp = ZERO;
    int playerDiscard = ZERO;
    // stores the number of turns taken
    int turn = ZERO;
    // stores the current player
    int currentPlayer = ONE;
    // stores the user's menu choice
    int choice = ZERO;
    choice = displayMenu();
    while (choice != EXIT) {
        if (choice == PLAY) {
            printf("Player One, enter your name\n");
            scanf("%s", one);

            printf("Player Two, enter your name\n");
            scanf("%s", two);

            printf("\n%s and %s let's play Phase 9!\n\n", one, two);

            initializeDeck(deck);
            shuffleDeck(deck);
            dealHand(deck, &deckIdx, oneHand);
            // sort player 1's hand
            qsort(oneHand, HAND, sizeof(oneHand[ZERO]), comp);
            dealHand(deck, &deckIdx, twoHand);
            // sort player 2's hand
            qsort(twoHand, HAND, sizeof(twoHand[ZERO]), comp);
            int discard = dealDiscard(deck, &deckIdx);

            while (turn < TWO) {
                if (currentPlayer == ONE) {
                    displayPlayerHand(one, oneHand);
                    displaySingle(discard);
                    discardOrDraw = playerOption(one);
                    if (discardOrDraw == DISCARD) {
                        printf("%s chose to pick up the discard\n", one);
                        pickUp = discard;
                        printf("New card\n");
                        displaySingle(pickUp);
                    } else if (discardOrDraw == DRAW) {
                        printf("%s chose to draw from the deck\n", one);
                        pickUp = draw(deck, &deckIdx);
                        printf("New card\n");
                        displaySingle(pickUp);
                    }
                    playerDiscard = discardCard(one, oneHand, pickUp);
                    updateHand(one, oneHand, playerDiscard, &discard, pickUp);

                    currentPlayer = TWO;
                } else if (currentPlayer == TWO) {
                    displayPlayerHand(two, twoHand);
                    displaySingle(discard);
                    discardOrDraw = playerOption(two);
                    if (discardOrDraw == DISCARD) {
                        printf("%s chose to pick up the discard\n", two);
                        pickUp = discard;
                        printf("New card\n");
                        displaySingle(pickUp);
                    } else if (discardOrDraw == DRAW) {
                        printf("%s chose to draw from the deck\n", two);
                        pickUp = draw(deck, &deckIdx);
                        printf("New card\n");
                        displaySingle(pickUp);
                    }
                    playerDiscard = discardCard(one, oneHand, pickUp);
                    updateHand(one, oneHand, playerDiscard, &discard, pickUp);

                    currentPlayer = ONE;
                }
                turn += 1;
            }
        } else if (choice == LEAD) {
            printf("\n");
            readLeaderboardFile();
            printf("\n");
        } else {
            exit(ZERO);
        }
        // reset variables
        choice = displayMenu();
        deckIdx = ZERO;
        turn = ZERO;
    }
}

int displayMenu() {
    // stores if user's choice is valid or not
    int valid = FALSE;
    // stores user's menu choice
    int choice = ZERO;
    while (!valid) {
        // game menu options
        printf("Select a menu option:\n");
        printf("1. Play Phase 9\n");
        printf("2. View Leaderboard\n");
        printf("3. Exit Game\n");
        scanf("%d", &choice);
        // validate user's menu choice
        if (choice != PLAY && choice != LEAD && choice != EXIT) {
            valid = FALSE;
        } else {
            valid = TRUE;
        }
    }
    return choice;
}

void displayLeaderboard() {
    // hardcoded statistics
    printf("------------------------------------\n");
    printf("\t\tPhase 9 Leaderboard\n");
    printf("------------------------------------\n");
    printf("Position\t\tPlayer\t\tWins\n");
    printf("--------\t\t------\t\t----\n\n");
    printf("1\t\t\t\tBlaze\t\t39\n");
    printf("2\t\t\t\tSmoke\t\t33\n");
    printf("3\t\t\t\tKarin\t\t30\n");
    printf("4\t\t\t\tSamuel\t\t29\n");
    printf("5\t\t\t\tKeystone\t26\n");
    printf("6\t\t\t\tNatty\t\t20\n");
    printf("7\t\t\t\tStorm\t\t9\n");
}

void initializeDeck(int deck[DECK]) {
    int idx = ZERO;
    for (int i = 0; i < EIGHT; i++) {
        for (int j = 1; j <= TWELVE; j++) {
            deck[idx] = j;
            idx += 1;
        }
    }
    for (int i = 0; i < EIGHT; i++) {
        deck[idx] = WILD;
        idx += 1;
    }
    for (int i = 0; i < FOUR; i++) {
        deck[idx] = SKIP;
        idx += 1;
    }
}

void shuffleDeck(int deck[DECK]) {
    for (int i = 0; i < DECK; i++) {
        // swapping one card with another random one
        int c;
        c = rand() % 108;
        int card = deck[i];
        deck[i] = deck[c];
        deck[c] = card;
    }
}

void displayDeck(int deck[DECK]) {
    printf("Phase 9 deck of cards:\n");
    for (int i = 0; i < DECK; i++) {
        printf("%d ", deck[i]);
    }
    printf("\n\n");
}

void dealHand(int deck[DECK], int *deckIdx, int playerHand[HAND]) {
    for (int i = 0; i < HAND; i++) {
        playerHand[i] = deck[*deckIdx];
        (*deckIdx) += 1;
    }
}
void displayPlayerHand(char player[NAME], int playerHand[HAND]) {
    printf("\n%s's hand\n\n", player);
    printf("+---------------------------------------------------------------------+\n");
    printf("|      |      |      |      |      |      |      |      |      |      |\n");
    printf("|");
    for (int i = 0; i < HAND; i++) {
        if (playerHand[i] == WILD) {
            printf("  W   |");
        }
        else if (playerHand[i] == SKIP) {
            printf("  S   |");
        } else {
            printf(" %3d  |", playerHand[i]);
        }
    }
    printf("\n");
    printf("|      |      |      |      |      |      |      |      |      |      |\n");
    printf("+---------------------------------------------------------------------+\n");
}

int dealDiscard(int deck[DECK], int *deckIdx) {
    int discard = deck[*deckIdx];
    (*deckIdx) += 1;
    return discard;
}

void displaySingle(int discard) {
    printf("+------+\n");
    printf("|      |\n");
    if (discard == WILD) {
        printf("|  W   |\n");
    }
    else if (discard == SKIP) {
        printf("|  S   |\n");
    } else {
        printf("| %3d  |\n", discard);
    }
    printf("|      |\n");
    printf("+------+\n");
}

int comp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void readLeaderboardFile() {
    char line[LINE];
    int fieldIdx = ZERO;
    char *data[DATA];
    // open the file
    FILE *fp = fopen("leaderboard.txt", "r");
    printf("------------------------------------\n");
    printf("\t\tPhase 9 Leaderboard\n");
    printf("------------------------------------\n");
    printf("Position\t\tPlayer\t\t\tWins\n");
    printf("--------\t\t------\t\t\t----\n\n");
    // if file cannot be found
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }
    while (fgets(line, LINE, fp) != NULL) {
        char *field = strtok(line, ",");
        // trim white space
        field = trim(field);
        while (field != NULL) {
            data[fieldIdx] = malloc(strlen(field) + 1);
            strcpy(data[fieldIdx], field);
            field = strtok(NULL, ",");
            // trim white space
            field = trim(field);
            fieldIdx += 1;
        }
    }
    // close the file
   fclose(fp);
    for (int i =0; i<DATA; i+=FIELDS) {
        if (strlen(data[i+1]) >= 7) {
            printf("%s\t\t\t\t %s\t\t %s\n", data[i], data[i+1], data[i+2]);
        } else {
            printf("%s\t\t\t\t %s\t\t\t %s\n", data[i], data[i+1], data[i+2]);
        }
    }
}
int playerOption(char player[NAME]) {
    int choice = ZERO;
    int valid = FALSE;
    while (valid == FALSE) {
        printf("%s, select an option:\n", player);
        printf("1. Pick up discard\n");
        printf("2. Draw from deck\n");
        scanf("%d", &choice);
        if (choice != DISCARD && choice!= DRAW) {
            valid = FALSE;
        } else {
            valid = TRUE;
        }
    }
    return choice;
}
int draw(int deck[DECK], int *deckIdx) {
    int card = deck[*deckIdx];
    // increment the index
    (*deckIdx)++;
    return card;
}

int discardCard(char player[NAME], int playerHand[HAND], int pickUp) {
    int choice = ZERO;
    displayPlayerHand(player, playerHand);
    printf("  ( 1)   ( 2)   ( 3)   ( 4)   ( 5)   ( 6)   ( 7)   ( 8)   ( 9)   (10)\n");
    displaySingle(pickUp);
    printf("  (11)\n");
    printf("Select which card to discard (1 - 11)\n");
    scanf("%d", &choice);
    return choice;
}

void updateHand(char player[NAME], int playerHand[HAND], int discardIdx, int *discard, int newCard) {
    if (discardIdx == ELEVEN) {
        printf("%s selected the drawn card to be discarded, hand does not change\n", player);
        return;
    } else {
        int card = playerHand[discardIdx-ONE];
        playerHand[discardIdx-ONE] = newCard;
        // display current hand
        displayPlayerHand(player, playerHand);
        // sort the hand
        qsort(playerHand, HAND, sizeof(playerHand[ZERO]), comp);
        *discard = card;
        // display sorted hand
        displayPlayerHand(player, playerHand);
        printf("Discarded card\n");
        displaySingle(*discard);
    }

}



// trims leading and trailing white space
char *trim(char *str)
{
    // check if the string is empty
    if (str == NULL || *str == '\0') {
        return str;
    }
    // trim leading white space
    char *start = str;
    while (isspace((unsigned char)*start)) {
        start++;
    }
    // trim trailing white space
    char *end = str + strlen(str) - 1;
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }
    // add the null terminator
    end[1] = '\0';
    // return the updated string
    return start;
}