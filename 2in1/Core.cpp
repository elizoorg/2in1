#include "Core.h"

int Core::Run()
{
	_end = Init();
	while (_end) Loop();
	return 0;
}

Core::~Core()
{
	delete button;
	delete image;	
	delete player;
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}

bool Core::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	window = SDL_CreateWindow("2in1", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		900, 600, 0);
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_SOFTWARE);
	SDL_Color col{ 220,220,220 };
	SDL_Color col2{ 128,128,128 };
	button = new Button(300, 50, 300, 100, col, col2);
	menugui.addButton(button);

	button = new Button(300, 250, 300, 100, col, col2);
	menugui.addButton(button);

	button = new Button(300, 450, 300, 100, col, col2);
	menugui.addButton(button);

	label.InitFont("arial.ttf", 32);
	menugui.addLabel(label);
	maingui.addLabel(label);

	player = new Player(render);

	menugui.setBackground(render, "fon.png");
	maingui.setBackground(render, "gamefon.png");

	for (int i = 0; i < 10; i++) {
		box = new Box(render, "box.png");
		poop = new Poop(render, "poop.png");
		coin = new Coin(render, "coin.png");
		items.push_back(box);
		items.push_back(coin);
		items.push_back(poop);
	}

	image = new DynamicImage(render, "belt.png", 1);

	start = SDL_GetTicks();

	return window && render;
}

bool Core::Update()
{
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			if (gamemode != 0) { gamemode = 0; Reset(); }
			else  _end = false;
			break;
		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&mouseX, &mouseY);
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				if (gamemode == MENU) {
					if (menugui.getActiveButton() == 0) gamemode = GAME;
					if (menugui.getActiveButton() == 1) gamemode = TABLE;
					if (menugui.getActiveButton() == 2) _end = false;
				}
			}

		case SDL_KEYDOWN:
			if (gamemode == TABLE) {
				if (event.key.keysym.sym == SDLK_RETURN) {
					gamemode = MENU;
				}
			}
			if (gamemode == PAUSE) {
				if (event.key.keysym.sym == SDLK_RETURN) {
					gamemode = GAME; mt = ms; start = SDL_GetTicks();
				}
				if (event.key.keysym.sym == SDLK_ESCAPE) gamemode = 0;
			}
			if (gamemode == GAME) {
				if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) player->UpdatePosition(true);
				if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) player->UpdatePosition(false);
				if (event.key.keysym.sym == SDLK_ESCAPE) gamemode = PAUSE;
			}
			if (gamemode == NAMEINPUT) {
				if (event.key.keysym.sym == SDLK_RETURN) {
					gamemode = TABLE;
					scoreManager.UpdateScore(inputText, score);
					Reset();
				}
				if (event.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0)
				{
					inputText.pop_back();
				}
				else if (event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
				{
					SDL_SetClipboardText(inputText.c_str());
				}

				else if (event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
				{
					inputText = SDL_GetClipboardText();
				}
			}

			break;
		case SDL_TEXTINPUT:
			if (!(SDL_GetModState() & KMOD_CTRL && (event.text.text[0] == 'c' || event.text.text[0] == 'C' || event.text.text[0] == 'v' || event.text.text[0] == 'V')) && inputText.length()<15)
			{
				inputText += event.text.text;
			}
		}
	}

	if (gamemode == MENU) {
		menugui.Update(mouseX, mouseY);
	}
	if (gamemode == GAME) {
		image->Update();
		for (auto a : items)
			a->Update();
		for (auto a : items)
			if (a->Dead(player->getBelt() - 1)) score += a->getValue();
		ms = SDL_GetTicks() - start + mt;
		if (ms > 5000) { gamemode = NAMEINPUT; SDL_StartTextInput(); }
	}

	return false;
}

void Core::Draw()
{
	SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
	SDL_RenderClear(render);

	if (gamemode == MENU) {
		menugui.Draw(render);
		menugui.DrawStringCentered(render, "Start", 450, 75);
		menugui.DrawStringCentered(render, "Score", 450, 275);
		menugui.DrawStringCentered(render, "Exit", 450, 475);
	}
	if (gamemode == GAME) {
		maingui.Draw(render);

		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 3; j++)
				image->Draw(render, 260 + 64 * i, 128 * j + 264);
		player->Draw(render);

		for (auto a : items)
			a->Draw(render);

		maingui.DrawInt(render, score, 850, 20);
		maingui.DrawInt(render, (ms) / 1000, 100, 20);
		maingui.DrawString(render, "Time:", 20, 20);
		maingui.DrawString(render, "Score:", 750, 20);
	}
	if (gamemode == PAUSE) {
		maingui.Draw(render);
		maingui.DrawStringCentered(render, "Press enter to continue", 450, 300);
		maingui.DrawStringCentered(render, "Press escape to exit", 450, 350);
	}

	if (gamemode == NAMEINPUT) {
		maingui.Draw(render);
		maingui.DrawStringCentered(render, inputText, 450, 300);
	}
	if (gamemode == TABLE) {
		maingui.Draw(render);
		maingui.DrawTable(render);
	}

	SDL_RenderPresent(render);
}

void Core::Loop()
{
	Update();
	Draw();
	SDL_Delay(1000 / 60);
}

void Core::Reset()
{
	items.clear();
	for (int i = 0; i < 10; i++) {
		box = new Box(render, "box.png");
		poop = new Poop(render, "poop.png");
		coin = new Coin(render, "coin.png");
		items.push_back(box);
		items.push_back(coin);
		items.push_back(poop);
	}
	score = 0;
	ms = 0;
	start = SDL_GetTicks();
	mt = 0;
	inputText = "Player";
}