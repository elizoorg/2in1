#include "Terrain.h"

Terrain::Terrain(int const& _vertexSpacing,  float const& _terrainSize, vec2f const& _centerPosition)
{
	terrain.clear() ;

	vertexSpacing = _vertexSpacing ;
	terrainSize = _terrainSize ;
	centerPosition = _centerPosition ;

	int vertexCount = (int)(terrainSize/(float)vertexSpacing) ;
	terrain.push_back(vec2f(centerPosition)) ;

	srand(time(NULL)) ;
	vector<float> slopeDirection ; slopeDirection.push_back(-1) ;
	int slopeDirectionRand ;
	
	for(int i(1) ; i < vertexCount ; i++)
	{
		slopeDirectionRand = rand()%100 ;
		if(slopeDirectionRand < 10)
		{
			slopeDirection.push_back( ((rand()%RAND_MAX)/(float)RAND_MAX-0.5f)*3 ) ;
		}
		else
			slopeDirection.push_back( slopeDirection[i-1] ) ;
		
	}
	for(int i(1) ; i < vertexCount ; i++)
	{
		terrain.push_back( vec2f( i*vertexSpacing + centerPosition.x  , terrain[i-1].y + (float)(rand()%20)*slopeDirection[i] ) ) ;
	}
}

vector<vec2f> Terrain::getTerrain() const
{
	return terrain ;
}
int Terrain::getVertexSpacing() const
{
	return vertexSpacing ;
}
int Terrain::getSize() const
{
	return terrain.size();
}
vec2f Terrain::getPoint(int const& i) const
{
	return terrain[i];
}
vec2f Terrain::getCenterPosition() const
{
	return centerPosition ;
}

void Terrain::draw(SDL_Renderer* render,vec2f pos)
{
	SDL_SetRenderDrawColor(render, 255, 255, 255, 0);
	for (int v = 0 ; v < terrain.size()-1 ; v++){
		SDL_RenderDrawLine(render, terrain[v].x-pos.x, terrain[v].y-pos.y,
			terrain[v + 1].x - pos.x, terrain[v + 1].y - pos.y);
	}
	SDL_SetRenderDrawColor(render, 0, 0, 0, 0);

}