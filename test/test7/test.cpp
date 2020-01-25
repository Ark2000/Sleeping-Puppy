#include "..\..\src\api.h"
#include <cstdlib>

void CONFIG()
{
	SetWindow("HELLO", 256, 256);
}

TiledTexture tiled;
FrameAnimation bird_fly;

void INIT()
{
	//太他妈丑了...

	Texture galletcity_tiles_png = ImportTextureFromFile("galletcity_tiles.png");
	Texture flying_creature_cycle_skin_png = ImportTextureFromFile("flying-creature-cycle-skin.png");

	tiled = ImportTiledTextureFromTexture(galletcity_tiles_png, 8, 21);
	bird_fly = 	ImportFrameAnimationFromTexture(flying_creature_cycle_skin_png, 7, 1, 100, 0, 6);
}

int t = 0;
void MAINLOOP()
{
	DrawClear();
	DrawTile(tiled, (t / 30) % (8*21), Vec2(100, 100), 8, 1);
	DrawAnimation(bird_fly, Vec2(100, 100), 5, 1);
	++t;
}

void EXIT()
{
	
}