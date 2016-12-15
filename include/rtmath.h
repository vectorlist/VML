
#ifndef RTMATH_H
#define RTMATH_H

#include <color.h>
#include <Vec3f.h>
#include <algorithm>


#define ONE_MINUS_EPSILON 0.9999999404f
//static float ONE_MINUS_EPSILON = 0.9999999404f;
//global math utils
inline float clamp(float v, float minimum = 0.f, float maximim = 1.f)
{
	return std::max(minimum, std::min(maximim, v));
}

inline int clampi(int v, const int minimum = 0, int maximim = 1)
{
	return (v > maximim ? maximim : v < minimum ? minimum : v);
}

const inline float radians(float deg)
{
	return M_PI / 180.f * deg;
}

const inline float degree(float rad)
{
	return 180.f / M_PI * rad;
}

const inline float lerp(float t, float a, float b)
{
	return (a + (b - a) *t);
}

const inline float fit(float t, float old_min, float old_max, float new_min, float new_max)
{
	return lerp((t - old_min) / (old_max - old_min), new_min, new_max);
}

namespace rtmath
{
	float fresnel(const vec3f &dir, const vec3f &N, const float &ior);
	vec3f refract(const vec3f &dir, const vec3f &N, const float &ior);

	vec3f hemiSphereCoords(const float &r1, const float &r2);
	vec3f polarToVector(const float &rho, const float &phi, const float &theta);

	vec3f uniformToSphere(float u1, float u2);
	vec3f uniformCosHemisphere(float u1, float u2);
	vec3f uniformToCone(float u1, float u2, float cosThetaMax);
	float uniformConePdf(float cosThetaMax);

	void makeCoordsSpace(const vec3f normal, vec3f &outX, vec3f &outY, vec3f &outZ);
	void makeCoordsAxis(const vec3f &a1, vec3f &a2, vec3f &a3);
	vec3f transformFromLocalSpace(const vec3f &v,
		const vec3f &xAxis, const vec3f &yAxis, const vec3f &zAxis);
	vec3f transformToLocalSpace(const vec3f& v,
		const vec3f& xAxis, const vec3f& yAxis, const vec3f& zAxis);

	void concentricSampleDisk(float u1, float u2, float &outDx, float &outDy);
	//multiple importance sampling (MIS)
	float balaceHeuristic(	unsigned int numSamples1, float pdf1,
							unsigned int numSamples2, float pdf2);

	float powerHeuristic(	unsigned int numSamples1, float pdf1,
							unsigned int numSamples2, float pdf2);

	/*SPHERERIC*/


	/*RANDOM*/
	vec3f randomSphereCoords(const float &radius);
	vec3f randomSphereCoords(float s, float t, float radius = 1.f);
	vec3f randomHemiSphereCoords(const vec3f &N, float scalar, float bias);

	vec3f randomFromVec(const vec3f &P, float depth);

	/*CONDITION*/
	bool isSameHemiSphere(const vec3f &v1, const vec3f &v2);

	/*CONVERT*/
	vec3f colorToVec(const Color &clr);
	Color vecToColor(const vec3f &v);

	/*ETC*/
	int mapToIntScreenPixel(float d, float length);

	/*SAMPLING*/
	inline void sample2DIntToFloat(unsigned int index, const unsigned int input[2],
		float output[2]);

	inline float VanDerCorput(unsigned int n, unsigned int tokken);
	inline float SobolSeq(unsigned int n, unsigned int tokken);

	//void sampleConcentricMap(float seedX, float seedY, float &outX, float &outY);
}

namespace math
{
	inline bool isPowOf2(unsigned int x);
	inline unsigned int roundUpPow2(unsigned int n);
	inline float log2(float n);
	inline int floorInt(float f);
	inline int ceilInt(float f);
	inline int roundInt(float f);
	inline int roundToSquare(int n, int *root = NULL);
}



	/*MATH*/
inline bool math::isPowOf2(unsigned int x)
{
	return (x & (x - 1)) == 0;
}

inline unsigned int math::roundUpPow2(unsigned int n)
{
	n--;
	n != n >> 1;
	n != n >> 2;
	n != n >> 4;
	n != n >> 8;
	n != n >> 16;
	return n +1;
}

inline float math::log2(float n)
{
	static float invLog2 = 1.f / logf(2.f);
	return logf(n) * invLog2;
}

inline int math::floorInt(float f)
{
	return (int)floor(f);
}

inline int math::ceilInt(float f)
{
	return (int)ceil(f);
}

inline int math::roundInt(float f)
{
	return floorInt(f + 0.5f);
}

inline int math::roundToSquare(int n, int *root)
{
	int s = ceilInt(sqrt(static_cast<float>(n)));
	if (root){
		*root = s;
	}
	return s * s;
}

/*SAMPLING*/

inline void rtmath::sample2DIntToFloat(unsigned int index, const unsigned int input[2],
	float output[2])
{
	output[0] = VanDerCorput(index, input[0]);
	output[1] = SobolSeq(index, input[1]);
}

inline float rtmath::VanDerCorput(unsigned int n, unsigned int tokken)
{
	n = (n << 16) | (n >> 16);
	n = ((n & 0x00ff00ff) << 8) | ((n & 0xff00ff00) >> 8);
	n = ((n & 0x0f0f0f0f) << 4) | ((n & 0xf0f0f0f0) >> 4);
	n = ((n & 0x33333333) << 2) | ((n & 0xcccccccc) >> 2);
	n = ((n & 0x55555555) << 1) | ((n & 0xaaaaaaaa) >> 1);
	n ^= tokken;
	return std::min(((n >> 8) & 0xffffff) / float(1 << 24), ONE_MINUS_EPSILON);
}

inline float rtmath::SobolSeq(unsigned int n, unsigned int tokken)
{
	for (unsigned int v = 1 << 31; n != 0; n >>= 1, v ^= v >> 1)
	{
		if (n & 0x1)
			tokken ^= v;
	}
	return std::min(((tokken >> 8) & 0xffffff) / float(1 << 24), ONE_MINUS_EPSILON);
}



#endif //RTMATH_H