#include "color.h"
Color::Color():
	r(255), g(255), b(255), a(255), hex(0xffffffff) { }

Color::Color(uint32_t hex_):
	r((hex_ >> 24) & 0x000000ff),
	g((hex_ >> 16) & 0x000000ff),
	b((hex_ >> 8) & 0x000000ff),
	a(hex_ & 0x000000ff) { }

Color::Color(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t a_):
	r(r_), g(g_), b(b_), a(a_), 
	hex(a_ + b_ * 256 + g_ * 65536 + r_ * 16777216) { }