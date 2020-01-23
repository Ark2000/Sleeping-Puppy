#include "color.h"
#include <cstdio>
RGBA::RGBA():
	r(255), g(255), b(255), a(255) { }

RGBA::RGBA(Color col):
	r((col >> 24) & 0x000000ff),
	g((col >> 16) & 0x000000ff),
	b((col >> 8) & 0x000000ff),
	a(col & 0x000000ff) { }