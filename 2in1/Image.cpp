#include "Image.h"

Image::Image()
{
}

Image::~Image()
{
}

Image::Image(SDL_Renderer* render, string name)
{
	SDL_Surface* temp;
	temp = IMG_Load(name.c_str());
	if (!temp) cout << "Нельзя создать поверхность\n";
	texture = SDL_CreateTextureFromSurface(render, temp);
	if (!texture) cout << "Нельзя создать текстуру\n";
	s_Rect.w = s_Rect.h = temp->w;
	SDL_FreeSurface(temp);
}

void Image::Draw(SDL_Renderer* render, int x, int y)
{
	s_Rect.x = x;
	s_Rect.y = y;
	SDL_RenderCopy(render, texture, 0, &s_Rect);
}
