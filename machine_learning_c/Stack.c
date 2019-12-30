#include "Stack.h"

const int MAXSIZE = 10;

int width;
int height;

int isempty(PipesStack *stack) {

	if (stack->top == 0)
		return 1;
	else
		return 0;
}

int isfull(PipesStack *stack) {

	if (stack->top == MAXSIZE -1)
		return 1;
	else
		return 0;
}

Pipe peek(PipesStack *stack)
{
	if (!isempty(stack))
	{		
		return stack->stack[0];
	}
}
Pipe pop(PipesStack *stack) {
	Pipe data;

	if (!isempty(stack)) {
 		data = stack->stack[0];
		stack->top -= 1;

  		PipesStack *pipes = (struct PipesStack*)malloc(sizeof(PipesStack));
		int newTop = 0;
		for (int i = 1; i <= stack->top; i++)
		{
			pipes->stack[i - 1] = stack->stack[i];
			newTop++;
		}
		pipes->top = newTop;
		*stack = *pipes;
		free(pipes);
		return data;
	}
	else {
		puts("Could not retrieve data, Stack is empty.\n");
	}
}

void push(Pipe data, PipesStack *stack) {

	if (!isfull(stack)) {
		stack->stack[stack->top] = data;
		stack->top = stack->top + 1;
	}
	else {
		puts("Could not insert data, Stack is full.\n");
	}
}


void createPipe(PipesStack *pipes)
{
	Pipe pipe;
	pipe.space = 250;
	pipe.x = width;
	int num = (rand() % (height- (int)pipe.space + 1));
	pipe.yUpRect = num;
	pipe.yDownRect = num + pipe.space;
	pipe.width = 50;
	SDL_Rect rect = { pipe.x,0,30,pipe.yUpRect };
	pipe.upRect = rect;
	SDL_Rect rect2 = { pipe.x,pipe.yDownRect,30,height - pipe.yDownRect };
	pipe.downRect = rect2;
	push(pipe, pipes);
}



void updatePipes(PipesStack *pipes)
{
	for (int i = 0; i<pipes->top; i++)
	{
		pipes->stack[i].x-=5;
	}
	if (pipes->top > 0)
	{
		Pipe first = peek(pipes);

		if (pipes->top > 0 && first.x < 0)
		{
			pop(pipes);
		}
		for (int i = 0; i<pipes->top; i++)
		{
			if (pipes->stack[i].x == 200)
				createPipe(pipes);
		}
	}
	else
		createPipe(pipes);
}

void checkForHits(Bird* bird, PipesStack *pipes)
{
	for (int i = 0; i<pipes->top; i++)
	{
		if (hits(bird, pipes->stack[i]))
			bird->isAlive = false;
	}
}

