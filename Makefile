CFLAGS=-Wall -Wextra -Werror -pedantic
CC=clang $(CFLAGS)

all: hanoi

hanoi: hanoi.c
	$(CC) $(CFLAGS) hanoi.c -o hanoi