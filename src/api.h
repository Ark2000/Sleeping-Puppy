#pragma once
#include "color.h"
#include "vec2.h"
#include "timer.h"
#include "texture.h"
#include "basicio.h"
#include "sound.h"

void SetWindow(const char* caption, int width, int height);

void DrawClear(const Color& col = 0xffffffff);
void DrawLine(const Vec2& pos0, const Vec2& pos1, const Color& col = 0x000000ff, int priority = 0);
void DrawRectB(const Vec4& rect, const Color& col = 0x000000ff, int priority = 0);
void DrawRect(const Vec4& rect, const Color& col = 0x000000ff, int priority = 0);
void DrawCircB(const Vec2& center, int radius, const Color& col = 0x000000ff, int priority = 0);
void DrawCirc(const Vec2& center, int radius, const Color& col = 0x000000ff, int priority = 0);

Timer CreateTimer();
void TimerStart(Timer& t);
void TimerStop(Timer& t);
void TimerReset(Timer& t);
int GetTime(Timer& t);

Texture ImportTextureFromFile(const char* path);
Texture ImportTextureFromBase64(const char* base64);
void DrawTexture(Texture& t, Vec2 pos, int scale = 1, int priority = 0);

TiledTexture ImportTiledTextureFromTexture(const Texture& t, int w, int h);
void DrawTile(TiledTexture& tt, int id, Vec2 pos, int scale = 1, int priority = 0);

FrameAnimation ImportFrameAnimationFromTiledTexture(const TiledTexture& tt, int interval, int sid, int eid, int loop = 1);
FrameAnimation ImportFrameAnimationFromTexture(const Texture& t, int w, int h, int interval, int sid, int eid, int loop = 1);
void DrawAnimation(FrameAnimation& fa, Vec2 pos, int scale = 1, int priority = 0);
void StartAnimation(FrameAnimation& fa);
void StopAnimation(FrameAnimation& fa);
void ResetAnimation(FrameAnimation& fa);

void Print(const char* string, const Vec2& pos, const Vec2& w_h = Vec2(8, 8), const Color& col = 0x000000ff, int priority = 255);
void PrintCenter(const char* string, const Vec4& rect, const Vec2& w_h = Vec2(8, 8), const Color& color = 0x000000ff, const Vec2& diff = Vec2(0, 0), int priority = 255);

int KeyDown(Key k);
int KeyDownE(Key k);
int KeyUpE(Key k);
int KeyTime(Key k);
Vec2 MousePos();

Music ImportMusicFromFile(const char* path);
Sound ImportSoundFromFile(const char* path);
void PlayMusic(Music mus, int loops);
void PauseMusic();
void ResumeMusic();
int MusicPlaying();
void PlaySound(Sound s, int loops);
void SetMusicVolume(int v);
void SetSoundVolume(int v);

int GetFPS();

void QuitSys();
