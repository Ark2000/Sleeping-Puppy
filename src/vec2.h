#pragma once

struct Vec2 {
	int x;
	int y;

	friend int operator!=(const Vec2& lhs, const Vec2& rhs);
	friend int operator==(const Vec2& lhs, const Vec2& rhs);
	friend Vec2 operator+(const Vec2& lhs, const Vec2& rhs);
	friend Vec2 operator-(const Vec2& lhs, const Vec2& rhs);

	Vec2(int x_, int y_): x(x_), y(y_) { }
	Vec2(): x(0), y(0) { }
};

struct Vec4 {
	int x;
	int y;
	int w;
	int h;

	friend int operator!=(const Vec4& lhs, const Vec4& rhs);
	friend int operator==(const Vec4& lhs, const Vec4& rhs);

	Vec4(int x_, int y_, int w_, int h_): x(x_), y(y_), w(w_), h(h_) { }
	Vec4(): x(0), y(0), w(0), h(0) { }
};