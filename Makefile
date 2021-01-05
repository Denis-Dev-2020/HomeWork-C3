CFLAGS = -O3 -fPIC -g -Wall -Werror
CC = gcc
all : Main Sort Execute
.PHONY : clean
clean :
	rm *.o
Sort : isort.c
	$(CC) isort.c -o isort
Main : txtfind.c
	$(CC)  txtfind.c -o txtfind
Execute : txtfind
	./isort
	./txtfind<input.txt