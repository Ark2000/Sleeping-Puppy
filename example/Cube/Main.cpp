#include "../../src/api.h"
#include <cmath>
#include <cstdio>
char buffer[256];

int W_ = 512;
int H_ = 512;

double center[3] = {250, 250, 1250};

double vertex[8][3] = {
	{100, 100, 1100},
	{400, 100, 1100},
	{100, 400, 1100},
	{100, 100, 1400},
	{100, 400, 1400},
	{400, 100, 1400},
	{400, 400, 1100},
	{400, 400, 1400},
};

int edges[12][2] {
	{0, 1},
	{0, 2},
	{0, 3},
	{1, 5},
	{1, 6},
	{2, 4},
	{2, 6},
	{3, 4},
	{3, 5},
	{4, 7},
	{5, 7},
	{6, 7},
};

double x0, y0, z0;

int transform(double x1, double y1, double z1, int* x2, int* y2)
{
	if (z1 < 0) return 0;
	*x2 = x1 + z1 * (x1 - x0) / (z0 - z1);
	*y2 = y1 + z1 * (y1 - y0) / (z0 - z1);
	return 1;
}

void draw_cube()
{
	Vec2 trans[8];
	for (int i = 0; i < 8; ++i) {
		transform(vertex[i][0], vertex[i][1], vertex[i][2], &(trans[i].x), &(trans[i].y));
	}
	for (int i = 0; i < 12; ++i) {
		DrawLine(trans[edges[i][0]], trans[edges[i][1]], 0xffffffff);
	}
}

//果然不出所料闪退了
void rotate(double cx, double cy, double cz, double* tx, double* ty, double* tz, double angle, int dir)
{
	//水平旋转
	if (dir == 0) {
		double a = atan((*tz - cz) / (*tx - cx)) + angle;
		if ((*tx - cx) < 0) a += 3.1415926535898;
		double r = sqrt((*tz - cz) * (*tz - cz) + (*tx - cx) * (*tx - cx));
		*tz = cz + r * sin(a);
		*tx = cx + r * cos(a);
	} else {
		double a = atan((*tz - cz) / (*ty - cy)) + angle;
		if ((*ty - cy) < 0) a += 3.1415926535898;
		double r = sqrt((*tz - cz) * (*tz - cz) + (*ty - cy) * (*ty - cy));
		*tz = cz + r * sin(a);
		*ty = cy + r * cos(a);
	}
}

void rotate_cube(double angle, int dir)
{
	for (int i = 0; i < 8; ++i) {
		rotate(center[0], center[1], center[2], &(vertex[i][0]), &(vertex[i][1]), &(vertex[i][2]), angle, dir);
	}
}

void INIT()
{
	x0 = W_ / 2;
	y0 = H_ / 2;
	z0 = -800;
}

void MAINLOOP()
{
	DrawClear(0x000000ff);
	static double vx = 0.03;
	static double vy = 0.01;


	int dx = 0, dy = 0, dz = 0;

	if (KeyDown(KEY_S)) dy = +2;
	if (KeyDown(KEY_W)) dy = -2;
	if (KeyDown(KEY_A)) dx = -2;
	if (KeyDown(KEY_D)) dx = +2;
	if (KeyDown(KEY_Z)) dz = +2;
	if (KeyDown(KEY_X)) dz = -2;
	if (KeyDown(KEY_Q)) z0 -= 10;
	if (KeyDown(KEY_E)) if (z0 < -100) z0 += 10;

	if (center[2] + dz > 450) {
		for (int i = 0; i < 8; ++i) {
			vertex[i][0] += dx;
			vertex[i][1] += dy;
			vertex[i][2] += dz;
		}
		center[0] += dx;
		center[1] += dy;
		center[2] += dz;
	}

	if (KeyDown(KEY_LEFT)) {
		rotate_cube(-0.05, 0);
	}
	if (KeyDown(KEY_RIGHT)) {
		rotate_cube(+0.01, 0);
	}
	if (KeyDown(KEY_UP)) {
		rotate_cube(-0.03, 1);
	}
	if (KeyDown(KEY_DOWN)) {
		rotate_cube(+0.03, 1);
	}

	rotate_cube(vx, 0);
	rotate_cube(vy, 1);

	for (int i = 0; i < 8; ++i) {
		sprintf(buffer, "%.0f %.0f %.0f", vertex[i][0], vertex[i][1], vertex[i][2]);
		Print(buffer, Vec2(0, (i + 2) * 16), Vec2(16, 16), 0xffffffff);
	}
	draw_cube();

	DrawRect(Vec4(0, 0, W_ ,32), 0x2f2f2fff);
	PrintCenter("Keys: W, S, A, D, Z, X, \nUP, DOWN, LEFT, RIGHT, Q, E", Vec4(0, 0, W_, 32), Vec2(16, 16), 0xffffffff);
}

void EXIT()
{

}

void CONFIG()
{
	SetWindow("cube", W_, H_);
}