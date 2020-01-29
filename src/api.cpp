#include "wconfig.h"	//获取窗口变量的使用权限
#include "position.h"	//api函数有权知道自己被哪个特殊函数调用
#include "sche_task.h"	//计划任务，主要用于分层渲染
#include "internal.h"
#include <assert.h>
#include <cstring>
#include "api.h"

//初始化窗口参数
void SetWindow(const char* caption, int width, int height)
{
	assert(POSITION == CONFIG_);
	
	W_CAPTION = caption;
	W_WIDTH = width;
	W_HEIGHT =height;
}

void DrawLine(const Vec2& pos0, const Vec2& pos1, const Color& col, int priority)
{

	assert(POSITION != CONFIG_);

	static const int TID = 1;
	ScheduledTask task({priority, TID, new DrawLineArg({pos0, pos1, col})});
	TaskEnqueue(task);
}

void DrawRectB(const Vec4& rect, const Color& col, int priority)
{

	assert(POSITION != CONFIG_);

	static const int TID = 2;
	ScheduledTask task({priority, TID, new DrawRectArg({rect, col})});
	TaskEnqueue(task);
}

void DrawRect(const Vec4& rect, const Color& col, int priority)
{

	assert(POSITION != CONFIG_);

	static const int TID = 3;
	ScheduledTask task({priority, TID, new DrawRectArg({rect, col})});
	TaskEnqueue(task);
}

void DrawCircB(const Vec2& center, int radius, const Color& col, int priority)
{

	assert(POSITION != CONFIG_);

	static const int TID = 4;
	ScheduledTask task({priority, TID, new DrawCircArg({center, radius, col})});
	TaskEnqueue(task);
}

void DrawCirc(const Vec2& center, int radius, const Color& col, int priority)
{

	assert(POSITION != CONFIG_);

	static const int TID = 5;
	ScheduledTask task({priority, TID, new DrawCircArg({center, radius, col})});
	TaskEnqueue(task);
}

void DrawTexture(Texture& t, const Vec4& rect, int flip, int priority)
{
	assert(POSITION != CONFIG_);

	static const int TID = 6;
	ScheduledTask task({priority, TID, new DrawTextureArg({t, rect, flip})});
	TaskEnqueue(task);
}

void DrawTile(TiledTexture& tt, int id, const Vec4& rect, int flip, int priority)
{
	assert(POSITION != CONFIG_);

	static const int TID = 7;
	ScheduledTask task({priority, TID, new DrawTileArg({tt, id, rect, flip})});
	TaskEnqueue(task);
}

void DrawAnimation(FrameAnimation& fa, const Vec4& rect, int flip, int priority)
{
	assert(POSITION != CONFIG_);
	
	static const int TID = 8;
	ScheduledTask task({priority, TID, new DrawAnimationArg({&fa, rect, flip})});
	TaskEnqueue(task);
}

void Print(const char* string, const Vec2& pos, const Vec2& w_h, const Color& col, int priority)
{
	assert(POSITION != CONFIG_);

	static const int TID = 10;
	PrintArg* pa = new PrintArg();
	assert(strlen(string) < 128);
	strcpy(pa->string, string);
	pa->pos = pos; pa->w_h = w_h; pa->color = col;
	ScheduledTask task({priority, TID, pa});
	TaskEnqueue(task);
}

void PrintCenter(const char* string, const Vec4& rect, const Vec2& w_h, const Color& color, const Vec2& diff, int priority)
{
	assert(POSITION != CONFIG_);

	static const int TID = 11;
	PrintCenterArg* pca = new PrintCenterArg();
	assert(strlen(string) < 128);
	strcpy(pca->string, string);
	pca->rect = rect; pca->w_h = w_h; pca->color = color; pca->diff = diff;
	ScheduledTask task({priority, TID, pca});
	TaskEnqueue(task);
}

int GetFPS()
{
	return fps_info;
}

Texture ImportTextureFromFile(const char* path)
{
	assert(POSITION == INIT_);

	return Texture(new Texture_(path, 0));
}

Texture ImportTextureFromBase64(const char* base64)
{
	assert(POSITION == INIT_);

	return Texture(new Texture_(base64, 1));
}

Timer CreateTimer()
{
	return Timer();
}

void TimerStart(Timer& t)
{
	t.start();
}

void TimerStop(Timer& t)
{
	t.stop();
}

void TimerReset(Timer& t)
{
	t.reset();
}

int GetTime(Timer& t)
{
	return t.get();
}

TiledTexture ImportTiledTextureFromTexture(const Texture& t, int w, int h)
{
	assert(POSITION == INIT_);

	return TiledTexture(new TiledTexture_(*t, w, h));
}

FrameAnimation ImportFrameAnimationFromTiledTexture(const TiledTexture& tt, int interval, int sid, int eid, int loop)
{
	assert(POSITION == INIT_);

	return FrameAnimation(tt, interval, sid, eid, loop);
}

FrameAnimation ImportFrameAnimationFromTexture(const Texture& t, int w, int h, int interval, int sid, int eid, int loop)
{
	assert(POSITION == INIT_);

	return ImportFrameAnimationFromTiledTexture(ImportTiledTextureFromTexture(t, w, h), interval, sid, eid, loop);
}

void StartAnimation(FrameAnimation& fa)
{
	fa.start();
}

void StopAnimation(FrameAnimation& fa)
{
	fa.stop();
}

void ResetAnimation(FrameAnimation& fa)
{
	fa.reset();
}

extern KeyInfo KeyBoard[KEY_TOTAL_COUNT];

int KeyDown(Key k)
{
	return KeyBoard[k].is_pressed;
}

int KeyDownE(Key k)
{
	return KeyBoard[k].press_event;
}

int KeyUpE(Key k)
{
	return KeyBoard[k].release_event;
}

int KeyTime(Key k)
{
	return KeyBoard[k].key_timer.get();
}

Vec2 MousePos()
{
	Vec2 pos;
	SDL_GetMouseState(&pos.x, &pos.y);
	return pos;
}

void QuitSys()
{
	extern int quit_;
	quit_ = 1;
}