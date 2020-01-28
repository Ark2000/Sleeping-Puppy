#include "../../src/api.h"
#include <deque>
#include <cmath>
#include <vector>
#include <cstdio>

#define SQR(X) ((X) * (X))

constexpr int SIZE = 4;
const Color colors[] = {
	Color(238, 228, 218),
	Color(237, 224, 200),
	Color(242, 177, 121),
	Color(245, 149, 99),
	Color(246, 124, 95),
	Color(246, 94, 59),
	Color(237, 207, 144),
	Color(237, 204,97),
	Color(224, 194, 46),
	Color(226, 185, 19),
	Color(237, 194, 46),
	Color(187, 173, 160),
	Color(205, 192, 180),
};
const Color bgcolor(250, 248, 238);
const Color gameover(220, 10, 10);

const int W_ = 480;
const int H_ = 640;

const int SX = 22;
const int SY = 180;
const int GAP = 12;
const int SZ = 100;

const double move_factor = 0.2;
const int animation_time = 10;

char buffer[256];

double swell(double t)
{
	return -SQR(t-0.6) + 1.16;
}

double swelll(double t)
{
	return 1 + 0.32 * sin(t * 3.14);
}

struct Tile {
	Tile(int x_, int y_, int sz_, int num_):
		x(x_), y(y_), sz(sz_), num(num_)
	{
		tx = x;
		ty = y;
		isMoving = true;
		born = 0;
		reborn = 0xffffff;
		dead = false;
		color = colors[0];
		dying = false;
	}
	Tile() = default;
	void render()
	{
		if (dead) return;
		double scale = 1.0;

		if (born < animation_time) {
			scale = swell(born / (double)animation_time);
			++born;
		} else
		if (reborn < animation_time) {
			if (reborn > 0)
				scale = swelll(reborn / (double)animation_time);
			++reborn;
		}
		int d = (scale - 1) / 2 * sz;
		DrawRect(Vec4(x-d, y-d, sz * scale, sz * scale), color);
		sprintf(buffer, "%d", num);
		PrintCenter(buffer, Vec4(x-d, y-d, sz * scale, sz * scale), Vec2(24, 24), bgcolor);
	}

	void setTarget(int x, int y)
	{
		tx = x;
		ty = y;
	}

	bool update()
	{
		if (dead) return false;
		int dx, dy;
		if (tx > x) 
			dx = ceil((tx - x) * move_factor);
		else
			dx = floor((tx - x) * move_factor);
		if (ty > y)
			dy = ceil((ty - y) * move_factor);
		else
			dy = floor((ty - y) * move_factor);
		x += dx;
		y += dy;

		if (reborn == 1) {
			num = nextnum;
			int idx = 0;
			if (num > 2)    ++idx;
			if (num > 4)    ++idx;
			if (num > 8)    ++idx;
			if (num > 16)   ++idx;
			if (num > 32)   ++idx;
			if (num > 64)   ++idx;
			if (num > 128)  ++idx;
			if (num > 256)  ++idx;
			if (num > 512)  ++idx;
			if (num > 1024) ++idx;
			color = colors[idx];
		}
		if (x == tx && y == ty && born >= animation_time && reborn >= animation_time) {
			isMoving = false;
			if (dying) {
				dead = true;
				dying = false;
			}
		} else isMoving = true;
		return isMoving;
	}

	int x;
	int y;
	int tx;
	int ty;
	int sz;
	int num;
	int nextnum;
	Color color = 0x000000ff;
	bool isMoving;
	int born;
	int reborn;
	bool dead = true;
	bool dying = false;
	char buffer[16] = "";
};

struct Event {
	int x;
	int y;
	int tx;
	int ty;
	int newval;
	bool dying;
	bool born;
	bool reborn;
};

std::deque<Event> events;

Tile tiles[SIZE*SIZE];
int media[SIZE][SIZE];

