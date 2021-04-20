#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
using namespace std;
class Label
{
public:
	Label();
	~Label();
	void InitFont(string str, int size);
	void DrawString(SDL_Renderer* render, string str, int x, int y);
	void DrawInt(SDL_Renderer* render, int a, int x, int y);
private:
	TTF_Font* font;
	SDL_Color color{ 255,0,0 };
	SDL_Surface* temp;
	SDL_Texture* text;
	SDL_Rect clipRect;
};
