
#ifndef VEC4F_H
#define VEC4F_H

#include <assert.h>

class vec4f
{
public:
	vec4f() : x(0.0f), y(0.0f), z(0.0f), w(0.0f){};
	vec4f(float _x, float _y, float _z, float _w):
		x(_x), y(_y), z(_z), w(_w){}
	vec4f(const vec4f &other);

	vec4f& operator=(const vec4f &other);
	float& operator[](unsigned int index);

	~vec4f(){};


	float x, y, z, w;
	//float data[4];
private:
	
};

//vec4f::vec4f(const vec4f &other){
//	x = other.x;
//	y = other.y;
//	z = other.z;
//	w = other.w;
//}
//
//vec4f& vec4f::operator=(const vec4f &other){
//	x = other.x;
//	y = other.y;
//	z = other.z;
//	w = other.w;
//	return *this;
//}
//
//
//inline float& vec4f::operator[](unsigned int index)
//{
//	//assert(i >= 0 && i <= 2);
//	assert(index >= 0 && index <= 3);
//	return (&x)[index];
//}

#endif // VEC4F_H
