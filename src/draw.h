#pragma once
#include "color.h"
#include "vec2.h"
#include "texture.h"

void DrawLine_(const Vec2& pos0, const Vec2& pos1, const Color& col);
void DrawRectB_(const Vec4& rect, const Color& col);
void DrawRect_(const Vec4& rect, const Color& col);
void DrawCircB_(const Vec2& center, int radius, const Color& col);
void DrawCirc_(const Vec2& center, int radius, const Color& col);

void DrawTexture_(Texture t, const Vec4& rect, int flip);
void DrawTile_(TiledTexture tt, int id, const Vec4& rect, int flip);
void DrawAnimation_(FrameAnimation* fa, const Vec4& rect, int flip);