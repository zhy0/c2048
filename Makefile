CC=gcc
CFLAGS=-std=gnu11 -lm -Wall
SRC=board.o main.o ai.o
TEST=board.o test.o ai.o

all: $(SRC)
	$(CC) -o main $(SRC) $(CFLAGS) -O3

test: $(TEST)
	$(CC) -o test $(TEST) $(CFLAGS)

profile: $(SRC)
	$(CC) -o main $(SRC) $(CFLAGS) -pg

clean:
	rm -f main *.o
