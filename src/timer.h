#pragma once
#include <SDL.h>

struct Timer
{
	Timer(): t(0), ticking(0) { }
	Timer& start()
	{
		if (!ticking) {
			t = SDL_GetTicks() - t;
			ticking = 1;
		}
		return *this;
	}
	Timer& stop()
	{
		if (ticking) {
			t = SDL_GetTicks() - t;
			ticking = 0;
		}
		return *this;
	}
	Timer& reset()
	{
		t = 0;
		ticking = 0;
		return *this;
	}
	int get()
	{
		if (ticking) return SDL_GetTicks() - t;
		else return t;
	}

private:
	Uint32 t;
	int ticking;
};