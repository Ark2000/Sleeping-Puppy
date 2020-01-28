#include "internal.h"
#include "draw.h"
#include <SDL.h>

void DrawClear(const Color& col)
{
	SDL_SetRenderDrawColor(G_renderer, col.r, col.g, col.b, col.a);
	SDL_RenderClear(G_renderer);
}

void DrawLine_(const Vec2& v0, const Vec2& v1, const Color& col)
{
	SDL_SetRenderDrawColor(G_renderer, col.r, col.g, col.b, col.a);
	SDL_RenderDrawLine(G_renderer, v0.x, v0.y, v1.x, v1.y);
}

void DrawRectB_(const Vec4& rect, const Color& col)
{
	SDL_SetRenderDrawColor(G_renderer, col.r, col.g, col.b, col.a);
	SDL_Rect r = {rect.x, rect.y, rect.w, rect.h};
	SDL_RenderDrawRect(G_renderer, &r);
}

void DrawRect_(const Vec4& rect, const Color& col)
{
	SDL_SetRenderDrawColor(G_renderer, col.r, col.g, col.b, col.a);
	SDL_Rect r = {rect.x, rect.y, rect.w, rect.h};
	SDL_RenderFillRect(G_renderer, &r);
}

void DrawCircB_(const Vec2& center, int radius, const Color& col)
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

void DrawCirc_(const Vec2& center, int radius, const Color& col)
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

void DrawTexture_(Texture t, Vec2 pos, int scale)
{
	t->draw(Vec4(pos.x, pos.y, t->w * scale, t->h * scale));
}

void DrawTile_(TiledTexture tt, int id, Vec2 pos, int scale)
{
	tt->draw(id, Vec4(pos.x, pos.y, tt->cell_w * scale, tt->cell_h * scale));
}

void DrawAnimation_(FrameAnimation* fa, Vec2 pos, int scale)
{
	fa->draw(Vec4(pos.x, pos.y, fa->tt->cell_w * scale, fa->tt->cell_h * scale));
}