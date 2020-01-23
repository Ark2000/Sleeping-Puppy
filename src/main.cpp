#include <SDL.h>
#include <assert.h>	//暂时使用assert处理异常
#include "internal.h"
#include "wconfig.h"
#include "sche_task.h"	//任务队列
#include "position.h"

void MAINLOOP();
void CONFIG();
void INIT();
void EXIT();

int main(int argc, char** argv)
{
	POSITION = CONFIG_;
	CONFIG();

	assert(SDL_Init(SDL_INIT_EVERYTHING) >= 0);

	G_window = SDL_CreateWindow("SDL_TEST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W_WIDTH, W_HEIGHT, SDL_WINDOW_SHOWN);
	G_renderer = SDL_CreateRenderer(G_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	assert(G_renderer != NULL);

	SDL_SetRenderDrawColor(G_renderer, 0, 0, 0, 255);
	SDL_SetRenderDrawBlendMode(G_renderer, SDL_BLENDMODE_BLEND);

	POSITION = INIT_;
	INIT();

	SDL_Event e;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
		POSITION = MAINLOOP_;
		MAINLOOP();
		RunTasks();

		SDL_RenderPresent(G_renderer);
	}

	POSITION = EXIT_;
	EXIT();

	SDL_DestroyWindow(G_window);
	SDL_DestroyRenderer(G_renderer);

	SDL_Quit();

	return 0;
}