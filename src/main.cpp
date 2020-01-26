#include <SDL.h>
#include <SDL_image.h>
#include <assert.h>	//暂时使用assert处理异常
#include "internal.h"
#include "wconfig.h"
#include "sche_task.h"	//任务队列
#include "position.h"
#include "text.h"
void UpdateKeyBoard(int key, int type);

void MAINLOOP();
void CONFIG();
void INIT();
void EXIT();

int main(int argc, char** argv)
{
	assert(SDL_Init(SDL_INIT_EVERYTHING) >= 0);

	POSITION = CONFIG_; CONFIG();

	G_window = SDL_CreateWindow(W_CAPTION, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W_WIDTH, W_HEIGHT, SDL_WINDOW_SHOWN);
	G_renderer = SDL_CreateRenderer(G_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	assert(G_renderer != NULL);

	SDL_SetRenderDrawColor(G_renderer, 0, 0, 0, 255);
	SDL_SetRenderDrawBlendMode(G_renderer, SDL_BLENDMODE_BLEND);

	int imgFlag = IMG_INIT_PNG;
	assert(IMG_Init(imgFlag) & imgFlag);


	POSITION = INIT_; LoadFont(); INIT();

	SDL_Event e;
	bool quit = false;
	Uint32 t = SDL_GetTicks();
	int frame = 0;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			} else
			if (e.type == SDL_KEYDOWN) {
				UpdateKeyBoard(e.key.keysym.sym, 0);
			} else
			if (e.type == SDL_KEYUP) {
				UpdateKeyBoard(e.key.keysym.sym, 1);
			} else
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				if (e.button.button == SDL_BUTTON_LEFT) {
					UpdateKeyBoard(-1, 0);
				} else
				if (e.button.button == SDL_BUTTON_RIGHT) {
					UpdateKeyBoard(-2, 0);
				}
			} else
			if (e.type == SDL_MOUSEBUTTONUP) {
				if (e.button.button == SDL_BUTTON_LEFT) {
					UpdateKeyBoard(-1, 1);
				} else
				if (e.button.button == SDL_BUTTON_RIGHT) {
					UpdateKeyBoard(-2, 1);
				}
			}
		}

		if (frame % 10 == 0) {
			fps_info = 10000 / (SDL_GetTicks() - t);
			t = SDL_GetTicks();
		}

		POSITION = MAINLOOP_; MAINLOOP();
		RunTasks();

		SDL_RenderPresent(G_renderer);
		++frame;
	}

	POSITION = EXIT_; EXIT();

	SDL_DestroyWindow(G_window);
	SDL_DestroyRenderer(G_renderer);

	IMG_Quit();
	SDL_Quit();

	return 0;
}