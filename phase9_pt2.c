// include stdio library header file
#include <stdio.h>
// include stdlib.h library header file
#include <stdlib.h>
// include time.h library header file
#include <time.h>

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



// function prototypes
void welcomeScreen();
void playGame();
void displayHand();
void displayDiscard();
int displayMenu();
void displayLeaderboard();
void randomHand(char player[NAME]);
int drawCard();
void randomDiscard();


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
    // stores the current player
    int currentPlayer = ONE;
    // stores the user's menu choice
    int choice = ZERO;
    choice = displayMenu();
    if (choice == PLAY) {
        printf("Player One, enter your name\n");
        scanf("%s", one);

        printf("Player Two, enter your name\n");
        scanf("%s", two);

        printf("\n%s and %s let's play Phase 9!\n\n", one, two);
        if (currentPlayer == ONE) {
            // pass as an argument the variable for player one's name
            randomHand(one);
            // show discard pile
            randomDiscard();
            currentPlayer = TWO;
        }
        if (currentPlayer == TWO) {
            // pass as an argument the variable for player two's name
            randomHand(two);
            // show discard pile
            randomDiscard();
            currentPlayer = ONE;
        }
    } else if (choice == LEAD) {
        displayLeaderboard();
    } else {
        exit(ZERO);
    }
}

// function displayHand displays a hardcoded version of a player's cards
void displayHand() {
    printf("\nPlayer's hand\n\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|     |     |     |     |     |     |     |     |     |     |\n");
    printf("|  2  |  2  |  4  |  4  |  5  |  7  |  8  |  8  |  9  |  9  |\n");
    printf("|     |     |     |     |     |     |     |     |     |     |\n");
    printf("+-----------------------------------------------------------+\n");
}
// function displayDiscard displays a hardcoded version of the discard pile
void displayDiscard() {
    printf("\nDiscard pile\n\n");
    printf("+-----+\n");
    printf("|     |\n");
    printf("| 12  |\n");
    printf("|     |\n");
    printf("+-----+\n");
}

int displayMenu() {
    // stores user's menu choice
    int choice = ZERO;
    // game menu options
    printf("Select a menu option:\n");
    printf("1. Play Phase 9\n");
    printf("2. View Leaderboard\n");
    scanf("%d", &choice);
    // validate user's menu choice
    if (choice != PLAY && choice != LEAD) {
        choice = ZERO;
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