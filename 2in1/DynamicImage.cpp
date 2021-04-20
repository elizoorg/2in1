#include "DynamicImage.h"

DynamicImage::DynamicImage()
{
}

DynamicImage::~DynamicImage()
{
}

DynamicImage::DynamicImage(SDL_Renderer* render, string name, int xSpeed)
{
	SDL_Surface* temp;
	temp = IMG_Load(name.c_str());
	if (!temp) cout << "Нельзя создать поверхность\n";
	texture = SDL_CreateTextureFromSurface(render, temp);
	if (!texture) cout << "Нельзя создать текстуру\n";
	d_Rect.w = d_Rect.h = s_Rect.w = s_Rect.h = temp->h;
	width = temp->w;
	SDL_FreeSurface(temp);
	speedX = xSpeed;
}
