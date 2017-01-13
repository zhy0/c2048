#ifndef __board_h__
#define __board_h__
#include <stdbool.h>
#include <stdint.h>

#define RIGHT 0
#define LEFT  1
#define UP    2
#define DOWN  3

/* Board size */
#define SIZE  4

typedef struct Board {
    uint32_t board[SIZE][SIZE];
    int score;
} Board;

typedef struct Change {
    int score_diff;
    bool moved;
} Change;

typedef Change (*merger)(uint32_t v[SIZE]);

bool zero_end(uint32_t v[SIZE]);
bool zero_begin(uint32_t v[SIZE]);
void transpose(uint32_t v[SIZE][SIZE]);
Change merge_left(uint32_t v[SIZE]);
Change merge_right(uint32_t v[SIZE]);

bool move(Board *b, int d);
void fill_random(Board *b);

int count_empty(const Board *b);
bool can_merge(const Board *b);
bool is_end(const Board *b);
bool is_same(const Board a, const Board b);
void copy_board(Board *dest, const Board *src);


void print_array(const int v[SIZE]);
void print(const Board b);
Board init_board();

#endif
