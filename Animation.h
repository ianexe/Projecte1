#pragma once
#include "p2DynArray.h"

class Animation
{
public:
	float speed;
	p2DynArray<SDL_Rect> frames;
	bool loop;

private:
	float current_frame;

public:
	Animation() : frames(5), speed(1.0f), current_frame(0), loop(true)
	{}

	SDL_Rect& GetCurrentFrame()
	{
			current_frame += speed;
		if (current_frame >= frames.Count() && loop == false)
			current_frame -= speed;
		if(current_frame >= frames.Count() && loop == true)
			current_frame = 0;

		return frames[(int)current_frame];
	}

	const float getFrame() const
	{
		return current_frame;
	}

	const void setToZero()
	{
		current_frame = 0;
	}

};