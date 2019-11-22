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
    int choice1 = 1, curPlayer = 0;
    struct gameState G, prevState;  // the original state

    initializeGame(2, k, seed, &G);
    memcpy(&prevState, &G, sizeof(struct gameState));
    
    // set coins to 0
    G.coins = 0;
    // set handCount to all cooper and set first one to baron
    for (int i = 0; i < G.handCount[curPlayer]; i++) {
        G.hand[curPlayer][i] = copper;
    }
    G.hand[curPlayer][0] = estate;
    // discard count is 0
    G.discardCount[curPlayer] = 0;
    
 
    printf("Begin Unit Testing baronCardEffect():\n");
    printf("Start of unit test 1: player has an estate card\n");
    int funcTest = baronCardEffect(choice1, &G, curPlayer); // call baron
    myAssert(funcTest == 0, "baronCardEffect() successful.");
    myAssert((prevState.coins + 4) == G.coins, "4 coins successfully added.");
    myAssert(G.discardCount[curPlayer] == 2, "Discard count successfully incremented");
    myAssert(G.discard[curPlayer][0] == estate, "Estate in discard arr.");
    for (int i = 0; i < G.discardCount[curPlayer]; i++) {
        if (G.discard[curPlayer][i] == baron) {
            myAssert(G.hand[curPlayer][i] == baron, "Baron card is discarded.");
        }

        if (i == G.discardCount[curPlayer] - 1) {
            printf("baron is discarded.\t FAILED\n");
        }
    }

    // initalize new game
    initializeGame(2, k, seed, &G);
    memcpy(&prevState, &G, sizeof(struct gameState));
    
    // set coins to 0
    G.coins = 0;
    // set handCount to all cooper and set first one to baron
    for (int i = 0; i < G.handCount[curPlayer]; i++) {
        G.hand[curPlayer][i] = copper;
    }
    // discard count is 0
    G.discardCount[curPlayer] = 0;
    
    printf("\nBegin Unit Testing baronCardEffect():\n");
    printf("Start of unit test 1: player has no estate card\n");
    funcTest = baronCardEffect(choice1, &G, curPlayer); // call baron
    myAssert(funcTest == 0, "baronCardEffect() successful.");
    myAssert(G.coins == 0, "4 coins not added.");
    myAssert(G.discardCount[curPlayer] == 1, "Discard count successfully incremented");
    myAssert(prevState.supplyCount[estate] == G.supplyCount[estate], "Estate suppy count was decremented");
    for (int i = 0; i < G.handCount[curPlayer]; i++) {
        if (G.hand[curPlayer][i] == estate) {
            myAssert(G.hand[curPlayer][i] == estate, "Estate card is gain.");
        }

        if (i  == G.handCount[curPlayer] - 1) {
            myAssert(i == G.handCount[curPlayer] - 1, "Estate card is not gain.");
        }
    }
    for (int i = 0; i < G.discardCount[curPlayer]; i++) {
        if (G.discard[curPlayer][i] == baron) {
            myAssert(G.hand[curPlayer][i] == baron, "baron card is discarded.");
        }

        if (i == G.discardCount[curPlayer] - 1) {
            printf("baron is discarded.\t FALED\n");
        }
    }
   return 0;
}



