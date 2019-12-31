#ifndef birdHeader
#define birdHeader

#include <stdbool.h>
#include "SDL.h"
#include "NeuralNetwork.h"

typedef struct Birds {
	double fittnes;
	int score;
	int x;
	double y;
	SDL_Surface* circle;
	double velocity;
	bool isAlive;
	NeuralNetwork brain;
} Bird;


void resetBirdNoBrain(Bird* bird);
void birdJump(Bird *bird);
void birdUpdate(Bird *bird);
void resetBird(Bird *bird);
#endif
