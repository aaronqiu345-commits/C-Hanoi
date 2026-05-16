#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

typedef struct Stack {
    char name;
    int top;
    int capacity;
    int* items;
} Stack;

Stack * stackCreate(int capacity, char name) {
 Stack *s = (Stack *)malloc(sizeof(Stack));

 s->capacity = capacity;
 s-> top = -1;
 s-> name = name;
 s-> items = (int*)malloc(sizeof(int) * capacity);
 return s;
}

void stackDelete(Stack *s) {
    free(s->items);
    free(s);
}

int stackEmpty(Stack *s) {
    return s->top == -1;
}

int stackPop(Stack *s) {
    if (stackEmpty(s)) {
        return -1;
    }
    return s->items[s->top--];
}

void stackPush(Stack *s, int item) {
    if (s->top == s->capacity - 1) {
        printf("Stack full; can't push\n");
        return;
    }
    s++;
    s->items[s->top] = item;
}

int stackPeek(Stack *s) {
 // returns top value of stack
    if (stackEmpty(s)) {
        return -1;
    }

    return s->items[s->top];
}

int moveDisc(Stack *source, Stack *target) {
    int topSource = stackPeek(source);
    int topTarget = stackPeek(target);
    if (topSource == -1) {
        int discToMove = stackPop(target);
        stackPush(source, discToMove);
        printf("Moving %d from %c to %c \n", discToMove, target->name, source->name);
        return 0;
    }
    if (topTarget == -1) {
        int discToMove = stackPop(source);
        stackPush(target, discToMove);
        printf("Moving %d from %c to %c \n", discToMove, source->name, target->name);
        return 0;
    }

    if (topTarget < topSource) {
        int discToMove = stackPop(target);
        stackPush(source, discToMove);
        printf("Moving %d from %c to %c \n", discToMove, target->name, source->name);
    }
    else {
        int discToMove = stackPop(source);
            stackPush(target, discToMove);
            printf("Moving %d from %c to %c \n", discToMove, source->name, target->name);
        }
    return 0;
}

int count = 0;
int recurHanoi(int n, Stack *source, Stack *target, Stack *auxil) {
    if (n > 0) {
        count++;
        recurHanoi(n-1, source, auxil, target);
        printf("Moving %d from %c to %c \n", n, source->name, target->name);
        recurHanoi(n-1, auxil, target, source);
    }
    return 0;
}

void iterHanoi(int n, Stack *s, Stack *t, Stack *a) {
    int max = (1 << n) - 1;
    int count = 0;
    for (int i = 1; i <= max; i++) {
        count += 1;
        if (i % 3 == 1) {
            moveDisc(s, t);
        }
        else if (i % 3 == 2) {
            moveDisc(s, a);
        }
        else {
            moveDisc(t, a);
        }
    }
    printf("Moves taken: %d\n", count);
}

int main(int argc, char* argv[]) {
    int n = 3;
    int opt;

    Stack* A = stackCreate(n, 'A');
    Stack* B = stackCreate(n, 'B');
    Stack* C = stackCreate(n, 'C');

    for (int x = n; x >= 1; x--) {
        stackPush(A, x);
    }

    while ((opt = getopt(argc, argv, "n:si")) != -1) {
        switch(opt) {
            case 'n':
                n = atoi(optarg);
                break;

            case 's':
                iterHanoi(n, A, C, B);
                break;
            
            case 'i':
                recurHanoi(n, A, C, B);
                printf("Moves taken: %d\n", count);
                break;
        }
    }
    stackDelete(A);
    stackDelete(B);
    stackDelete(C);
    return 0;
}

#endif
