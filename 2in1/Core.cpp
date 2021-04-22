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
    SDL_Color col{ 255,0,0 };
    SDL_Color col2{ 255,255,255 };
    button = new Button(100, 100, 300, 100,col,col2);
    menugui.addButton(button);
   
    button = new Button(300, 300, 300, 100,col,col2);
    menugui.addButton(button);

    button = new Button(300, 500, 300, 100, col, col2);
    menugui.addButton(button);

    label.InitFont("arial.ttf", 32);
    menugui.addLabel(&label);
    

    for (int i = 0; i < 10; i++) {
        item = new Item(render, "box.png");
        coin = new Coin(render, "coin.png");
        items.push_back(item);
        items.push_back(coin);
    }

    image = new DynamicImage(render, "belt.png",1);
    player = new DynamicImage(render, "player.png", 64);
    game = new Background(render, "gamefon.png");
    menu = new Background(render, "fon.png");

    return window && render;
}

bool Core::Update()
{
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT: _end = false; break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&mouseX, &mouseY);
            break;

        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_DOWN) belt++;
            if (event.key.keysym.sym == SDLK_UP) belt--;
            if (belt < 1) belt = 1;
            if (belt > 3) belt = 3;
            break;
        }
    }


    image->Update();
    player->Update();
    menugui.Update(mouseX,mouseY);

    for (auto a : items)
        a->Update();
    for (auto a : items) 
        if (a->Dead(belt - 1)) score++;
    return false;
}

void Core::Draw()
{
    SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
    SDL_RenderClear(render);
    menu->Draw(render);

    menugui.Draw(render);
   
    label.DrawInt(render, score, 0, 200);
    
    for(int i =0;i<10;i++)
        for(int j = 0 ; j < 3; j++)
    image->Draw(render,260+64*i,128*j+264);
    player->Draw(render, 196, 128 * (belt - 1) + 264);

    for (auto a : items)
        a->Draw(render);

    SDL_RenderPresent(render);
}

void Core::Loop()
{
    Update();
    Draw();
}
