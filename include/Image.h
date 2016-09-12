#ifndef IMAGE_H
#define IMAGE_H

#include <qimage.h>
#include <Color.h>
#include <qdebug.h>
#include <memory>

class Image
{
public:
	Image(){};
	Image(int width, int height,const Color pixels[],
		const float &gamma = 1.0f);
	Image(int width, int height, const std::unique_ptr<Color[]> &pixels,
		const float &gamma = 1.0f);
	~Image();

	QImage data() const{ return *mImage; }			//return QImage
	friend QDebug& operator<<(QDebug& d, const Image &i)
	{
		return d.nospace() << "Image[ "
			<< i.mImage->constBits() << ' ]';
	}
	
private:
	QImage *mImage;
};

#endif // IMAGE_H
