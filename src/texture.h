#pragma once
#include <SDL.h>
#include "vec2.h"
#include "timer.h"
#include <memory>

struct Texture_
{
	friend struct TiledTexture_;

	//从文件或base64中加载材质
	Texture_(const char* str, int is_base64);

	~Texture_();

	//拷贝初始化控制
	Texture_(const Texture_& r);

	//拷贝赋值
	Texture_& operator=(const Texture_& r);

	Texture_& draw(const Vec2& area0, const Vec2& area1);

	int w, h;
	SDL_Texture* data;
private:
	int* count;	//引用计数
};

struct TiledTexture_
{
	Texture_ texture;
	int grid_w;
	int grid_h;
	int cell_w;
	int cell_h;

	TiledTexture_(const Texture_& t_, int w, int h):
		texture(t_), grid_w(w), grid_h(h),
		cell_w(t_.w / grid_w), cell_h(t_.h / grid_h) { }
	
	TiledTexture_& draw(int id, const Vec2& area0, const Vec2& area1);
};

typedef std::shared_ptr<Texture_> Texture;
typedef std::shared_ptr<TiledTexture_> TiledTexture;

struct FrameAnimation
{
	friend void DrawAnimation_(FrameAnimation* fa, Vec2 pos, int scale);

	FrameAnimation() = default;

	FrameAnimation(const TiledTexture tt_, int interval_, int sid_, int eid_, int loop_ = 1);

	FrameAnimation& draw(const Vec2& area0, const Vec2& area1);

	FrameAnimation& start();
	FrameAnimation& stop();
	FrameAnimation& reset();

private:
	Timer t;
	TiledTexture tt;
	int sid;	//起始帧
	int eid;	//结束帧
	int interval;	//帧间隔时间
	int loop;	//是否循环
};