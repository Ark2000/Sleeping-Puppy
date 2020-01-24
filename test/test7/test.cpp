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

	tiled = ImportTiledTextureFromTexture(
			ImportTextureFromFile("galletcity_tiles.png"),
			8, 21
	);

	bird_fly = 	ImportFrameAnimationFromTiledTexture(
				ImportTiledTextureFromTexture(
				ImportTextureFromFile("flying-creature-cycle-skin.png"),
				7, 1
				), 100, 0, 6);
}

int t = 0;
void MAINLOOP()
{
	DrawClear();
	DrawTile(tiled, (t / 30) % (8*21), Vec2(0, 0), 8);
	DrawAnimation(bird_fly, Vec2(100, 100), 5);
	++t;
}

void EXIT()
{
	
}