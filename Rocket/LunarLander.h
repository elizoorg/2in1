#pragma once


#include <iostream> 
#include "RigidBody.h"
#include "Terrain.h" 
#include "Utility.h"
#include "SDL_mixer.h"



class LunarLander : public RigidBody
{
public:
	LunarLander(vector<int> const& cfgData, SDL_Texture* const& texture, Terrain *terrain, int height, int width) ;
	void updatePosition(float const& dt) ;
	void updateRotation(float const& dt , int way) ;
	void checkCollision() ;
	void updateSound(float const& dt) ;
	void update(float const& dt) ;

	bool throttlePushed() ;
	vec2f getThrust() ;
	vec2f getDrag() const ;

	void updateFlame(float const& dt) ;
	vector<vec2f> getFlame() const ;

	float getFuel() const ;
	int getWidth() const ;
	int getHeight() const ;

	vec2f getPosition() { return pos; }
	void setPosition(vec2f x) { pos = x; }
	float getRotation(){ return angle; }
	
	void setPressed(bool x) { pressed = x; }

	void draw(SDL_Renderer* render) {
		SDL_RenderCopyEx(render, m_texture, 0, &p_Rect,angle,0,SDL_FLIP_NONE);
		SDL_SetRenderDrawColor(render, 255, 0, 0, 0);
		f_texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET,15 ,32);
		SDL_SetRenderTarget(render, f_texture);
		SDL_RenderDrawLine(render, m_flame[0].x, m_flame[0].y, m_flame[1].x, m_flame[1].y);
		SDL_RenderDrawLine(render, m_flame[1].x, m_flame[1].y, m_flame[2].x, m_flame[2].y);
		SDL_SetRenderTarget(render,NULL);
		SDL_RenderDrawLine(render, f_Rect.x, f_Rect.y,p_Rect.x + p_Rect.w / 2, p_Rect.y + p_Rect.h / 2);
		f_Rect.x =540+ (-f_Rect.w / 2) * cos(angle * M_PI / 180) + (-p_Rect.h/2 ) * sin(angle * M_PI / 180);
			f_Rect.y =360+ (-f_Rect.w / 2) * sin(angle * M_PI / 180) - (-p_Rect.h/2 ) * cos(angle * M_PI / 180);
		SDL_Point center{ 0,0 };
		SDL_RenderCopyEx(render, f_texture, 0, &f_Rect,angle,&center,SDL_FLIP_NONE);
		SDL_DestroyTexture(f_texture);
		SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
	}
	bool isAlive() const ;
	bool isWin() const ;
	void lose() { m_fuel = -10; }
	bool Done() { return m_fuel < 0; }
	int getScore() {
		return score;
	}
	void reset() ;

private :
	bool m_isAlive ;
	bool m_win ;

	Mix_Chunk* sample;


	float m_fuel ;
	float m_thrust ;
	float m_drag ;

	int score;
	vec2f pos;
	float angle;



	bool pressed;

	SDL_Rect p_Rect{ 521,344,38,33 };
	SDL_Rect f_Rect{ 521,344,15,32 };

	SDL_Texture* f_texture;
	SDL_Texture* m_texture ;
	int m_width ;
	int m_height ;

	vec2f m_speed;

	vector<vec2f> m_flame ;
	float m_flameLength ;
	float m_flameTime;

	

	Terrain *m_terrain ;




	int m_maxAngle ;
	int m_maxDistance ;
	int m_maxSpeed ;

	int m_rotationSpeed ;

	int m_fuelBonus ;
	int m_fuelConsumption ;
};

