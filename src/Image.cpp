#include "Image.h"
#include <rtmath.h>

Image::Image(int width, int height, const Color pixels[], const float &gamma)
	: mImage(NULL)
{
	float mGamma = 1.0f/gamma;
	mImage = new QImage(width, height, QImage::Format_RGB888);
	int rows = 0;
	int cols = 0;
	for (unsigned int i = 0; i < (width * height); ++i)
	{
		if (i % width == 0 && i != 0)
		{
			rows++;
			cols = 0;
		}
		if (gamma != 1.0f){
			mImage->setPixel(cols, rows, qRgb(
				rtmath::clamp(pow(pixels[i].r, mGamma), 0.0f,1.0f) * 255.0f,
				rtmath::clamp(pow(pixels[i].g, mGamma), 0.0f, 1.0f) * 255.0f,
				rtmath::clamp(pow(pixels[i].b, mGamma), 0.0f, 1.0f) * 255.0f
				));
		}
		else{
			mImage->setPixel(cols, rows, qRgb(
				pixels[i].r * 255.0f,
				pixels[i].g * 255.0f,
				pixels[i].b * 255.0f
				));
		}
		cols++;
	}
}

Image::Image(int width, int height, const std::unique_ptr<Color[]> &pixels, const float &gamma)
	:mImage(NULL)
{
	float mGamma = 1.0f / gamma;
	mImage = new QImage(width, height, QImage::Format_RGB888);
	int rows = 0;
	int cols = 0;
	for (unsigned int i = 0; i < (width * height); ++i)
	{
		if (i % width == 0 && i != 0)
		{
			rows++;
			cols = 0;
		}
		if (gamma != 1.0f){
			mImage->setPixel(cols, rows, qRgb(
				rtmath::clamp(pow(pixels[i].r, mGamma), 0.0f, 1.0f) * 255.0f,
				rtmath::clamp(pow(pixels[i].g, mGamma), 0.0f, 1.0f) * 255.0f,
				rtmath::clamp(pow(pixels[i].b, mGamma), 0.0f, 1.0f) * 255.0f
				));
		}
		else{
			mImage->setPixel(cols, rows, qRgb(
				pixels[i].r * 255.0f,
				pixels[i].g * 255.0f,
				pixels[i].b * 255.0f
				));
		}
		cols++;
	}
}

Image::~Image()
{
	if (mImage)
		delete mImage;
}
