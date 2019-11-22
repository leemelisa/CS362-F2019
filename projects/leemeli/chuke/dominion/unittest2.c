#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h> 
#include <time.h> 

int myAssert(int boolean, char* str) {
    if (boolean == 0) {
        printf("\"%s\" FAILED\n", str);
        return 0;
    }

    printf("\"%s\" PASSED\n", str);
    return 1;
}

int main () {
    int seed = 1000;
    // set your card array    
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int choice1 = 1, choice2 = 0, curPlayer = 0, handPos = 0;
    struct gameState G, prevState;  // the original state

    initializeGame(2, k, seed, &G);
    G.coins = 0;
    memcpy(&prevState, &G, sizeof(struct gameState));

    printf("Begin Unit Testing minionCardEffect():\n");
    printf("Start of unit test 1: player choose to gain + 2 coins\n");

    minionCardEffect(choice1, choice2, &G, handPos, curPlayer);
    myAssert((prevState.coins + 2) == G.coins, "2 coins successfully added.");

    printf("\nStart of unit test 2: player choose to gain discard hand\n");
    initializeGame(2, k, seed, &G);
    G.handCount[1] = 5;
    // set other player hand to 5 card
    for (int i = 0; i < G.handCount[1]; i++) {
        G.hand[1][i] = copper;
    }
    memcpy(&prevState, &G, sizeof(struct gameState));
    minionCardEffect(0, 1, &G, 0, curPlayer);
    printf("hand count: %d\n", G.discardCount[curPlayer]);
    myAssert(G.handCount[curPlayer] == 4, "Current plyaer drew 4 cards");
    myAssert(G.handCount[1] == 4, "Other players drew 4 cards");
    myAssert(G.discardCount[curPlayer] == prevState.handCount[curPlayer], "Current player hand properly discarded");
    myAssert(G.discardCount[1] == prevState.handCount[1], "Other player hand properly discarded");
    return 0;
}

