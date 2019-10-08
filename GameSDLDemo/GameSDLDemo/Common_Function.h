
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <Windows.h>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <SDL_ttf.h>

const int SCREEN_WIDTH = 300;
const int SCREEN_HEIGHT = 500;
const int SCREEN_BPP = 32;
const int NUM_THREATS = 3;

static SDL_Surface* g_screen = NULL;
static SDL_Surface* g_bkground = NULL;
static SDL_Event g_even;
static SDL_Surface *g_img_menu = NULL;
namespace SDLCommonFunc
{
	SDL_Surface* LoadImage(std::string file_path);
	SDL_Rect ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	void ApplySurfaceclip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y);
	void CleanUp();
	bool CheckCollision(const SDL_Rect& object_1, const SDL_Rect& object_2);
	int ShowMenu(SDL_Surface* des, TTF_Font* font);
	bool CheckFocusSwitchRect(const int& x,const int& y,const SDL_Rect& rect); 
}

#endif