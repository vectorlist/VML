#include <rtmath.h>

float rtmath::clamp(const float& v, const float &min_, const float &max_)
{
	return std::max(min_, std::min(max_, v));
}



void rtmath::fresnel(const vec3f &mDir, const vec3f &N, const float &ior, float &output)
{
	float cosI = clamp(vec3f::dot(mDir, N), -1, 1);
	float etaI = 1;
	float etaT = ior;

	if (cosI > 0) std::swap(etaI, etaT);

	float sinT = etaI / etaT * sqrtf(std::max(0.0f, 1 - cosI* cosI));
	if (sinT >= 1)
	{
		output = 1;
	}
	else
	{
		float cosT = sqrtf(std::max(0.0f, 1 - sinT * sinT));
		cosI = fabsf(cosI);
		float rs = ((etaT * cosI) - (etaI * cosT)) /
			((etaT * cosI) + (etaI * cosT));
		float rp = ((etaI * cosI) - (etaT * cosT)) /
			((etaI * cosI) + (etaT * cosT));

		output = (rs * rs + rp * rp) / 2;
	}

}

float rtmath::fresnel(const vec3f &mDir, const vec3f &N, const float &ior)
{
	float cosI = clamp(vec3f::dot(mDir, N), -1, 1);
	float etaI = 1;
	float etaT = ior;
	float output;
	if (cosI > 0) std::swap(etaI, etaT);

	float sinT = etaI / etaT * sqrtf(std::max(0.0f, 1 - cosI* cosI));
	if (sinT >= 1)
	{
		output = 1;
	}
	else
	{
		float cosT = sqrtf(std::max(0.0f, 1 - sinT * sinT));
		cosI = fabsf(cosI);
		float rs = ((etaT * cosI) - (etaI * cosT)) /
			((etaT * cosI) + (etaI * cosT));
		float rp = ((etaI * cosI) - (etaT * cosT)) /
			((etaI * cosI) + (etaT * cosT));

		output = (rs * rs + rp * rp) / 2;
	}
	return output;
}

vec3f rtmath::refract(const vec3f &mDir, const vec3f &N, const float &ior)
{
	float cosI = clamp(vec3f::dot(mDir, N), -1, 1);
	float etaI = 1;
	float etaT = ior;

	vec3f normal = N;
	if (cosI < 0)
		cosI = -cosI;
	else
	{
		std::swap(etaI, etaT);
		normal = -N;
		/*normal = vec3f(0) - N;*/
	}
	float eta = etaI / etaT;
	float k = 1 - eta * eta * (1 - cosI * cosI);
	vec3f refractVector;
	if (k < 0)
		refractVector = vec3f(0);
	else
		refractVector = eta * mDir + (eta * cosI - sqrt(k)) * normal;

	return refractVector;
}

vec3f rtmath::hemiSphereCoords(const float &r1, const float &r2)
{
	float sinT = sqrt(1 - r1 * r2);
	float phi = 2 * M_PI * r2;

	return  vec3f(sinT * cos(phi), r1, sinT * sin(phi));
}

vec3f rtmath::polarToVector(const float &rho, const float &phi, const float &theta)
{
	/*x = r sin еш cos еї
	y = r sin еш sin еї
	z = r cos еш   from wiki*/

	vec3f v;
	v.x = rho * sin(phi) * cos(theta);
	v.y = rho * sin(phi) * sin(theta);
	v.z = rho * cos(phi);
	return v;
}

vec3f rtmath::polarToVector(const polar3f &p)
{
	vec3f v;
	v.x = p.rho * sin(p.phi) * cos(p.theta);
	v.y = p.rho * sin(p.phi) * sin(p.theta);
	v.z = p.rho * cos(p.phi);
	return v;
}

polar3f rtmath::vectorToPolar(const vec3f &v)
{
	polar3f p;
	//length 
	p.rho = v.length();
	float S = sqrt(v.x * v.x + v.y * v.y);
	p.phi = acos(v.z / p.rho);
	p.theta = (0 <= v.x) ? asin(v.y / S) : M_PI - asin(v.y / S);
	return p;
}

