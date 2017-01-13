#ifndef __ai_h__
#define __ai_h__

#define CPROB_THRESHOLD 0.001f

typedef struct action {
    float score;
    int move;
} action;

float evalfn(const Board *b);
action expectimax(const Board *b, int depth, int agent, float cprob);

#endif
