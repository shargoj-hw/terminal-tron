CC = clang++
OUTFILE = bin/ccis-hack

all:
	$(CC) -Wall -g src/*.cpp -lncurses -o $(OUTFILE)

