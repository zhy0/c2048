#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> // infinity 
#include <stdint.h>
#include <stdbool.h>
#include "board.h"
#include "ai.h"


/* Heuristics function */
float evalfn(const Board *b)
{
    //return b->score;
    return count_empty(b);
}


extern uint64_t numtries;

action expectimax(const Board *b, int depth, int agent, float cprob)
{
    int i, j;
    float empty, p;
    action best, next;
    Board new;
    numtries++;

    if (depth == 0 || cprob < CPROB_THRESHOLD) {
        best.score = evalfn(b);
        best.move = 0;
        return best;
    }
    if (is_end(b)) {
        best.score = -1;
        best.move = 0;
        return best;
    }

    memcpy(&new, b, sizeof(Board));

    if (agent == 0) {
        best.score = -INFINITY;
        best.move = 0;
        for (i = 0; i < 4; i++) {
            memcpy(&new, b, sizeof(Board));
            if (!move(&new, i)) continue; 
            next = expectimax(&new, depth-1, (agent+1)%2, cprob);
            if (next.score > best.score) {
                best.score = next.score;
                best.move = i;
            }
        }
        
    } else {
        best.score = 0;
        best.move = 0;
        empty = count_empty(b);
        if (empty == 0)
            return expectimax(b, depth-1, (agent+1)%2, cprob);
        p = 1.0/empty;

        for (i = 0; i < SIZE; i++) {
            for (j = 0; j < SIZE; j++) {
                if (b->board[i][j] == 0) {
                    new.board[i][j] = 2;
                    next = expectimax(&new, depth-1, (agent+1)%2, cprob*p*0.9);
                    best.score += p*next.score * 0.9;

                    new.board[i][j] = 4;
                    next = expectimax(&new, depth-1, (agent+1)%2, cprob*p*0.1);
                    best.score += p*next.score * 0.1;

                    new.board[i][j] = 0;
                }
            }
        }
    }

    return best;
}
