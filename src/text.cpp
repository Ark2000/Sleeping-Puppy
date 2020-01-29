#include "text.h"
#include "color.h"
#include <cstring>
#include <cassert>

const char* font_bitmap = "iVBORw0KGgoAAAANSUhEUgAAAGgAAABAAQMAAADMLaC5AAAAAXNSR0IB2cksfwAAAAlwSFlzAAASdAAAEnQB3mYfeAAAAAZQTFRFAAAA////pdmf3QAAAAJ0Uk5TAP9bkSK1AAACFklEQVR4nFVSUYrbMBCdsiD6IbL5HIpJrzCpFiHwIEq/e4J+FIFg9iMhMQR2DTUyPcYeoMfYr0CP0J8eYG/hdORtmmaMjR9v5o3ejAD+BemLZVXGcSV8e+gzsHN+vXaCxtEjiEvu7i4p8jSCxOSYU0HDtIEyc/eC4tdZM7WOtE5/FFXN/r0wH8YM15GbwvqI5CwjHLwTJ19mJPAtK+pQkZfPsM9RYqNo0zDCfaYdLxSNHteQPbHXbvyYMatmvzgwF8yZR4AOFtBAh7YLs0kDvlolBODIevrWB3b4AMZJlF5atB5HiC5JIXFoGTfqSCRRdJXL0H7llntz4O2Bz44GgHDx9fbKJZ5zeNduY5z9FRAV9ensb0Y8+xNUFCOZd8Kjjx9AmEw/2BZ9NkV1+ttL0+tgZF4UHSqj96BuZJVIRFjRDo3xQzIVjVCwacQMliPqQB6QzGh0hAZBd6vH0DQSC8pxKTomJg418zoQGrI0/94ARF0Eoqt2VSdJk8iuKlIdti2QHScodRwGd/CX00UMTqDWBcCkmrmFqomAH/9rtZy/C+h0a4kD0EJrACUT2e28TirW7Antz0pAAmP3ZLW1XgFUDvdk7HzmWgeJbl6RCnU6tjcMJ5XXKGW7DEtFJ8Cu/X6awqCIj1q3+/F7GkLAF3mqKspN08DHT8/1ZM/HYZimGSn39BLCr+GSudR4Vem0g96WUDv8AdABuSC21eK3AAAAAElFTkSuQmCC";
const char* chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

int code[128];

TiledTexture default_glyphs;

void LoadFont()
{
	Texture font_png = ImportTextureFromBase64(font_bitmap);
	default_glyphs = ImportTiledTextureFromTexture(font_png, 13, 8);
	for (int i = 0; i < 128; ++i) code[i] = -1;
	const char* p = chars;
	int cnt = 0;
	while (*p) {
		code[(int)*p] = cnt++;
		++p;
	}
}

void Print_(const char* string, const Vec2& pos, const Vec2& w_h, const Color& color)
{
	const char* p = string;
	char c;
	int col = pos.x;
	int row = pos.y;

	//default_glyphs->texture.data这个东西不能是private...
	SDL_SetTextureColorMod(default_glyphs->texture.data, color.r, color.g, color.b);

	while((c = *p++)) {
		//可打印字符
		if (c != '\n') {
			assert(c >= 0 && c < 128);
			if (c != ' ') {
				int id = code[(int)c];
				default_glyphs->draw(id, Vec4(col, row, w_h.x, w_h.y), 0);
			}
			col += w_h.x;
		} else {
			//控制字符
			col = pos.x;	//回车
			row += w_h.y;	//换行
		}
	}
}

void PrintCenter_(const char* string, const Vec4& rect, const Vec2& w_h, const Vec2& diff, const Color& color)
{
	SDL_SetTextureColorMod(default_glyphs->texture.data, color.r, color.g, color.b);
	
	Vec2 pos;

	{
		int lines = 0;
		const char* p = string;
		while (*p) if (*p++ == '\n') ++lines;
		++lines;
		pos.y = rect.y + (rect.h - lines * w_h.y) / 2;
	}

	{
		const char* p0 = string;
		const char* p1 = string;
		while (*p1) {
			if (*p1 == '\n') {
				pos.x = rect.x + (rect.w - (p1 - p0) * w_h.x) / 2;
				for (const char* p = p0; p != p1; ++p) {
					if (*p != ' ') {
						default_glyphs->draw(code[(int)*p], Vec4(pos.x + diff.x, pos.y + diff.y, w_h.x, w_h.y), 0);
					}
					pos.x += w_h.x;
				}
				++p1;
				p0 = p1;
				pos.y += w_h.y;
			} else {
				++p1;
			}
		}
		pos.x = rect.x + (rect.w - (p1 - p0) * w_h.x) / 2;
		for (const char* p = p0; p != p1; ++p) {
			if (*p != ' ') {
				default_glyphs->draw(code[(int)*p], Vec4(pos.x + diff.x, pos.y + diff.y, w_h.x, w_h.y), 0);
			}
			pos.x += w_h.x;
		}
	}
}