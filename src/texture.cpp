#include "texture.h"

#include "internal.h"
#include <cassert>
#include <SDL_image.h>

char* decode(const char* code, int* filesize);

Texture::Texture(const char* str, int is_base64): count(new int(1))
{
	SDL_Surface* tmp;
	if (!is_base64) {
		tmp = IMG_Load(str);
	} else {
		int bufsize;
		char* buf = decode(str, &bufsize);
		//这里的话，IMG模块应该会帮我释放掉buf
		SDL_RWops *src = SDL_RWFromMem(buf, bufsize);
		tmp = IMG_Load_RW(src, 1);
	}

	assert(tmp);
	w = tmp->w;
	h = tmp->h;
	data = SDL_CreateTextureFromSurface(G_renderer, tmp);
	SDL_FreeSurface(tmp);
	assert(data);
	SDL_SetTextureBlendMode(data, SDL_BLENDMODE_BLEND);
}

Texture::~Texture()
{
	if (--*count == 0) {
		delete count;
		SDL_DestroyTexture(data);
	}
}

Texture::Texture(const Texture& r)
{
	data = r.data;
	w = r.w;
	h = r.h;
	count = r.count;
	++*count;
}

Texture& Texture::operator=(const Texture& r)
{
	++*r.count;
	if (--*count == 0) {
		delete count;
		SDL_DestroyTexture(data);
	}
	data = r.data;
	w = r.w;
	h = r.h;
	count = r.count;

	return *this;
}

Texture& Texture::draw(Vec2 area0, Vec2 area1)
{
	SDL_Rect srcrect = {0, 0, w, h};
	SDL_Rect dstrect = {area0.x, area0.y, area1.x - area0.x, area1.y - area0.y};
	SDL_RenderCopy(G_renderer, data, &srcrect, &dstrect);

	return *this;
}