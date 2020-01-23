#pragma once
#include "sche_task.h"
#include "color.h"
#include "vec2.h"

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
	Vec2 pos;
	Vec2 w_h;
	Color col;
};

struct DrawCircArg
{
	Vec2 center;
	int radius;
	Color col;
};