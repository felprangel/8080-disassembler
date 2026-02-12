CFLAGS=-std=c17 -Wall -Wextra -Werror `sdl2-config --cflags --libs`

all:
	gcc disassembler.c -o disassembler $(CFLAGS)