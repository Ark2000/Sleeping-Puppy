#include "wconfig.h"	//获取窗口变量的使用权限
#include "position.h"	//api函数有权知道自己被哪个特殊函数调用
#include "sche_task.h"	//计划任务，主要用于分层渲染
#include "internal.h"
#include <assert.h>
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

void DrawRectB(const Vec2& pos, const Vec2& w_h, const Color& col, int priority)
{

	assert(POSITION != CONFIG_);

	static const int TID = 2;

	ScheduledTask task({priority, TID, new DrawRectArg({pos, w_h, col})});

	TaskEnqueue(task);
}

void DrawRect(const Vec2& pos, const Vec2& w_h, const Color& col, int priority)
{

	assert(POSITION != CONFIG_);

	static const int TID = 3;

	ScheduledTask task({priority, TID, new DrawRectArg({pos, w_h, col})});

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

double GetFPS()
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

void DrawTexture(Texture& t, Vec2 pos, int scale)
{
	assert(POSITION != CONFIG_);

	t->draw(pos, pos + Vec2(t->w * scale, t->h * scale));
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

void DrawTile(TiledTexture& tt, int id, Vec2 pos, int scale)
{
	assert(POSITION != CONFIG_);

	tt->draw(id, pos, pos + Vec2(tt->cell_w * scale, tt->cell_h * scale));
}

FrameAnimation ImportFrameAnimationFromTiledTexture(const TiledTexture& tt, int interval, int sid, int eid, int loop)
{
	assert(POSITION == INIT_);

	return FrameAnimation(tt, interval, sid, eid, loop);
}

void DrawAnimation(FrameAnimation& fa, Vec2 pos, int scale)
{
	assert(POSITION != CONFIG_);

	fa.draw(pos, pos + Vec2(fa.tt->cell_w * scale, fa.tt->cell_h * scale));
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