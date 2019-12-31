#ifndef StackHeader
#define StackHeader
#include "pipe.h"


typedef struct PipesQueues {
	int top;
	Pipe queue[10];
} PipesQueue;

int isempty(PipesQueue *stack);
int isfull(PipesQueue *stack);
Pipe peek(PipesQueue *stack);
PipesQueue* pop(PipesQueue *stack);
void push(Pipe data, PipesQueue *stack);
PipesQueue* updatePipes(PipesQueue *pipes);
void createPipe(PipesQueue *pipes);

#endif

