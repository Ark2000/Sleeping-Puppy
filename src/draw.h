#pragma once
#include "color.h"
#include "vec2.h"

void DrawLine_(const Vec2& pos0, const Vec2& pos1, const Color& col);
void DrawRectB_(const Vec2& pos, const Vec2& w_h, const Color& col);
void DrawRect_(const Vec2& pos, const Vec2& w_h, const Color& col);
void DrawCircB_(const Vec2& center, int radius, const Color& col);
void DrawCirc_(const Vec2& center, int radius, const Color& col);