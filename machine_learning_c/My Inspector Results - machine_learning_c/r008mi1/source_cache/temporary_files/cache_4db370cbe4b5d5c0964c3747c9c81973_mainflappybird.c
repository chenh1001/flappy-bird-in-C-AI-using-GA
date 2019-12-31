#include "mainFlappyBird.h"

int width;
int height;


Pipe closestPipe(Bird* bird, PipesStack* pipes)
{
	if (pipes->top == 0)
	{
		puts("0 pipes");
		return;
	}
	Pipe minPipe = pipes->stack[0];
	double distance = width*width;
	for (int i = 0; i<pipes->top; i++)
	{
		if (pipes->stack[i].x - bird->x < distance && pipes->stack[i].x - bird->x > 10)
		{
			minPipe = pipes->stack[i];
			distance = pipes->stack[i].x - bird->x;
		}
	}
	return minPipe;
}

void think(Bird* bird, PipesStack* pipes)
{
	int inputSize = 5;
	double inputs[5];
	Pipe pipe = closestPipe(bird, pipes);
	inputs[0] = pipe.x / width;
	inputs[1] = pipe.yUpRect / height;
	inputs[2] = pipe.yDownRect / height;
	inputs[3] = bird->y / height;
	inputs[4] = bird->velocity / 10;

	Matrix outputs = NNfeedingForward(inputs, inputSize, bird->brain);
	if (outputs.data[0][0]>outputs.data[0][1])
	{
		birdJump(bird);
	}
	for (int i = 0; i<outputs.rows; i++)
	{
		free(outputs.data[i]);
	}
	free(outputs.data);
	outputs.data = NULL;
}

int main(int argc, char **argv)
{
	// Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	// Create a SDL window
	SDL_Window *window = SDL_CreateWindow("Hello, SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

	// Create a renderer (accelerated and in sync with the display refresh rate)
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_Surface * image = SDL_LoadBMP("E:/blueBall.bmp");
	Uint32 colorkey = SDL_MapRGB(image->format, 255, 255, 255);
	SDL_SetColorKey(image, SDL_TRUE, colorkey);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	bool running = true;
	SDL_Event event;

	Bird **birds = (struct Bird**)malloc(sizeof(Bird) * numOfBirds);
	for (int i = 0; i<numOfBirds; i++)
	{
		birds[i] = (Bird*)malloc(sizeof(Bird));
	}
	for (int i = 0; i < numOfBirds; i++)
	{
		resetBird(birds[i]);
		birds[i]->circle = image;
	}
	
	PipesStack *pipes = (struct PipesStack*)malloc(sizeof(PipesStack));
	pipes->top = 0;
	createPipe(pipes);
	srand(time(0));

	double speed = 1;
	while (running)
	{
		for (double n = 0; n < speed; n++) {

			// Process events
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					running = false;
				}
				if (event.type == SDL_KEYDOWN)
				{
					if (event.key.keysym.sym == SDLK_x) 
					{
						speed *= 2;
					}
					if (event.key.keysym.sym == SDLK_z)
					{
						speed /= 2;
					}
					if (event.key.keysym.sym == SDLK_c)
					{
						speed = 1;
					}
				}
			}
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderClear(renderer);

			pipes = updatePipes(pipes);
		
			for (int i = 0; i < numOfBirds; i++)
			{
				if (birds[i]->isAlive)
				{
					think(birds[i], pipes);
					birdUpdate(birds[i]);
					checkForHits(birds[i], pipes);
				}
			}

			bool flag = false;
			int bestScore = 0;
			for (int i = 0; i < numOfBirds && flag == false; i++)
			{
				if (birds[i]->isAlive)
					flag = true;
				bestScore = max(birds[i]->score, bestScore);
			}
			if (flag == false)//every bird is dead
			{
				printf("%d was the best score\n", bestScore);
				while (isempty(pipes) == false)
					pipes = pop(pipes);
				birds = nextGen(birds);
			
				createPipe(pipes);	
			
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		int rectCounter = 0;
		SDL_Rect* rects = (SDL_Rect*)malloc(sizeof(SDL_Rect) * pipes->top * 2);
		for (int i = 0; i < pipes->top; i++)
		{
			pipes->stack[i].upRect.x = pipes->stack[i].x;
			pipes->stack[i].downRect.x = pipes->stack[i].x;
			SDL_Rect rectUp1 = pipes->stack[i].upRect;
			SDL_Rect rectDown1 = pipes->stack[i].downRect;
			rects[rectCounter] = rectUp1;
			rects[rectCounter + 1] = rectDown1;
			rectCounter += 2;
		}
		SDL_RenderDrawRects(renderer, rects, pipes->top * 2);
		SDL_RenderFillRects(renderer, rects, pipes->top * 2);

		SDL_Rect* birdRects = (SDL_Rect*)malloc(sizeof(SDL_Rect) * numOfBirds);
		int counter = 0;
		for (int i = 0; i < numOfBirds; i++)
		{
			if (birds[i]->isAlive)
			{
				SDL_Rect rect = { birds[i]->x,birds[i]->y,50,50 };
				birdRects[counter] = rect;
				counter++;
			}
		}
		for (int i = 0; i < counter; i++)
		{
			SDL_RenderCopy(renderer, texture, NULL, &birdRects[i]);
		}

		SDL_RenderPresent(renderer);
		free(rects);
		free(birdRects);
	}
	// Release resources
	free(pipes);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

void drawingPipes(PipesStack *pipes)
{
	for (int i = 0; i<pipes->top; i++)
	{
		pipes->stack[i].upRect.x = pipes->stack[i].x;
		pipes->stack[i].downRect.x = pipes->stack[i].x;
	}
}






