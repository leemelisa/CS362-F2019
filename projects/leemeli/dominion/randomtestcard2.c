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
    int n, numPlayers, choice1, choice2, handPos = 0, curPlayer;
    struct gameState G, prevState;  // the original state
    int addMinion = getRandomNum(0, 1);
   
    printf("Begin Random Testing minionCardEffect():\n");

    for (n = 0; n < 2000; n++) {
        numPlayers = getRandomNum(1, 4);
        curPlayer = getRandomNum(1, numPlayers);
        choice1 = getRandomNum(0, 1);
        if (choice1) {
	   choice2 = 0;
	} else {
	   choice2 = 1;
	}

        initializeGame(numPlayers, k, seed, &G);
	G.whoseTurn = curPlayer; 
	if (addMinion == 0) {
	   G.hand[curPlayer][0] = minion;
	}
        memcpy(&prevState, &G, sizeof(struct gameState));
        minionCardEffect(choice1, choice2, &G, handPos, curPlayer); // call baron
        printf("Minon card added: %d \t Choice1: %d\n", addMinion, choice1); 
	myAssert(prevState.numActions == G.numActions + 1, "Number of action incremnted");
        if (choice1) {
            // test for coin update
            myAssert(prevState.coins == (G.coins + 2), "Coins added.");
        } else {
	    myAssert(prevState.coins == G.coins, "No coins added");
            myAssert(G.handCount[curPlayer] == 4, "Hand count is 4");
            myAssert(G.discardCount[curPlayer] ==  prevState.handCount[curPlayer], "Hand is in discard pile");
            myAssert((prevState.deckCount - 4) == G.deckCount[curPlayer], "Deck count is decremented");
	    myAssert(prevState.deckCount[numPlayers] > G.deckCount[numPlayers], "Drawn cards from deck.");
	    myAssert(prevState.playedCardCount < G.playedCardCount, "Played card count incremented");	
            // look at other player hand count should be either 4 if prev is 5
            for (int i = 0; i < G.numPlayers; i++) {
		if (i != curPlayer) {
		   if (prevState.handCount[i] > 4) {
			myAssert(G.handCount[i] == 4, "Player drawn 4 cards.");
		   }
		}

            }

	}
    }

    return 0;
}
