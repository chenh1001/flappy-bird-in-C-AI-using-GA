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
PipesStack* pop(PipesStack *stack);
void push(Pipe data, PipesStack *stack);
PipesStack* updatePipes(PipesStack *pipes);
void createPipe(PipesStack *pipes);

#endif

