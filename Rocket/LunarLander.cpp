#include "LunarLander.h"
#include "RigidBody.cpp"

LunarLander::LunarLander(vector<int> const& cfgData, SDL_Texture* const& texture, Terrain *terrain,int height,int width)
{
	RBsetPosition(vec2f(0,0)) ;
	
	setMass(cfgData[4]) ;
	setMovable();

	m_thrust = cfgData[5] ;
	m_drag = cfgData[6] ;
	m_fuel = cfgData[7] ;


	m_speed.x = rand() % 100;
	m_speed.y = rand() % 100;
	setSpeeed(m_speed);
	m_width = width;
	m_height = height;


	m_texture = texture ;
	

	m_flame.push_back(vec2f(0,0));
	m_flame.push_back(vec2f(5,0));
	m_flame.push_back(vec2f(10,0));

	m_flameLength = 0 ;

	m_terrain = terrain ;

	m_isAlive = true ;
	m_win = false ;

	sample = Mix_LoadWAV("Resourcess/burner.aif");
	if (!sample) {
		cout << "Mix_LoadWav Resourcess/burner.aif" << "  " << Mix_GetError() << endl;
	}


	m_maxAngle = cfgData[9] ;
	m_maxDistance = cfgData[10] ;
	m_maxSpeed = cfgData[11] ;

	m_rotationSpeed = cfgData[12] ;

	m_fuelBonus = cfgData[13] ;
	m_fuelConsumption = cfgData[14] ;

}
void LunarLander::updatePosition(float const& dt)
{
	RBupdatePosition(dt) ;
	setPosition(RBgetPosition()) ;
}
void LunarLander::updateRotation(float const& dt,int way)
{
	angle += m_rotationSpeed * dt * way;

}
void LunarLander::checkCollision()
{
	vec2f TL = rotatePoint( getPosition()+vec2f(-m_width/3.2f,-m_height/2.f), getPosition(), getRotation()) ;
	vec2f TR = rotatePoint( getPosition()+vec2f(+m_width/3.2f,-m_height/2.f), getPosition(), getRotation()) ;
	vec2f BL = rotatePoint( getPosition()+vec2f(-m_width/2.f,+m_height/2.f), getPosition(), getRotation()) ;
	vec2f BR = rotatePoint( getPosition()+vec2f(+m_width/2.f,+m_height/2.f), getPosition(), getRotation()) ;

	for(int i( (int)( minClamp((getPosition().x-m_terrain->getCenterPosition().x-m_width/2.f)/(float)m_terrain->getVertexSpacing() ,0))) ; 
			i <(int)( maxClamp((getPosition().x-m_terrain->getCenterPosition().x+m_width/2.f)/(float)m_terrain->getVertexSpacing() , m_terrain->getSize()-1)) ; i++)
	{
		if(collisionTrianglePoint(TL, TR, BL, m_terrain->getPoint(i)) || collisionTrianglePoint(TR, BR, BL, m_terrain->getPoint(i))) 
		{
			m_isAlive = false ;
			float distance = 0 ;

			for(int i( (int)( minClamp((getPosition().x-m_terrain->getCenterPosition().x-m_width/2.f)/(float)m_terrain->getVertexSpacing() ,0))) ; 
			i <(int)( maxClamp((getPosition().x-m_terrain->getCenterPosition().x+m_width/2.f)/(float)m_terrain->getVertexSpacing() , m_terrain->getSize()-1)) ; i++)
			{
				distance += m_terrain->getPoint(i).y - (BL.y+BR.y)/2.f ;
			} distance = abs(distance) ;
			if(distance < m_maxDistance && Norm(getSpeed()) < m_maxSpeed && (getRotation() < m_maxAngle || getRotation() > 360-m_maxAngle))
			{
				m_win = true ;
				score += m_fuel * 10;
				m_fuel += m_fuelBonus ;
				
			}
			else
			{
				m_win = false ;
				score -=m_fuelBonus * 5;
				m_fuel -= m_fuelBonus ;
			}
			
			return ;
		}
	}
}
void LunarLander::updateSound(float const& dt)
{
	if (throttlePushed() && isAlive()) {  Mix_PlayChannel(-1, sample, 0); }
	else Mix_HaltChannel(-1);
}
void LunarLander::update(float const& dt)
{
	if(m_isAlive)
	{
		updatePosition(dt) ;
		updateRotation(dt,0) ;
		updateFlame(dt) ;

		clearForce() ;
		addForce( getThrust() ) ;
		addForce( getDrag() ) ;
			
		checkCollision() ;

		if(throttlePushed() && m_fuel > 0) m_fuel -= m_fuelConsumption*dt ;
	}
	updateSound(dt) ;
}

bool LunarLander::throttlePushed() 
{
	if (m_fuel > 0 && pressed) return true;
	else return false;
	
}
vec2f LunarLander::getThrust()
{
	if(throttlePushed() && m_fuel > 0) 
		return vec2f(m_thrust*sin(getRotation()*(PI/180.f)) , -m_thrust*cos(getRotation()*(PI/180.f)));
	else return vec2f(0,0) ;
}
vec2f LunarLander::getDrag() const
{
	return -getSpeed()*m_drag;
}

void LunarLander::updateFlame(float const& dt)
{
	if(throttlePushed() && m_flameLength < 24)
		m_flameLength += 100*dt ;
	else if(throttlePushed() && m_flameLength >= 24)
		m_flameLength = 30 + 3*cos(50) ;
	else
		m_flameLength = minClamp(m_flameLength - 100*dt, 0) ;

	m_flame[1] = vec2f(5, m_flameLength);
}
vector<vec2f> LunarLander::getFlame() const
{
	return m_flame ;
}

float LunarLander::getFuel() const
{
	return m_fuel ;
}
int LunarLander::getWidth() const
{
	return m_width ;
}
int LunarLander::getHeight() const
{
	return m_height ;
}

bool LunarLander::isAlive() const
{
	return m_isAlive ;
}
bool LunarLander::isWin() const
{
	return m_win ;
}

void LunarLander::reset()
{
	m_isAlive = true ;
	m_win = false ;
	m_speed.x = rand() % 100;
	m_speed.y = rand() % 100;
	setSpeeed(m_speed);
}