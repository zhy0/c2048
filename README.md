# c2048
Game engine and Expectimax AI for 2048 in C.
Simply clone and make:

    $ git clone https://github.com/zhy0/c2048.git
    $ make
    $ ./main

Default player is the AI. You can change this
to human in the `main` function in `main.c`.

For a different board size, change the value of
`SIZE` in `board.h`. Make sure you run `make clean`
before `make`.

The expectimax algorithm currently uses a very
basic (but quite powerful) evaluation function: the number of empty tiles.
The depth is also determined by the number of empty
tiles: The game is more likely to end if there are fewer
empty tiles and the AI can search deeper since there are
fewer branches to evaluate.

The AI usually achieves the 2048 tile and in some cases the
4096 tile. 