void handleEvent()
{
	for (auto &e: events) {
		if (e.born) {
			int i = 0;
			int dyingmark = SIZE*SIZE;
			for (; i < SIZE * SIZE; ++i) {
				if (tiles[i].dead) break;
				if (tiles[i].dying) dyingmark = i;
			}
			if (i < SIZE * SIZE)
				media[e.y][e.x] = i;
			else {
				if (dyingmark < SIZE*SIZE) {
					media[e.y][e.x] = dyingmark;
				}
			}
			tiles[media[e.y][e.x]] = 
				Tile(SX + e.x * (GAP + SZ), SY + e.y * (GAP + SZ), SZ, e.newval);
		}
		int idx = media[e.y][e.x];
		tiles[idx].tx = (e.x + e.tx) * (GAP + SZ) + SX;
		tiles[idx].ty = (e.y + e.ty) * (GAP + SZ) + SY;
		if (!e.dying) {
			media[e.y+e.ty][e.x+e.tx] = idx;
		} else {
			tiles[idx].dying = true;
		}
		if (e.reborn) {
			tiles[idx].reborn = -6;
			tiles[idx].nextnum = e.newval;
		} 
	}
	events.clear();
}

bool udAll()
{
	bool flag = false;
	DrawRect(Vec4(SX - GAP, SY - GAP, SIZE * SZ + GAP * (SIZE + 1), SIZE * SZ + GAP * (SIZE + 1)), colors[11]);
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			DrawRect(Vec4(SX+j*(GAP+SZ), SY+i*(GAP+SZ), SZ, SZ), colors[12]);
		}
	}
	for (int i = 0; i < SIZE * SIZE; ++i) {
		if (tiles[i].update()) flag = true;
		tiles[i].render();
	}
	
	return flag;
}

void drawText(const char* words, int val, int x, int y)
{
	DrawRect(Vec4(x, y, 100, 50), colors[12]);
	Print(words, Vec2(x, y), Vec2(16, 16), bgcolor);
	sprintf(buffer, "%d", val);
	Print(buffer, Vec2(x, y + 25), Vec2(16, 16), 0xffffffff);
}

void drawInfo()
{
	Print("2048", Vec2(20, 40), Vec2(48, 48), colors[12]);
	Print("Help: WASD to slide, R to restart", Vec2(20, 130), Vec2(12, 12), colors[12]);
}

using Vint = std::vector<int>;
typedef int BoardType[SIZE][SIZE];
enum DirType {UP, DOWN, LEFT, RIGHT, CNT};
const int Dir[CNT][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

BoardType brd;
char msg[256];
int score;
int highest;
bool add(BoardType board);
int get(const BoardType board, int x, int y);
void set(BoardType board, int x, int y, int val);
void raw_draw(const BoardType board);
bool slide(BoardType board, DirType dir);
bool checkLose(BoardType board);
void reset(BoardType board);


void CONFIG()
{
	SetWindow("2048", W_, H_);
}

void INIT()
{
	add(brd);
}

void MAINLOOP()
{
	if (KeyDownE(KEY_W) || KeyDownE(KEY_S) || KeyDownE(KEY_A) || KeyDownE(KEY_D))
	{
		bool flag;
		if (KeyDownE(KEY_W)) flag = slide(brd, UP);
		if (KeyDownE(KEY_S)) flag = slide(brd, DOWN);
		if (KeyDownE(KEY_A)) flag = slide(brd, LEFT);
		if (KeyDownE(KEY_D)) flag = slide(brd, RIGHT);
		if (flag) {
			add(brd);
			if (checkLose(brd)) {
				sprintf(msg, "GAME OVER");
			}
		}
	}
	if (KeyDownE(KEY_R)) {
		reset(brd);
	}
	DrawClear(bgcolor);
	Print(msg, Vec2(20, 100), Vec2(16, 16), gameover);
	drawText("SCORE", score, 240, 40);
	drawText("BEST", highest, 360, 40);
	drawInfo();
	udAll();
	handleEvent();
}

void EXIT()
{

}

bool add(BoardType board)
{
	bool flag = true;
	Vint candidates;
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (get(brd, j, i) == 0)
				candidates.push_back(j+i*SIZE);
		}
	}
	if (candidates.empty()) flag = false;
	else {
		int sz = candidates.size();
		int idx = candidates[rand()%sz];
		int x = idx % SIZE;
		int y = idx / SIZE;
		set(brd, x, y, 2);
		Event newbirth = {x, y, 0, 0, 2, false, true, false};
		events.push_back(newbirth);
	}
	return flag;
}

