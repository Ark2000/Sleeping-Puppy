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
			DrawLineArg *args1 = (DrawLineArg*)task.args;
			DrawLine_(args1->pos0, args1->pos1, args1->col);
			delete args1;
			break;
		}
		case 2:
		{
			DrawRectArg *args2 = (DrawRectArg*)task.args;
			DrawRectB_(args2->pos, args2->w_h, args2->col);
			delete args2;
			break;
		}
		case 3:
		{
			DrawRectArg *args3 = (DrawRectArg*)task.args;
			DrawRect_(args3->pos, args3->w_h, args3->col);
			delete args3;
			break;
		}
		case 4:
		{
			DrawCircArg *args4 = (DrawCircArg*)task.args;
			DrawCircB_(args4->center, args4->radius, args4->col);
			delete args4;
			break;
		}
		case 5:
		{
			DrawCircArg *args5 = (DrawCircArg*)task.args;
			DrawCirc_(args5->center, args5->radius, args5->col);
			delete args5;
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