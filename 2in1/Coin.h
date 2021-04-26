#pragma once
#include "Item.h"
class Coin : public Item
{
public:
	Coin();
	~Coin();
	Coin(SDL_Renderer* render, string name) :Item(render, name) {
		value = 5;
	};
};
