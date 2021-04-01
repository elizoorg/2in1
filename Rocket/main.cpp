
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "LunarLander.h"
#include "Terrain.h"
#include "GUI.h"
#include "Vector.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <time.h>



using namespace std;



int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    TTF_Init();
    vector<int> cfgData = readCfgFile("Resourcess/cfg.txt");

    int const width = cfgData[0];
    int const height = cfgData[1];

    SDL_Window* window = SDL_CreateWindow("Lunar Lander", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE || SDL_RENDERER_ACCELERATED || SDL_RENDERER_TARGETTEXTURE || SDL_RENDERER_PRESENTVSYNC);
 
    bool play = true;

    srand(time(NULL));

    Terrain terrain(cfgData[2], cfgData[3], vec2f(0, 0)); //vertexSpacing, terrainSize, centerPosition

    SDL_Texture* landerTexture;
    SDL_Surface* temp = IMG_Load("Resourcess/lunarLander.png");
    int w = temp->w;
    int h = temp->h;
    landerTexture = SDL_CreateTextureFromSurface(render, temp);
    SDL_FreeSurface(temp);
	int FPS = 120;
	int lastFrame, frameCount=0, lastTime=0, timerFPS;
    LunarLander lander(cfgData, landerTexture, &terrain,w,h); //position, mass, thrust, drag, texture, terrain

    GUI gui(width, height, &lander, &terrain);
    while (gui.Menu(render)) {
        while (true)
        {

            terrain = Terrain(cfgData[2], cfgData[3], vec2f(0, 0));
            lander.RBsetPosition(terrain.getPoint(0.5 * cfgData[3] / (float)cfgData[2]) - vec2f(0, 400));

            lander.reset();

            double dt = 0.01;
            vec2f p_pos;
            SDL_Event event;
            play = true;
            while (play)
            {
                lastFrame = SDL_GetTicks();
                if (lastFrame >= (lastTime + 1000)) {
                    lastTime = lastFrame;
                    FPS = frameCount;
                    frameCount = 0;
                }


                while (SDL_PollEvent(&event)) {
                    switch (event.type) {
                    case SDL_KEYDOWN:
                        if (event.key.keysym.sym == SDLK_LEFT) {
                            lander.updateRotation(dt, -1);
                        }
                        if (event.key.keysym.sym == SDLK_RIGHT) {
                            lander.updateRotation(dt, 1);
                        }
                        if (event.key.keysym.sym == SDLK_UP) {
                            lander.setPressed(true);
                        }
                        if (event.key.keysym.sym == SDLK_SPACE) {
                            play = false;
                        }
                        if (event.key.keysym.sym == SDLK_ESCAPE) {
                            lander.lose();
                            play = false;
                        }
                        break;
                    case SDL_KEYUP:
                        if (event.key.keysym.sym == SDLK_UP) {
                            lander.setPressed(false);
                        }
                        break;
                    }
                }
                SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
                SDL_RenderClear(render);
                lander.update(dt);
                lander.addForce(vec2f(0, cfgData[8]));
                lander.draw(render);
                terrain.draw(render, lander.getPosition() - vec2f(width / 2, height / 2));
                gui.draw(render);
                frameCount++;
                timerFPS = SDL_GetTicks() - lastFrame;
                dt = (double)timerFPS / 60;
                if (timerFPS < (1000 / 60))
                    SDL_Delay(1000 / 60 - timerFPS);
                SDL_RenderPresent(render);
            }
            if (lander.Done()) break;
        }

        gui.score(render, lander.getScore());
    }
    return 0;
}











