#include "Quaternion.h"
#include <rtmath.h>

Quaternion::Quaternion() : w(1.f), v(0.0f){}

Quaternion::Quaternion(float w, float x, float y, float z) : w(w), v(x, y, z){}

Quaternion::Quaternion(float w, const vec3f &vv) : w(w), v(vv){}

Quaternion::Quaternion(const vec3f &axis, float angle)
{
	//must be deggree to radians
	float t2 = angle / 360.f * M_PI * 2.f;
	float t = t2 / 2;
	vec3f tmpAxis = axis.normalized();

	float sinT = std::sin(t);

	w = std::cos(t);
	v = tmpAxis * sinT;
}

Quaternion::Quaternion(const Matrix4x4 &m)
{
	float trace = m[0][0] + m[1][1] + m[2][2];
	if (trace > 0.0f)
	{
		float s = sqrtf(trace + 1.0f);
		w = s / 2.0f;
		s = 0.5f / s;
		v.x = (m[2][1] - m[1][2]) * s;
		v.y = (m[0][2] - m[2][0]) * s;
		v.z = (m[1][0] - m[0][1]) * s;
	}
	else
	{
		const int nxt[3] = { 1, 2, 0 };
		float q[3];
		int i = 0;
		if (m[1][1] > m[0][0]) i = 1;
		if (m[2][2] > m[i][i]) i = 2;
		int j = nxt[i];
		int k = nxt[j];
		float s = sqrtf((m[i][i] - (m[j][j] + m[k][k])) + 1.0);
		q[i] = s * 0.5f;
		if (s != 0.f) s = 0.5f / s;
		w = (m[k][j] - m[j][k]) * s;
		q[j] = (m[j][i] + m[i][j]) * s;
		q[k] = (m[k][i] + m[i][k]) * s;
		v.x = q[0];
		v.y = q[1];
		v.z = q[2];
	}
}

Quaternion Quaternion::operator*(const Quaternion &other)
{
	//in other hand (QT method)
	/*qreal ww = (q1.zp + q1.xp) * (q2.xp + q2.yp);
	qreal yy = (q1.wp - q1.yp) * (q2.wp + q2.zp);
	qreal zz = (q1.wp + q1.yp) * (q2.wp - q2.zp);
	qreal xx = ww + yy + zz;
	qreal qq = 0.5 * (xx + (q1.zp - q1.xp) * (q2.xp - q2.yp));

	qreal w = qq - ww + (q1.zp - q1.yp) * (q2.yp - q2.zp);
	qreal x = qq - xx + (q1.xp + q1.wp) * (q2.xp + q2.wp);
	qreal y = qq - yy + (q1.wp - q1.xp) * (q2.yp + q2.zp);
	qreal z = qq - zz + (q1.zp + q1.yp) * (q2.wp - q2.xp);

	Quaternion(w, x, y, z);*/

	//http://math.ucr.edu/~huerta/introquaternions.pdf
	//v · w = v1w1 + v2w2 + v3w3
	//(v0, v)(w0, w) = (v0w0 − v · w, v0w + w0v + v × w).
	//The quaternion product is the same as the cross product of vector
	//i × j = k,                j × k = i,            k × i = j;
	float scalar = (w * other.w) - vec3f::dot(v, other.v);
	vec3f vv =
		w *			other.v +
		other.w			* v +
		vec3f::cross(v, other.v);					// ok got it

	return Quaternion(scalar, vv);
}

vec3f Quaternion::operator*(const vec3f &p) const
{
	vec3f uv = vec3f::cross(v, p);
	vec3f uuv = vec3f::cross(v, uv);
	uv *= (2.f * w);
	uuv *= 2.f;
	return p + uv + uuv;
}

Quaternion Quaternion::normalized() const
{
	/*A quaternion can be normalised in a way similar to vectors.The
	magnitude of the quaternion is calculated first.Then both the
	scalar and vector part of the quaternion are divided by this value.
	A unit quaternion will always have a magnitude of 1.0*/

	/*q_normalized = q / square(norm(q))
	with, q = q1 + q2i + q3 j + q4 k norm(q) = (q1) ^ 2 + (q2) ^ 2 + (q3) ^ 2) + (q4) ^ 4*/

	/*QT Method*/
	/*double len = double(xp) * double(xp) +
	double(yp) * double(yp) +
	double(zp) * double(zp) +
	double(wp) * double(wp);
	len = qSqrt(len);
	xp /= len;
	yp /= len;
	zp /= len;
	wp /= len;*/

	Quaternion Q = *this;
	float len = sqrt(norm());
	float inv_len = 1.f / len;
	//if (inv_len == 1.f) return Q;

	Q.w *= inv_len;
	Q.v *= inv_len;
	return Q;

}

Quaternion Quaternion::fromAxisAngle(const vec3f &axis, float angle)
{
	float half = angle * 0.5f * M_PI / 180.f;
	float sinT = sin(half);
	Quaternion q;
	q.v = axis.normalized() * sinT;
	q.w = cos(half);
	return q.normalized();
}

Matrix4x4 Quaternion::matrix() const
{
	//http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q56
	//Q54  but it's transposed Matrix
	float x2 = 2.0f * v.x;
	float y2 = 2.0f * v.y;
	float z2 = 2.0f * v.z;

	float xx2 = x2 * v.x;
	float xy2 = x2 * v.y;
	float xz2 = x2 * v.z;
	float xw2 = x2 * w;

	float yy2 = y2 * v.y;
	float yz2 = y2 * v.z;
	float yw2 = y2 * w;

	float zz2 = z2 * v.z;
	float zw2 = z2 * w;

	Matrix4x4 M(
		1.f - yy2 - zz2, xy2 - zw2, xz2 + yw2, 0.f,			//0 row
		xy2 + zw2, 1.f - xx2 - zz2, yz2 - xw2, 0.f,			//1 row 
		xz2 - yw2, yz2 + xw2, 1.f - xx2 - yy2, 0.f,         //2 row
		0.f, 0.f, 0.f, 0.f);

	M.type().identiy = false;
	return M;
}

QDebug& operator<<(QDebug& d, const Quaternion &q)
{
	d.nospace() << "Quaternion( " <<
		/*qSetFieldWidth(5) <<*/
		q.w << ", " << q.v.x << ", " << q.v.y << ", " << q.v.z <<
		/*qSetFieldWidth(0) << */')';
	return d.space();
}