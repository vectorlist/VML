
#ifndef VEC2F_H
#define VEC2F_H

#include <qdebug.h>

template<typename T>
class vec2
{
public:
	vec2() : x(0), y(0) {}
	vec2(T _x) : x(_x), y(_x){}
	vec2(T _x, T _y) : x(_x), y(_y){}

	vec2 operator + (const vec2 &v) const{
		return vec2(x + v.x, y + v.y);
	}
	vec2 operator - (const vec2 &v) const{
		return vec2(x - v.x, y - v.y);
	}
	vec2 operator / (const vec2 &v) const{
		return vec2(x / v.x, y / v.y);
	}
	vec2 operator * (const vec2 &v) const{
		return vec2(x * v.x, y * v.y);
	}
	vec2& operator *= (const vec2 &v){
		x *= v.x;
		y *= v.y;
		return *this;
	}
	vec2& operator /= (const vec2 &v){
		x /= v.x;
		y /= v.y;
		return *this;
	}
	vec2 operator *(const float &f)
	{
		return vec2(x * f, y * f);
	}
	friend vec2 operator *(const float &f, const vec2 &v)
	{
		return vec2(f * v.x, f * v.y);
	}
	friend QDebug& operator<<(QDebug &d, const vec2 &v)
	{
		char* tn;
		if (typeid(T) == typeid(float))
			tn = "vec2f";
		else
			tn = "vec2i";
		d.nospace() << tn << '(' << v.x << ',' << v.y << ')';
		return d.space();
	}

	/*friend QDebug& operator<<(QDebug &d, const vec2<int> &v)
	{
	d.nospace() << "vec2i(" << v.x << ',' << v.y << ')';
	return d.space();
	}*/
	T x, y;
};

typedef vec2<float> vec2f;
typedef vec2<int> vec2i;


#endif //VEC3F_H