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
	x = rand() % 1000 + 1000;
	belt = rand() % 3;
	y = belt*128 + 264;
}

void Item::Update()
{
	x--;
}

bool Item::Dead(int bbel)
{
	if (x < 260) {
		x = rand() % 1000 + 1000;
		belt = rand() % 3;
		y = belt * 128 + 264;
		return belt == bbel;
	}
	return false;
}

void Item::Draw(SDL_Renderer* render)
{
	image->Draw(render, x, y);
}
