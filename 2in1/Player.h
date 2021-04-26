#pragma once
#include "SDL.h"
#include "DynamicImage.h"
class Player
{
public:
	Player();
	~Player();
	Player(SDL_Renderer* render);
	int getBelt();
	void UpdatePosition(bool up);
	void Draw(SDL_Renderer* render);

private:
	DynamicImage* playerTexture;
	int belt = 1;
};
