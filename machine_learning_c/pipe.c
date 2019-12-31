#include "pipe.h"


bool hits(Bird *bird, Pipe pipe)//check if a bird is colliding the given pipe
{
	if (bird->x >= pipe.x && bird->x <= pipe.x + pipe.width && bird->y < pipe.yUpRect || bird->x >= pipe.x && bird->x <= pipe.x + pipe.width && bird->y > pipe.yDownRect)
	{
		return true;
	}
	return false;
}


