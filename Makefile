CC=gcc
CFLAGS=-std=gnu11 -lm -Wall
SRC=board.o main.o ai.o

all: $(SRC)
	$(CC) -o main $(SRC) $(CFLAGS) -O3

profile: $(SRC)
	$(CC) -o main $(SRC) $(CFLAGS) -pg

clean:
	rm -f main *.o
