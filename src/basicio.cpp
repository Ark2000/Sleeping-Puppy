#include "basicio.h"
#include "sche_task.h"
#include <SDL.h>

KeyInfo KeyBoard[KEY_TOTAL_COUNT];

void UpdateKeyBoard(int key, int type)
{
	int k;
	switch (key) {
		case SDLK_a:case SDLK_b:case SDLK_c:case SDLK_d:case SDLK_e:case SDLK_f:
		case SDLK_g:case SDLK_h:case SDLK_i:case SDLK_j:case SDLK_k:case SDLK_l:
		case SDLK_m:case SDLK_n:case SDLK_o:case SDLK_p:case SDLK_q:case SDLK_r:
		case SDLK_s:case SDLK_t:case SDLK_u:case SDLK_v:case SDLK_w:case SDLK_x:
		case SDLK_y:case SDLK_z:
		{
			k = key - SDLK_a + 1;
			break;
		}
		case SDLK_0:case SDLK_1:case SDLK_2:case SDLK_3:case SDLK_4:
		case SDLK_5:case SDLK_6:case SDLK_7:case SDLK_8:case SDLK_9:
		{
			k = key - SDLK_0 + 27;
			break;
		}
		case SDLK_RETURN: k = KEY_RETURN; break;
		case SDLK_TAB: k = KEY_TAB; break;
		case SDLK_BACKSPACE: k = KEY_BACKSPACE; break;
		case SDLK_SPACE: k = KEY_SPACE; break;
		case SDLK_ESCAPE: k = KEY_ESCAPE; break;
		case SDLK_UP: k = KEY_UP; break;
		case SDLK_DOWN: k = KEY_DOWN; break;
		case SDLK_LEFT: k = KEY_LEFT; break;
		case SDLK_RIGHT: k = KEY_RIGHT; break;
		case SDLK_LSHIFT: k = KEY_LSHIFT; break;

		case -1: k = KEY_MLEFT; break;
		case -2: k = KEY_MRIGHT; break;

		default: k = 0;
	}

	const int TID = 9;

	switch (type) {
		case 0:
		{
			if (KeyBoard[k].is_pressed == 1) break;
			KeyBoard[k].is_pressed = 1;
			KeyBoard[k].press_event = 1;	//在本次的MAINLOOP执行完毕后需要马上设为0，添加到计划任务
			TaskEnqueue(ScheduledTask({0, TID, new SetKeyEventArg({k, 0})}));
			KeyBoard[k].key_timer.start();
			break;
		}
		case 1:
		{
			KeyBoard[k].is_pressed = 0;
			KeyBoard[k].release_event = 1;	//在本次的MAINLOOP执行完毕后需要马上设为0，添加到计划任务
			TaskEnqueue(ScheduledTask({0, TID, new SetKeyEventArg({k, 1})}));
			KeyBoard[k].key_timer.reset();
			break;
		}
	}
}

//计划任务
void SetKeyEvent(int k, int type)
{
	switch (type) {
		case 0:
		{
			KeyBoard[k].press_event = 0;
			break;
		}
		case 1:
		{
			KeyBoard[k].release_event = 0;
			break;
		}
	}
}