#include "../../src/api.h"
const int W_ = 640;
const int H_ = 360;
char buffer[1024];

void INIT()
{

}

void MAINLOOP()
{
	static Vec2 tpos(213, 152);

	if (KeyDown(KEY_UP)) tpos.y--;
	if (KeyDown(KEY_DOWN)) tpos.y++;
	if (KeyDown(KEY_LEFT)) tpos.x--;
	if (KeyDown(KEY_RIGHT)) tpos.x++;

	DrawClear(0x1f1f1fff);

	Print("Hello, player!", tpos, Vec2(16, 16), 0xffffffff);

	sprintf(buffer, "%d %d", tpos.x, tpos.y);
	Print(buffer, Vec2(0, 0), Vec2(8, 8), 0xffffffff);

	sprintf(buffer, "%d", GetFPS());
	Print(buffer, Vec2(620, 0), Vec2(8, 8), 0xffffffff);

}

void EXIT()
{

}

void CONFIG()
{
	SetWindow("Template", W_, H_);
}