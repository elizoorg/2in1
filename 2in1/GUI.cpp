#include "GUI.h"

GUI::GUI()
{
}

GUI::~GUI()
{
	buttons.clear();
	labels.clear();
}

void GUI::addButton(Button *button)
{
	buttons.push_back(button);
}

void GUI::addLabel(Label *label)
{
	labels.push_back(label);
}

void GUI::setBackground(SDL_Renderer* render, string name)
{
	back = new Background(render, name);
}

void GUI::Update(int x,int y)
{
	size_t t;
	for (t=0; t < buttons.size(); t++) {
		if (buttons[t]->isIntersect(x, y)) { current = t; break; }
	}
	if (t == buttons.size())
		current = -1;
}

void GUI::Draw(SDL_Renderer* render)
{
	back->Draw(render);
	for (auto a : buttons) {
		a->Draw(render);
	}
}
