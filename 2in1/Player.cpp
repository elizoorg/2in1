#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

Player::Player(SDL_Renderer* render)
{
	playerTexture = new DynamicImage(render, "player.png", 64);
}

int Player::getBelt()
{
	return belt;
}

void Player::UpdatePosition(bool up)
{
	if (up) belt++;
	else belt--;
	if (belt < 1) belt = 1;
	if (belt > 3) belt = 3;
}

void Player::Draw(SDL_Renderer* render)
{
	playerTexture->Update();
	playerTexture->Draw(render, 196, 128 * (belt - 1) + 264);
}