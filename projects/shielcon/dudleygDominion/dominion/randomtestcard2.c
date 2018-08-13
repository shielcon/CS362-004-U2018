#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

#define DEBUG 0
#define NOISY_TEST 1

int functionFailures = 0;
int currentPlayerHandFailure = 0;
int currentPlayerDiscardCountFailure = 0;
int currentPlayerDeckCountFailure = 0;
int currentPlayerPileFailure = 0;
int otherPlayerHandCountFailure = 0;
int otherPlayerDiscardCountFailure = 0;
int otherPlayerDeckCountFailure = 0;
int otherPlayerPileFailure = 0;
int numBuysFailure = 0;


int RandomTestCouncilRoom(int p, struct gameState *post, int handPos){

  int i;
  int failed = 0;
  struct gameState pre;
  memcpy(&pre, post, sizeof(struct gameState));
  
  council_roomCard(post, p, handPos);

  if (post->handCount[p] != pre.handCount[p] + 3){
	currentPlayerHandFailure++;
	failed = 1;
  }
  if (pre.deckCount[p] > 3){
    if (post->discardCount[p] != pre.discardCount[p]){
	currentPlayerDiscardCountFailure++;
	failed = 1;
    }
    if (post->deckCount[p] != pre.deckCount[p] - 4){
	currentPlayerDeckCountFailure++;
	failed = 1;
    }
  }
  else {
	if ((post->deckCount[p] + post->discardCount[p]) != (pre.deckCount[p] + pre.discardCount[p] - 4))   {
	currentPlayerPileFailure++;
	failed = 1;
	}
  }
  for (i = 0; i < post->numPlayers; i++){
	if (i != p){
		if (post->handCount[i] != pre.handCount[i] + 1){
			otherPlayerHandCountFailure++;
			failed = 1;
		}
		if (pre.deckCount[i] > 1){
			if (post->deckCount[i] != pre.deckCount[i] - 1){
				otherPlayerDeckCountFailure++;
				failed = 1;
			}
			if (post->discardCount[i] != pre.discardCount[i]){
				otherPlayerDiscardCountFailure++;
				failed = 1;
			}
		}
		else {
			if ((post->deckCount[i] + post->discardCount[i])
			    != (pre.deckCount[i] + pre.discardCount[i]) - 1){
				otherPlayerPileFailure++;
				failed = 1;
			}
		}
  	}
  }

  if (post->numBuys != pre.numBuys + 1){
	numBuysFailure++;
	failed = 1;
  }

  return failed;
}

int main(){

  printf("Testing Council Room\n");

  struct gameState G;
  int i, j, n, r, p, failures, handPos;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};

  SelectStream(2);
  PutSeed(3);

  failures = 0;
  for (n = 0; n < 100000; n++){
  	for (j = 0; j < sizeof(struct gameState); j++) {
       		((char*)&G)[j] = floor(Random() * 256);
  	}
        G.numPlayers = floor(Random() * 3) + 1;
        G.whoseTurn = floor(Random() * G.numPlayers);
        p = G.whoseTurn;

  	for (i = 0; i < G.numPlayers; i++){
		G.deckCount[i] = floor(Random() * MAX_DECK);
                G.discardCount[i] = floor(Random() * MAX_DECK);
                G.handCount[i] = floor(Random() * MAX_DECK);
        	for (j = 0; j < G.deckCount[i]; j++)
                	G.deck[i][j] = floor(Random() * 28);
        	for (j = 0; j < G.discardCount[i]; j++)
                	G.discard[i][j] = floor(Random() * 28);
        	for (j = 0; j < G.handCount[i]; j++)
                	G.hand[i][j] = floor(Random() * 28);
	}
  
        handPos = (Random() * G.handCount[p]);
        G.playedCardCount = floor(Random() * MAX_DECK);
        failures += RandomTestCouncilRoom(p, &G, handPos);
  }


  if (failures > 0){
	printf("failed: failures: %d\n", failures);
	printf("function Failures: %d\nCurrent player hand failures:  %d\ncurrent player discard count failures: %d\ncurrent player deck count failures: %d\ncurrent player total card pile failures: %d\nother player handcount failures: %d\nother player discard count failures: %d\nother player deck count railures: %d\nother player total card pile failures: %d\nnumber of buys failures: %d\n", functionFailures, currentPlayerHandFailure, currentPlayerDiscardCountFailure, currentPlayerDeckCountFailure, currentPlayerPileFailure, otherPlayerHandCountFailure, otherPlayerDiscardCountFailure, otherPlayerDeckCountFailure, otherPlayerPileFailure, numBuysFailure);
  }
/*
int functionFailures = 0;
int currentPlayerHandFailure = 0;
int currentPlayerDiscardCountFailure = 0;
int currentPlayerDeckCountFailure = 0;
int currentPlayerPileFailure = 0;
int otherPlayerHandCountFailure = 0;
int otherPlayerDiscardCountFailure = 0;
int otherPlayerDeckCountFailure = 0;
int otherPlayerPileFailure = 0;
*/
  else
        printf("All tests passed\n");

  return 0;

}
