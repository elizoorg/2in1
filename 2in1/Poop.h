#pragma once
#include "Item.h"
class Poop : public Item
{
public:
	Poop();
	~Poop();
	Poop(SDL_Renderer* render, string name) :Item(render, name) {
		value = -3;
	};
};