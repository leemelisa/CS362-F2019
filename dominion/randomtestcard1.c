#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include<time.h>

int main() {
   srand(time(NULL));
   
   /* int baronCardEffect(int card, int choice1, int choice2, int choice3, 
   * struct gameState *state, int handPos, int *bonus, int currentPlayer); */

   /* set your card  array */
   int choice1, currentPlayer ;
   int card = 8, choice2 = 0, choice3 = 0, handPos = 0, bonus = 0;

   int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

   /* declarethe game state */
   struct gameStateG;
   



   return 0;
}
