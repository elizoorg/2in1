#include "Utility.h"

#include <cmath>
#include <iostream>
#include <string>


using namespace std ;

void interpolation(float &x, float const& y, float const& time, float const& deltaTime)
{
	x += (2.f*(y-x)*deltaTime)/time ;
}



float determinant(vec2f const& u, vec2f const& v) 
{
	float result = u.x*v.y - u.y*v.x ;
	return result ;
}

float dotProduct(vec2f const& u, vec2f const& v)
{
	return u.x*v.x + u.y*v.y ;
}

float Angle(vec2f const& v1, vec2f const& v2)
{
	float angle = atan2(determinant(v1,v2), dotProduct(v1,v2))*180/PI ;
	if(angle<0)
		angle = 360 + angle ;
	return angle ;
}




float Distance(vec2f const& u, vec2f const& v)
{
	return sqrt(pow(u.x-v.x,2)+pow(u.y-v.y,2)) ;
}

vec2f rotatePoint(vec2f const& point, vec2f const& center, float const& angle) 
{
	float x = center.x + (point.x - center.x)*cos(angle*(PI/180)) - (point.y - center.y)*sin(angle*(PI/180)) ;
	float y = center.y + (point.x - center.x)*sin(angle*(PI/180)) + (point.y - center.y)*cos(angle*(PI/180)) ;
	return vec2f(x,y) ;
}

float Norm (vec2f const& v) 
{
	float result = sqrt(pow(v.x,2)+pow(v.y,2)) ;
	return result ;
}



float clamp(float value, float min, float max) 
{
	float result ;
	if(value > max)
		result = max ;
	else if(value < min)
		result = min ;
	else
		result = value ;
	return result ;
}
float minClamp(float value, float min) 
{
	float result ;
	if(value < min)
		result = min ;
	else
		result = value ;
	return result ;
}
float maxClamp(float value, float max) 
{
	float result ;
	if(value > max)
		result = max ;
	else
		result = value ;
	return result ;
}

bool checkSegmentIntersection(vec2f const& A, vec2f const& B, vec2f const& C, vec2f const& D)
{
	if(determinant(B-A,C-A)*determinant(B-A,D-A)<0 && determinant(D-C,A-C)*determinant(D-C,B-C)<0)
		return true ;
	return false ;
}

bool collisionTrianglePoint(vec2f const& a, vec2f const& b, vec2f const& c, vec2f const& point)
{
	vec2<float> ab = b-a ;
	vec2<float> bc = c-b ;
	vec2<float> ca = a-c ;
	
	if(determinant(ab,point-a) > 0 && determinant(bc,point-b) > 0 && determinant(ca,point-c) > 0)
	{
		return true ;
	}
	else return false ;
}

vec2f randvec2f(float const& among)
{
	return vec2f((rand()%RAND_MAX/(float)RAND_MAX-0.5)*among,(rand()%RAND_MAX/(float)RAND_MAX-0.5)*among) ; 
}
vector<int> readCfgFile(string path)
{
	ifstream cfg(path) ;
	string line ;
	vector<int> result ;
	int intBuf ;
	string strBuf ;
	
	cfg>>strBuf>>intBuf ;
	result.push_back(intBuf) ;

	while(getline(cfg, line))
	{
		cfg.ignore() ;
		cfg>>strBuf>>intBuf ;
		result.push_back(intBuf) ;
	}
	return result ;
}