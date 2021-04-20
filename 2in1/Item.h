#pragma once
#include "Image.h"
#include "SDL.h"
#include <iostream>
using namespace std;
class Item
{
public:
	Item();
	~Item();
	Item(SDL_Renderer* render, string name);
	void Update();
	void Draw(SDL_Renderer* render);
private:


protected:
	int value;
	int x, y;
	Image* image;
};

