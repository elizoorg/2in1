#pragma once


#include <string>
#include <iostream> 
#include <sstream>
#include <fstream>
#include <cstdio>
#include "SDL.h"
#include "SDL_image.h"
#include "LunarLander.h"
#include "Terrain.h" 
#include "Utility.h"
#include "TextVisuliaser.h"


using namespace std ;

class GUI
{
public:
	GUI(int const& _width, int const& _height, LunarLander *_lander, Terrain *_terrain);

	void draw(SDL_Renderer* render) ;
	void score(SDL_Renderer* render,int score);
	bool Menu(SDL_Renderer* render);
private:
	int width ;
	int height ;
	float screenSpacing, textSpacing ;
	LunarLander *lander ;
	Terrain *terrain ;
	TextVisuliaser visual;
	TextVisuliaser menuvisual;

	ostringstream oss ;

};

