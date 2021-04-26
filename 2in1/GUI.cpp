#include "GUI.h"

GUI::GUI()
{
}

GUI::~GUI()
{
	buttons.clear();
}

void GUI::addButton(Button* button)
{
	buttons.push_back(button);
}

void GUI::addLabel(Label label)
{
	labels = label;
}

void GUI::setBackground(SDL_Renderer* render, string name)
{
	back = new Background(render, name);
}

void GUI::DrawString(SDL_Renderer* render, string s, int x, int y)
{
	labels.DrawString(render, s, x, y);
}

void GUI::DrawStringCentered(SDL_Renderer* render, string s, int x, int y)
{
	labels.DrawStringCentered(render, s, x, y);
}

void GUI::DrawInt(SDL_Renderer* render, int value, int x, int y)
{
	labels.DrawInt(render, value, x, y);
}

void GUI::Update(int x, int y)
{
	size_t t;
	for (t = 0; t < buttons.size(); t++) {
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

void GUI::DrawTable(SDL_Renderer* render)
{
	ifstream ifile;
	ifile.open("score.txt");
	int k = 0;
	string fname;
	int fscore;
	while (ifile >> fname >> fscore) {
		labels.DrawString(render, fname, 198, 100 + k * 30);
		labels.DrawInt(render, fscore, 605, 100 + (k++) * 30);
	}
	ifile.close();
}
