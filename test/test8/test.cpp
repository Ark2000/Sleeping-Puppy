#include "..\..\src\api.h"

void CONFIG()
{
	SetWindow("TEXT TEST", 640, 360);
}


void INIT()
{
	DrawClear(0xf0f0f0ff);
	Print("The quick brown fox \njumps over the lazy dog.", Vec2(0, 0), Vec2(16, 20));
}

void MAINLOOP()
{

}

void EXIT()
{
	
}