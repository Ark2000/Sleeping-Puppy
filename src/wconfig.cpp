#include "wconfig.h"

const char* W_CAPTION = "SDL_TEST";	//窗口标题
int W_WIDTH = 240;	//窗口宽度
int W_HEIGHT = 160; //窗口高度
int W_is_config = 0;	//标记是否在CONFIG函数内部（只有在INIT函数内才能调用SetWindow函数）