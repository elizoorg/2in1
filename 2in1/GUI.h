#pragma once
#include "Button.h"
#include "Label.h"
#include "Background.h"
#include <vector>
using namespace std;
class GUI
{
public:
	GUI();
	~GUI();
	void addButton(Button *button);
	void addLabel(Label *label);
	void setBackground(SDL_Renderer* render, string name);
	void Update(int x,int y);
	void Draw(SDL_Renderer* render);
	int getActiveButton() { return current; }
private:
	vector<Button*> buttons;
	vector<Label*> labels;
	Background* back;
	int current;
};

