#include "text.h"
#include <cassert>

const char* font_bitmap = "iVBORw0KGgoAAAANSUhEUgAAAGgAAABAAgMAAACLjdppAAAABGdBTUEAALGPC/xhBQAAACBjSFJNAAB6JgAAgIQAAPoAAACA6AAAdTAAAOpgAAA6mAAAF3CculE8AAAACVBMVEXtHCQAAAD///9YQpCFAAAAAXRSTlMAQObYZgAAAAFiS0dEAmYLfGQAAAAJcEhZcwAAEnQAABJ0Ad5mH3gAAAAHdElNRQfkARkJKReZNOMyAAACeElEQVQ4y31UUY7rMAjE0vLfSnAfV6r/qWTf/yo7A07a7etr0jSJx8DAQEQ+HFq31n226dOXrzbNNGS5ejcVDeVh2nCqWetieBd3wT41wctFLyYbgokvQjOh0DCBc0KhYgMvL1ZOK6NVgyEd7lhSsWoloZNhb4sMNcBwmcqXA54C8fZlPOAMvpY43WqmYNf7EzLQHYxKyIUUrHbZJcQQUFmg2WJDo4EK83NAYogksyBfihS0sWBVSds5hWNzY3mTYZfpWSoWijTwtEDfmcOEPMFnxAgX7U/hDHc7RFRuEEYhhay2DvjqVBACm0glDPpOEoMOyRCxNEVhkUuFhJjhkJ086qK57bBiRuOKWIjCFIwpWOT/X1E8kl//pNDHxd2Tb07gd+ow5vcq5ZRDIPz+0euE9EWvalVCcAWu1u4pCvTC+49ke2HZO6gHC0UXwlhJpcuSN3Ly9WBw6gudZ3VkrljVPHk1zkuSyugJ5dhwpjyo3gGxewGhA5EJWJEjqsKCwcrZcyTPKcx2E6ZbU1k12K5wk5IGocHKj8aJbNa+HX45uKOxVPFHcb5Ao+x68OzZNHsiKyUDdW6LNk8oslCsd3qAHAv1Zs1rC8lPebPKrkdvUPszFlsNm4shaAw5GSbjfvlPOi/PDL2HybIaGXlmDKk2w7iTjMVz+EiXXbdyIWKTkpxV/gUhbNkN48TLCi4J2QHB6ojFVaX3J6Sb4e6rhkvWKt7lGXJaNIwdsyKEC7OOocUHFKVVNHdBGlE62bxfH2NN1LNT/onP8+22aZQVT45i6OVnPHahxiPUw4PgCZXV7YZPG5w90KYfHDap84WGb/KpbkpZ5H8ButiSNX69CcUAAAAldEVYdGRhdGU6Y3JlYXRlADIwMjAtMDEtMjVUMDk6NDE6MjMrMDA6MDDeWKTPAAAAJXRFWHRkYXRlOm1vZGlmeQAyMDIwLTAxLTI1VDA5OjQxOjIzKzAwOjAwrwUccwAAAABJRU5ErkJggg==";
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

void Print(const char* string, const Vec2& pos, const Vec2& w_h)
{
	const char* p = string;
	char c;
	int col = pos.x;
	int row = pos.y;
	while((c = *p++)) {
		//可打印字符
		if (c != '\n') {
			assert(c >= 0 && c < 128);
			if (c != ' ') {
				int id = code[(int)c];
				default_glyphs->draw(id, pos + Vec2(col, row), pos + Vec2(col, row) + Vec2(w_h.x, w_h.y));
			}
			col += w_h.x;
		} else {
			//控制字符
			col = pos.x;	//回车
			row += w_h.y;	//换行
		}
	}
}