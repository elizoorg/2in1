#include "Background.h"

Background::Background()
{
}

Background::~Background()
{
}

Background::Background(SDL_Renderer* render, string name)
{
	SDL_Surface* temp;
	temp = IMG_Load(name.c_str());
	if (!temp) cout << "Нельзя создать поверхность\n";
	texture = SDL_CreateTextureFromSurface(render, temp);
	if (!texture) cout << "Нельзя создать текстуру\n";
	SDL_FreeSurface(temp);
}
