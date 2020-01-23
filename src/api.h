#pragma once
#include "color.h"
#include "vec2.h"

void SetWindow(const char* caption, int width, int height);

void DrawClear(const Color& col = 0xffffffff);
void DrawLine(const Vec2& pos0, const Vec2& pos1, const Color& col = 0x000000ff);
void DrawRectB(const Vec2& pos, const Vec2& w_h, const Color& col = 0x000000ff);
void DrawRect(const Vec2& pos, const Vec2& w_h, const Color& col = 0x000000ff);
void DrawCircB(const Vec2& center, int radius, const Color& col = 0x000000ff);
void DrawCirc(const Vec2& center, int radius, const Color& col = 0x000000ff);