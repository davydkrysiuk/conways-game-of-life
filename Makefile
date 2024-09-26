all: gameoflife.c
	gcc gameoflife.c -o gol -Wextra -Wall -lncurses
