#ifndef StackHeader
#define StackHeader
#include "pipe.h"


typedef struct PipesStacks {
	int top;
	Pipe stack[10];
} PipesStack;

int isempty(PipesStack *stack);
int isfull(PipesStack *stack);
Pipe peek(PipesStack *stack);
Pipe pop(PipesStack *stack);
void push(Pipe data, PipesStack *stack);

void updatePipes(PipesStack *pipes);
void createPipe(PipesStack *pipes);

#endif

