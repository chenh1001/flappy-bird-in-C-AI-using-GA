#include "bird.h"

extern int width = 800;
extern int height = 600;

static const double JUMP_POWER = 10;
static const double GRAVITY = 0.3;

Bird* newBird(Bird* bird)
{
	Bird* temp = (Bird*)malloc(sizeof(Bird));
	temp->velocity = 0;
	temp->fittnes = 0;
	temp->score = 0;
	temp->x = 30;
	temp->y = randBetweenZeroAndOne() * height / 2 + height / 4;
	temp->isAlive = true;
	temp->brain = copyNeuralNetwork(bird->brain);
	temp->circle = bird->circle;

	return temp;
}

void birdJump(Bird* bird)
{
	if (bird->velocity >= 0)
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


void resetBird(Bird* bird)
{
	bird->velocity = 0;
	bird->fittnes = 0;
	bird->score = 0;
	bird->x = 30;
	bird->y = randBetweenZeroAndOne() * height / 2 + height / 4;
	bird->isAlive = true;
	bird->brain = newNeuralNetwork(5, 8, 2);
}

