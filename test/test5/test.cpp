#include "..\..\src\api.h"
#include <cstdlib>

int t = 0;

void CONFIG()
{
	SetWindow("HELLO", 1280, 720);
}


void INIT()
{
	DrawClear();
	for (int i = 0; i < 240; ++i) {
		Color col1(rand()%255, rand()%255, rand()%255);
		DrawRect(Vec2(rand() % 1200, rand() % 640), Vec2(rand() % 100, rand() % 100), col1, 3);
		Color col2(rand()%255, rand()%255, rand()%255);
		DrawRectB(Vec2(rand() % 1200, rand() % 640), Vec2(rand() % 100, rand() % 100), col2, 2);
		Color col3(rand()%255, rand()%255, rand()%255);
		DrawCirc(Vec2(rand()% 1200, rand()%600), rand()%100, col3, 1);
		Color col4(rand()%255, rand()%255, rand()%255);
		DrawCircB(Vec2(rand()% 1200, rand()%600), rand()%100, col4, 0);
	}
}

void MAINLOOP()
{

}

void EXIT()
{
	
}