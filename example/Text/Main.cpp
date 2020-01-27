#include "../../src/api.h"
#include <cstdio>
const int W_ = 640;
const int H_ = 360;
char buffer[1024];
typedef void (*Scene)(int init);

void default_scene(int init)
{
	DrawClear(0x1f1f1fff);
}

Scene CurrentScene = default_scene;

void LoadScene(Scene s)
{
	s(1);
	CurrentScene = s;
}

void SayNihao(int init)
{
	static Timer t;	//场景内部变量
	static char text[3][256] = {
		"(c) 1997 Nintendo\n(c) 1997 Eon Productions\nU.A.C. All Rights Reserved",
		"Suitable only for 1-4 persons",
		"James Bond",
	};
	if (init) {		//初始化场景 
		t.start();
	}

	DrawClear(0x000000ff);
	PrintCenter(text[t.get() / 3000], Vec2(0, 0), Vec2(W_, H_), Vec2(16, 16), Vec2(0, 0), 0xffffffff, 0);
	int alpha;
	if (t.get() % 3000 < 1000) alpha = (1000 - t.get() % 3000) * 255 / 1000;
	else if (t.get() % 3000 < 2000) alpha = 0;
	else alpha = (t.get() % 3000 - 2000) * 255 / 1000;
	DrawRect(Vec2(0, 0), Vec2(W_, H_), Color(0, 0, 0, alpha), 0);

	if (t.get() > 8998) {
		LoadScene(default_scene);	//场景跳转
	}
}

void MAINLOOP()
{
	CurrentScene(0);
}

void EXIT()
{

}

void CONFIG()
{
	SetWindow("Text", W_, H_);
}

void INIT()
{
	LoadScene(SayNihao);
}