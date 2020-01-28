#include "sche_task.h"
#include "draw.h"
#include <assert.h>

struct Node {
	ScheduledTask data;
	Node* next;
	Node(): data({256, 0, nullptr}), next(nullptr) { }
	Node(const ScheduledTask& data_): data(data_), next(nullptr) { }
};

struct TaskQueue {
	Node head;
	Node tail;
	
	TaskQueue()
	{
		head.next = &tail;
	}

	void enqueue(const ScheduledTask& t)
	{
		assert(t.priority < 256);

		Node* p = new Node(t);

		Node* q = &head;
		while (p->data.priority >= q->next->data.priority) {
			q = q->next;
		}
		Node* tmp = q->next;
		q->next = p;
		p->next = tmp;
	}
	int is_empty()
	{
		assert(head.next);
		return head.next->next == nullptr;
	}
	ScheduledTask dequeue()
	{
		assert(!is_empty());

		Node* tmp = head.next->next;
		ScheduledTask t = head.next->data;
		delete head.next;
		head.next = tmp;
		return t;
	}
	~TaskQueue()
	{
		while (!is_empty()) {
			dequeue();
		}
	}
};

static void RunTask(const ScheduledTask& task)
{
	switch (task.taskId) {
		case 1:
		{
			DrawLineArg *args = (DrawLineArg*)task.args;
			DrawLine_(args->pos0, args->pos1, args->col);
			delete args;
			break;
		}
		case 2:
		{
			DrawRectArg *args = (DrawRectArg*)task.args;
			DrawRectB_(args->rect, args->col);
			delete args;
			break;
		}
		case 3:
		{
			DrawRectArg *args = (DrawRectArg*)task.args;
			DrawRect_(args->rect, args->col);
			delete args;
			break;
		}
		case 4:
		{
			DrawCircArg *args = (DrawCircArg*)task.args;
			DrawCircB_(args->center, args->radius, args->col);
			delete args;
			break;
		}
		case 5:
		{
			DrawCircArg *args = (DrawCircArg*)task.args;
			DrawCirc_(args->center, args->radius, args->col);
			delete args;
			break;
		}

		case 6:
		{
			DrawTextureArg *args = (DrawTextureArg*)task.args;
			DrawTexture_(args->t, args->pos, args->scale);
			delete args;
			break;
		}

		case 7:
		{
			DrawTileArg *args = (DrawTileArg*)task.args;
			DrawTile_(args->tt, args->id, args->pos, args->scale);
			delete args;
			break;
		}

		case 8:
		{
			DrawAnimationArg *args = (DrawAnimationArg*)task.args;
			DrawAnimation_(args->pfa, args->pos, args->scale);
			delete args;
			break;
		}

		case 9:
		{
			void SetKeyEvent(int k, int type);
			SetKeyEventArg *args = (SetKeyEventArg*)task.args;
			SetKeyEvent(args->k, args->type);
			delete args;
			break;
		}

		case 10:
		{
			void Print_(const char* string, const Vec2& pos, const Vec2& w_h, const Color& color);
			PrintArg *args = (PrintArg*)task.args;
			Print_(args->string, args->pos, args->w_h, args->color);
			delete args;
			break;
		}

		case 11:
		{
			void PrintCenter_(const char* string, const Vec4& rect, const Vec2& w_h, const Vec2& diff, const Color& color);
			PrintCenterArg *args = (PrintCenterArg*)task.args;
			PrintCenter_(args->string, args->rect, args->w_h, args->diff, args->color);
			delete args;
			break;
		}

		default:
			assert(0);	//没有对应的任务ID
	}
}

TaskQueue TQueue;

void TaskEnqueue(const ScheduledTask& task)
{
	TQueue.enqueue(task);
}

void RunTasks()
{
	while (!TQueue.is_empty()) {
		ScheduledTask t = TQueue.dequeue();
		RunTask(t);
	}
}