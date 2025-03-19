// include stdio library header file
#include <stdio.h>

// function prototypes
void welcomeScreen();
void playGame();
void displayHand();
void displayDiscard();

// main function
int main() {
    // call function welcomeScreen
    welcomeScreen();
    // call function playGame
    playGame();
    // call function displayHand
    displayHand();
    // call function displayDiscard
    displayDiscard();
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
    char one[20];
    char two[20];

    printf("Player One, enter your name\n");
    scanf("%s", one);

    printf("Player Two, enter your name\n");
    scanf("%s", two);

    printf("\n%s and %s let's play Phase 9!\n\n", one, two);
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