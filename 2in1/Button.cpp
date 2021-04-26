#include "Button.h"

Button::Button()
{
}

Button::~Button()
{
}

Button::Button(int x, int y, int w, int h, SDL_Color color1, SDL_Color color2)
{
	col1 = color1;
	col2 = color2;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}

void Button::Draw(SDL_Renderer* render)
{
	if (pressed)
		SDL_SetRenderDrawColor(render, col1.r, col1.g, col1.b, 0);
	else
		SDL_SetRenderDrawColor(render, col2.r, col2.g, col2.b, 0);
	SDL_RenderFillRect(render, &rect);
	SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
}

bool Button::isIntersect(int x, int y)
{
	pressed = (x > rect.x) && (x < rect.x + rect.w) && (y > rect.y) && (y < rect.y + rect.h);
	return pressed;
}