#include "Button.h"

Button::Button()
{
}

Button::~Button()
{
}

Button::Button(int x, int y, int w, int h)
{
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}



void Button::Draw(SDL_Renderer* render, SDL_Color color)
{
	SDL_SetRenderDrawColor(render, color.r, color.g, color.b, 0);
	SDL_RenderFillRect(render, &rect);
	SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
}

bool Button::isIntersect(int x, int y)
{
	return (x>rect.x) && (x<rect.x+rect.w) && (y>rect.y) && (y<rect.y+rect.h);
}
