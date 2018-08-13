#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

#define DEBUG 0
#define NOISY_TEST 1

int coinFailures = 0;
int stateFailures = 0;
int choice1Failures = 0;
int choice2Failures = 0;
int choice3Failures = 0;

int stewardRandomTest(int p, struct gameState *post, int choice1, int choice2, int choice3, int handPos);


int main(){

  printf("Testing Steward\n");

  struct gameState G;
  int i, j, n, r, p, deckCount, discardCount, handCount, failures, choice1, choice2, choice3, handPos;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};

  SelectStream(2);
  PutSeed(3);

  failures = 0;
  for (i = 0; i < 10000; i++){
        for (j = 0; j < sizeof(struct gameState); j++) {
            ((char*)&G)[j] = floor(Random() * 256);
        }
        p = floor(Random() * 2);
        G.deckCount[p] = floor(Random() * MAX_DECK);
        for (n = 0; n < G.deckCount[p]; n++)
                G.deck[p][n] = floor(Random() * 28);
	G.discardCount[p] = floor(Random() * MAX_DECK);
        for (n = 0; n < G.discardCount[p]; n++)
                G.discard[p][n] = floor(Random() * 28);

        G.handCount[p] = floor(Random() * MAX_HAND);
        for (n = 0; n < G.handCount[p]; n++)
                G.hand[p][n] = floor(Random() * 28);
        choice1 = floor(Random() * 4);
	choice2 = (Random() * 4);
	choice3 = (Random() * 4);
	handPos = (Random() * G.handCount[p]);
	G.playedCardCount = floor(Random() * MAX_DECK);
        failures += stewardRandomTest(p, &G, choice1, choice2, choice3, handPos);
  }

  if (failures > 0)
	printf("Some tests failed. Total failures: %d\nFailures for choice 1: %d\nFailures for choice 2: %d\nFailures for choice 3: %d\nCases where the state was incorrectly changed - indeterminant by this test case: %d\n", failures, choice1Failures, choice2Failures, choice3Failures, stateFailures);

  else
        printf("All tests passed\n");

  return 0;

}

int stewardRandomTest(int p, struct gameState *post, int choice1, int choice2, int choice3, int handPos){

  struct gameState pre;
  int i;
  int failures = 0;
  post->whoseTurn = p;
  updateCoins(p, post, 0);
  memcpy(&pre, post, sizeof(struct gameState));
if (memcmp(&pre, post, sizeof(struct gameState)) != 0){
        printf("Change\n");
  }


  cardEffect(steward, choice1, choice2, choice3, post,  handPos, NULL);



  //Manually create Steward behavior for pre
  if (choice1 == 1){
	drawCard(p, &pre);
	drawCard(p, &pre);
	discardCard(handPos, p, &pre, 0);
	if (pre.handCount[p] != post->handCount[p]){
		choice1Failures++;
		failures++;
	}
	else if (pre.discardCount[p] != post->discardCount[p]){
		choice1Failures++;
		failures++;
	}
	else if (pre.coins != post->coins){
		choice1Failures++;
		failures++;
	}
  }
  else if (choice1 == 2){
	pre.coins += 2;
	discardCard(handPos, p, &pre, 0);
	if (pre.coins != post->coins){
		choice2Failures++;
		failures++;
	}
  }
  else{
	discardCard(choice2, p, &pre, 1);
	discardCard(choice3, p, &pre, 1);
	discardCard(handPos, p, &pre, 0);
	if (pre.handCount[p] != post->handCount[p]){
		choice3Failures++;
		failures++;
	}
	else if (pre.discardCount[p] != post->discardCount[p]){
		choice3Failures++;
		failures++;
	}
	else if (pre.coins != post->coins){
		choice3Failures++;
		failures++;
	}
  }

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
  pre.coins = 0;
  post->coins = 0;


  if (memcmp(&pre, post, sizeof(struct gameState)) != 0){
  	stateFailures++;
  }

  return failures;

}








