// include stdio library header file
#include <stdio.h>
// include stdlib.h library header file
#include <stdlib.h>
// include time.h library header file
#include <time.h>
// include string.h library header file
#include <string.h>


// declare macros to use as global constants for the application
#define ZERO 0
#define ONE 1
#define TWO 2
#define FOURTEEN 14
#define NAME 20
// Used for playing Phase 9
#define PLAY 1
// Used for seeing the leaderboard
#define LEAD 2
#define EXIT 3
#define FALSE 0
#define TRUE 1
// Used for # of cards in player's hand
#define HAND 10
// Used for # of cards in deck
#define DECK 108
// Used for amount of skips
#define FOUR 4
// Used for amount of wild cards
#define EIGHT 8
#define TWELVE 12
// Used for wilds
#define WILD 13
// Used for skips
#define SKIP 14

// function prototypes
void welcomeScreen();
void playGame();
void displayHand();
int displayMenu();
void displayLeaderboard();
void randomHand(char player[NAME]);
int drawCard();
void randomDiscard();
void initializeDeck(int deck[DECK]);
void shuffleDeck(int deck[DECK]);
void displayDeck(int deck[DECK]);
void dealHand(int deck[DECK], int *deckIdx, int playerHand[HAND]);
void displayPlayerHand(char player[NAME], int playerHand[HAND]);
int dealDiscard(int deck[DECK], int *dexkIdx);
void displayDiscard(int discard);
int comp(const void *a, const void *b);

// main function
int main() {
    // call function welcomeScreen
    welcomeScreen();
    // seed the random function
    srand ((unsigned int) time (NULL));
    // call function playGame
    playGame();

    // call function displayHand
    // displayHand();
    // call function displayDiscard
    // displayDiscard();
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
            displayDeck(deck);
            shuffleDeck(deck);
            displayDeck(deck);
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
                    displayDiscard(discard);
                    currentPlayer = TWO;
                } else if (currentPlayer == TWO) {
                    displayPlayerHand(two, twoHand);
                    displayDiscard(discard);
                    currentPlayer = ONE;
                }
                turn += 1;
            }
        } else if (choice == LEAD) {
            printf("\n");
            displayLeaderboard();
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

void randomHand(char player[NAME]) {
    // declare 10 variables, one for each card's value
    int cOne = drawCard();
    int cTwo = drawCard();
    int cThree = drawCard();
    int cFour = drawCard();
    int cFive = drawCard();
    int cSix = drawCard();
    int cSeven = drawCard();
    int cEight = drawCard();
    int cNine = drawCard();
    int cTen = drawCard();
    // output the player's name and random hand
    printf("\n%s's hand\n\n", player);
    printf("+---------------------------------------------------------------------+\n");
    printf("|      |      |      |      |      |      |      |      |      |      |\n");
    printf("| %3d  | %3d  | %3d  | %3d  | %3d  | %3d  | %3d  | %3d  | %3d  | %3d  |\n",
        cOne, cTwo, cThree, cFour, cFive, cSix, cSeven, cEight, cNine, cTen);
    printf("|      |      |      |      |      |      |      |      |      |      |\n");
    printf("+---------------------------------------------------------------------+\n");
}

int drawCard() {
    int cardValue = (rand() % FOURTEEN + ONE);
    return cardValue;
}

void randomDiscard() {
    int discard = drawCard();
    printf("\nDiscard pile\n");
    printf("+------+\n");
    printf("|      |\n");
    printf("| %3d  |\n", discard);
    printf("|      |\n");
    printf("+------+\n");
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

void displayDiscard(int discard) {
    printf("\nDiscard pile\n\n");
    printf("+------+\n");
    printf("|      |\n");
    printf("| %3d  |\n", discard);
    printf("|      |\n");
    printf("+------+\n");
}

int comp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}