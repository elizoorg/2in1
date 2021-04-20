#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <iostream>
using namespace std;
class Image
{
public:
	Image();
	~Image();
	Image(SDL_Renderer* render, string name);
	void Draw(SDL_Renderer* render,int x,int y);
private:
	SDL_Texture* texture;
	SDL_Rect s_Rect;
};

