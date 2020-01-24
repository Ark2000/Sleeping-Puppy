#pragma once
#include <SDL.h>
#include "vec2.h"

struct Texture
{

	//从文件或base64中加载材质
	Texture(const char* str, int is_base64);

	~Texture();

	//拷贝初始化控制
	Texture(const Texture& r);

	//拷贝赋值
	Texture& operator=(const Texture& r);

	Texture& draw(Vec2 area0, Vec2 area1);

	int w, h;
private:
	SDL_Texture* data;
	int* count;	//引用计数
};