#include "bird.h"
#include "SDL.h"

extern int width = 800;
extern int height = 600;

static const double JUMP_POWER = 5;
static const double GRAVITY = 0.2;
int startingX = 50;


void birdJump(Bird* bird)
{
	//if (bird->velocity >= 0)
		bird->velocity -= JUMP_POWER;
}

void birdUpdate(Bird* bird) 
{
	bird->score++;
	bird->velocity += GRAVITY;
	bird->y += bird->velocity;
	if (bird->y > height || bird->y < 0)
	{
		bird->score /= 2;
		bird->isAlive = false;
	}
}

void resetBirdNoBrain(Bird* bird)
{
	bird->velocity = 0;
	bird->fittnes = 0;
	bird->score = 0;
	bird->x = startingX;
	bird->y = randBetweenZeroAndOne() * height / 2 + height / 4;
	bird->isAlive = true;
}

void resetBird(Bird* bird)
{
	bird->velocity = 0;
	bird->fittnes = 0;
	bird->score = 0;
	bird->x = startingX;
	bird->y = randBetweenZeroAndOne() * height / 2 + height / 4;
	bird->isAlive = true;
	bird->brain = newNeuralNetwork(5, 8, 2);
	SDL_Surface * image = SDL_LoadBMP("E:/blueBall.bmp");
	Uint32 colorkey = SDL_MapRGB(image->format, 255, 255, 255);
	SDL_SetColorKey(image, SDL_TRUE, colorkey);
	bird->circle = image;
}

