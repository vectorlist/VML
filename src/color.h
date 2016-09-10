
#ifndef COLOR_H
#define COLOR_H

#include <math.h>
#include <algorithm>
#include <qdebug.h>
#include <vec3f.h>

class Color
{
public:
	float r, g, b;
	Color() :r(0.0), g(0.0), b(0.0){};
	Color(const float &f) : r(f), g(f), b(f){}
	Color(float _r, float _g, float _b) : r(_r), g(_g), b(_b){}
	Color(const Color &c) :r(c.r), g(c.g), b(c.b){};

	void clamp(float min = 0.0, float max = 1.0)
	{
		r = std::max(min, std::min(max, r));
		g = std::max(min, std::min(max, g));
		b = std::max(min, std::min(max, b));
	}

	Color& operator = (const Color &c)
	{
		r = c.r;
		g = c.g;
		b = c.b;
		return *this;
	}

	Color& operator += (const Color &c)
	{
		r += c.r;
		g += c.g;
		b += c.b;
		return *this;
	}

	Color& operator -= (const Color &c)
	{
		r -= c.r;
		g -= c.g;
		b -= c.b;
		return *this;
	}

	Color& operator *= (const Color &c)
	{
		r *= c.r;
		g *= c.g;
		b *= c.b;
		return *this;
	}

	Color& operator /= (const Color &c)
	{
		r /= c.r;
		g /= c.g;
		b /= c.b;
		return *this;
	}

	Color& operator *= (float f)
	{
		r *= f;
		g *= f;
		b *= f;
		return *this;
	}

	Color& operator /= (float f)
	{
		r /= f;
		g /= f;
		b /= f;
		return *this;
	}

	
	friend QDebug& operator<<(QDebug& d,const Color& c)
	{
		return d.nospace() << "Color(" << c.r << ',' << c.g << ',' << c.b << ')';
	}
};

inline Color operator+(const Color &c1, const Color &c2)
{
	return Color(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
}

inline Color operator-(const Color &c1, const Color &c2)
{
	return Color(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b);
}

inline Color operator*(const Color &c1, const Color &c2)
{
	return Color(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b);
}

inline Color operator/(const Color &c1, const Color &c2)
{
	return Color(c1.r / c2.r, c1.g / c2.g, c1.b / c2.b);
}

inline Color operator*(const Color &c1, float f)
{
	return Color(c1.r * f, c1.g * f, c1.b * f);
}

inline Color operator*(float f,const Color &c1)
{
	return Color(f * c1.r,f * c1.g, f * c1.b);
}

inline Color operator/(const Color &c1, float f)
{
	return Color(c1.r / f, c1.g / f, c1.b / f);
}

#endif//COLOR_H