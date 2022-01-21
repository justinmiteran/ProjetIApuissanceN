all: puissanceN puissanceN.o list.o board.o

list.o: list.c list.h
	gcc -c list.c -lm -g

board.o: board.c board.h
	gcc -c board.c -lm -g

puissanceN: puissanceN.c list.c board.h list.h item.h
	gcc -o puissanceN puissanceN.c board.c list.c -lm -g
