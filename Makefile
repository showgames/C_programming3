#Makefile
main: main.c game.c game.h
		gcc -Wall -o main main.c game.c
