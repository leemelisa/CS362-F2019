#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main (int argc, char** argv) {

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
    memcpy(G.hand[p], coppers, sizeof(int) * handCount);
    printf("Start of unit test 1\n");
    minion(5, 1, 0, 0, &G, 1, 0, 1);

    assert(G.coins, 2);

    memset(&G, 23, sizeof(struct gameState)); // set the game state
    int r = initializeGame(2, k, 1, &G); // initialize a new game
    G.handCount[p] = handCount; // set any other variables
    G.coin = 0;
    G.handCount = 0;
    /* set all player hand count to 0 */
    memcpy(G.hand[p], coppers, sizeof(int) * handCount);
    printf("Start of unit test 1\n");
    minion(5, 2, 0, 0, &G, 1, 0, 1);

    /* check if all other palyer hand count is 0 */
    assert(G.handCount, 0);

    memset(&G, 23, sizeof(struct gameState)); // set the game state
    int r = initializeGame(2, k, 1, &G); // initialize a new game
    G.handCount[p] = handCount; // set any other variables
    G.coin = 0;
    G.handCount = 0;
    /* set all player hand count to 5 */
    memcpy(G.hand[p], coppers, sizeof(int) * handCount);
    printf("Start of unit test 1\n");
    minion(5, 2, 0, 0, &G, 1, 0, 1);

    /* check if all other palyer hand count is 4 */
    assert(G.handCount, 4);


   return 0;
}

