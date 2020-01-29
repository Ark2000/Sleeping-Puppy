#pragma once
#include "sche_task.h"
#include "color.h"
#include "vec2.h"
#include "texture.h"
#include "basicio.h"

struct ScheduledTask
{
	int priority;	//优先级
	int taskId;		//对应的任务
	void* args;		//参数包,由任务决定类型
};

void TaskEnqueue(const ScheduledTask& task);

void RunTasks();

//任务参数包
struct DrawLineArg
{
	Vec2 pos0;
	Vec2 pos1;
	Color col;
};

struct DrawRectArg
{
	Vec4 rect;
	Color col;
};

struct DrawCircArg
{
	Vec2 center;
	int radius;
	Color col;
};

struct DrawTextureArg
{
	Texture t;
	Vec4 rect;
	int flip;
};

struct DrawTileArg
{
	TiledTexture tt;
	int id;
	Vec4 rect;
	int flip;
};

struct DrawAnimationArg
{
	FrameAnimation* pfa;
	Vec4 rect;
	int flip;
};

struct SetKeyEventArg
{
	int k;
	int type;
};

struct PrintArg
{
	char string[128];
	Vec2 pos;
	Vec2 w_h;
	Color color;
};

struct PrintCenterArg
{
	char string[128];
	Vec4 rect;
	Vec2 w_h;
	Color color;
	Vec2 diff;
};