vec3f rtmath::uniformToSphere(float u1, float u2)
{
	//find a height uniformly distributed on the sphere
	float z = 1.0f - 2.0f * u1;
	//find the radius based on that height that sits on the sphere surface
	float radius = sqrt(std::max(0.0f, 1.0f - z * z));
	//find a ramdom algle around on the sphere coord
	float phi = M_PI * 2.0f * u2;
	return vec3f(cos(phi) * radius, sin(phi) * radius, z);

}

vec3f rtmath::uniformCosHemisphere(float u1, float u2)
{
	float dx, dy;
	rtmath::concentricSampleDisk(u1, u2, dx, dy);
	float z = sqrt(std::max(0.0f, 0.1f - dx * dx - dy * dy));
	return vec3f(dx, dy, z);
}

vec3f rtmath::uniformToCone(float u1, float u2, float cosThetaMax)
{
	float cosTheta = u1 * (cosThetaMax - 1.0) + 1.0f;
	float sinTheta = sqrt(std::max(0.0f, 0.1f - cosTheta * cosTheta));
	float phi = M_PI * 2.0f * u2;
	return vec3f(cos(phi) * sinTheta, sin(phi) * sinTheta, cosTheta);
}

float rtmath::uniformConePdf(float cosThetaMax)
{
	return cosThetaMax >= 1.0f ? 0.0 : 1.0f / (2.0f * M_PI * (1.0f - cosThetaMax));
}

void rtmath::makeCoordsSpace(const vec3f normal, vec3f &outX, vec3f &outY, vec3f &outZ)
{
	outZ = normal.normalized();
	vec3f tempAxis;
	if (outZ.x != 0.0f || outZ.z != 0.0f)
		tempAxis = vec3f(0.f, 1.f, 0.f);
	else
		tempAxis = vec3f(1.0, 0.f, 0.f);

	outX = vec3f::cross(tempAxis, outZ).normalized();
	outY = vec3f::cross(outZ, outX).normalized();
}

vec3f rtmath::transformFromLocalSpace(const vec3f &v,
	const vec3f &xAxis, const vec3f &yAxis, const vec3f &zAxis)
{
	return vec3f(
		v.x * xAxis.x + v.y * yAxis.x + v.z * zAxis.x,
		v.x * xAxis.y + v.y * yAxis.y + v.z * zAxis.y,
		v.x * xAxis.z + v.y * yAxis.z + v.z * zAxis.z);
}

void rtmath::concentricSampleDisk(float u1, float u2, float &outDx, float &outDy)
{
	//ref http://l2program.co.uk/900/concentric-disk-sampling
	//give an radom number from -1 to 1
	float r, theta;
	float sx = 2.0f *u1 - 1.0f;
	float sy = 2.0f *u2 - 1.0f;

	if (sx == 0.0f && sy == 0.0f)
	{
		outDx = 0.0f;
		outDy = 0.0f;
		return;
	}
	if (sx >= -sy)
	{
		if (sx > sy)
		{
			//FIRST REGION
			r = sx;
			if (sy > 0.0f)
				theta = sy / r;
			else
				theta = 8.0f + sy / r;
		}
		else
		{
			//SECOND REGION
			r = sy;
			theta = 2.0f - sx / r;
		}
	}
	else
	{
		if (sx <= sy)
		{
			//THIRD REGION
			r = -sx;
			theta = 4.0f - sy / r;
		}
		else
		{
			//FOUTH REGION
			r = -sx;
			theta = 6.0f - sy / r;
		}
	}
	theta *= M_PI / 4.0f;
	outDx = r * cos(theta);
	outDy = r * sin(theta);
}

float rtmath::balaceHeuristic(	unsigned int numSamples1, float pdf1,
								unsigned int numSamples2, float pdf2)
{
	return numSamples1 * pdf1 / (numSamples1 * pdf1 + numSamples2 * pdf2);
}

float rtmath::powerHeuristic(	unsigned int numSamples1, float pdf1,
								unsigned int numSamples2, float pdf2)
{
	float weight1 = numSamples1 * pdf1;
	float weight2 = numSamples2 * pdf2;
	return weight1 * weight1 / (weight1 * weight1 + weight2 * weight2);
}