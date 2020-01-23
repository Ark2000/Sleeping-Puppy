#pragma once
#include "color.h"
#include "vec2.h"

void SetWindow(const char* caption, int width, int height);

void DrawClear(const Color& col = 0xffffffff);
void DrawLine(const Vec2& pos0, const Vec2& pos1, const Color& col = 0x000000ff, int priority = 0);
void DrawRectB(const Vec2& pos, const Vec2& w_h, const Color& col = 0x000000ff, int priority = 0);
void DrawRect(const Vec2& pos, const Vec2& w_h, const Color& col = 0x000000ff, int priority = 0);
void DrawCircB(const Vec2& center, int radius, const Color& col = 0x000000ff, int priority = 0);
void DrawCirc(const Vec2& center, int radius, const Color& col = 0x000000ff, int priority = 0);