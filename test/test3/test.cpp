#include "..\..\src\api.h"

#include <cstdlib>

int t = 0;

void CONFIG()
{
	SetWindow("HELLO", 240, 160);
}


void INIT()
{
	DrawClear();
}

void MAINLOOP()
{
	if (t % 10 == 0) {
		int x1 = rand() % 240;
		int x2 = rand() % 240;
		Color col(rand() % 256, rand() % 256, rand() % 256);

		DrawLine(Vec2(x1, 0), Vec2(x2, 159), col);
	}

	++t;
}

void EXIT()
{
}