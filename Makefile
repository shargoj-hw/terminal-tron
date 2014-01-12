CC = clang++
OUTFILE = bin/ccis-hack

all:
	$(CC) -g src/*.cpp -o $(OUTFILE)

