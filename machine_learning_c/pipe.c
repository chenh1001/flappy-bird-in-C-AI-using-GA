#include "pipe.h"


bool hits(Bird *bird, Pipe pipe)
{
	if (bird->x >= pipe.x && bird->x <= pipe.x + pipe.width && bird->y < pipe.yUpRect || bird->x >= pipe.x && bird->x <= pipe.x + pipe.width && bird->y > pipe.yDownRect)
	{
		return true;
	}
	return false;
}


