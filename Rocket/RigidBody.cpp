#include "RigidBody.h"

RigidBody::RigidBody()
{
	m_mass = 50 ;
	m_position = vec2f(50,50) ;
	m_speed = vec2f(0,0) ;
	m_acceleration = vec2f(0,0) ;
	m_movable = true ;
}
RigidBody::RigidBody(float mass, vec2f position, vec2f speed)
{
	m_mass = mass ;
	m_position = position ;
	m_speed = speed ;
}

float RigidBody::getMass() const
{
	return m_mass ;
}
void RigidBody::setMass(float const& mass)
{
	m_mass=mass ;
}

vector<vec2f> RigidBody::getForce() const
{
	return m_force ;
}
vec2f RigidBody::getTotalForce() const
{
	vec2f totalForce(0,0) ;
	for(int i(0) ; i < m_force.size() ; i++)
	{
		totalForce += m_force[i] ;
	}
	return totalForce ;
}
void RigidBody::addForce(vec2f const& force)
{
	m_force.push_back(force) ;
}
void RigidBody::clearForce()
{
	m_force.clear() ;
}

vec2f RigidBody::RBgetPosition() const
{
	return m_position ;
}
vec2f RigidBody::getPreviousPosition() const
{
	return m_previousPosition ;
}
void RigidBody::RBsetPosition(vec2f const& position)
{
	m_position = position ;
}

vec2f RigidBody::getSpeed() const
{
	return m_speed ;
}
void RigidBody::setSpeeed(vec2f const& speed) 
{
	m_speed = speed ;
}

vec2f RigidBody::getAcceleration() const
{
	return m_acceleration ;
}
void RigidBody::setAcceleration(vec2f const& acceleration)
{
	m_acceleration = acceleration ;
}
void RigidBody::setStatic()
{
	m_movable = false ;
}
void RigidBody::setMovable()
{
	m_movable = true ;
}
bool RigidBody::isMovable()
{
	return m_movable ;
}

void RigidBody::RBupdatePosition(float const& dt)
{
	m_previousPosition = m_position ;
	m_position = m_position + m_speed*dt + 0.5f*getTotalForce()/m_mass*(float)pow(dt,2);
	m_speed = (m_position-m_previousPosition)/dt ;
}