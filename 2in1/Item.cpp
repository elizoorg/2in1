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
	y = rand() % 3 * 128 + 134;
}

void Item::Update()
{
	x--;
	if (x < 260) {
		x = rand() % 1000 + 1000;
		y = rand() % 3 * 128 + 134;
	}
}

void Item::Draw(SDL_Renderer* render)
{
	image->Draw(render, x, y);
}
