#include "mainFlappyBird.h"

int width;
int height;

Pipe closestPipe(Bird* bird, PipesQueue* pipes)//return closest coming pipe to bird
{
	if (pipes->top == 0)
	{
		puts("0 pipes");
		return;
	}
	Pipe minPipe = pipes->queue[0];
	double distance = width*width;
	for (int i = 0; i<pipes->top; i++)
	{
		if (pipes->queue[i].x - bird->x < distance && pipes->queue[i].x - bird->x > 10) // if is ahead of bird and closest
		{
			minPipe = pipes->queue[i];
			distance = pipes->queue[i].x - bird->x;
		}
	}
	return minPipe;
}

void think(Bird* bird, PipesQueue* pipes)//makes bird take action based on nn feed forward
{
	int inputSize = 5;
	double inputs[5];
	Pipe pipe = closestPipe(bird, pipes);
	inputs[0] = pipe.x / width;
	inputs[1] = pipe.yUpRect / height;
	inputs[2] = pipe.yDownRect / height;
	inputs[3] = bird->y / height;
	inputs[4] = bird->velocity / 10;

	Matrix outputs = NNfeedingForward(inputs, inputSize, bird->brain); //get NN output from input
	if (outputs.data[0][0]>outputs.data[0][1])
	{
		birdJump(bird);//jump
	}
	freeMatrix(outputs);
}

int main(int argc, char **argv)
{
	// Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	// Create a SDL window
	SDL_Window *window = SDL_CreateWindow("Hello, SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

	// Create a renderer (accelerated and in sync with the display refresh rate)
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_Surface * image = SDL_LoadBMP("E:/blueBall.bmp"); // get the ball bmp image
	Uint32 colorkey = SDL_MapRGB(image->format, 255, 255, 255);// hide white background
	SDL_SetColorKey(image, SDL_TRUE, colorkey);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);//makes a texture out of the image surface

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);//clear with white background

	bool running = true;
	SDL_Event event;

	Bird **birds = (struct Bird**)malloc(sizeof(Bird) * numOfBirds); // allocate the array of birds pointers
	for (int i = 0; i<numOfBirds; i++)
	{
		birds[i] = (Bird*)malloc(sizeof(Bird));
	}
	for (int i = 0; i < numOfBirds; i++)
	{
		resetBird(birds[i]); //reset bird's vals
		birds[i]->circle = image;
	}
	
	PipesQueue *pipes = (struct PipesQueue*)malloc(sizeof(PipesQueue)); // allocate the pipes queue
	pipes->top = 0;
	createPipe(pipes); //create the first pipe
	srand(time(0)); //reset random

	double speed = 1;

	printf("Press X to make training faster\n");
	printf("Press Z to make training slower\n");
	printf("Press C to make training speed = 1\n");

	while (running)
	{
		for (double n = 0; n < speed; n++) { //speed loop

			// Process events
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT) // if X is preesed quit
				{
					running = false;
				}
				if (event.type == SDL_KEYDOWN) //listen to key events
				{
					if (event.key.keysym.sym == SDLK_x) //if x speed up
					{
						speed *= 2;
					}
					if (event.key.keysym.sym == SDLK_z)// if z slow down
					{
						speed /= 2;
					}
					if (event.key.keysym.sym == SDLK_c)// if  c reset speed
					{
						speed = 1;
					}
				}
			}
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //white background
			SDL_RenderClear(renderer);
		
			for (int i = 0; i < numOfBirds; i++)//action for every bird 
			{
				if (birds[i]->isAlive)
				{
					think(birds[i], pipes);//bird take action
					birdUpdate(birds[i]);//bird update value after action taken
					checkForHits(birds[i], pipes);//check if colided with a pipe
				}
			}

			pipes = updatePipes(pipes);// update pipe values and create new if needed

			bool flag = false;
			int bestScore = 0;
			for (int i = 0; i < numOfBirds && flag == false; i++)//check if every bird is dead and best score
			{
				if (birds[i]->isAlive)
					flag = true;
				bestScore = max(birds[i]->score, bestScore);
			}
			if (flag == false)//every bird is dead
			{
				printf("%d was the best score\n", bestScore);
				while (isempty(pipes) == false)//empty pipes
					pipes = pop(pipes);
				birds = nextGen(birds);//calc next gen of birds and assaign to birds
			
				createPipe(pipes);//create new first pipe 
			
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		int rectCounter = 0;
		SDL_Rect* rects = (SDL_Rect*)malloc(sizeof(SDL_Rect) * pipes->top * 2);//draw pipes
		for (int i = 0; i < pipes->top; i++)
		{
			pipes->queue[i].upRect.x = pipes->queue[i].x;
			pipes->queue[i].downRect.x = pipes->queue[i].x;
			SDL_Rect rectUp1 = pipes->queue[i].upRect;
			SDL_Rect rectDown1 = pipes->queue[i].downRect;
			rects[rectCounter] = rectUp1;
			rects[rectCounter + 1] = rectDown1;
			rectCounter += 2;
		}
		SDL_RenderDrawRects(renderer, rects, pipes->top * 2);
		SDL_RenderFillRects(renderer, rects, pipes->top * 2);

		SDL_Rect* birdRects = (SDL_Rect*)malloc(sizeof(SDL_Rect) * numOfBirds);//draw birds
		int counter = 0;
		for (int i = 0; i < numOfBirds; i++)
		{
			if (birds[i]->isAlive)
			{
				SDL_Rect rect = { birds[i]->x,birds[i]->y,30,30 };
				birdRects[counter] = rect;
				counter++;
			}
		}
		SDL_Rect temp = { width-1,height-1,30,30 }; //bug with sdl - need to draw first texture 

		SDL_RenderCopy(renderer, texture, NULL, &temp);

		for (int i = 0; i < counter; i++)
		{
			SDL_RenderCopy(renderer, texture, NULL, &birdRects[i]); // draw the bird texture 
		}

		SDL_RenderPresent(renderer);//present renderer
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

void drawingPipes(PipesQueue *pipes)
{
	for (int i = 0; i<pipes->top; i++)
	{
		pipes->queue[i].upRect.x = pipes->queue[i].x;
		pipes->queue[i].downRect.x = pipes->queue[i].x;
	}
}






