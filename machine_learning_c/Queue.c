#include "Queue.h"

const int MAXSIZE = 10;

int width;
int height;

int isempty(PipesQueue *queue) {//is Queue Empty

	if (queue->top == 0)
		return 1;
	else
		return 0;
}

int isfull(PipesQueue *queue) {//is Queue full

	if (queue->top == MAXSIZE -1)
		return 1;
	else
		return 0;
}

Pipe peek(PipesQueue *queue)//returns the first pipe without removal
{
	if (!isempty(queue))
	{		
		return queue->queue[0];
	}
}
PipesQueue* pop(PipesQueue *queue) //returns the first pipe with removal
{
	Pipe data;
	if (!isempty(queue)) {
 		data = queue->queue[0];
		queue->top -= 1;
		PipesQueue *pipes = (struct PipesQueue*)malloc(sizeof(PipesQueue));//create new Queue on memory without the first pipe
		int newTop = 0;
		for (int i = 1; i <= queue->top; i++)
		{
			pipes->queue[i - 1] = queue->queue[i];
			newTop++;
		}
		pipes->top = newTop;
		free(queue);
		queue = pipes;
		pipes = NULL;
		//return data;
		return queue;
	}
	else {
		puts("Could not retrieve data, queue is empty.\n");
	}
}

void push(Pipe data, PipesQueue *queue) //pushes a new pipe to the queue
{
	if (!isfull(queue)) {
		queue->queue[queue->top] = data;
		queue->top = queue->top + 1;
	}
	else {
		puts("Could not insert data, queue is full.\n");
	}
}


void createPipe(PipesQueue *pipes)//creates a new pipe and adds it to the queue
{
	Pipe pipe;
	pipe.space = 150;
	pipe.x = width;
	int num = (rand() % (height- (int)pipe.space + 1));
	pipe.yUpRect = num;
	pipe.yDownRect = num + pipe.space;
	pipe.width = 50;
	SDL_Rect rect = { pipe.x,0,pipe.width,pipe.yUpRect };
	pipe.upRect = rect;
	SDL_Rect rect2 = { pipe.x,pipe.yDownRect,pipe.width,height - pipe.yDownRect };
	pipe.downRect = rect2;
	push(pipe, pipes);
}



PipesQueue* updatePipes(PipesQueue *pipes)//updates the pipes value
{
	for (int i = 0; i<pipes->top; i++)
	{
		pipes->queue[i].x-=5;
	}

	if (pipes->top > 0)
	{
		Pipe first = peek(pipes);
		if (pipes->top > 0 && first.x < 0)
		{
			pipes = pop(pipes);
		}
		for (int i = 0; i<pipes->top; i++)
		{
			if (pipes->queue[i].x == 200)
			{
				createPipe(pipes);
			}
		}
	}
	else
		createPipe(pipes);
	return pipes;
}

void checkForHits(Bird* bird, PipesQueue *pipes)//checks if a bird is hited by a pipe
{
	for (int i = 0; i<pipes->top; i++)
	{
		if (hits(bird, pipes->queue[i]))
			bird->isAlive = false;
	}
}

