#pragma once
#include "SDL.h"
#include <string>
using namespace std;
class Button
{
public:
	Button();
	~Button();
	Button(int x, int y, int w, int h,SDL_Color color1, SDL_Color color2);

	void Draw(SDL_Renderer* render);
	bool isIntersect(int x, int y);
private:
	SDL_Rect rect;
	string label;
	bool pressed;
	SDL_Color col1;
	SDL_Color col2;

};

