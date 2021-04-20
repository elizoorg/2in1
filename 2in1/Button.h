#pragma once
#include "SDL.h"
#include <string>
using namespace std;
class Button
{
public:
	Button();
	~Button();
	Button(int x, int y, int w, int h);

	void Draw(SDL_Renderer* render, SDL_Color color);
	bool isIntersect(int x, int y);
private:
	SDL_Rect rect;
	string label;

};

