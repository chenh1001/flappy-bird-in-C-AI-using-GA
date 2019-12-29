#ifndef pipeHeader
#define pipeHeader
#include <time.h>
#include "bird.h"

int width;
int height;

typedef struct Pipes {
	bool isOveriteable;
	double space;
	double x;
	double yUpRect;
	double yDownRect;
	double width;
	SDL_Rect upRect;
	SDL_Rect downRect;
} Pipe;

/*struct Pipes newPipe() {
	double space = 150;
	double x = width;
	srand(time(NULL));
	int num = (rand() % (height - 150 + 1)) + 150;
	double yUpRect = num;
	double yDownRect = num + 150;
	double pipeWidth = 50;
	SDL_Rect upRect = { x,0,pipeWidth,yUpRect };
	SDL_Rect downRect = { x,yDownRect,pipeWidth,height - yDownRect };
}*/

bool hits(Bird *bird, Pipe pipe);

#endif
