#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "board.h"
#include "ai.h"

#define STOP -1
#define UNKN -2

typedef int (*get_move)(Board b);

int human(Board b)
{
    char c;
    int d;

    c = getchar();
    if (c == 'w') {
        d = UP;
    } else if (c == 's') {
        d = DOWN;
    } else if (c == 'a') {
        d = LEFT;
    } else if (c == 'd') {
        d = RIGHT;
    } else if (c == 'q') {
        d = STOP;
    } else {
        d = UNKN;
    }
    return d;
}

unsigned long long numtries = 0;
static int empty_depth[16] = {8,7,6,5,5,4,4,4,4,4,4,4,4,3,3,3};

int drunk(Board b)
{
    return rand() % 4;
}

int ai(Board b)
{
    action a;
    int depth;
    int free = count_empty(&b);

    //depth = free > 7 ? 2 : (free > 4 ? 3 : 4);
    depth = empty_depth[free];
    //depth = 2;

    a = expectimax(&b, depth*2, 0, 1.0);
    printf("DEPTH = %d\n", depth);
    return a.move;
}

int main(void)
{
    int d;
    get_move mover = ai;
    setbuf(stdout, NULL);
    

    Board b;
    Board temp;
    b = init_board();

    print(b);

    while (!is_end(&b)) {
        d = mover(b);
        if (d == STOP) break;
        if (d == UNKN) continue;
        
        copy_board(&temp, &b);
        if (move(&b, d))
            fill_random(&b);
        else
            continue;

        print(b);
    }
    printf("%llu\n", numtries);
}
