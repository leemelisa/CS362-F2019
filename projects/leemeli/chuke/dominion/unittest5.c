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
    G.handCount[curPlayer] = 1;
    G.hand[curPlayer][0] = copper;
    memcpy(&prevState, &G, sizeof(struct gameState));
    mineCardEffect(choice1, choice2, &G, handPos, curPlayer);
    myAssert(G.discardCount[curPlayer] == prevState.handCount[curPlayer], "Current player hand properly discarded");
    myAssert(G.hand[curPlayer][0] == copper, "Copper added properly");
    myAssert(G.hand[curPlayer][0] == silver, "silver added properly");
    myAssert(G.hand[curPlayer][0] == gold, "gold added properly");



    return 0;
}

