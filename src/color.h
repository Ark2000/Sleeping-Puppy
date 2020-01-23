#pragma once
#include <cstdint>

struct Color {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
	uint32_t hex;
	Color();
	Color(uint32_t hex_);
	Color(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t a_ = 255);
};