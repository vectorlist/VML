
#ifndef VEC3F_H
#define VEC3F_H

#define VECTOR3F

#include <algorithm>
#include <qdebug.h>
#include <assert.h>

//typedef vec3f Point;

class vec3f
{
public:
	float x, y, z;
	vec3f() : x(0.0), y(0.0), z(0.0){}
	vec3f(const vec3f &v) : x(v.x), y(v.y), z(v.z){}
	vec3f(float _x, float _y, float _z) : x(_x), y(_y), z(_z){}
	explicit vec3f(float f) : x(f), y(f), z(f){}

	float& operator[](unsigned int i)
	{
		assert(i >= 0 && i <= 2);
		return (&x)[i];
	}
	float operator[](unsigned int i) const
	{
		assert(i >= 0 && i <= 2);
		return (&x)[i];
	}

	float length2() const { return x * x + y * y + z * z; }
	float length() const { return std::sqrt(length2()); }

	float normalize() { float len = length(); *this /= len; return len; }
	vec3f normalized() const
	{
		vec3f nor(*this);
		nor.normalize();
		return nor;
	}

	vec3f operator * (const float &r) const { return vec3f(x * r, y * r, z * r); }
	vec3f operator * (const vec3f &v) const { return vec3f(x * v.x, y * v.y, z * v.z); }
	vec3f operator - (const vec3f &v) const { return vec3f(x - v.x, y - v.y, z - v.z); }
	vec3f operator + (const vec3f &v) const { return vec3f(x + v.x, y + v.y, z + v.z); }
	vec3f operator + (const float &f) const { return vec3f(x + f, y + f, z + f); }
	vec3f& operator = (const vec3f &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}
	vec3f operator-() const
	{
		return vec3f(-x, -y, -z);
	}

	vec3f& operator+=(const vec3f &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	vec3f& operator-=(const vec3f &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	vec3f& operator*=(const vec3f &v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	vec3f& operator/=(const vec3f &v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	vec3f& operator*=(const float &f)
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

	vec3f& operator/= (const float &f)
	{
		x /= f;
		y /= f;
		z /= f;
		return *this;
	}
	/*----------------- LOCAL -------------------------*/
	inline float dot(const vec3f &v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	/*----------------- STATICS -----------------------*/
	static float dot(const vec3f &v1, const vec3f &v2);
	static vec3f cross(const vec3f &v1, const vec3f &v2);
	static vec3f reflect(const vec3f &mDir, const vec3f &n);
	/*-------------------------------------------------*/

	friend QDebug& operator<<(QDebug &d,const vec3f &v)
	{
		return d.nospace() << "vec3f(" << v.x << ',' << v.y << ',' << v.z << ')';
	}

	/*friend QDebug& operator<<(QDebug &d, const Point &v)
	{
		return d.nospace() << "Point(" << v.x << ',' << v.y << ',' << v.z << ')';
	}*/
};

//inline vec3f operator+(const vec3f &v1, const vec3f &v2)
//{
//	return vec3f(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
//}
//
//inline vec3f operator-(const vec3f &v1, const vec3f &v2)
//{
//	return vec3f(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
//}
//
//inline vec3f operator*(const vec3f &v1, const vec3f &v2)
//{
//	return vec3f(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
//}
//
//inline vec3f operator*(const vec3f &v, float f)
//{
//	return vec3f(f * v.x,
//		f * v.y,
//		f * v.z);
//}
//
inline vec3f operator*(float f, const vec3f &v)
{
	return vec3f(f * v.x,
		f * v.y,
		f * v.z);
}

inline vec3f operator/(float f, const vec3f &v)
{
	return vec3f(f / v.x,
		f / v.y,
		f / v.z);
}

inline vec3f operator/(const vec3f &v, float f)
{
	return vec3f(f / v.x,
		f / v.y,
		f / v.z);
}

//inline vec3f operator/(const vec3f &v1, const vec3f &v2)
//{
//	return vec3f(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
//}

inline bool operator==(const vec3f &r, const vec3f &l)
{ 
	return (r.x == l.x && r.y == l.y && r.z == l.z);
}

inline bool operator!=(const vec3f &r, const vec3f &l)
{
	return (r.x != l.x && r.y != l.y && r.z != l.z);
}

inline bool operator>(const vec3f &r, const vec3f &l)
{
	return (r.length2() > l.length2());
}

inline bool operator<(const vec3f &r, const vec3f &l)
{
	return (r.length2() < l.length2());
}
typedef vec3f Point;

#endif //VEC3F_H