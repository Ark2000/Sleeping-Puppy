#include "../../src/api.h"
#include <cstdio>
#include <cmath>
#define ABS(x) ((x) > 0 ? (x) : (-(x)))
#define SQR(x) ((x) * (x))
const int W_ = 1280;
const int H_ = 720;

char buffer[1024];

void INIT()
{
	DrawClear(0x1f1f1fff);
}

int t = 0;

void MAINLOOP()
{
	static Vec2 last;
	static Color palette[8] = {
		0x1f1f1fff,
		0xffffffff,
		0x00ffffff,
		0xff00ffff,
		0xffff00ff,
		0x0000ffff,
		0x00ff00ff,
		0xff0000ff,
	};
	static int ccur;
	DrawRect(Vec4(0, 0, W_, 16), 0x000000ff);
	sprintf(buffer, "Q<-%d(R)->W A<-%d(G)->S Z<-%d(B)->X", palette[ccur].r, palette[ccur].g, palette[ccur].b);
	PrintCenter(buffer, Vec4(0, 0, W_, 16), Vec2(16, 16), palette[ccur]);
	for (int i = 0; i < 8; ++i) {
		DrawRect(Vec4(0, (i + 3) * 32, 64, 32), palette[i]);
	}

	DrawRectB(Vec4(0, (ccur + 3) * 32, 64, 32), 0xff0000ff);
	DrawRectB(Vec4(0 + 1, (ccur + 3) * 32 + 1, 62, 30), 0xff0000ff);
	
	if (KeyDownE(KEY_MLEFT)) {
		for (int i = 0; i < 8; ++i) {
			Vec2 mpos = MousePos();
			if (mpos.x >= 0 && mpos.x < 64 && mpos.y >= (i + 3) * 32 && mpos.y < (i + 4) * 32) {
				ccur = i;
				break;
			}
		}
	}

	if (KeyDown(KEY_Q)) if (palette[ccur].r > 0) --palette[ccur].r;
	if (KeyDown(KEY_W)) if (palette[ccur].r < 255) ++palette[ccur].r;
	if (KeyDown(KEY_A)) if (palette[ccur].g > 0) --palette[ccur].g;
	if (KeyDown(KEY_S)) if (palette[ccur].g < 255) ++palette[ccur].g;
	if (KeyDown(KEY_Z)) if (palette[ccur].b > 0) --palette[ccur].b;
	if (KeyDown(KEY_X)) if (palette[ccur].b < 255) ++palette[ccur].b;


	if (KeyUpE(KEY_MRIGHT)) DrawClear(palette[0]);
	if (KeyDownE(KEY_MLEFT)) {
		last = MousePos();
		DrawCirc(last, 8, palette[ccur]);
	}

	if (KeyDown(KEY_MLEFT) && !(MousePos() == last)) {
		Vec2 cur = MousePos();
		double xstep;
		double ystep;
		int steps;	//it can't be zero.
		if (ABS(cur.x - last.x) > ABS(cur.y - last.y)) {
			steps = ABS(cur.x - last.x);
			xstep = cur.x > last.x ? 1.0 : -1.0;
			ystep = (double)(cur.y - last.y) / steps;
		} else {
			steps = ABS(cur.y - last.y);
			ystep = cur.y > last.y ? 1.0 : -1.0;
			xstep = (double)(cur.x - last.x) / steps;
		}
		{
			double x = last.x;
			double y = last.y;
			int len = (int)sqrt(SQR(cur.x - last.x) + SQR(cur.y - last.y));
			int radius = 8;
			if (len > 4) --radius;
			if (len > 8) --radius;
			if (len > 16) --radius;
			if (len > 32) --radius;
			if (len > 64) --radius;
			if (len > 128) --radius;
			if (len > 256) --radius;
			
			for (int i = 0; i < steps; ++i) {
				x += xstep;
				y += ystep;
				DrawCirc(Vec2((int)x, (int)y), radius, palette[ccur]);
			}
			last = cur;
		}
	}

	++t;
}

void EXIT()
{

}

void CONFIG()
{
	SetWindow("paint", W_, H_);
}