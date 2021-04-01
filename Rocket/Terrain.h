#pragma once

#include "SDL.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "Vector.h"


using namespace std ;

class Terrain
{
public:
	Terrain(int const& _vertexSpacing,  float const& _terrainSize, vec2f const& _centerPosition);
	
	vector<vec2f> getTerrain() const ;
	int getVertexSpacing() const ;
	int getSize() const ;
	vec2f getPoint(int const& i) const ;
	vec2f getCenterPosition() const ;

	void draw(SDL_Renderer* render,vec2f pos) ;

private:
	int vertexSpacing ;
	float terrainSize ;
	vec2f centerPosition ;
	vector<vec2f> terrain ;
};