#include "vec2.h"

Vec2 operator+(const Vec2& lhs, const Vec2& rhs)
{
	return Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
}

Vec2 operator-(const Vec2& lhs, const Vec2& rhs)
{
	return Vec2(lhs.x - rhs.x, lhs.y - rhs.y);
}

int operator==(const Vec2& lhs, const Vec2& rhs)
{
	return (lhs.x == rhs.x) && (lhs.y ==rhs.y);
}

int operator!=(const Vec2& lhs, const Vec2& rhs)
{
	return !operator==(lhs, rhs);
}

int operator==(const Vec4& lhs, const Vec4& rhs)
{
	return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.w == rhs.w) && (lhs.h == rhs.h);
}

int operator!=(const Vec4& lhs, const Vec4& rhs)
{
	return !operator==(lhs, rhs);
}