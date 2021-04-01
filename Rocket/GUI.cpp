#include "GUI.h"



GUI::GUI(int const& _width, int const& _height, LunarLander *_lander, Terrain *_terrain)
{
	width = _width ;
	height = _height ;
	lander = _lander ;
	terrain = _terrain ;
	visual.InitFont("Resourcess/arial.ttf",20);
	menuvisual.InitFont("Resourcess/18940.otf",64);
	screenSpacing = 600;
	textSpacing = 30 ;
}

void GUI::draw(SDL_Renderer* render)
{
	vec2f position = lander->getPosition() ;
	oss.str("") ; oss.clear() ; oss<<"Score : "<<lander->getScore() ;
	visual.DrawString(render,oss.str(), screenSpacing - width / 2.f, screenSpacing - height / 2.f);
	
	oss.str("") ; oss.clear() ; oss<<"Fuel : "<<(int)lander->getFuel() ;
	visual.DrawString(render, oss.str(), screenSpacing - width / 2.f, screenSpacing - height / 2.f + 2 * textSpacing);

	if(lander->isAlive())
	{
		oss.str("") ; oss.clear() ; 
		oss<<"Altitude : "<< (int)(Distance(lander->getPosition(),terrain->getPoint((int)( clamp((lander->getPosition().x-terrain->getCenterPosition().x-lander->getWidth()/2.f)/(float)terrain->getVertexSpacing() ,0,terrain->getSize()-1))))-lander->getHeight()+6) ;
	}
	else 
	{
		oss.str("") ; oss.clear() ; oss<<"Altitude : "<< 0 ; 
	}
	visual.DrawString(render, oss.str(), width / 2.f - 250, screenSpacing - height / 2.f);
	oss.str("") ; oss.clear() ; oss<<"Horizontal Speed : "<<(int)lander->getSpeed().x ;
	visual.DrawString(render, oss.str(), width / 2.f - 250, screenSpacing - height / 2.f + textSpacing);
	oss.str("") ; oss.clear() ; oss<<"Vertical Speed : "<<(int)lander->getSpeed().y ;
	visual.DrawString(render, oss.str(), width / 2.f - 250, screenSpacing - height / 2.f + 2 * textSpacing);

	if(!lander->isAlive() && lander->isWin()) 
	{
		oss.str("") ; oss.clear() ; oss<<"You landed succesfully ! Fuel bonus ! " ;	
		visual.DrawString(render, oss.str(), 200, 0);

	}
	else if(!lander->isAlive() && !lander->isWin()) 
	{
		oss.str("") ; oss.clear() ; oss<<"You crashed ! Fuel tank destroyed. " ;
		visual.DrawString(render, oss.str(), 200, 0);
	}
}

