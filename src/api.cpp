#include "wconfig.h"	//获取窗口变量的使用权限
#include "internal.h"
#include <SDL.h>
#include <assert.h>
#include "api.h"

//初始化窗口参数
void SetWindow(const char* caption, int width, int height)
{
	assert(W_is_config == 1);	//当前程序一定执行在INIT函数内部。不能在其他地方调用该函数
	
	W_CAPTION = caption;
	W_WIDTH = width;
	W_HEIGHT =height;
}

void DrawClear(const Color& col)
{
	SDL_SetRenderDrawColor(G_renderer, col.r, col.g, col.b, col.a);
	SDL_RenderClear(G_renderer);
}

void DrawLine(const Vec2& v0, const Vec2& v1, const Color& col)
{
	SDL_SetRenderDrawColor(G_renderer, col.r, col.g, col.b, col.a);
	SDL_RenderDrawLine(G_renderer, v0.x, v0.y, v1.x, v1.y);
}

void DrawRectB(const Vec2& pos, const Vec2& w_h, const Color& col)
{
	SDL_SetRenderDrawColor(G_renderer, col.r, col.g, col.b, col.a);
	SDL_Rect r = {pos.x, pos.y, w_h.x, w_h.y};
	SDL_RenderDrawRect(G_renderer, &r);
}

void DrawRect(const Vec2& pos, const Vec2& w_h, const Color& col)
{
	SDL_SetRenderDrawColor(G_renderer, col.r, col.g, col.b, col.a);
	SDL_Rect r = {pos.x, pos.y, w_h.x, w_h.y};
	SDL_RenderFillRect(G_renderer, &r);
}

void DrawCircB(const Vec2& center, int radius, const Color& col)
{
	SDL_SetRenderDrawColor(G_renderer, col.r, col.g, col.b, col.a);
	int tx = radius - 1, ty = 0;
	int rr = radius * radius;
	while (ty <= tx) {
		SDL_RenderDrawPoint(G_renderer, center.x + tx, center.y + ty);
		SDL_RenderDrawPoint(G_renderer, center.x + tx, center.y - ty);
		SDL_RenderDrawPoint(G_renderer, center.x - tx, center.y + ty);
		SDL_RenderDrawPoint(G_renderer, center.x - tx, center.y - ty);
		SDL_RenderDrawPoint(G_renderer, center.x + ty, center.y + tx);
		SDL_RenderDrawPoint(G_renderer, center.x + ty, center.y - tx);
		SDL_RenderDrawPoint(G_renderer, center.x - ty, center.y + tx);
		SDL_RenderDrawPoint(G_renderer, center.x - ty, center.y - tx);
		for(++ty; tx*tx+ty*ty>rr;--tx);
	}
}

void DrawCirc(const Vec2& center, int radius, const Color& col)
{
	SDL_SetRenderDrawColor(G_renderer, col.r, col.g, col.b, col.a);
	int tx = radius - 1, ty = 0;
	int rr = radius * radius;
	while (ty <= tx) {
		SDL_RenderDrawLine(G_renderer, center.x - tx, center.y + ty, center.x + tx, center.y + ty);
		SDL_RenderDrawLine(G_renderer, center.x - tx, center.y - ty, center.x + tx, center.y - ty);
		SDL_RenderDrawLine(G_renderer, center.x - ty, center.y + tx, center.x + ty, center.y + tx);
		SDL_RenderDrawLine(G_renderer, center.x - ty, center.y - tx, center.x + ty, center.y - tx);
		for(++ty; tx*tx+ty*ty>rr;--tx);
	}
}