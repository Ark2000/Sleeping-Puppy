#pragma once
#include <cstdint>
typedef uint32_t Color;

struct RGBA {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
	RGBA();
	RGBA(Color col);
};