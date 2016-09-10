
#ifndef RTMATH_H
#define RTMATH_H

#include <Vec3f.h>
#include <math.h>
#include <qdebug.h>

struct polar3f
{
	polar3f(){}
	polar3f(const float &r, const float &p, const float &t)
		: rho(r), phi(p), theta(t)
	{}
	float rho, phi, theta;

	friend QDebug& operator<<(QDebug& d, const polar3f &p)
	{
		d.nospace() << "Polar3f(" << p.rho << ',' << p.phi
			<< ',' << p.theta << ')' << endl;
		return d.space();
	}
};

namespace rtmath
{
	float clamp(const float& v, const float &min_ = 0.0f, const float &max_ = 1.0f);

	void fresnel(const vec3f &mDir, const vec3f &N, const float &ior, float &output);
	float fresnel(const vec3f &mDir, const vec3f &N, const float &ior);

	vec3f refract(const vec3f &mDir, const vec3f &N, const float &ior);

	vec3f hemiSphereCoords(const float &r1, const float &r2);
	vec3f polarToVector(const float &rho, const float &phi, const float &theta);
	vec3f polarToVector(const polar3f &p);
	polar3f vectorToPolar(const vec3f &v);

	vec3f uniformToSphere(float u1, float u2);
	vec3f uniformCosHemisphere(float u1, float u2);
	vec3f uniformToCone(float u1, float u2, float cosThetaMax);
	float uniformConePdf(float cosThetaMax);
	//make a local coords AXIS from normal
	void makeCoordsSpace(const vec3f normal, vec3f &outX, vec3f &outY, vec3f &outZ);
	//transform a vector from local space bu axis
	vec3f transformFromLocalSpace(const vec3f &v,
		const vec3f &xAxis, const vec3f &yAxis, const vec3f &zAxis
		);

	void concentricSampleDisk(float u1, float u2, float &outDx, float &outDy);
	//multiple importance sampling (MIS)
	float balaceHeuristic(	unsigned int numSamples1, float pdf1,
							unsigned int numSamples2, float pdf2);

	float powerHeuristic(	unsigned int numSamples1, float pdf1,
							unsigned int numSamples2, float pdf2);
}



#endif //RTMATH_H