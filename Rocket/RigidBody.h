#pragma once
#include "Vector.h"
#include <vector>



class RigidBody
{
public:

	inline RigidBody() ;
	inline RigidBody(float mass, vec2f position, vec2f speed) ;

	inline float getMass() const ;
	inline void setMass(float const& mass) ;
	inline vector<vec2f> getForce() const;
	inline vec2f getTotalForce() const ;
	inline void addForce(vec2f const& force) ;
	inline void clearForce() ;
	inline vec2f RBgetPosition() const ;
	inline vec2f getPreviousPosition() const ;
	inline void RBsetPosition(vec2f const& position) ;
	inline vec2f getSpeed() const ;
	inline void setSpeeed(vec2f const& speed);
	inline vec2f getAcceleration() const ;
	inline void setAcceleration(vec2f const& acceleration) ;
	inline void setStatic() ;
	inline void setMovable() ;
	inline bool isMovable() ;

	inline void RBupdatePosition(float const& dt) ;
	
private:
	float m_mass ;

	vector<vec2f> m_force ;
	vec2f m_position ;
	vec2f m_previousPosition ;
	vec2f m_speed ;
	vec2f m_acceleration ;

	bool m_movable ;
};
