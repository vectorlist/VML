
#ifndef QUATERNION_H
#define QUATERNION_H

#include <vec3f.h>
#include <matrix4x4.h>
#include <qdebug.h>

enum class QAxis : unsigned int
{
	XYZ = 0 << 1,
	XZY = 1 << 1,

	YXZ = 2 << 1,
	YZX = 3 << 1,

	ZXY = 4 << 1,
	ZYX = 5 << 1
};

class Quaternion
{
public:
	Quaternion();
	Quaternion(float w, float x, float y, float z);
	Quaternion(float w, const vec3f &vv);
	Quaternion(const vec3f &axis, float angle);
	Quaternion(const Matrix4x4 &m);
	~Quaternion(){};

	/*OPERATORS*/
	Quaternion operator*(const Quaternion &other);
	vec3f operator*(const vec3f &p) const;
	Quaternion operator*(float f) const;
	Quaternion& operator*=(float f);


	float norm() const;
	Quaternion conjugate() const;
	Quaternion normalized() const;
	static Quaternion fromAxisAngle(const vec3f &axis, float angle);
	Matrix4x4 matrix() const;

	float w;
	vec3f v;

	friend QDebug& operator<<(QDebug& d, const Quaternion &q);
};

inline Quaternion& Quaternion::operator*=(float f)
{
	w *= f;
	v *= f;
	return *this;
}

inline Quaternion Quaternion::operator*(float f) const
{
	Quaternion Q = *this;
	Q.w *= f;
	Q.v *= f;
	return Q;
}

//global built in multiply func
//inline vec3f operator*(const vec3f &v, const Quaternion &q) 
//{
//	return (q * v);
//}

inline Quaternion Quaternion::conjugate() const
{
	//Qr =  ( Qr.scalar, -Qr.vector )
	return Quaternion(w, -v);
}

inline float Quaternion::norm() const
{
	//The square root of the product of a quaternion with 
	//its conjugate is called its norm and is denoted ||q|| 
	//sqrt w2 + x2 + y2  + z2

	return (w * w) + v.length2();
}


#endif // QUATERNION_H