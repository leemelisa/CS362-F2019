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
    /* hand count of left is 3 */
    G.coin = 0;
    G.actionCount = 0;
    G.victoryCount = 0;
    /* set all player hand count to 0 */
    memcpy(G.hand[p], coppers, sizeof(int) * handCount);
    printf("Start of unit test 1\n");
    int tributeRevealedCards[2] = {1, 2};
    tribute(5, 1, 0, 0, &G, 1, 0, 1);
    assert(G.coins, 2);
    assert(G.victoryCount, 2);

    memset(&G, 23, sizeof(struct gameState)); // set the game state
    int r = initializeGame(2, k, 1, &G); // initialize a new game
    G.handCount[p] = handCount; // set any other variables
    /* hand count of left is 3 */
    G.coin = 0;
    G.actionCount = 0;
    G.victoryCount = 0;
    /* set all player hand count to 0 */
    memcpy(G.hand[p], coppers, sizeof(int) * handCount);
    printf("Start of unit test 1\n");
    int tributeRevealedCards[2] = {2, 3};
    tribute(5, 1, 0, 0, &G, 1, 0, 1);
    assert(G.coins, 2);
    assert(G.actionCount, 2);



    return 0;
}

