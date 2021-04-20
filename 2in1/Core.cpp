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
    buttons.clear();
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
    button = new Button(100, 100, 300, 100);
    buttons.push_back(button);
    button = new Button(300, 300, 300, 100);
    buttons.push_back(button);
    button = new Button(300, 500, 300, 100);
    buttons.push_back(button);

    for (int i = 0; i < 10; i++) {
        item = new Item(render, "box.png");
        coin = new Coin(render, "coin.png");
        items.push_back(item);
        items.push_back(coin);
    }

    image = new DynamicImage(render, "belt.png",1);


    label.InitFont("arial.ttf", 16);

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
        }
    }


    image->Update();

    for (auto a : items)
        a->Update();

    return false;
}

void Core::Draw()
{
    SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
    SDL_RenderClear(render);

    for (auto a : buttons)
        if (a->isIntersect(mouseX,mouseY))
          a->Draw(render, SDL_Color{ 255, 0, 0 });
        else 
          a->Draw(render, SDL_Color{ 255, 255, 255 });
    label.DrawString(render, "Helloworld", 0, 200);
    for(int i =0;i<10;i++)
        for(int j = 0 ; j < 3; j++)
    image->Draw(render,260+64*i,128*j+134);

    for (auto a : items)
        a->Draw(render);

    SDL_RenderPresent(render);
}

void Core::Loop()
{
    Update();
    Draw();
}
