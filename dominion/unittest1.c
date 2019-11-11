#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main (int argc, char** argv) {
    // set your card array
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
    struct gameState G;
    G.coins = 0;


    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];

    memset(&G, 23, sizeof(struct gameState)); // set the game state
    int r = initializeGame(2, k, 1, &G); // initialize a new game
    G.handCount[p] = handCount; // set any other variables
    G.coin = 0;
    G.discardCount = 0;
    memcpy(G.hand[p], coppers, sizeof(int) * handCount);  
    printf("Start of unit test 1\n");
    baronCardEffect(5, 1, 0, 0, &G, 1, 0, 1);

    // check coing increase by 4
    if (G.coins == 4) {
	printf("true");
    } else {
	printf("false");
    }
    // check if estate is throw
    if (G.discardCount == 1) {
	printf(" true");
    } else {
	printf("false");
    }


    memset(&G, 23, sizeof(struct gameState)); // set the game state
    int r = initializeGame(1, k, 1, &G); // initialize a new game
    G.handCount[p] = handCount; // set any other variables
    G.coin = 0;
    G.discardCount = 0;
    memcpy(G.hand[p], coppers, sizeof(int) * handCount);
    printf("Start of unit test 1\n");
    baronCardEffect(5, 0, 0, 0, &G, 1, 0, 1);

    if (G.coins == 0) {
        printf("true");
    } else {
        printf("false");
    }

    if (G.discardCount == 0) {
        printf(" true");
    } else {
        printf("false");
    }

    memset(&G, 23, sizeof(struct gameState)); // set the game state
    int r = initializeGame(1, k, 1, &G); // initialize a new game
    G.handCount[p] = handCount; // set any other variables
    G.handCount = 0;
    G.discardCount = 0;
    memcpy(G.hand[p], coppers, sizeof(int) * handCount);
    printf("Start of unit test 1\n");
    baronCardEffect(5, 0, 0, 0, &G, 1, 0, 1);

    if (G.handCount == 1) {
        printf("true");
    } else {
        printf("false");
    }


    memset(&G, 23, sizeof(struct gameState)); // set the game state
    int r = initializeGame(1, k, 1, &G); // initialize a new game
    G.handCount[p] = handCount; // set any other variables
    G.handCount = 0;
    G.discardCount = 0;
    memcpy(G.hand[p], coppers, sizeof(int) * handCount);
    printf("Start of unit test 1\n");
    baronCardEffect(5, 0, 0, 0, &G, 1, 0, 1);

    if (G.handCount == 0) {
        printf("true");
    } else {
        printf("false");
    }


   return 0;
}



