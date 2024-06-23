#include "Animation.h"

using namespace sf;

Animation::Animation(IntRect* rect, int framesNumber)
{
	bounds = rect;
	fps = framesNumber;
	Value_reset = rect->left;
}

void Animation::Frame_changer()
{
	if (CLK.getElapsedTime().asSeconds() >= 0.1f)
	{
		if (bounds->left >= (Value_reset + 15 * (fps - 1)))
		{
			bounds->left = Value_reset;
		}
		else
		{
			bounds->left += 15;
		}
		CLK.restart();
	}
}

IntRect Animation::getBounds()
{
	return *bounds;
}