#pragma once
#include "Item.h"
class Box : public Item
{
public:
	Box();
	~Box();
	Box(SDL_Renderer* render, string name) :Item(render, name) {
		value = 5;
	};
};