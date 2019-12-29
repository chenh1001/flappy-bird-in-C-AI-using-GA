#include "bird.h"

extern int width = 800;
extern int height = 600;

static const double JUMP_POWER = 10;
static const double GRAVITY = 0.3;


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

void resetBird(Bird* bird)
{
	bird->velocity = 0;
	bird->fittnes = 0;
	bird->score = 0;
	bird->x = 30;
	bird->y = height / 2;
	bird->isAlive = true;
}
