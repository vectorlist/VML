#include <vec4f.h>

vec4f::vec4f(const vec4f &other){
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
}

vec4f& vec4f::operator=(const vec4f &other){
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
	return *this;
}


inline float& vec4f::operator[](unsigned int index)
{
	//assert(i >= 0 && i <= 2);
	assert(index >= 0 && index <= 3);
	return (&x)[index];
}