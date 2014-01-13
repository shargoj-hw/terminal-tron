CC = clang++
OUTFILE = bin/ccis-hack

all:
	$(CC) --std=c++11 -Wall -g src/*.cpp -lncurses -o $(OUTFILE)

