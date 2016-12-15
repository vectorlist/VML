
#ifndef MATRIX3X3_H
#define MATRIX3X3_H

#include <vec3f.h>
#include <qdebug.h>

class matrix3x3
{
public:
	matrix3x3();
	matrix3x3(const matrix3x3 &other);
	matrix3x3(	float m00, float m01, float m02,
				float m10, float m11, float m12,
				float m20, float m21, float m22);
	matrix3x3(const vec3f &row0, const vec3f &row1, const vec3f &row2);
	~matrix3x3(){};

	void setIdentity();
	matrix3x3 transposed() const;

	/*OPERATOR*/
	matrix3x3 operator*(const matrix3x3 &other);
	vec3f operator*(const vec3f &v);

	
	/*LOG*/
	friend QDebug& operator<<(QDebug &d, const matrix3x3 &m);


protected:
	float m[3][3];
private:
	
};

#endif // MATRIX3X4_H