int get(const BoardType board, int x, int y)
{
	if (x < 0 || x >= SIZE || y < 0 || y >= SIZE)
		return -1;
	return board[y][x];
}

void set(BoardType board, int x, int y, int val)
{
	if (x < 0 || x >= SIZE || y < 0 || y >= SIZE)
		return;
	board[y][x] = val;
}

bool single_slide(BoardType board, int x, int y, DirType dir)
{
	bool flag = false;
	int dx = Dir[dir][0];
	int dy = Dir[dir][1];
	int tx = 0;
	int ty = 0;
	if (get(board, x, y) == 0) return false;
	for (; get(board, x+dx+tx, y+dy+ty) == 0; tx += dx, ty += dy);
	int v1 = get(board, x+tx+dx, y+ty+dy);
	int v2 = get(board, x, y);
	if (v1 == v2) {
		set(board, x + dx + tx, y + dy + ty, v1 + v2);
		set(board, x, y, 0);

		Event death = {x, y, tx+dx, ty+dy, 0, true, false, false};
		Event combi = {x+dx+tx, y+dy+ty, 0, 0, v1+v2, false,false, true};
		events.push_back(death);
		events.push_back(combi);
		flag = true;
		score += (v1 + v2);
	} else
	if (tx || ty) {
		set(board, x + tx, y + ty, v2);
		set(board, x, y, 0);
		Event move = {x, y, tx, ty, 0, false, false, false};
		events.push_back(move);
		flag = true;
	}
	return flag;
}

bool slide(BoardType board, DirType dir)
{
	bool flag = false;
	switch(dir) {
	case UP:
		for (int x = 0; x < SIZE; ++x) {
			for (int y = 1; y < SIZE; ++y) {
				if (single_slide(board, x, y, dir)) flag = true;
			}
		} break;
	case DOWN:
		for (int x = 0; x < SIZE; ++x) {
			for (int y = SIZE - 2; y >= 0; --y) {
				if (single_slide(board, x, y, dir)) flag = true;
			}
		} break;
	case LEFT:
		for (int y = 0; y < SIZE; ++y) {
			for (int x = 1; x < SIZE; ++x) {
				if (single_slide(board, x, y, dir)) flag = true;
			}
		} break;
	case RIGHT:
		for (int y = 0; y < SIZE; ++y) {
			for (int x = SIZE - 2; x >= 0; --x) {
				if (single_slide(board, x, y, dir)) flag = true;
			}
		} break;
	default:
		break;
	}
	return flag;
}

bool checkLose(BoardType board)
{
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0 ; j < SIZE - 1; ++j) {
			if (board[i][j] == 0) return false;
			if (board[j][i] == board[j+1][i] || board[i][j] == board[i][j+1])
				return false;
		}
	}
	for (int i = 0; i < SIZE; ++i) {
		if (board[i][SIZE-1] == 0) return false;
	}
	return true;
}

void reset(BoardType board)
{
	*msg = 0;
	highest = score > highest ? score : highest;
	score = 0;
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (board[i][j] != 0) {
				board[i][j] = 0;
				Event death = {j, i, 0, -6, 0, true, false, false};
				events.push_back(death);
			}
		}
	}
	add(board);
}