#pragma once

#include <vector>
#include <fstream>
#include "Vector.h"

#define PI 3.14159265359

using namespace std ;

void interpolation(float &x, float const& y, float const& time, float const& deltaTime);
float determinant(vec2f const& u, vec2f const& v) ;
float dotProduct(vec2f const& u, vec2f const& v) ;
float Angle(vec2f const& v1, vec2f const& v2) ;
float Distance(vec2f const& u, vec2f const& v) ;
vec2f rotatePoint(vec2f const& point, vec2f const& center, float const& angle) ;
float Norm (vec2f const& v) ;
float clamp(float value, float min, float max) ;
float minClamp(float value, float min) ;
float maxClamp(float value, float max) ;
bool checkSegmentIntersection(vec2f const& A, vec2f const& B, vec2f const& C, vec2f const& D) ;
bool collisionTrianglePoint(vec2f const& a, vec2f const& b, vec2f const& c, vec2f const& point) ;
vec2f randvec2f(float const& among) ;
vector<int> readCfgFile(string path) ;
