#pragma once
#include <SDL.h>
#include <string>
#include <iostream>
#include <SDL_image.h>
using namespace std;
class DynamicImage
{
public:
	DynamicImage();
	~DynamicImage();
	DynamicImage(SDL_Renderer* render, string name, int xSpeed);

	void Draw(SDL_Renderer* render,int x,int y) {
		d_Rect.x = x;
		d_Rect.y = y;
		SDL_RenderCopy(render, texture, &s_Rect, &d_Rect);
	}
	void Update() {
		if (delay > 10) {
			s_Rect.x += speedX; delay = 0;
		}
		delay++;
		if (s_Rect.x > width - s_Rect.w) s_Rect.x = 0;
	}

private:
	SDL_Texture* texture;
	SDL_Rect s_Rect{ 0,0,0,0 };
	SDL_Rect d_Rect{ 0,0,0,0 };
	int width;
	int delay;
	int speedX;
};

