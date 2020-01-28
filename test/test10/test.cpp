#include "..\..\src\api.h"
#include <cstdio>

#include <SDL_mixer.h>

void CONFIG()
{
	SetWindow("MUSIC TEST", 640, 360);
}

Mix_Chunk* click;
Mix_Music* music;

void INIT()
{
	click = Mix_LoadWAV("43678_stijn_click2.ogg");
	music = Mix_LoadMUS("sample_music.ogg");
}

void MAINLOOP()
{
	static char buffer[256];
	static int volume = 128;

	if (KeyUpE(KEY_ESCAPE)) QuitSys();

	if (KeyDownE(KEY_MLEFT)) {
		Mix_PlayChannel(-1, click, 0);
	}
	if (KeyDownE(KEY_MRIGHT)) {
		Mix_PlayMusic(music, 0);
	}

	if (KeyDown(KEY_W)) {
		if (volume < 128) ++volume;
		Mix_Volume(-1, volume);
		Mix_VolumeMusic(volume);
	}
	if (KeyDown(KEY_S)) {
		if (volume > 0) --volume;
		Mix_Volume(-1, volume);
		Mix_VolumeMusic(volume);
	}

	DrawClear();
	sprintf(buffer, "%d", Mix_Volume(-1, -1));
	Print(buffer, Vec2(0, 0), Vec2(16, 16));

}

void EXIT()
{
	Mix_FreeChunk(click);
}