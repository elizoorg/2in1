#include "Item.h"

Item::Item()
{
}

Item::~Item()
{
}

Item::Item(SDL_Renderer* render, string name)
{
	image = new Image(render, name);
	x = rand() % 5500 + 3000;
	belt = 0;
	y = belt * 128 + 264;
}

void Item::Update()
{
	x -= 100;
}

bool Item::Dead(int bbel)
{
	if (x < 228) {
		x = rand() % 5500 + 3000;
		belt = 0;
		y = belt * 128 + 264;
		return belt == bbel;
	}

	return false;
}

void Item::Draw(SDL_Renderer* render)
{
	image->Draw(render, x, y);
}