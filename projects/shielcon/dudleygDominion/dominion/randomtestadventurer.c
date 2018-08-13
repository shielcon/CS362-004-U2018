#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

#define DEBUG 0
#define NOISY_TEST 1

int handFailures = 0;
int handDeckDiscardFailures = 0;

int adventurerRandomTest(int p, struct gameState *G);


int main(){

  printf("Testing Adventurer\n");

  struct gameState G;
  int i, j, n, r, p, deckCount, discardCount, handCount, failures;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  SelectStream(2);
  PutSeed(3);

  failures = 0;
  handFailures = 0;
  
  for (i = 0; i < 100000; i++){
	for (j = 0; j < sizeof(struct gameState); j++) {
	    ((char*)&G)[j] = floor(Random() * 256);
	}
	p = floor(Random() * 2);
	G.deckCount[p] = floor(Random() * MAX_DECK);
	for (n = 0; n < G.deckCount[p]; n++)
		G.deck[p][n] = rand() % 28;
	G.discardCount[p] = floor(Random() * MAX_DECK);
        for (n = 0; n < G.discardCount[p]; n++)
                G.discard[p][n] = rand() % 28;

	G.handCount[p] = floor(Random() * MAX_HAND);
        for (n = 0; n < G.handCount[p]; n++)
                G.hand[p][n] = rand() % 28;

	failures += adventurerRandomTest(p, &G);
  }
  int totalFailures = failures + handFailures + handDeckDiscardFailures;
  if (failures > 0)
	printf("Some tests failed, total failures: %d\ntotal hand failures: %d\ntotal failures of total cards in hand/deck/discard (i.e., adventurer reduces the total number of cards in the player's piles): %d\ntotal failures related to general state change: %d\n", totalFailures, handFailures, handDeckDiscardFailures, failures);

  else
	printf("All tests passed\n");

  return 0;

}

int adventurerRandomTest(int p, struct gameState *post){

  int i, expectedTreasure, failed, currentTreasure, treasureAfterAdventurer;
  struct gameState pre;
  memcpy(&pre, post, sizeof(struct gameState));

  int temphand[MAX_HAND];
  adventurerCard(post, p, 0, temphand, 0, 0);

  currentTreasure = 0;
  for (i = 0; i < pre.handCount[p]; i++){
	if (pre.hand[p][i] == 4 || pre.hand[p][i] == 5 || pre.hand[p][i] == 6)
		currentTreasure++;
  }

  if (pre.deckCount[p] > 0){
	i = 0;
	expectedTreasure = 0;
	while (expectedTreasure < 2 && i < pre.deckCount[p]){
		if (pre.deck[p][i] == 4 || pre.deck[p][i] == 5 || pre.deck[p][i] == 6){
			expectedTreasure++;
			pre.hand[p][pre.handCount[p]] = pre.deck[p];
			pre.handCount[p]++;
		}
		else {
			pre.discard[p][pre.discardCount[p]] = pre.deck[p];
			pre.discardCount[p]++;
		}
		i++;
	}
  }
  else {
        i = 0;
        expectedTreasure = 0;
        while (expectedTreasure < 2 && i < pre.discardCount[p]){
                if (pre.discard[p][i] == 4 || pre.discard[p][i] == 5 || pre.discard[p][i] == 6)
                        expectedTreasure++;
                i++;
        }
  }

  treasureAfterAdventurer = 0;
  for (i = 0; i < pre.handCount[p]; i++){
        if (post->hand[p][i] == 4 || post->hand[p][i] == 5 || post->hand[p][i] == 6)
                treasureAfterAdventurer++;
  } 
  if (treasureAfterAdventurer != (currentTreasure + expectedTreasure))
	handFailures++;
  //if ((post->deckCount[p] + post->discardCount[p] + post->handCount[p]) != (pre.deckCount[p] + pre.discardCount[p] + pre.handCount[p]))
  handDeckDiscardFailures++;

  //clean everything up, to compare other aspects of the gamestate

  for (i = 0; i < MAX_DECK; i++){
	pre.deck[p][i] = 0;
	pre.discard[p][i] = 0;
	pre.hand[p][i] = 0;
	post->deck[p][i] = 0;
	post->discard[p][i] = 0;
	post->hand[p][i] = 0;
  }

  pre.deckCount[p] = 0;
  pre.discardCount[p] = 0;
  pre.handCount[p] = 0;
  post->deckCount[p] = 0;
  post->discardCount[p] = 0;
  post->handCount[p] = 0;

  if (memcmp(&pre, post, sizeof(struct gameState)) != 0){
	failed = 1;		 
//	printf("failed by %d\n",memcmp(&pre, post, sizeof(struct gameState)));
  }
  
  return failed;

}
















