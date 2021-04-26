#pragma once
#include <SDL.h>
#include <string>
#include <iostream>
#include <SDL_image.h>
using namespace std;
class Background
{
public:
	Background();
	~Background();
	Background(SDL_Renderer* render, string name);
	void Draw(SDL_Renderer* render) {
		SDL_RenderCopy(render, texture, 0, 0);
	}
private:
	SDL_Texture* texture;
};
