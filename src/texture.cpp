#include "texture.h"

#include "internal.h"
#include <cassert>
#include <SDL_image.h>
#include <memory>

char* decode(const char* code, int* filesize);

Texture_::Texture_(const char* str, int is_base64): count(new int(1))
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

Texture_::~Texture_()
{
	if (--*count == 0) {
		delete count;
		SDL_DestroyTexture(data);
	}
}

Texture_::Texture_(const Texture_& r)
{
	data = r.data;
	w = r.w;
	h = r.h;
	count = r.count;
	++*count;
}

Texture_& Texture_::operator=(const Texture_& r)
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

Texture_& Texture_::draw(Vec2 area0, Vec2 area1)
{
	SDL_Rect srcrect = {0, 0, w, h};
	SDL_Rect dstrect = {area0.x, area0.y, area1.x - area0.x, area1.y - area0.y};
	SDL_RenderCopy(G_renderer, data, &srcrect, &dstrect);

	return *this;
}

TiledTexture_& TiledTexture_::draw(int id, Vec2 area0, Vec2 area1)
{
	assert(id >= 0 && id < grid_w * grid_h);
	int x = id % grid_w;
	int y = id / grid_w;
	SDL_Rect srcrect = {x * cell_w, y * cell_h, cell_w, cell_h};
	SDL_Rect dstrect = {area0.x, area0.y, area1.x - area0.x, area1.y - area0.y};
	SDL_RenderCopy(G_renderer, texture.data, &srcrect, &dstrect);

	return *this;
}

FrameAnimation::FrameAnimation(const TiledTexture tt_, int interval_, int sid_, int eid_, int loop_):
tt(tt_), sid(sid_), eid(eid_), interval(interval_), loop(loop_) 
{
	t.start();
}

FrameAnimation& FrameAnimation::draw(Vec2 area0, Vec2 area1)
{
	int id;
	if (loop) {
		id = (t.get() / interval) % (eid - sid + 1) + sid;
	} else {
		int tmp = (t.get() / interval) + sid;
		id = tmp > eid ? eid: tmp;
	}

	tt->draw(id, area0, area1);

	return *this;
}

FrameAnimation& FrameAnimation::start()
{
	t.start();
	return *this;
}

FrameAnimation& FrameAnimation::stop()
{
	t.stop();
	return *this;
}

FrameAnimation& FrameAnimation::reset()
{
	t.reset();
	return *this;
}