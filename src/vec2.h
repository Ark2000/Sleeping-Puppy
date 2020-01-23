#pragma once

struct Vec2 {
	int x;
	int y;

	friend Vec2 operator+(const Vec2& lhs, const Vec2& rhs);
	friend Vec2 operator-(const Vec2& lhs, const Vec2& rhs);

	Vec2(int x_, int y_): x(x_), y(y_) { }
	Vec2(): x(0), y(0) { }
};