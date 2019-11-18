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
    int n, numPlayers, choice1, curPlayer = 0;
    struct gameState G, testCase;  // the original state

    for (n = 0; n < 2000; n++) {
        numPlayers = getRandomNum(1, 2);
        choice1 = getRandomNum(0, 1);
     
        initializeGame(2, k, seed, &G);
        memcpy(&testCase, &G, sizeof(struct gameState));

        G.whoseTurn = getRandomNum(1, 2);

        int prevDiscard = testCase.discardCount[curPlayer];   // prev discard count
        int prevCoin = testCase.coins; // prev coinCount
        int funcTest = baronCardEffect(choice1, &G, curPlayer); // call baron
        printf("Begin Testing %d baronCardEffect():\n", n);
  
        int count = 0;

        for (int i = 0; i < G.handCount[curPlayer]; i++) {
            if (G.hand[curPlayer][i] == estate) {
                myAssert(G.hand[curPlayer][i] == estate, "Estate card is gain.");
            }

            if (count == G.handCount[curPlayer] - 1) {
                myAssert(count == G.handCount[curPlayer] - 1, "Estate card is not gain.");
            }
        } 
 
        myAssert(funcTest == 0, "baronCardEffect() successful.");
        myAssert(G.hand[curPlayer][0] != estate, "Estate card successfully is no longer in player hand.");
        myAssert((prevCoin + 4) == G.coins, "4 coins successfully added.");
        myAssert(G.discard[curPlayer][0] == estate, "Estate in discard arr.");
        myAssert((prevDiscard + 1) == G.discardCount[curPlayer], "Discard count successfully incremented");
        myAssert(testCase.handCount[curPlayer] == G.handCount[curPlayer] - 1, "Hand count is less my 1" );
        myAssert(testCase.numBuys == 1, "Num of buy is back to 1.");
        myAssert(testCase.numActions == 1, "Num of action is back to 1.");     
	myAssert(testCase.supplyCount[estate] == G.supplyCount[estate], "no estate was added");
    }

    return 0;
}
