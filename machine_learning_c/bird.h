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

/*struct Birds newBird() {
	double fittnes = 0;
	int score = 0;
	int x = 30;
	double y = height / 2;
	SDL_Surface* circle;
	double velocity = 0;
	bool isAlive = true;
}*/
Bird* newBird(Bird* bird);
void birdJump(Bird *bird);
void birdUpdate(Bird *bird);
void resetBird(Bird *bird);
#endif