void GUI::score(SDL_Renderer* render,int score)
{
	bool quit = false;
	SDL_Event e;
	SDL_Color textColor = { 255, 0, 0, 0xFF };
	std::string inputText = "PlayerName";
	SDL_StartTextInput();
	while (!quit)
	{

		bool renderText = false;
		while (SDL_PollEvent(&e) != 0)
		{

			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_RETURN) {
					quit = true;
				}
				if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0)
				{

					inputText.pop_back();
					renderText = true;
				}

				else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
				{
					SDL_SetClipboardText(inputText.c_str());
				}

				else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
				{
					inputText = SDL_GetClipboardText();
					renderText = true;
				}
			}
			else if (e.type == SDL_TEXTINPUT)
			{

				if (!(SDL_GetModState() & KMOD_CTRL && (e.text.text[0] == 'c' || e.text.text[0] == 'C' || e.text.text[0] == 'v' || e.text.text[0] == 'V')))
				{

					inputText += e.text.text;
					renderText = true;
				}
			}
		}

		if (renderText)
		{
			SDL_SetRenderDrawColor(render, 0x0, 0x0, 0x0, 0x0);
			if (inputText != "")
			{
				SDL_RenderClear(render);
				visual.DrawString(render, inputText.c_str(), 448, 340);
				
			}
			else
			{	
				SDL_RenderClear(render);
				visual.DrawString(render, " ", 448, 340);
			}
			SDL_RenderPresent(render);
		}



	}
	SDL_StopTextInput();

	ifstream ifile;
	ofstream ofile;

	string fname;
	int fscore;
	int c = 0;
	ifile.open("score.txt");
	if (!ifile) cout << "Error to open ifile\n";
	ofile.open("fscore.txt");
	if (!ofile) cout << "Error to open ofile\n";
	while (c < 10 && ifile >> fname >> fscore) {	
		if (fscore < score) {		
			ofile << inputText << " " << score << endl;
			score = 0;
			c++;
		}
		ofile << fname << " " << fscore << endl;
		c++;
	}

	ifile.close();
	ofile.close();

	if(remove("score.txt") != 0)
		perror("Error deleting file");
	else
		puts("File successfully deleted");
	if (rename("fscore.txt", "score.txt") != 0)
		perror("Error renaming file");
	else
		cout << "File renamed successfully";
	SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
	SDL_RenderClear(render);
	int y = 245;
	int k=0;
	ifile.open("score.txt");
	while (ifile >> fname >> fscore) {
		visual.DrawString(render, fname, 398, y + k * 30);
		visual.DrawInt(render,fscore, 605, y + (k++) * 30);
	}
	SDL_RenderPresent(render);
	ifile.close();

	SDL_Delay(5000);
}

bool GUI::Menu(SDL_Renderer* render)
{

	bool done = false;


	SDL_RenderClear(render);
	SDL_Color text_color = { 221,214,196 };
	SDL_Surface* temp = IMG_Load("Resourcess/menu.bmp");
	if (!temp) cout << "Error";
	SDL_Texture* menu = SDL_CreateTextureFromSurface(render, temp);
	SDL_FreeSurface(temp);
	SDL_RenderCopy(render, menu, 0, 0);
	menuvisual.DrawString(render, u8"Старт", 520, 200);
	menuvisual.DrawString(render, u8"Правила", 520, 320);
	menuvisual.DrawString(render, u8"Выход", 520, 440);
	int x=0, y=0;
	SDL_RenderPresent(render);

	SDL_Event event;
	while (true) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_RETURN) return true;
				if (event.key.keysym.sym == SDLK_ESCAPE) return false;
			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&x, &y);
				break;
			}
		}
		if (x > 520 && x < 968) {
			if (y > 200 && y < 264) return true;
			if (y > 320 && y < 384) {
				SDL_RenderClear(render);
				visual.DrawString(render, u8"Цель игры - посадить луноход", 320, 200);
				visual.DrawString(render, u8"Стрелка вверх - полет, стрелки вправо влево угол", 320, 260);
				visual.DrawString(render, u8"но за это вы тратите топливо", 320, 320);
				visual.DrawString(render, u8"Когда топливо упадет ниже 0 вы проиграете", 320, 380);
				visual.DrawString(render, u8"За каждое падение у вас отнимается топливо", 320, 440);
				visual.DrawString(render, u8"И вы появляетесь в совершенно другом месте", 320, 500);
				visual.DrawString(render, u8"Садить нужно аккуратно со скоростью ниже 25", 320, 560);
				visual.DrawString(render, u8"И саблюдать угод посадки (ниже 25)", 320, 620);
				SDL_RenderPresent(render);
				x = y = 0;
				SDL_Delay(5000);
				SDL_RenderCopy(render, menu, 0, 0);
				SDL_RenderCopy(render, menu, 0, 0);
				menuvisual.DrawString(render, u8"Старт", 520, 200);
				menuvisual.DrawString(render, u8"Правила", 520, 320);
				menuvisual.DrawString(render, u8"Выход", 520, 440);
				SDL_RenderPresent(render);
			}
			if (y > 440 && y < 504) return false;
		}
	}


	return false;
}
