#include "TextVisuliaser.h"
#include <string>
TextVisuliaser::TextVisuliaser()
{
}

TextVisuliaser::~TextVisuliaser()
{
}

void TextVisuliaser::InitFont(string str,int size)
{
	font = TTF_OpenFont(str.c_str(), size);
	if (!font) cout << "Unable to upload font \n";
}

void TextVisuliaser::DrawString(SDL_Renderer* render, string str, int x, int y)
{
	temp = TTF_RenderUTF8_Solid(font, str.c_str(), color);
	if (!temp) cout << "Нельзя создать поверхность\n";
	text = SDL_CreateTextureFromSurface(render, temp);
	if (!text) cout << "Нельзя создать текстуру\n";
	SDL_Rect rect{ x,y,temp->w,temp->h };
	SDL_RenderCopy(render, text, 0, &rect);
	SDL_FreeSurface(temp);
	SDL_DestroyTexture(text);
}

void TextVisuliaser::DrawInt(SDL_Renderer* render, int a, int x, int y)
{
	temp = TTF_RenderUTF8_Solid(font, to_string(a).c_str(), color);
	text = SDL_CreateTextureFromSurface(render, temp);
	SDL_Rect rect{ x,y,temp->w,temp->h };
	SDL_RenderCopy(render, text, 0, &rect);
	SDL_FreeSurface(temp);
	SDL_DestroyTexture(text);
}