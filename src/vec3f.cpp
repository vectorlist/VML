#include <vec3f.h>

float vec3f::dot(const vec3f &v1, const vec3f &v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vec3f vec3f::cross(const vec3f& v1, const vec3f& v2)
{
	return vec3f(v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
}

vec3f vec3f::reflect(const vec3f &mDir, const vec3f &n)
{
	/*Vnew = b * (-2 * (V dot N)*N + V)*/
	//vec3f reflected = (mDir * 2 * vec3f::dot(n, mDir)) - n;
	return mDir - n * 2 * vec3f::dot(n, mDir);
}