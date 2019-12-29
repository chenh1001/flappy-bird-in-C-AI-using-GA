#include "mainFlappyBird.h"

int width;
int height;

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

	Bird *bird = (struct Bird*)malloc(sizeof(Bird));
	resetBird(bird);
	bird->circle = image;

	
	PipesStack *pipes = (struct PipesStack*)malloc(sizeof(PipesStack));
	pipes->top = 0;
	createPipe(pipes);
	srand(time(0));

	while (running)
	{
		// Process events
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
				birdJump(bird);
			}
		}
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		birdUpdate(bird);
		updatePipes(pipes);
		checkForHits(bird, pipes);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		int rectCounter = 0;
		SDL_Rect* rects = (SDL_Rect*)malloc(sizeof(SDL_Rect) * pipes->top*2);
		for (int i = 0; i<pipes->top; i++)
		{
			pipes->stack[i].upRect.x = pipes->stack[i].x;
			pipes->stack[i].downRect.x = pipes->stack[i].x;
			SDL_Rect rectUp1 = pipes->stack[i].upRect;
			SDL_Rect rectDown1 = pipes->stack[i].downRect;
			rects[rectCounter] = rectUp1;
			rects[rectCounter + 1] = rectDown1;
			rectCounter += 2;
		}
		SDL_RenderDrawRects(renderer, rects, pipes->top*2);
		SDL_RenderFillRects(renderer, rects, pipes->top * 2);

		if (bird->isAlive == false)
		{
			while (isempty(pipes) == false)
				pop(pipes);
			createPipe(pipes);
			resetBird(bird);
		}
		// Clear screen with black
		SDL_Rect ballRect = { bird->x,bird->y,50,50 };
		SDL_RenderCopy(renderer, texture, NULL, &ballRect);
		SDL_RenderPresent(renderer);

	}
	// Release resources
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



