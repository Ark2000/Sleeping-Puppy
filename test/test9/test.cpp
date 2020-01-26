#include "..\..\src\api.h"
#include <cstdio>

void CONFIG()
{
	SetWindow("TEXT TEST", 640, 360);
}

void INIT()
{
}

void MAINLOOP()
{
	static char buf[512];
	DrawClear(0x1f1f1fff);
	sprintf(buf, "%d", GetFPS());
	Print(buf, Vec2(0, 0), Vec2(16, 16), 0xf0f0f0ff);
	sprintf(buf, "%d %d", MousePos().x, MousePos().y);
	Print(buf, Vec2(0, 32), Vec2(16, 16), 0xf0f0f0ff);
	sprintf(buf, "KEY_UP: %d %d %d %d", KeyDown(KEY_UP), KeyDownE(KEY_UP), KeyUpE(KEY_UP), KeyTime(KEY_UP));
	Print(buf, Vec2(0, 48), Vec2(16, 16), 0xf0f0f0ff);
	sprintf(buf, "KEY_DOWN: %d %d %d %d", KeyDown(KEY_DOWN), KeyDownE(KEY_DOWN), KeyUpE(KEY_DOWN), KeyTime(KEY_DOWN));
	Print(buf, Vec2(0, 64), Vec2(16, 16), 0xf0f0f0ff);
	sprintf(buf, "KEY_LEFT: %d %d %d %d", KeyDown(KEY_LEFT), KeyDownE(KEY_LEFT), KeyUpE(KEY_LEFT), KeyTime(KEY_LEFT));
	Print(buf, Vec2(0, 80), Vec2(16, 16), 0xf0f0f0ff);
	sprintf(buf, "KEY_RIGHT: %d %d %d %d", KeyDown(KEY_RIGHT), KeyDownE(KEY_RIGHT), KeyUpE(KEY_RIGHT), KeyTime(KEY_RIGHT));
	Print(buf, Vec2(0, 96), Vec2(16, 16), 0xf0f0f0ff);
	sprintf(buf, "KEY_MLEFT: %d %d %d %d", KeyDown(KEY_MLEFT), KeyDownE(KEY_MLEFT), KeyUpE(KEY_MLEFT), KeyTime(KEY_MLEFT));
	Print(buf, Vec2(0, 112), Vec2(16, 16), 0xf0f0f0ff);
	sprintf(buf, "KEY_MRIGHT: %d %d %d %d", KeyDown(KEY_MRIGHT), KeyDownE(KEY_MRIGHT), KeyUpE(KEY_MRIGHT), KeyTime(KEY_MRIGHT));
	Print(buf, Vec2(0, 128), Vec2(16, 16), 0xf0f0f0ff);

	if (KeyUpE(KEY_ESCAPE)) QuitSys();
}

void EXIT()
{
	
}