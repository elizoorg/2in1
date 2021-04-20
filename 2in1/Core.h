#pragma once
#include "SDL.h"
#include "Button.h"
#include "Label.h"
#include <vector>
#include "DynamicImage.h"
#include "Item.h"
#include "Coin.h"
using namespace std;
class Core
{
public:
	int Run();
	~Core();
	Core() {};
private:
	bool Init();
	bool Update();
	void Draw();
	void Loop();
private:
	SDL_Window* window;
	SDL_Renderer* render;
	SDL_Event event;

	bool _end;
	int mouseX, mouseY;

	Label label;
	DynamicImage* image;

	Item* item;
	Coin* coin;

	vector <Item*> items;

	Button *button;
	vector <Button*> buttons;

};

