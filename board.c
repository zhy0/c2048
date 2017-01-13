#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "board.h"


bool zero_end(uint32_t v[SIZE])
{
    int i;
    int c = 0;
    bool seen_zero = false;
    bool changed = false;

    for (i = 0; i < SIZE; i++) {
        if (v[i]) {
            v[c++] = v[i];
            if (seen_zero)
                changed = true;
        } else {
            seen_zero = true;
        } 
    }

    while (c < SIZE)
        v[c++] = 0;

    return changed;
}

bool zero_begin(uint32_t v[SIZE])
{
    int i;
    int c = SIZE-1;
    bool changed = false;
    bool seen_zero = false;

    for (i = SIZE-1; i >= 0; i--) {
        if (v[i]) {
            v[c--] = v[i];
            if (seen_zero)
                changed = true;
        } else {
            seen_zero = true;
        }
    }

    while (c >= 0)
        v[c--] = 0;

    return changed;
}

void transpose(uint32_t v[SIZE][SIZE])
{
    int i, j, temp;
    for (i = 0; i < SIZE-1; i++) {
        for (j = i+1; j < SIZE; j++) {
            temp = v[i][j];
            v[i][j] = v[j][i];
            v[j][i] = temp;
        }
    }
}

Change merge_left(uint32_t v[SIZE])
{
    int i;
    int s = 0; // score
    Change c;

    c.moved = zero_end(v);
    for (i = 0; i < SIZE-1; i++) {
        if (v[i] == 0) continue;
        if (v[i] == v[i+1]) {
            s += 2*v[i];
            v[i] = 2*v[i];
            v[i+1] = 0;
        }
    }
    c.score_diff = s;
    if (zero_end(v) || c.score_diff)
        c.moved = true;

    return c;
}

Change merge_right(uint32_t v[SIZE])
{
    int i;
    int s = 0; // score
    Change c;

    c.moved = zero_begin(v);
    zero_begin(v);
    for (i = SIZE-1; i > 0; i--) {
        if (v[i] == 0) continue;
        if (v[i] == v[i-1]) {
            s += 2*v[i];
            v[i] = 2*v[i];
            v[i-1] = 0;
        }
    }
    c.score_diff = s;
    if (zero_begin(v) || c.score_diff)
        c.moved = true;

    return c;
}


bool move(Board *b, int d)
{
    int i;
    Change c;
    merger merge;
    bool board_changed = false;

    merge = (d == UP || d == LEFT) ? merge_left : merge_right;

    if (d == UP || d == DOWN)
        transpose(b->board);
         
    for (i = 0; i < SIZE; i++) {
        c = merge(b->board[i]);
        b->score += c.score_diff;
        if (c.moved)
            board_changed = true;
    }

    if (d == UP || d == DOWN)
        transpose(b->board);

    return board_changed;
}


int count_empty(const Board *b)
{
    int i, j, c;
    c = 0;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (b->board[i][j] == 0) c++;
        }
    }
    return c;
}

bool can_merge(const Board *b)
{
    int i, j;
    for (i = 0; i < SIZE-1; i++) {
        for (j = 0; j < SIZE-1; j++) {
            if (b->board[i][j] == b->board[i+1][j]) return true;
            if (b->board[i][j] == b->board[i][j+1]) return true;
        }
    }

    // check the last column
    for (i = 0; i < SIZE-1; i++)
        if (b->board[i][SIZE-1] == b->board[i+1][SIZE-1]) return true;

    // check the last row
    for (j = 0; j < SIZE-1; j++)
        if (b->board[SIZE-1][j] == b->board[SIZE-1][j+1]) return true;

    return false;
}

bool is_end(const Board *b)
{
    if (count_empty(b)) return false; 
    return can_merge(b) ? false : true;
}

bool is_same(const Board a, const Board b)
{
    int i, j;
    if (a.score != b.score) return false;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            if (a.board[i][j] != b.board[i][j]) return false;
    return true;
}


void fill_random(Board *b)
{
    int i, j, c;
    uint32_t empty[SIZE*SIZE];
    int rand_value, rand_index;

    c = 0;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (b->board[i][j] == 0)
                empty[c++] = i*SIZE + j;  
        }
    }

    if (c == 0) return;

    rand_value = (rand() % 9) ? 2 : 4;
    rand_index =  empty[rand() % c];
    i = rand_index / SIZE;
    j = rand_index % SIZE;
    
    b->board[i][j] = rand_value;
}

void copy(Board *dest, const Board *src)
{
    int i, j;
    dest->score = src->score;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            dest->board[i][j] = dest->board[i][j];
}

void copy_board(Board *dest, const Board *src)
{
    dest->score = src->score;
    memcpy(dest, src, sizeof(Board));
}


Board init_board()
{
    int i, j;
    Board b;
    b.score = 0;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            b.board[i][j] = 0;
    fill_random(&b);
    fill_random(&b);
    return b;
}


void print(const Board b)
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d\t", b.board[i][j]);
        }
        printf("\n");
    }
    printf("\t\t\tScore: %d", b.score); 
    printf("\n");
}

void print_array(const int v[SIZE])
{
    for (int i = 0; i < SIZE; i++)
        printf("%d ", v[i]);
    printf("\n");
}
