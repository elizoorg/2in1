#pragma once
#include "SDL.h"
#include "Button.h"
#include "Label.h"
#include <vector>
#include "DynamicImage.h"
#include "Player.h"
#include "Item.h"
#include "Coin.h"
#include "Background.h"
#include "GUI.h"
#include "GUI.h"
#include "Box.h"
#include "Poop.h"
#include "ScoreManager.h"
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
	void Reset();
private:

	enum gamemodes {
		MENU, GAME, TABLE, PAUSE, NAMEINPUT, ENDGAME
	};

	SDL_Window* window;
	SDL_Renderer* render;
	SDL_Event event;

	bool _end;
	int mouseX, mouseY;

	string inputText = "Player";

	ScoreManager scoreManager;

	int score = 0;

	Label label;
	DynamicImage* image;

	Item* item;
	Coin* coin;
	Box* box;
	Poop* poop;

	long long int start = 0;
	long long ms = 0;
	long long mt = 0;

	int gamemode = 0;

	Player* player;

	GUI menugui;
	GUI maingui;
	GUI tablegui;

	vector <Item*> items;

	Button* button;
};
