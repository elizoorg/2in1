#pragma once
#include "Button.h"
#include "Label.h"
#include "Background.h"
#include <fstream>
#include <vector>
using namespace std;
class GUI
{
public:
	GUI();
	~GUI();
	void addButton(Button* button);
	void addLabel(Label label);
	void setBackground(SDL_Renderer* render, string name);
	void DrawString(SDL_Renderer* render, string s, int x, int y);
	void DrawStringCentered(SDL_Renderer* render, string s, int x, int y);
	void DrawInt(SDL_Renderer* render, int value, int x, int y);
	void Update(int x, int y);
	void Draw(SDL_Renderer* render);
	void DrawTable(SDL_Renderer* render);
	int getActiveButton() { return current; }
private:
	vector<Button*> buttons;
	Label labels;
	Background* back;
	int current;
};
