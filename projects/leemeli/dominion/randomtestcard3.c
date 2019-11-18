#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

// non terminating assert function
int myAssert(int boolean, char* str) {
    if (boolean == 0) {
        printf("\"%s\" FAILED\n", str);
        return 0;
    }

     printf("\"%s\" PASSED\n", str);
    return 1;
}

int getRandomNum(int lower, int upper) {
    return (rand() % (upper - lower + 1)) + lower;
}

int main() {
    srand(time(NULL));
    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int n, numPlayers, curPlayer, nextPlayer;
    struct gameState G, prevState;  // the original state

    printf("Begin Random Testing tributeCardEffect():\n");

    for (n = 0; n < 2000; n++) {
        numPlayers = getRandomNum(1, 4);      
        curPlayer = getRandomNum(1, numPlayers);

        initializeGame(numPlayers, k, seed, &G);
        G.whoseTurn = curPlayer;
	//G.supplyCount[5];
        G.hand[curPlayer][0] = tribute; // add tribute card
        if (curPlayer == 4) {
            nextPlayer = 1;
        } else {
            nextPlayer = curPlayer + 1;
        }
        
        memcpy(&prevState, &G, sizeof(struct gameState));
        tributeCardEffect(&G, curPlayer, nextPlayer); // call test func

        myAssert(prevState.coins == G.coins + 2, "Coins added");
        myAssert(prevState.handCount[curPlayer] == G.handCount[curPlayer] + 1, "Card added");
        myAssert(prevState.numActions == G.numActions + 2, "Number of Action incremented");
	myAssert(prevState.discardCount[curPlayer] == G.discardCount[curPlayer] + 1, "tribute card in discard pile.");
	myAssert(prevState.playedCardCount == prevState.playedCardCount - 1, "played card count incremnted");

   }

       
    return 0;
}
