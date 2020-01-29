#include "../../src/api.h"
#define ZERO(X) ((X) > -0.001) && ((X) < 0.001)
#include <assert.h>
const int W_ = 768;
const int H_ = 432;

Texture sky, mountains, clouds_BG, clouds_MG_1, clouds_MG_2, clouds_MG_3, char_adventurer;
FrameAnimation adventurer_idle, adventurer_run, adventurer_jump, adventurer_fall, adventurer_crouch;
Timer tm;

void INIT()
{
	sky = ImportTextureFromFile("sky.png");
	mountains = ImportTextureFromFile("mountains.png");
	clouds_BG = ImportTextureFromFile("clouds_BG.png");
	clouds_MG_1 = ImportTextureFromFile("clouds_MG_1.png");
	clouds_MG_2 = ImportTextureFromFile("clouds_MG_2.png");
	clouds_MG_3 = ImportTextureFromFile("clouds_MG_3.png");
	char_adventurer = ImportTextureFromFile("adventurer-v1.5-Sheet.png");
	adventurer_idle = ImportFrameAnimationFromTexture(char_adventurer, 7, 16, 180, 0, 3);
	adventurer_run = ImportFrameAnimationFromTexture(char_adventurer, 7, 16, 100, 8, 10);
	adventurer_jump = ImportFrameAnimationFromTexture(char_adventurer, 7, 16, 100, 11, 11, 0);
	adventurer_fall = ImportFrameAnimationFromTexture(char_adventurer, 7, 16, 400, 12, 12, 0);
	adventurer_crouch = ImportFrameAnimationFromTexture(char_adventurer, 7, 16, 400, 4, 7);
	tm.start();
}

enum {RUN, IDLE, JUMP, FALL, CROUCH};
enum {RIGHT, LEFT};
class Player
{
	friend void restrain(Player& p);

	int state = IDLE;
	Vec4 rect = {320, 0, 38, 61};
	double vx = 0.0;
	double vy = 0.0;
	int dir = LEFT;
public:
	void draw()
	{
		DrawRectB(rect, 0xff00ffff, 1);
		switch (state) {
			case IDLE:
				Print("IDLE", Vec2(0, 0), Vec2(16, 16));
				DrawAnimation(adventurer_idle, Vec4(rect.x - 32, rect.y - 11, 100, 74), dir, 1);
				break;
			case RUN:
				Print("RUN", Vec2(0, 0), Vec2(16, 16));
				DrawAnimation(adventurer_run, Vec4(rect.x - 32, rect.y - 11, 100, 74), dir, 1);
				break;
			case JUMP:
				Print("JUMP", Vec2(0, 0), Vec2(16, 16));
				DrawAnimation(adventurer_jump, Vec4(rect.x - 32, rect.y - 11, 100, 74), dir, 1);
				break;
			case FALL:
				Print("FALL", Vec2(0, 0), Vec2(16, 16));
				DrawAnimation(adventurer_fall, Vec4(rect.x - 32, rect.y - 11, 100, 74), dir, 1);
				break;
			case CROUCH:
				Print("CROUCH", Vec2(0, 0), Vec2(16, 16));
				DrawAnimation(adventurer_crouch, Vec4(rect.x - 32, rect.y - 11 - 20, 100, 74), dir, 1);
				break;
		}
	}
	void update()
	{
		if (vy > 0) state = FALL;

		switch (state) {
			case IDLE:
			{
				assert(ZERO(vx) && ZERO(vy));
				if (KeyDown(KEY_A) && !KeyDown(KEY_D)) {
					dir = LEFT;
					vx = -3;
					state = RUN;
				} else
				if (KeyDown(KEY_D) && !KeyDown(KEY_A)) {
					dir = RIGHT;
					vx = 3;
					state = RUN;
				} else
				if (KeyDown(KEY_W)) {
					vy = -8;
					state = JUMP;
				} else
				if (KeyDown(KEY_S)) {
					state = CROUCH;
					rect.y += 20;
					rect.h -= 20;
				}
				break;
			}
			case RUN:
			{
				assert((vx > 0 && dir == RIGHT) || (vx < 0 && dir == LEFT));
				if (KeyDown(KEY_S)) {
					vx = 0;
					state = CROUCH;
					rect.y += 20;
					rect.h -= 20;
				} else
				if (KeyDown(KEY_W)) {
					vy -= 8;
					state = JUMP;
				} else 
				if (KeyDown(KEY_A) && !KeyDown(KEY_D)) {
				} else 
				if (!KeyDown(KEY_A) && KeyDown(KEY_D)) {
				} else {
					state = IDLE;
					vx = 0;
				}
				break;
			}
			case FALL:
			{
				if (ZERO(vy)) {
					state = IDLE;
					vx = 0;
				}

				break;
			}
			case JUMP:
			{
				if (vy > 0) state = FALL;

				break;
			}
			case CROUCH:
			{
				if (!KeyDown(KEY_S)) {
					rect.y -= 20;
					rect.h += 20;
					state = IDLE;
				}
			}
		}

		restrain(*this);	//施加重力和地面

		if (vx > 3.1) vx = 3.0;
		if (vx < -3.1) vx = -3.0;
		if (vy > 4.1) vy = 4.0;
		if (vy < -4.1) vy = -4.0;

		rect.x += vx;
		rect.y += vy;
	}
};

Player p;

void DrawBG()
{
	static int t1 = 64000;
	static int t2 = 42000;
	static int t3 = 30000;
	static int t4 = 18000;
	DrawTexture(sky, Vec4(0, 0, W_, H_));
	DrawTexture(clouds_BG, Vec4(-(GetTime(tm) % t1) * W_ / t1, 0, W_, H_));
	DrawTexture(clouds_BG, Vec4(-(GetTime(tm) % t1) * W_ / t1 + W_, 0, W_, H_));
	DrawTexture(mountains, Vec4(0, 0, W_, H_));
	DrawTexture(clouds_MG_3, Vec4(-(GetTime(tm) % t2) * W_ / t2, 0, W_, H_));
	DrawTexture(clouds_MG_3, Vec4(-(GetTime(tm) % t2) * W_ / t2 + W_, 0, W_, H_));
	DrawTexture(clouds_MG_2, Vec4(-(GetTime(tm) % t3) * W_ / t3, 0, W_, H_));
	DrawTexture(clouds_MG_2, Vec4(-(GetTime(tm) % t3) * W_ / t3 + W_, 0, W_, H_));
	DrawRect(Vec4(0, 360, W_, H_), 0xf0f0f0ff);
	DrawTexture(clouds_MG_1, Vec4(-(GetTime(tm) % t4) * W_ / t4, 0, W_, H_), 0, 2);
	DrawTexture(clouds_MG_1, Vec4(-(GetTime(tm) % t4) * W_ / t4 + W_, 0, W_, H_), 0, 2);

	DrawRect(Vec4(0, 0, W_, H_), 0x0000ff12, 255);
}

void MAINLOOP()
{
	p.update();

	DrawClear();
	DrawBG();
	p.draw();
}

void EXIT()
{

}

void CONFIG()
{
	SetWindow("adventurer", W_, H_);
}

void restrain(Player& p)
{
	p.vy += 0.3;

	if (p.rect.y + p.vy + p.rect.h > 360) {
		p.vy = 0.0;
		p.rect.y = 360 - p.rect.h;
	}
}