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
    int curPlayer = 0, nextPlayer = 1;
    struct gameState G, prevState;  // the original state

    initializeGame(3, k, seed, &G);
    G.handCount[nextPlayer] = 2;
    G.hand[nextPlayer][0] = copper;
    G.hand[nextPlayer][1] = silver;
    G.coins = 0;
    G.hand[curPlayer][0] = tribute;
    int tributeRevealedCards[2] = {copper, silver}; 
    memcpy(&prevState, &G, sizeof(struct gameState));
    tributeCardEffect(&G, curPlayer, nextPlayer, tributeRevealedCards); // call test func

    printf("Begin Unit Testing tributeCardEffect(): with treasure cards\n");
    printf("coins: %d", G.coins);
    myAssert(prevState.coins == G.coins + 2, "Coins added");

    printf("\nBegin Unit Testing tributeCardEffect(): with victory cards\n");
    initializeGame(2, k, seed, &G);
    G.handCount[nextPlayer] = 2;
    G.hand[nextPlayer][0] = estate;
    G.hand[nextPlayer][1] = duchy;
    G.coins = 0;
    G.hand[curPlayer][0] = tribute;
    tributeRevealedCards[0] = estate;
    tributeRevealedCards[1] =  duchy;
    memcpy(&prevState, &G, sizeof(struct gameState));
    tributeCardEffect(&G, curPlayer, nextPlayer, tributeRevealedCards); // call test func
    myAssert(prevState.numActions == G.numActions + 2, "Number of Action incremented");

    printf("\nBegin Unit Testing tributeCardEffect(): with action cards\n");
    myAssert(prevState.handCount[curPlayer] == G.handCount[curPlayer] + 1, "Card added");

    initializeGame(2, k, seed, &G);
    G.handCount[nextPlayer] = 2;
    G.hand[nextPlayer][0] = mine;
    G.hand[nextPlayer][1] = smithy;
    G.coins = 0;
    G.hand[curPlayer][0] = tribute;
    tributeRevealedCards[0] = mine;
    tributeRevealedCards[1] =  smithy;
    memcpy(&prevState, &G, sizeof(struct gameState));
    tributeCardEffect(&G, curPlayer, nextPlayer, tributeRevealedCards); // call test func

    myAssert(prevState.discardCount[curPlayer] == G.discardCount[curPlayer] + 1, "tribute card in discard pile.");
    myAssert(prevState.playedCardCount == prevState.playedCardCount - 1, "played card count incremnted");

    return 0;
}

