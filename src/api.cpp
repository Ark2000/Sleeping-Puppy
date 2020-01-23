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