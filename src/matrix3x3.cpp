
#include <matrix3x3.h>
#include <memory>

matrix3x3::matrix3x3()
{
	setIdentity();
}

void matrix3x3::setIdentity()
{
	m[0][0] = 1.f;
	m[0][1] = 0.f;
	m[0][2] = 0.f;

	m[1][0] = 0.f;
	m[1][1] = 1.f;
	m[1][2] = 0.f;

	m[1][0] = 0.f;
	m[1][1] = 0.f;
	m[1][2] = 1.f;
}

matrix3x3::matrix3x3(const matrix3x3 &other)
{
	std::memcpy(m, other.m, sizeof(m));
}

matrix3x3::matrix3x3(	float m00, float m01, float m02,
						float m10, float m11, float m12,
						float m20, float m21, float m22)
{
	m[0][0] = m00;
	m[0][1] = m01;
	m[0][2] = m02;

	m[1][0] = m10;
	m[1][1] = m11;
	m[1][2] = m12;

	m[2][0] = m20;
	m[2][1] = m21;
	m[2][2] = m22;
}

matrix3x3::matrix3x3(const vec3f &row0, const vec3f &row1, const vec3f &row2)
{
	m[0][0] = row0.x;
	m[0][1] = row0.y;
	m[0][2] = row0.z;

	m[1][0] = row1.x;
	m[1][1] = row1.y;
	m[1][2] = row1.z;

	m[2][0] = row2.x;
	m[2][1] = row2.y;
	m[2][2] = row2.z;
}

matrix3x3 matrix3x3::transposed() const
{
	matrix3x3 mat;
	for (int i = 0; i < 3; ++i){
		for (int j = 0; j < 3; ++j){
			mat.m[i][j] = m[j][i];
		}
	}
	return mat;
}

	/*OPERATOR*/
matrix3x3 matrix3x3::operator*(const matrix3x3 &other)
{
	matrix3x3 mat;
	for (int i = 0; i < 3; ++i){
		for (int j = 0; j < 3; ++j){
			mat.m[i][j] = 
				m[i][0] * other.m[0][j] + 
				m[i][1] * other.m[1][j] +
				m[i][2] * other.m[2][j];
		}
	}
	return mat;
}

vec3f matrix3x3::operator*(const vec3f &v)
{
	float x, y, z;
	x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z;
	y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z;
	z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z;
	return vec3f(x, y, z);
}

QDebug& operator<<(QDebug &d, const matrix3x3 &m)
{
	d.nospace() << "Matrix3x3[" << endl
		<< qSetFieldWidth(10)
		<< m.m[0][0]  << m.m[0][1]  << m.m[0][2] << endl
		<< m.m[1][0]  << m.m[1][1]  << m.m[1][2] << endl
		<< m.m[2][0]  << m.m[2][1]  << m.m[2][2] << endl
		<< qSetFieldWidth(0) << ']';
	return d.space();
}
