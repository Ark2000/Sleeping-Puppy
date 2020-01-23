#include "../../src/color.h"
#include "../../src/vec2.h"
#include <cstdio>
using namespace std;
int main()
{
	RGBA rgba(0x12345678);

	printf("%d %d %d %d\n", rgba.r, rgba.g, rgba.b, rgba.a);

	Vec2 v1(1, 2), v2(3, 4);
	Vec2 v3 = v1 + v2;
	Vec2 v4 = v2 - v1;

	printf("%d %d\n", v3.x, v3.y);
	printf("%d %d\n", v4.x, v4.y);
	return 0;
}