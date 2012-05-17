/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Graphics/PixelBuffer.h"
#include "BaseLib/Buffers/BinaryFileBuffer.h"
#include "BaseLib/Strings/Manipulation.h"
#include "BaseLib/Files/LocalFile.h"
#include "BaseLib/Graphics/BTFormat.h"
#include "BaseLib/Graphics/intern/Errors.h"
#include "BaseLib/Containers/Array.h"
#include <jpeglib.h>
#include <png.h>
#include <memory>
#include <float.h>



#define MAX_SIZE 1024*256-1



namespace BaseLib {
namespace Graphics {



using namespace BaseLib::Buffers;
using namespace BaseLib::Strings;
using namespace BaseLib::Streams;
using namespace BaseLib::Files;
using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Containers;



BL_DEFINE_REFLECTION_BASE_CLASS(PixelBuffer)
{
	registerProperty("pixelFormat", &PixelBuffer::getPixelFormatAsString, &PixelBuffer::setPixelFormat);
	registerProperty("width", &PixelBuffer::getWidth);
	registerProperty("height", &PixelBuffer::getHeight);
	registerProperty("depth", &PixelBuffer::getDepth);
	registerProperty("bytesPerLine", &PixelBuffer::getBytesPerLine);
	registerProperty("resizeable", &PixelBuffer::isResizeable);
	registerProperty("bytesPerLinePixelAligned", &PixelBuffer::isBytesPerLinePixelAligned);
}



PixelBuffer::PixelBuffer()
	: resizeable(true)
	, width(0)
	, height(0)
	, depth(0)
	, bytesPerLine(0)
	, pixelFormat(8, 8, 8, 8, 0, 8, 16, 24)
	, buffer(0, false)
	, progressCallback(NULL)
{
	BL_ASSERT(pixelFormat.isValid() == true);
}



PixelBuffer::PixelBuffer(const PixelFormat& format, int newWidth, int newHeight, int newDepth, int newBitsPerLine, bool isResizeable, void* usePixels)
	: resizeable(isResizeable)
	, width(newWidth)
	, height(newHeight)
	, depth(newDepth)
	, bytesPerLine(newBitsPerLine == 0 ? format.byteSize() * newWidth : (newBitsPerLine + 7) >> 3)
	, pixelFormat(format)
	, buffer(usePixels, bytesPerLine * height * depth)
	, progressCallback(NULL)
{
	if (pixelFormat.isValid() == false)
	{
		argumentError("Invalid pixel-format '" + String(format) + "' !" ERROR_AT);
	}
	checkArgumentRange(NAME_VALUE(newWidth), 0, MAX_SIZE);
	checkArgumentRange(NAME_VALUE(newHeight), 0, MAX_SIZE);
	checkArgumentRange(NAME_VALUE(newDepth), 0, MAX_SIZE);

	const int bitsPerLine = width * pixelFormat.totalBits;
	if (bytesPerLine*8 < bitsPerLine) bytesPerLine = (bitsPerLine+7) >> 3;
}



PixelBuffer::PixelBuffer(const PixelBuffer& other)
	: resizeable(true)
	, width(0)
	, height(0)
	, depth(0)
	, bytesPerLine(0)
	, pixelFormat(8, 8, 8, 8, 0, 8, 16, 24)
	, buffer(0, false)
	, progressCallback(NULL)
{
	operator =(other);
}



PixelBuffer::PixelBuffer(const String& fileName)
	: resizeable(true)
	, width(0)
	, height(0)
	, depth(0)
	, bytesPerLine(0)
	, pixelFormat(8, 8, 8, 8, 0, 8, 16, 24)
	, buffer(0, false)
	, progressCallback(NULL)
{
	loadFromFile(fileName);
}



PixelBuffer::~PixelBuffer()
{
}



PixelBuffer& PixelBuffer::operator =(const PixelBuffer& right)
{
	resizeable = true;
	resize(right.getPixelFormat(), right.getWidth(), right.getHeight(), right.getDepth());
	copyFrom(right);
	resizeable = right.isResizeable();
	return *this;
}



bool PixelBuffer::isFormatEqual(const PixelBuffer& other) const
{
	return
		width == other.getWidth() &&
		height == other.getHeight() &&
		depth == other.getDepth() &&
		bytesPerLine == other.getBytesPerLine() &&
		pixelFormat == other.getPixelFormat();
}



void PixelBuffer::resize(int newWidth, int newHeight, int newDepth, int newBytesPerLine)
{
	if (resizeable == false)
	{
		stateError(PIXELBUFFER_NOT_RESIZEABLE);
		return;
	}

	if (newWidth != width || newHeight != height || newDepth != depth || newBytesPerLine != bytesPerLine)
	{
		if (checkArgumentRange(NAME_VALUE(newWidth), 0, MAX_SIZE) &&
		    checkArgumentRange(NAME_VALUE(newHeight), 0, MAX_SIZE) &&
			checkArgumentRange(NAME_VALUE(newDepth), 0, MAX_SIZE))
		{
			const int bitsPerLine = newWidth * pixelFormat.totalBits;
			if (newBytesPerLine*8 < bitsPerLine) newBytesPerLine = (bitsPerLine+7) >> 3;

			const int newSize = newBytesPerLine * newHeight * newDepth + 3;
			if (newSize != buffer.getSize())
			{
				buffer.setSize(newSize);
			}

			bytesPerLine = newBytesPerLine;
			width = newWidth;
			height = newHeight;
			depth = newDepth;
		}
	}
}



void PixelBuffer::resize(const PixelFormat& newPixelFormat, int newWidth, int newHeight, int newDepth, int newBytesPerLine)
{
	if (resizeable == false)
	{
		stateError(PIXELBUFFER_NOT_RESIZEABLE);
		return;
	}

	if (newPixelFormat != pixelFormat || newWidth != width || newHeight != height || newDepth != depth || newBytesPerLine != bytesPerLine)
	{
		if (newPixelFormat.isValid() == false)
		{
			argumentError("Invalid pixel-format '" + String(newPixelFormat) + "' !" ERROR_AT);
			return;
		}

		if (checkArgumentRange(NAME_VALUE(newWidth), 0, MAX_SIZE) &&
		    checkArgumentRange(NAME_VALUE(newHeight), 0, MAX_SIZE) &&
			checkArgumentRange(NAME_VALUE(newDepth), 0, MAX_SIZE))
		{
			const int bitsPerLine = newWidth * newPixelFormat.totalBits;
			if (newBytesPerLine*8 < bitsPerLine)
			{
				newBytesPerLine = (bitsPerLine+7) >> 3;
			}

			const int newSize = newBytesPerLine * newHeight * newDepth + 3;
			if (newSize != buffer.getSize())
			{
				buffer.setSize(newSize);
			}

			pixelFormat = newPixelFormat;
			bytesPerLine = newBytesPerLine;
			width = newWidth;
			height = newHeight;
			depth = newDepth;
		}
	}
}



void PixelBuffer::setPixelFormat(const PixelFormat& newPixelFormat)
{
	if (newPixelFormat != pixelFormat)
	{
		if (newPixelFormat.isValid() == true)
		{
			int newBytesPerLine = bytesPerLine;
			const int bitsPerLine = width * newPixelFormat.totalBits;
			if (newBytesPerLine*8 < bitsPerLine) newBytesPerLine = (bitsPerLine+7) >> 3;

			const int newSize = newBytesPerLine * height * depth + 3;
			if (newSize != buffer.getSize())
			{
				if (resizeable == false)
				{
					stateError(PIXELBUFFER_NOT_RESIZEABLE);
					return;
				}

				buffer.setSize(newSize);
			}

			pixelFormat = newPixelFormat;
			bytesPerLine = newBytesPerLine;
		}
		else
		{
			argumentError("Invalid pixel-format '" + String(newPixelFormat) + "' !" ERROR_AT);
		}
	}
}



String PixelBuffer::getPixelFormatAsString() const
{
	return pixelFormat;
}



void PixelBuffer::setPixelFormat(const String& newPixelFormat)
{
	setPixelFormat(PixelFormat(newPixelFormat));
}



void PixelBuffer::fillWithColor(const ByteColor& fillColor)
{
	if (isBytesPerLinePixelAligned() == true)
	{
		PixelIterator pixelIterator = getPixelIterator();
		const int pixelCount = width * height * depth;
		for (int i = 0; i < pixelCount; ++i)
		{
			pixelIterator->setColor(fillColor);
			++pixelIterator;
		}
	}
	else
	{
		for (int z = 0; z < depth; ++z)
		{
			for (int y = 0; y < height; ++y)
			{
				PixelIterator pixelIterator = getPixelIterator(0, y, z);
				for (int x = 0; x < width; ++x)
				{
					pixelIterator->setColor(fillColor);
					++pixelIterator;
				}
			}
		}
	}
}



void PixelBuffer::fillWithColor(const FloatColor& fillColor)
{
	if (isBytesPerLinePixelAligned() == true)
	{
		PixelIterator pixelIterator = getPixelIterator();
		const int pixelCount = width * height * depth;
		for (int i = 0; i < pixelCount; ++i)
		{
			pixelIterator->setColor(fillColor);
			++pixelIterator;
		}
	}
	else
	{
		for (int z = 0; z < depth; ++z)
		{
			for (int y = 0; y < height; ++y)
			{
				PixelIterator pixelIterator = getPixelIterator(0, y, z);
				for (int x = 0; x < width; ++x)
				{
					pixelIterator->setColor(fillColor);
					++pixelIterator;
				}
			}
		}
	}
}



void PixelBuffer::fillWithColor(int red, int green, int blue, int alpha)
{
	if (isBytesPerLinePixelAligned() == true)
	{
		PixelIterator pixelIterator = getPixelIterator();
		const int pixelCount = width * height * depth;
		for (int i = 0; i < pixelCount; ++i)
		{
			pixelIterator->setColor(red, green, blue, alpha);
			++pixelIterator;
		}
	}
	else
	{
		for (int z = 0; z < depth; ++z)
		{
			for (int y = 0; y < height; ++y)
			{
				PixelIterator pixelIterator = getPixelIterator(0, y, z);
				for (int x = 0; x < width; ++x)
				{
					pixelIterator->setColor(red, green, blue, alpha);
					++pixelIterator;
				}
			}
		}
	}
}



void PixelBuffer::fillWithColor(float red, float green, float blue, float alpha)
{
	if (isBytesPerLinePixelAligned() == true)
	{
		PixelIterator pixelIterator = getPixelIterator();
		const int pixelCount = width * height * depth;
		for (int i = 0; i < pixelCount; ++i)
		{
			pixelIterator->setColor(red, green, blue, alpha);
			++pixelIterator;
		}
	}
	else
	{
		for (int z = 0; z < depth; ++z)
		{
			for (int y = 0; y < height; ++y)
			{
				PixelIterator pixelIterator = getPixelIterator(0, y, z);
				for (int x = 0; x < width; ++x)
				{
					pixelIterator->setColor(red, green, blue, alpha);
					++pixelIterator;
				}
			}
		}
	}
}



void PixelBuffer::fillWithColor(const uint8 colorComponents[4])
{
	if (isBytesPerLinePixelAligned() == true)
	{
		PixelIterator pixelIterator = getPixelIterator();
		const int pixelCount = width * height * depth;
		for (int i = 0; i < pixelCount; ++i)
		{
			pixelIterator->setColor(colorComponents);
			++pixelIterator;
		}
	}
	else
	{
		for (int z = 0; z < depth; ++z)
		{
			for (int y = 0; y < height; ++y)
			{
				PixelIterator pixelIterator = getPixelIterator(0, y, z);
				for (int x = 0; x < width; ++x)
				{
					pixelIterator->setColor(colorComponents);
					++pixelIterator;
				}
			}
		}
	}
}



void PixelBuffer::fillWithColor(const float colorComponents[4])
{
	if (isBytesPerLinePixelAligned() == true)
	{
		PixelIterator pixelIterator = getPixelIterator();
		const int pixelCount = width * height * depth;
		for (int i = 0; i < pixelCount; ++i)
		{
			pixelIterator->setColor(colorComponents);
			++pixelIterator;
		}
	}
	else
	{
		for (int z = 0; z < depth; ++z)
		{
			for (int y = 0; y < height; ++y)
			{
				PixelIterator pixelIterator = getPixelIterator(0, y, z);
				for (int x = 0; x < width; ++x)
				{
					pixelIterator->setColor(colorComponents);
					++pixelIterator;
				}
			}
		}
	}
}



void PixelBuffer::swapRedAndBlue(bool modifyPixelFormat)
{
	if (isBytesPerLinePixelAligned() == true)
	{
		PixelIterator pixelIterator = getPixelIterator();
		const int pixelCount = width * height * depth;
		if (pixelFormat.isFloatingPoint() == true)
		{
			for (int i = 0; i < pixelCount; ++i)
			{
				pixelIterator->swapRedAndBlueFloat();
				++pixelIterator;
			}
		}
		else
		{
			for (int i = 0; i < pixelCount; ++i)
			{
				pixelIterator->swapRedAndBlueInt();
				++pixelIterator;
			}
		}
	}
	else
	{
		if (pixelFormat.isFloatingPoint() == true)
		{
			for (int z = 0; z < depth; ++z)
			{
				for (int y = 0; y < height; ++y)
				{
					PixelIterator pixelIterator = getPixelIterator(0, y, z);
					for (int x = 0; x < width; ++x)
					{
						pixelIterator->swapRedAndBlueInt();
						++pixelIterator;
					}
				}
			}
		}
		else
		{
			for (int z = 0; z < depth; ++z)
			{
				for (int y = 0; y < height; ++y)
				{
					PixelIterator pixelIterator = getPixelIterator(0, y, z);
					for (int x = 0; x < width; ++x)
					{
						pixelIterator->swapRedAndBlueFloat();
						++pixelIterator;
					}
				}
			}
		}
	}

	if (modifyPixelFormat == true)
	{
		swap(pixelFormat.redBits, pixelFormat.blueBits);
		swap(pixelFormat.redShift, pixelFormat.blueShift);
	}
}



void PixelBuffer::filterBilinearSizeMinusOne()
{
	PixelBuffer copy = *this;
	filterBilinearSizeMinusOne(copy);
}



void PixelBuffer::filterBilinearSizeMinusOne(const PixelBuffer& srcPixelBuffer)
{
	if (&srcPixelBuffer == this)
	{
		argumentError("Can only filter from other pixel-buffer!" ERROR_AT);
		return;
	}
	if (checkArgumentGreater(NAME_VALUE(srcPixelBuffer.getWidth()), 1) == false ||
		checkArgumentGreater(NAME_VALUE(srcPixelBuffer.getHeight()), 1) == false)
	{
		return;
	}
	if (checkArgumentEquals(NAME_VALUE(srcPixelBuffer.getDepth()), 1) == false)
	{
		return;
	}

	resize(srcPixelBuffer.getPixelFormat(), srcPixelBuffer.getWidth()-1, srcPixelBuffer.getHeight()-1, srcPixelBuffer.getDepth());

	if (pixelFormat.isFloatingPoint() == true)
	{
		if (pixelFormat.hasColor() == true)
		{
			for (int y = 0; y < height; ++y)
			{
				for (int x = 0; x < width; ++x)
				{
					const float red =   0.25f * (srcPixelBuffer.pixel(x, y).getRedAsFloat() + 
												srcPixelBuffer.pixel(x+1, y).getRedAsFloat() + 
												srcPixelBuffer.pixel(x+1, y+1).getRedAsFloat() + 
												srcPixelBuffer.pixel(x, y+1).getRedAsFloat());

					const float green = 0.25f * (srcPixelBuffer.pixel(x, y).getGreenAsFloat() + 
												srcPixelBuffer.pixel(x+1, y).getGreenAsFloat() + 
												srcPixelBuffer.pixel(x+1, y+1).getGreenAsFloat() + 
												srcPixelBuffer.pixel(x, y+1).getGreenAsFloat());

					const float blue =  0.25f * (srcPixelBuffer.pixel(x, y).getBlueAsFloat() + 
												srcPixelBuffer.pixel(x+1, y).getBlueAsFloat() + 
												srcPixelBuffer.pixel(x+1, y+1).getBlueAsFloat() + 
												srcPixelBuffer.pixel(x, y+1).getBlueAsFloat());

					pixel(x, y).setRed(red);
					pixel(x, y).setGreen(green);
					pixel(x, y).setBlue(blue);
				}
			}
		}

		if (pixelFormat.hasAlpha() == true)
		{
			for (int y = 0; y < height; ++y)
			{
				for (int x = 0; x < width; ++x)
				{
					const float alpha = 0.25f * (srcPixelBuffer.pixel(x, y).getAlphaAsFloat() + 
												srcPixelBuffer.pixel(x+1, y).getAlphaAsFloat() + 
												srcPixelBuffer.pixel(x+1, y+1).getAlphaAsFloat() + 
												srcPixelBuffer.pixel(x, y+1).getAlphaAsFloat());

					pixel(x, y).setAlpha(alpha);
				}
			}
		}
	}
	else
	{
		if (pixelFormat.hasColor() == true)
		{
			for (int y = 0; y < height; ++y)
			{
				for (int x = 0; x < width; ++x)
				{
					const int red = (srcPixelBuffer.pixel(x, y).getRedInt() + 
										srcPixelBuffer.pixel(x+1, y).getRedInt() + 
										srcPixelBuffer.pixel(x+1, y+1).getRedInt() + 
										srcPixelBuffer.pixel(x, y+1).getRedInt()) >> 2;

					const int green = (srcPixelBuffer.pixel(x, y).getGreenInt() + 
										srcPixelBuffer.pixel(x+1, y).getGreenInt() + 
										srcPixelBuffer.pixel(x+1, y+1).getGreenInt() + 
										srcPixelBuffer.pixel(x, y+1).getGreenInt()) >> 2;

					const int blue = (srcPixelBuffer.pixel(x, y).getBlueInt() + 
										srcPixelBuffer.pixel(x+1, y).getBlueInt() + 
										srcPixelBuffer.pixel(x+1, y+1).getBlueInt() + 
										srcPixelBuffer.pixel(x, y+1).getBlueInt()) >> 2;

					pixel(x, y).setRed(red);
					pixel(x, y).setGreen(green);
					pixel(x, y).setBlue(blue);
				}
			}
		}

		if (pixelFormat.hasAlpha() == true)
		{
			for (int y = 0; y < height; ++y)
			{
				for (int x = 0; x < width; ++x)
				{
					const int alpha = (srcPixelBuffer.pixel(x, y).getAlphaInt() + 
										srcPixelBuffer.pixel(x+1, y).getAlphaInt() + 
										srcPixelBuffer.pixel(x+1, y+1).getAlphaInt() + 
										srcPixelBuffer.pixel(x, y+1).getAlphaInt()) >> 2;

					pixel(x, y).setAlpha(alpha);
				}
			}
		}
	}
}



void PixelBuffer::copyFrom(const PixelBuffer& srcPixelBuffer, int srcX, int srcY, int srcZ, int srcWidth, int srcHeight, int srcDepth, int dstX, int dstY, int dstZ)
{
	if (checkArgumentPositive(NAME_VALUE(srcX)) == false ||
		checkArgumentPositive(NAME_VALUE(srcY)) == false ||
		checkArgumentPositive(NAME_VALUE(srcZ)) == false ||
		checkArgumentPositive(NAME_VALUE(width)) == false ||
		checkArgumentPositive(NAME_VALUE(height)) == false ||
		checkArgumentPositive(NAME_VALUE(depth)) == false ||
		checkArgumentPositive(NAME_VALUE(dstX)) == false ||
		checkArgumentPositive(NAME_VALUE(dstY)) == false ||
		checkArgumentPositive(NAME_VALUE(dstZ)) == false)
	{
		return;
	}

	if (srcWidth == 0) srcWidth = srcPixelBuffer.getWidth();
	if (srcHeight == 0) srcHeight = srcPixelBuffer.getHeight();
	if (srcDepth == 0) srcDepth = srcPixelBuffer.getDepth();

	if ((srcX + srcWidth) > srcPixelBuffer.getWidth()) srcWidth = srcPixelBuffer.getWidth() - srcX;
	if ((srcY + srcHeight) > srcPixelBuffer.getHeight()) srcHeight = srcPixelBuffer.getHeight() - srcY;
	if ((srcZ + srcDepth) > srcPixelBuffer.getDepth()) srcDepth = srcPixelBuffer.getDepth() - srcZ;

	if ((dstX + srcWidth) > width) srcWidth = width - dstX;
	if ((dstY + srcHeight) > height) srcHeight = height - dstY;
	if ((dstZ + srcDepth) > depth) srcDepth = depth - dstZ;
	

	if (pixelFormat.isByteAligned() == true && srcPixelBuffer.pixelFormat == pixelFormat)
	{
		const int bytesPerPixel = pixelFormat.byteSize();
		const int bytesPerLine = bytesPerPixel * srcWidth;

		for (int z = 0; z < srcDepth; ++z)
		{
			for (int y = 0; y < srcHeight; ++y)
			{
				const Pixel srcPixel = srcPixelBuffer.pixel(srcX + 0, srcY + y, srcZ + z);
				Pixel dstPixel = pixel(dstX + 0, dstY + y, dstZ + z);
				memCopy(dstPixel.getAlignedPointer(), srcPixel.getAlignedPointer(), bytesPerLine);
			}
		}
	}
	else
	{
		for (int z = 0; z < srcDepth; ++z)
		{
			for (int y = 0; y < srcHeight; ++y)
			{
				ConstPixelIterator srcPixelIterator = srcPixelBuffer.getPixelIterator(srcX + 0, srcY + y, srcZ + z);
				PixelIterator dstPixelIterator = getPixelIterator(dstX + 0, dstY + y, dstZ + z);
				for (int x = 0; x < srcWidth; ++x)
				{
					dstPixelIterator->setColor(*srcPixelIterator);
					++srcPixelIterator;
					++dstPixelIterator;
				}
			}
		}
	}
}



void PixelBuffer::getColorRange(int& redMin, int& greenMin, int& blueMin, int& alphaMin, int& redMax, int& greenMax, int& blueMax, int& alphaMax, int x, int y, int z, int width, int height, int depth) const
{
	if (checkArgumentPositive(NAME_VALUE(width)) == false ||
		checkArgumentPositive(NAME_VALUE(height)) == false ||
		checkArgumentPositive(NAME_VALUE(depth)) == false)
	{
		return;
	}
	if (x < 0 || y < 0 || z < 0 || (x + width) >= getWidth() || (y + height) >= getHeight() || (z + depth) >= getDepth())
	{
		argumentError(PIXEL_AREA_OUT_OF_RANGE);
		return;
	}

	if (width == 0) width = getWidth() - x;
	if (height == 0) height = getHeight() - y;
	if (depth == 0) depth = getDepth() - z;

	const bool hasColor = pixelFormat.hasColor();
	const bool hasAlpha = pixelFormat.hasAlpha();

	int startMin = (hasColor == true) ? INT_MAX : 0;
	int startMax = (hasColor == true) ? INT_MIN : 0;
	redMin = startMin;
	greenMin = startMin;
	blueMin = startMin;
	redMax = startMax;
	greenMax = startMax;
	blueMax = startMax;

	startMin = (hasAlpha == true) ? INT_MAX : 0;
	startMax = (hasAlpha == true) ? INT_MIN : 0;
	alphaMin = startMin;
	alphaMax = startMax;

	for (int rz = 0; rz < depth; ++rz)
	{
		for (int ry = 0; ry < height; ++ry)
		{
			ConstPixelIterator pixelIterator = getPixelIterator(x + 0, y + ry, z + rz);
			for (int rx = 0; rx < width; ++rx)
			{
				if (hasColor == true)
				{
					const int red = pixelIterator->getRedInt(pixelFormat.redBits);
					const int green = pixelIterator->getGreenInt(pixelFormat.greenBits);
					const int blue = pixelIterator->getBlueInt(pixelFormat.blueBits);
					if (red < redMin) redMin = red;
					if (red > redMax) redMax = red;
					if (green < greenMin) greenMin = green;
					if (green > greenMax) greenMax = green;
					if (blue < blueMin) blueMin = blue;
					if (blue > blueMax) blueMax = blue;
				}
				if (hasAlpha == true)
				{	
					const int alpha = pixelIterator->getAlphaInt(pixelFormat.alphaBits);
					if (alpha < alphaMin) alphaMin = alpha;
					if (alpha > alphaMax) alphaMax = alpha;
				}
				++pixelIterator;
			}
		}
	}
}



void PixelBuffer::getColorRange(float& redMin, float& greenMin, float& blueMin, float& alphaMin, float& redMax, float& greenMax, float& blueMax, float& alphaMax, int x, int y, int z, int width, int height, int depth) const
{
	if (checkArgumentPositive(NAME_VALUE(width)) == false ||
		checkArgumentPositive(NAME_VALUE(height)) == false ||
		checkArgumentPositive(NAME_VALUE(depth)) == false)
	{
		return;
	}
	if (x < 0 || y < 0 || z < 0 || (x + width) >= getWidth() || (y + height) >= getHeight() || (z + depth) >= getDepth())
	{
		argumentError(PIXEL_AREA_OUT_OF_RANGE);
		return;
	}

	if (width == 0) width = getWidth() - x;
	if (height == 0) height = getHeight() - y;
	if (depth == 0) depth = getDepth() - z;

	const bool hasColor = pixelFormat.hasColor();
	const bool hasAlpha = pixelFormat.hasAlpha();

	float startMin = (hasColor == true) ? +FLT_MAX : 0;
	float startMax = (hasColor == true) ? -FLT_MAX : 0;
	redMin = startMin;
	greenMin = startMin;
	blueMin = startMin;
	redMax = startMax;
	greenMax = startMax;
	blueMax = startMax;

	startMin = (hasAlpha == true) ? +FLT_MAX : 0;
	startMax = (hasAlpha == true) ? -FLT_MAX : 0;
	alphaMin = startMin;
	alphaMax = startMax;

	for (int rz = 0; rz < depth; ++rz)
	{
		for (int ry = 0; ry < height; ++ry)
		{
			ConstPixelIterator pixelIterator = getPixelIterator(x + 0, y + ry, z + rz);
			for (int rx = 0; rx < width; ++rx)
			{
				if (hasColor == true)
				{
					const float red = pixelIterator->getRedAsFloat();
					const float green = pixelIterator->getGreenAsFloat();
					const float blue = pixelIterator->getBlueAsFloat();
					if (red < redMin) redMin = red;
					if (red > redMax) redMax = red;
					if (green < greenMin) greenMin = green;
					if (green > greenMax) greenMax = green;
					if (blue < blueMin) blueMin = blue;
					if (blue > blueMax) blueMax = blue;
				}
				if (hasAlpha == true)
				{
					const float alpha = pixelIterator->getAlphaAsFloat();				
					if (alpha < alphaMin) alphaMin = alpha;
					if (alpha > alphaMax) alphaMax = alpha;
				}
				++pixelIterator;
			}
		}
	}
}



void PixelBuffer::getColorRange(int& min, int& max, bool lookAtColor, bool lookAtAlpha, int x, int y, int z, int width, int height, int depth) const
{
	if (lookAtColor == false && lookAtAlpha == false)
	{
		argumentError("lookAtColor or lookAtAlpha must be true!" ERROR_AT);
		return;
	}

	int redMin;
	int greenMin;
	int blueMin;
	int alphaMin;
	int redMax;
	int greenMax;
	int blueMax;
	int alphaMax;

	getColorRange(redMin, greenMin, blueMin, alphaMin, redMax, greenMax, blueMax, alphaMax, x, y, z, width, height, depth);

	min = INT_MAX;
	max = INT_MIN;

	if (lookAtColor == true)
	{
		if (redMin < min) min = redMin;
		if (redMax > max) max = redMax;
		if (greenMin < min) min = greenMin;
		if (greenMax > max) max = greenMax;
		if (blueMin < min) min = blueMin;
		if (blueMax > max) max = blueMax;
	}

	if (lookAtAlpha == true)
	{
		if (alphaMin < min) min = alphaMin;
		if (alphaMax > max) max = alphaMax;
	}
}


void PixelBuffer::getColorRange(float& min, float& max, bool lookAtColor, bool lookAtAlpha, int x, int y, int z, int width, int height, int depth) const
{
	if (lookAtColor == false && lookAtAlpha == false)
	{
		argumentError("lookAtColor or lookAtAlpha must be true!" ERROR_AT);
		return;
	}

	float redMin;
	float greenMin;
	float blueMin;
	float alphaMin;
	float redMax;
	float greenMax;
	float blueMax;
	float alphaMax;

	getColorRange(redMin, greenMin, blueMin, alphaMin, redMax, greenMax, blueMax, alphaMax, x, y, z, width, height, depth);

	min = FLT_MAX;
	max = -FLT_MAX;

	if (lookAtColor == true)
	{
		if (redMin < min) min = redMin;
		if (redMax > max) max = redMax;
		if (greenMin < min) min = greenMin;
		if (greenMax > max) max = greenMax;
		if (blueMin < min) min = blueMin;
		if (blueMax > max) max = blueMax;
	}

	if (lookAtAlpha == true)
	{
		if (alphaMin < min) min = alphaMin;
		if (alphaMax > max) max = alphaMax;
	}
}



void PixelBuffer::changeColorRangeInt(int redDelta, int greenDelta, int blueDelta, int alphaDelta, float redScale, float greenScale, float blueScale, float alphaScale, int x, int y, int z, int width, int height, int depth)
{
	if (pixelFormat.isFloatingPoint() == true)
	{
		changeColorRangeFloat((float)redDelta, (float)greenDelta, (float)blueDelta, (float)alphaDelta, redScale, greenScale, blueScale, alphaScale, x, y, z, width, height, depth);
		return;
	}

	if (checkArgumentPositive(NAME_VALUE(width)) == false ||
		checkArgumentPositive(NAME_VALUE(height)) == false ||
		checkArgumentPositive(NAME_VALUE(depth)) == false)
	{
		return;
	}
	if (x < 0 || y < 0 || z < 0 || (x + width) >= getWidth() || (y + height) >= getHeight() || (z + depth) >= getDepth())
	{
		argumentError(PIXEL_AREA_OUT_OF_RANGE);
		return;
	}

	if (width == 0) width = getWidth() - x;
	if (height == 0) height = getHeight() - y;
	if (depth == 0) depth = getDepth() - z;

	const bool hasColor = pixelFormat.hasColor();
	const bool hasAlpha = pixelFormat.hasAlpha();

	for (int rz = 0; rz < depth; ++rz)
	{
		for (int ry = 0; ry < height; ++ry)
		{
			int value;
			PixelIterator pixelIterator = getPixelIterator(x + 0, y + ry, z + rz);
			for (int rx = 0; rx < width; ++rx)
			{
				if (hasColor == true)
				{
					value = pixelIterator->getRedInt() + redDelta;
					if (redScale != 1.0f) value = round<int>(value * redScale);
					pixelIterator->setRed(value);

					value = pixelIterator->getGreenInt() + greenDelta;
					if (greenScale != 1.0f) value = round<int>(value * greenScale);
					pixelIterator->setGreen(value);

					value = pixelIterator->getBlueInt() + blueDelta;
					if (blueScale != 1.0f) value = round<int>(value * blueScale);
					pixelIterator->setBlue(value);
				}
				if (hasAlpha == true)
				{
					value = pixelIterator->getAlphaInt() + alphaDelta;
					if (alphaScale != 1.0f) value = round<int>(value * alphaScale);
					pixelIterator->setAlpha(value);
				}				
				++pixelIterator;
			}
		}
	}
}



void PixelBuffer::changeColorRangeFloat(float redDelta, float greenDelta, float blueDelta, float alphaDelta, float redScale, float greenScale, float blueScale, float alphaScale, int x, int y, int z, int width, int height, int depth)
{
	if (checkArgumentPositive(NAME_VALUE(width)) == false ||
		checkArgumentPositive(NAME_VALUE(height)) == false ||
		checkArgumentPositive(NAME_VALUE(depth)) == false)
	{
		return;
	}
	if (x < 0 || y < 0 || z < 0 || (x + width) >= getWidth() || (y + height) >= getHeight() || (z + depth) >= getDepth())
	{
		argumentError(PIXEL_AREA_OUT_OF_RANGE);
		return;
	}

	if (width == 0) width = getWidth() - x;
	if (height == 0) height = getHeight() - y;
	if (depth == 0) depth = getDepth() - z;

	const bool hasColor = pixelFormat.hasColor();
	const bool hasAlpha = pixelFormat.hasAlpha();

	for (int rz = 0; rz < depth; ++rz)
	{
		for (int ry = 0; ry < height; ++ry)
		{
			PixelIterator pixelIterator = getPixelIterator(x + 0, y + ry, z + rz);
			for (int rx = 0; rx < width; ++rx)
			{
				if (hasColor == true)
				{
					pixelIterator->setRed((pixelIterator->getRedAsFloat() + redDelta) * redScale);
					pixelIterator->setGreen((pixelIterator->getGreenAsFloat() + greenDelta) * greenScale);
					pixelIterator->setBlue((pixelIterator->getBlueAsFloat() + blueDelta) * blueScale);
				}
				if (hasAlpha == true)
				{
					pixelIterator->setAlpha((pixelIterator->getAlphaAsFloat() + alphaDelta) * alphaScale);
				}
				++pixelIterator;
			}
		}
	}
}



bool PixelBuffer::loadFromFile(const String& fileName)
{
	if (fileName.endsCaseInsensitiveWith(".pbf") == true)
	{
		return loadFromPBF(fileName);
	}

	if (fileName.endsCaseInsensitiveWith(".tga") == true)
	{
		return loadFromTGA(fileName);
	}

	if (fileName.endsCaseInsensitiveWith(".png") == true)
	{
		return loadFromPNG(fileName);
	}

	if (fileName.endsCaseInsensitiveWith(".jpg") == true || fileName.endsCaseInsensitiveWith(".jpeg") == true)
	{
		return loadFromJPEG(fileName);
	}

	if (fileName.endsCaseInsensitiveWith(".bt") == true)
	{
		return loadFromBT(fileName, BTHeader());
	}

	argumentError(UNSUPPORTED_FILE_TYPE(fileName));
	return false;
}



bool PixelBuffer::saveAsFile(const String& fileName) const
{
	if (fileName.endsCaseInsensitiveWith(".pbf") == true)
	{
		return saveAsPBF(fileName);
	}

	if (fileName.endsCaseInsensitiveWith(".tga") == true)
	{
		return saveAsTGA(fileName);
	}

	if (fileName.endsCaseInsensitiveWith(".png") == true)
	{
		return saveAsPNG(fileName);
	}

	if (fileName.endsCaseInsensitiveWith(".jpg") == true || fileName.endsCaseInsensitiveWith(".jpeg") == true)
	{
		return saveAsJPEG(fileName);
	}

	if (fileName.endsCaseInsensitiveWith(".bt") == true)
	{
		return saveAsBT(fileName);
	}

	argumentError(UNSUPPORTED_FILE_TYPE(fileName));
	return false;
}



class JPEGLibError : public Exception {
public:
	JPEGLibError(const String& errorDescription) : Exception(errorDescription) {}
};



void jpgetLibErrorExit(j_common_ptr cinfo)
{
	throw JPEGLibError(cinfo->err->jpeg_message_table[cinfo->err->last_jpeg_message]); // TODO: must work without exceptions
}



bool PixelBuffer::loadFromJPEG(const String& fileName)
{
	FILE * file = fopen(fileName.getChar8CString(), "rb");	
	if (file == NULL)
	{
		ioError(FILE_NOT_FOUND(fileName));
		return false;
	}

	jpeg_error_mgr errorHandler;
	jpeg_decompress_struct decompressInfo;
	decompressInfo.err = jpeg_std_error(&errorHandler);
	errorHandler.error_exit = &jpgetLibErrorExit;

	try
	{
		jpeg_create_decompress(&decompressInfo);
		jpeg_stdio_src(&decompressInfo, file);
		jpeg_read_header(&decompressInfo, true);
		jpeg_start_decompress(&decompressInfo);

		PixelFormat newPixelFormat = decompressInfo.num_components == 1 ? "a8" : "r8g8b8";
		resize(newPixelFormat, decompressInfo.output_width, decompressInfo.output_height);
		const int jpegLineSize = decompressInfo.output_width * decompressInfo.output_components;

		const int maxReadLines = 8;
		JSAMPARRAY buffer = decompressInfo.mem->alloc_sarray(reinterpret_cast<j_common_ptr>(&decompressInfo), JPOOL_IMAGE, jpegLineSize, maxReadLines);
		const float ooHeight = 1.0f / static_cast<float>(decompressInfo.output_height);

		while (decompressInfo.output_scanline < decompressInfo.output_height)
		{
			if (progressCallback != NULL && (decompressInfo.output_scanline % (height / 10)) == 0)
			{				
				if (progressCallback(decompressInfo.output_scanline * ooHeight) == false)
				{
					jpeg_destroy_decompress(&decompressInfo);
					fclose(file);
					return false;
				}
			}

			const int currentScanline = decompressInfo.output_scanline;
			const int linesRead = jpeg_read_scanlines(&decompressInfo, buffer, maxReadLines);

			for (int l = 0; l < linesRead; ++l)
			{
				// byteausgerichtetes Kopieren - sp�ter durch bitausgerichtetes Kopieren ersetzen
				memCopy(offsetPointer(getBufferPointer(), (currentScanline+l)*bytesPerLine), buffer[l], jpegLineSize);
			}
		}

		if (progressCallback != NULL && progressCallback(1.0f) == false)
		{
			jpeg_destroy_decompress(&decompressInfo);
			fclose(file);
			return false;
		}

		jpeg_finish_decompress(&decompressInfo);
		jpeg_destroy_decompress(&decompressInfo);
	}
	catch(const JPEGLibError& jpegLibError)
	{
		jpeg_destroy_decompress(&decompressInfo);
		fclose(file);
		resultError(LOAD_JPEG_ERROR(fileName, jpegLibError.what()));
		return false;
	}

	fclose(file);
	if (progressCallback != NULL) progressCallback(1.0f);
	return true;
}



bool PixelBuffer::saveAsJPEG(const String& fileName, float quality, bool encodeProgressive) const
{
	if (pixelFormat.isJPEGCompatible() == false)
	{
		argumentError(PIXELFORMAT_NOT_JPEG_COMPATBLE(pixelFormat));
		return false;
	}

	if (quality < 0.0f || quality > 1.0f)
	{
		argumentError(ILLEGAL_COMPRESSION_QUALITY(quality));
		return false;
	}

	FILE * file = fopen(fileName.getChar8CString(), "wb");	
	if (file == NULL)
	{
		ioError(FILE_NOT_FOUND(fileName));
		return false;
	}

	jpeg_error_mgr errorHandler;
	jpeg_compress_struct compressInfo;
	compressInfo.err = jpeg_std_error(&errorHandler);
	errorHandler.error_exit = &jpgetLibErrorExit;

	try
	{
		jpeg_create_compress(&compressInfo);
		jpeg_stdio_dest(&compressInfo, file);

		compressInfo.image_width = width;
		compressInfo.image_height = height;
		compressInfo.input_components = pixelFormat.getComponentCount();
		compressInfo.in_color_space = compressInfo.input_components == 1 ? JCS_GRAYSCALE : JCS_RGB;
		compressInfo.optimize_coding = true;
		jpeg_set_defaults(&compressInfo);
		jpeg_set_quality(&compressInfo, static_cast<int>(quality * 99.0f + 1.5f), true);
		if (encodeProgressive == true)
		{
			jpeg_simple_progression(&compressInfo);
		}

		jpeg_start_compress(&compressInfo, true);
		
		JSAMPROW buffer[1];
		const float ooHeight = 1.0f / static_cast<float>(height);
		while (compressInfo.next_scanline < compressInfo.image_height)
		{
			if (progressCallback != NULL && (compressInfo.next_scanline % (height / 10)) == 0)
			{
				if (progressCallback(compressInfo.next_scanline * ooHeight) == false)
				{
					jpeg_destroy_compress(&compressInfo);
					fclose(file);
					return false;
				}
			}

			buffer[0] = &memoryAs<JSAMPLE>(const_cast<void*>(getBufferPointer()), compressInfo.next_scanline*bytesPerLine);
			jpeg_write_scanlines(&compressInfo, buffer, 1);
		}

		if (progressCallback != NULL && progressCallback(1.0f) == false)
		{
			jpeg_destroy_compress(&compressInfo);
			fclose(file);
			return false;
		}

		jpeg_finish_compress(&compressInfo);
		jpeg_destroy_compress(&compressInfo);
	}
	catch(const JPEGLibError& jpegLibError)
	{
		jpeg_destroy_compress(&compressInfo);
		fclose(file);
		resultError(SAVE_JPEG_ERROR(fileName, jpegLibError.what()));
		return false;
	}

	fclose(file);
	return true;
}


class CancelPNGProgress {};


void PNGAPI pngRowCallback(png_structp pngInstance, png_uint_32 row, int pass)
{
	const PixelBuffer* pixelBuffer = static_cast<const PixelBuffer*>(png_get_error_ptr(pngInstance));
	if (pixelBuffer->progressCallback != NULL)
	{
		const int height = pixelBuffer->getHeight();

		if (row % (height / 10) == 0 || row == height)
		{
			const float progress = static_cast<float>(row) / static_cast<float>(height);
			if (pixelBuffer->progressCallback(progress) == false)
			{
				throw CancelPNGProgress(); // TODO: must work without exceptions
			}
		}
		/// pass noch ber�cksichten ?
	}
}



class LibPNGError : public Exception {
public:
	LibPNGError(const String& errorDescription) : Exception(errorDescription) {}
};



void PNGAPI pngUserError(png_structp pngInstance, png_const_charp errorMsg)
{
	throw LibPNGError(errorMsg); // TODO: must work without exceptions
}



void PNGAPI pngUserWarning(png_structp pngInstance, png_const_charp warningMsg)
{
}



bool PixelBuffer::loadFromPNG(const String& fileName)
{
	String usedFileName = fileName;
	usedFileName.ensureEndsCaseInsensitiveWith(".png");

	FILE * file = fopen(usedFileName.getChar8CString(), "rb");	
	if (file == NULL)
	{
		ioError(FILE_NOT_FOUND(usedFileName));
		return false;
	}

	png_byte header[8];
	
    fread(header, sizeof(png_byte), sizeof(header), file);
    if (png_sig_cmp(header, 0, sizeof(png_byte)) != 0)
	{
		fclose(file);
		ioError(FILE_IS_NOT_A_PNG(fileName));
		return false;
	}	

	png_structp pngInstance = png_create_read_struct(PNG_LIBPNG_VER_STRING, this, pngUserError, pngUserWarning);
	if (pngInstance == NULL)
	{
		fclose(file);
		resultError(LOAD_PNG_ERROR(fileName, "png_create_read_struct() returned NULL"));
		return false;
	}

    png_infop pngInfo = png_create_info_struct(pngInstance);
	if (pngInfo == NULL)
	{
        png_destroy_read_struct(&pngInstance, NULL, NULL);
		fclose(file);
		resultError(LOAD_PNG_ERROR(fileName, "png_create_info_struct() returned NULL"));
		return false;
	}

    png_infop endInfo = png_create_info_struct(pngInstance);
	if (endInfo == NULL)
	{
        png_destroy_read_struct(&pngInstance, &endInfo, NULL);
		fclose(file);
		resultError(LOAD_PNG_ERROR(fileName, "png_create_info_struct() returned NULL"));
		return false;
	}

	try
	{
		png_init_io(pngInstance, file);
		png_set_sig_bytes(pngInstance, sizeof(header));
		png_set_read_status_fn(pngInstance, pngRowCallback);
		png_read_info(pngInstance, pngInfo);

		const int pngInterlaceType = png_get_interlace_type(pngInstance, pngInfo);
		const int numberOfPasses = png_set_interlace_handling(pngInstance);
		png_read_update_info(pngInstance, pngInfo);
		const int pngWidth = png_get_image_width(pngInstance, pngInfo);
		const int pngHeight = png_get_image_height(pngInstance, pngInfo);
		const int pngBitDepth = png_get_bit_depth(pngInstance, pngInfo);
		const int pngColorType = png_get_color_type(pngInstance, pngInfo);

		PixelFormat newPixelFormat;
		newPixelFormat.colorType = PixelFormat::COLOR_TYPE_RGB;

		if (pngColorType == PNG_COLOR_TYPE_PALETTE)
		{
			//fclose(file);
			//png_destroy_read_struct(&pngInstance, &pngInfo, &endInfo);
			//notImplementedError(LOAD_PNG_ERROR(fileName, "Color-Palettes are not supported by BaseLib::Graphics"));
			//return false;
			newPixelFormat.alphaBits = pngBitDepth;
		}
		else
		{
			if (pngColorType == PNG_COLOR_TYPE_GRAY || (pngColorType & PNG_COLOR_MASK_ALPHA) != 0)
			{
				newPixelFormat.alphaBits = pngBitDepth;
			}
			
			if ((pngColorType & PNG_COLOR_MASK_COLOR) != 0)
			{
				newPixelFormat.redBits = pngBitDepth;
				newPixelFormat.greenBits = pngBitDepth;
				newPixelFormat.blueBits = pngBitDepth;

				newPixelFormat.redShift = 0*pngBitDepth;
				newPixelFormat.greenShift = 1*pngBitDepth;
				newPixelFormat.blueShift = 2*pngBitDepth;

				if (newPixelFormat.alphaBits != 0) newPixelFormat.alphaShift = 3*pngBitDepth;
			}

			if (pngBitDepth == 16)
			{
				png_set_swap(pngInstance);
			}

		}

		newPixelFormat.calculateTotalBits();

		if (newPixelFormat.isValid() == false)
		{
			png_destroy_read_struct(&pngInstance, &pngInfo, &endInfo);
			fclose(file);
			notImplementedError(LOAD_PNG_ERROR(fileName, "PNG-ColorType is not supported by BaseLib::Graphics"));
			return false;
		}

		resize(newPixelFormat, pngWidth, pngHeight, 1);

		Array<png_bytep> rowPointers(height);
		for (int y = 0; y < height; ++y)
		{
			rowPointers[y] = &static_cast<png_bytep>(getBufferPointer())[y * bytesPerLine];
		}

		if (progressCallback != NULL && progressCallback(0.0f) == false) throw CancelPNGProgress(); // TODO: must work without exceptions

		png_read_image(pngInstance, &rowPointers.firstElement());
		png_read_end(pngInstance, endInfo);

		png_destroy_read_struct(&pngInstance, &pngInfo, &endInfo);
	}
	catch(const LibPNGError& libPNGError)
	{
		png_destroy_read_struct(&pngInstance, &pngInfo, &endInfo);
		fclose(file);
		resultError(LOAD_PNG_ERROR(fileName, libPNGError.what()));
        return false;
	}
	catch(const CancelPNGProgress&)
	{
		png_destroy_read_struct(&pngInstance, &pngInfo, &endInfo);
		fclose(file);
        return false;
	}

	fclose(file);
	return true;
}



bool PixelBuffer::saveAsPNG(const String& fileName, bool encodeProgressive, float compressionLevel) const
{
	String usedFileName = fileName;
	usedFileName.ensureEndsCaseInsensitiveWith(".png");

	if (pixelFormat.isPNGCompatible() == false)
	{
		argumentError(PIXELFORMAT_NOT_PNG_COMPATBLE(pixelFormat));
		return false;
	}

	if (compressionLevel > 1.0f || compressionLevel < 0.0f)
	{
		argumentError(ILLEGAL_COMPRESSION_LEVEL(compressionLevel));
		return false;
	}

	FILE * file = fopen(usedFileName.getChar8CString(), "wb");	
	if (file == NULL)
	{
		ioError(FILE_NOT_FOUND(usedFileName));
		return false;
	}

	png_structp pngInstance = png_create_write_struct(PNG_LIBPNG_VER_STRING, const_cast<PixelBuffer*>(this), pngUserError, pngUserWarning);
	if (pngInstance == NULL)
	{
		fclose(file);
		resultError(LOAD_PNG_ERROR(fileName, "png_create_write_struct() returned NULL"));
		return false;
	}

    png_infop pngInfo = png_create_info_struct(pngInstance);
	if (pngInfo == NULL)
	{
        png_destroy_write_struct(&pngInstance, NULL);
		fclose(file);
		resultError(LOAD_PNG_ERROR(fileName, "png_create_info_struct() returned NULL"));
		return false;
	}

	const bool hasColor = pixelFormat.hasColor();
	const bool hasAlpha = pixelFormat.hasAlpha();
	const int bitDepth = hasAlpha == true ? pixelFormat.alphaBits : pixelFormat.redBits;
	const int interlaceType = encodeProgressive == true ? PNG_INTERLACE_ADAM7 : PNG_INTERLACE_NONE;
	int colorType;
	if (hasColor == true)
	{
		if (hasAlpha == true)
		{
			colorType = PNG_COLOR_TYPE_RGB_ALPHA;
		}
		else
		{
			colorType = PNG_COLOR_TYPE_RGB;
		}
	}
	else
	{
		//if (hasAlpha == true)
		colorType = PNG_COLOR_TYPE_GRAY;
	}

	try
	{
		png_init_io(pngInstance, file);
		png_set_write_status_fn(pngInstance, pngRowCallback);
		png_set_filter(pngInstance, 0, PNG_ALL_FILTERS);
		png_set_compression_level(pngInstance, static_cast<int>(9.0f * compressionLevel + 0.5));
		png_set_IHDR(pngInstance, pngInfo, width, height, bitDepth, colorType, interlaceType, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
		png_write_info(pngInstance, pngInfo);

		Array<png_bytep> rowPointers(height);
		for (int y = 0; y < height; ++y)
		{
			rowPointers[y] = &static_cast<png_bytep>(const_cast<void*>(getBufferPointer()))[y * bytesPerLine];
		}

		if (progressCallback != NULL && progressCallback(0.0f) == false) throw CancelPNGProgress(); // TODO: must work without exceptions

		png_write_image(pngInstance, &rowPointers.firstElement());
		png_write_end(pngInstance, pngInfo);

		png_destroy_write_struct(&pngInstance, &pngInfo);
	}
	catch(const LibPNGError& libPNGError)
	{
		png_destroy_write_struct(&pngInstance, &pngInfo);
		fclose(file);
		resultError(SAVE_PNG_ERROR(fileName, libPNGError.what()));
        return false;
	}
	catch(const CancelPNGProgress&)
	{
		png_destroy_write_struct(&pngInstance, &pngInfo);
		fclose(file);
        return false;
	}

	fclose(file);
	return true;
}


enum TGAImageType {
	TGA_NO_IMAGE_DATA = 0,
	TGA_UNCOMPRESSED_COLORMAPED = 1,
	TGA_UNCOMPRESSED_TRUECOLOR = 2,
	TGA_UNCOMPRESSED_BLACK_AND_WHITE = 3,
	TGA_RUNLENGTH_ENCODED_COLORMAPPED = 9,
	TGA_RUNLENGTH_ENCODED_TRUECOLOR = 10,
	TGA_RUNLENGTH_ENCODED_BLACK_AND_WHITE = 11
};



#pragma pack(1)



struct TGAHeader {
	TGAHeader()
	  : idLength(0)
	  , colorMap(false)
	  , imageType(TGA_NO_IMAGE_DATA)
	  , firstColorMapEntryIndex(0)
	  , colorMapLength(0)
	  , colorMapEntrySize(0)
	  , xOrigin(0)
	  , yOrigin(0)
	  , imageWidth(0)
	  , imageHeight(0)
	  , pixelDepth(0)
	  , imageDescriptor(1<<5)
	{
	}

	uint8 idLength;
	bool8 colorMap;
	uint8 imageType;
	uint16 firstColorMapEntryIndex;
	uint16 colorMapLength;
	uint8 colorMapEntrySize;
	uint16 xOrigin;
	uint16 yOrigin;
	uint16 imageWidth;
	uint16 imageHeight;
	uint8 pixelDepth;
	uint8 imageDescriptor;
};



#pragma pack()



bool PixelBuffer::loadFromTGA(const String& fileName)
{
	String usedFileName = fileName;
	usedFileName.ensureEndsCaseInsensitiveWith(".tga");

	//pushIOErrorHandler();
	//setIOErrorHandler(ignoreError);
	BinaryFileBuffer fileBuffer(usedFileName, true, false);
	//popIOErrorHandler();

	if (fileBuffer.isOpen() == false)
	{
		ioError(CANT_OPEN_FILE(usedFileName));
		return false;
	}

	TGAHeader header;
	int bytesRead = fileBuffer.readFromCurrentPosition(&header, sizeof(header));
	if (bytesRead != sizeof(header))
	{
		ioError(LOAD_TGA_ERROR(fileName, "Can't read enough bytes"));
		return false;
	}
	fileBuffer.moveCurrentPosition(header.idLength);

	
	if (header.colorMap == true || header.imageType == TGA_UNCOMPRESSED_COLORMAPED || header.imageType == TGA_RUNLENGTH_ENCODED_COLORMAPPED)
	{
		notImplementedError(CANT_LOAD_COLORMAP_TGA_FORMAT(fileName));
		return false;
	}
	if (header.imageType != TGA_UNCOMPRESSED_TRUECOLOR
		&& header.imageType != TGA_UNCOMPRESSED_BLACK_AND_WHITE
		&& header.imageType != TGA_RUNLENGTH_ENCODED_TRUECOLOR
		&& header.imageType != TGA_RUNLENGTH_ENCODED_BLACK_AND_WHITE)
	{
		ioError(LOAD_TGA_ERROR(fileName, "Unknown image type: " + String::createFrom((int)header.imageType)));
		return false;
	}
	if (header.imageType == TGA_RUNLENGTH_ENCODED_TRUECOLOR
		|| header.imageType == TGA_RUNLENGTH_ENCODED_BLACK_AND_WHITE)
	{
		notImplementedError(LOAD_TGA_ERROR(fileName, "Compressed TGAs not supported"));
		return false;
	}

	const bool hasColor = header.pixelDepth > 8;
	const bool hasAlpha = header.pixelDepth == 32 || header.imageType == TGA_UNCOMPRESSED_BLACK_AND_WHITE || header.imageType == TGA_RUNLENGTH_ENCODED_BLACK_AND_WHITE;

	if ((hasColor == true && (header.pixelDepth == 16 || header.pixelDepth == 24 || header.pixelDepth == 32) == false)
		|| (hasAlpha == true && (header.pixelDepth == 8 || header.pixelDepth == 32) == false))
	{
		ioError(LOAD_TGA_ERROR(fileName, "Illegal combination of image-type and pixel-depth"));
		return false;
	}

	if ((header.imageDescriptor & 0xD0) != 0)
	{
		notImplementedError(LOAD_TGA_ERROR(fileName, "Unsupported image orientation"));
		return false;
	}

	const bool upsideDown = (header.imageDescriptor & (1<<5)) == 0;

	PixelFormat newPixelFormat;
	
	switch (header.pixelDepth)
	{
		case 8:
			newPixelFormat = "a8";
			break;

		case 16:
			newPixelFormat = "b5g6r5";
			break;

		case 24:
			newPixelFormat = "b8g8r8";
			break;

		case 32:
			newPixelFormat = "b8g8r8a8";
			break;

		default:
			ioError(LOAD_TGA_ERROR(fileName, "Illegal pixel-depth"));
			return false;
	}

	resize(newPixelFormat, header.imageWidth, header.imageHeight);

	if (progressCallback != NULL)
	{
		const float ooHeight = 1.0f / static_cast<float>(height);
		if (upsideDown == true)
		{
			for (int y = height-1; y >= 0; --y)
			{
				if (progressCallback((height-1 - y) * ooHeight) == false) return false;
				bytesRead = fileBuffer.readFromCurrentPosition(offsetPointer(getBufferPointer(), y*bytesPerLine), bytesPerLine);
				if (bytesRead != bytesPerLine)
				{
					ioError(LOAD_TGA_ERROR(fileName, "Can't read enough bytes"));
					return false;
				}
			}
		}
		else
		{
			for (int y = 0; y < height; ++y)
			{
				if (progressCallback(y * ooHeight) == false) return false;
				bytesRead = fileBuffer.readFromCurrentPosition(offsetPointer(getBufferPointer(), y*bytesPerLine), bytesPerLine);
				if (bytesRead != bytesPerLine)
				{
					ioError(LOAD_TGA_ERROR(fileName, "Can't read enough bytes"));
					return false;
				}
			}
		}

		if (progressCallback(1.0f) == false) return false;
	}
	else
	{
		if (upsideDown == true)
		{
			for (int y = height-1; y >= 0; --y)
			{
				bytesRead = fileBuffer.readFromCurrentPosition(offsetPointer(getBufferPointer(), y*bytesPerLine), bytesPerLine);
				if (bytesRead != bytesPerLine)
				{
					ioError(LOAD_TGA_ERROR(fileName, "Can't read enough bytes"));
					return false;
				}
			}
		}
		else
		{
			bytesRead = fileBuffer.readFromCurrentPosition(getBufferPointer(), height*bytesPerLine);
			if (bytesRead != height*bytesPerLine)
			{
				ioError(LOAD_TGA_ERROR(fileName, "Can't read enough bytes"));
				return false;
			}
		}
	}

	return true;
}



bool PixelBuffer::saveAsTGA(const String& fileName) const
{
	String usedFileName = fileName;
	usedFileName.ensureEndsCaseInsensitiveWith(".tga");

	if (pixelFormat.isTGACompatible() == false)
	{
		argumentError(PIXELFORMAT_NOT_TGA_COMPATBLE(pixelFormat));
		return false;
	}

	LocalFile::removeIfExists(usedFileName);
	BinaryFileBuffer fileBuffer(usedFileName, false, true);
	if (fileBuffer.isOpen() == false)
	{
		ioError(CANT_OPEN_FILE(usedFileName));
		return false;
	}

	TGAHeader header;
	header.imageWidth = width;
	header.imageHeight = height;
	header.pixelDepth = pixelFormat.totalBits;
	header.imageType = pixelFormat.hasColor() == true ? TGA_UNCOMPRESSED_TRUECOLOR : TGA_UNCOMPRESSED_BLACK_AND_WHITE;

	int bytesWritten = fileBuffer.writeAtCurrentPosition(&header, sizeof(header));
	if (bytesWritten != sizeof(header))
	{
		ioError(SAVE_TGA_ERROR(fileName, "Can't write enough bytes"));
		return false;
	}

	if (progressCallback != NULL)
	{
		const int linesPerWrite = height / 10;
		const float ooHeight = 1.0f / static_cast<float>(height);
		for (int y = 0; y < height; y += linesPerWrite)
		{
			if (progressCallback(y * ooHeight) == false) return false;

			bytesWritten = fileBuffer.writeAtCurrentPosition(offsetPointer(getBufferPointer(), y*bytesPerLine), linesPerWrite*bytesPerLine);
			if (bytesWritten != linesPerWrite*bytesPerLine)
			{
				ioError(SAVE_TGA_ERROR(fileName, "Can't write enough bytes"));
				return false;
			}
		}
		const int modLines = height % 10;
		if (modLines > 0)
		{
			bytesWritten = fileBuffer.writeAtCurrentPosition(offsetPointer(getBufferPointer(), linesPerWrite*10*bytesPerLine), modLines*bytesPerLine);
			if (bytesWritten != modLines*bytesPerLine)
			{
				ioError(SAVE_PBF_ERROR(fileName, "Can't write enough bytes"));
				return false;
			}
		}

		if (progressCallback(1.0f) == false) return false;
	}
	else
	{
		if (fileBuffer.writeAtCurrentPosition(getBufferPointer(), height*bytesPerLine) != height*bytesPerLine)
		{
			ioError(SAVE_TGA_ERROR(fileName, "Can't write enough bytes"));
			return false;
		}
	}

	return true;
}



#pragma pack(1)



struct BPFHeader {

	inline static const int32 getID() { return memoryAs<uint32>("PBF1", 0); }

	uint32 id;
	uint16 width;
	uint16 height;
	uint16 depth;
	uint16 bytesPerLine;
};



#pragma pack()



bool PixelBuffer::loadFromPBF(const String& fileName)
{
	String usedFileName = fileName;
	usedFileName.ensureEndsCaseInsensitiveWith(".pbf");

	//pushIOErrorHandler();
	//setIOErrorHandler(ignoreError);
	BinaryFileBuffer fileBuffer(usedFileName, true, false);
	//popIOErrorHandler();

	if (fileBuffer.isOpen() == false)
	{
		ioError(CANT_OPEN_FILE(usedFileName));
		return false;
	}

	BPFHeader header;
	int bytesRead = fileBuffer.readFromCurrentPosition(&header, sizeof(header));
	if (bytesRead != sizeof(header))
	{
		ioError(LOAD_PBF_ERROR(fileName, "Can't read enough bytes"));
		return false;
	}

	if (header.id != BPFHeader::getID())
	{
		notImplementedError(LOAD_PBF_ERROR(fileName, "Invalid file-type or version"));
		return false;
	}

	PixelFormat newPixelFormat;
	bytesRead = fileBuffer.readFromCurrentPosition(&newPixelFormat, sizeof(newPixelFormat));
	if (bytesRead != sizeof(newPixelFormat))
	{
		ioError(LOAD_PBF_ERROR(fileName, "Can't read enough bytes"));
		return false;
	}

	if (newPixelFormat.isValid() == false)
	{
		ioError(LOAD_PBF_ERROR(fileName, "Invalid pixel-format"));
		return false;
	}

	resize(newPixelFormat, header.width, header.height, header.depth, header.bytesPerLine);
	

	if (progressCallback != NULL)
	{
		const int lineCount = height * depth;
		const int linesPerRead = lineCount / 10;
		const float ooLineCount = 1.0f / static_cast<float>(lineCount);
		for (int l = 0; l < lineCount; l += linesPerRead)
		{
			if (progressCallback(l * ooLineCount) == false) return false;

			bytesRead = fileBuffer.readFromCurrentPosition(offsetPointer(getBufferPointer(), l*bytesPerLine), linesPerRead*bytesPerLine);
			if (bytesRead != linesPerRead*bytesPerLine)
			{
				ioError(LOAD_PBF_ERROR(fileName, "Can't read enough bytes"));
				return false;
			}
		}
		const int modLines = lineCount % 10;
		if (modLines > 0)
		{
			bytesRead = fileBuffer.readFromCurrentPosition(offsetPointer(getBufferPointer(), linesPerRead*10*bytesPerLine), modLines*bytesPerLine);
			if (bytesRead != modLines*bytesPerLine)
			{
				ioError(LOAD_PBF_ERROR(fileName, "Can't read enough bytes"));
				return false;
			}
		}

		if (progressCallback(1.0f) == false) return false;
	}
	else
	{
		const int totalBytes = bytesPerLine * height * depth;
		bytesRead = fileBuffer.readFromCurrentPosition(getBufferPointer(), totalBytes);
		if (bytesRead != totalBytes)
		{
			ioError(LOAD_PBF_ERROR(fileName, "Can't read enough bytes"));
			return false;
		}
	}

	return true;
}



bool PixelBuffer::saveAsPBF(const String& fileName) const
{
	String usedFileName = fileName;
	usedFileName.ensureEndsCaseInsensitiveWith(".pbf");

	if (width > USHRT_MAX || height > USHRT_MAX || depth > USHRT_MAX || bytesPerLine > USHRT_MAX)
	{
		stateError(SAVE_PBF_ERROR(usedFileName, "Buffer too large for PBF-file"));
		return false;
	}

	LocalFile::removeIfExists(usedFileName);
	BinaryFileBuffer fileBuffer(usedFileName, false, true);
	if (fileBuffer.isOpen() == false)
	{
		ioError(CANT_OPEN_FILE(fileName));
		return false;
	}

	BPFHeader header;
	header.id = BPFHeader::getID();
	header.width = static_cast<uint16>(width);
	header.height = static_cast<uint16>(height);
	header.depth = static_cast<uint16>(depth);
	header.bytesPerLine = static_cast<uint16>(bytesPerLine);

	int bytesWritten = fileBuffer.writeAtCurrentPosition(&header, sizeof(header));
	if (bytesWritten != sizeof(header))
	{
		ioError(SAVE_PBF_ERROR(fileName, "Can't write enough bytes"));
		return false;
	}

	bytesWritten = fileBuffer.writeAtCurrentPosition(&pixelFormat, sizeof(pixelFormat));
	if (bytesWritten != sizeof(pixelFormat))
	{
		ioError(SAVE_PBF_ERROR(fileName, "Can't write enough bytes"));
		return false;
	}


	if (progressCallback != NULL)
	{
		const int lineCount = height * depth;
		const int linesPerWrite = lineCount / 10;
		const float ooLineCount1 = 1.0f / static_cast<float>(lineCount-1);
		for (int l = 0; l < lineCount; l += linesPerWrite)
		{
			if (progressCallback(l * ooLineCount1) == false) return false;

			bytesWritten = fileBuffer.writeAtCurrentPosition(offsetPointer(getBufferPointer(), l*bytesPerLine), linesPerWrite*bytesPerLine);
			if (bytesWritten != linesPerWrite*bytesPerLine)
			{
				ioError(SAVE_PBF_ERROR(fileName, "Can't write enough bytes"));
				return false;
			}
		}
		const int modLines = lineCount % 10;
		if (modLines > 0)
		{
			bytesWritten = fileBuffer.writeAtCurrentPosition(offsetPointer(getBufferPointer(), linesPerWrite*10*bytesPerLine), modLines*bytesPerLine);
			if (bytesWritten != modLines*bytesPerLine)
			{
				ioError(SAVE_PBF_ERROR(fileName, "Can't write enough bytes"));
				return false;
			}
		}

		if (progressCallback(1.0f) == false) return false;
	}
	else
	{
		const int totalBytes = bytesPerLine * height * depth;
		bytesWritten = fileBuffer.writeAtCurrentPosition(getBufferPointer(), totalBytes);
		if (bytesWritten != totalBytes)
		{
			ioError(SAVE_PBF_ERROR(fileName, "Can't write enough bytes"));
			return false;
		}
	}

	return true;
}



const char BTHeader::ID[] = "binterr1.3";



bool PixelBuffer::loadFromBT(const String& fileName, BTHeader& header)
{
	BinaryFileBuffer fileBuffer(fileName, true, false);
	if (fileBuffer.isOpen() == false)
	{
		ioError(CANT_OPEN_FILE(fileName));
		return false;
	}

	int bytesRead = fileBuffer.readFromCurrentPosition(&header, sizeof(header));
	if (bytesRead != sizeof(header))
	{
		ioError(LOAD_BT_ERROR(fileName, "Can't read enough bytes"));
		return false;
	}

	String id(header.id, sizeof(header.id));
	id.setLength(id.getLength()-1);
	String referenceID = BTHeader::ID;
	referenceID.setLength(referenceID.getLength()-1);
	if (id != referenceID)
	{
		notImplementedError(LOAD_BT_ERROR(fileName, "Invalid file-type or version"));
		return false;
	}

	if (header.scale == 0.0f) header.scale = 1.0f;

	PixelFormat newPixelFormat;
	if (header.dataSize == 2)
	{
		newPixelFormat = "a16";
	}
	else if (header.dataSize == 4)
	{
		newPixelFormat = "a32";
		if (header.floatingPoint)
		{
			newPixelFormat.setFloatingPoint(true);
		}
	}
	else
	{
		ioError(LOAD_BT_ERROR(fileName, "Invalid data-size (" + String::createFrom(header.dataSize) + ") in header"));
		return false;
	}

	if (newPixelFormat.isValid() == false)
	{
		ioError(LOAD_BT_ERROR(fileName, "Invalid pixel-format"));
		return false;
	}

	resize(newPixelFormat, header.columns, header.rows);
	

	if (progressCallback != NULL)
	{
		const int lineCount = height * depth;
		const int linesPerRead = lineCount / 10;
		const float ooLineCount = 1.0f / static_cast<float>(lineCount);
		for (int l = 0; l < lineCount; l += linesPerRead)
		{
			if (progressCallback(l * ooLineCount) == false) return false;

			bytesRead = fileBuffer.readFromCurrentPosition(offsetPointer(getBufferPointer(), l*bytesPerLine), linesPerRead*bytesPerLine);
			if (bytesRead != linesPerRead*bytesPerLine)
			{
				ioError(LOAD_BT_ERROR(fileName, "Can't read enough bytes"));
				return false;
			}
		}
		const int modLines = lineCount % 10;
		if (modLines > 0)
		{
			bytesRead = fileBuffer.readFromCurrentPosition(offsetPointer(getBufferPointer(), linesPerRead*10*bytesPerLine), modLines*bytesPerLine);
			if (bytesRead != modLines*bytesPerLine)
			{
				ioError(SAVE_PBF_ERROR(fileName, "Can't read enough bytes"));
				return false;
			}
		}

		if (progressCallback(1.0f) == false) return false;
	}
	else
	{
		const int totalBytes = bytesPerLine * height * depth;
		bytesRead = fileBuffer.readFromCurrentPosition(getBufferPointer(), totalBytes);
		if (bytesRead != totalBytes)
		{
			ioError(LOAD_PBF_ERROR(fileName, "Can't read enough bytes"));
			return false;
		}
	}

	return true;
}



bool PixelBuffer::saveAsBT(const String& fileName) const
{
	LocalFile::removeIfExists(fileName);
	BinaryFileBuffer fileBuffer(fileName, false, true);
	if (fileBuffer.isOpen() == false)
	{
		ioError(CANT_OPEN_FILE(fileName));
		return false;
	}

	BTHeader header;
	memset(&header, 0, sizeof(header));
	memCopy(header.id, BTHeader::ID, sizeof(header.id));
	header.columns = width;
	header.rows = height;
	header.dataSize = pixelFormat.byteSize();
	header.floatingPoint = pixelFormat.isFloatingPoint() == true ? 1 : 0;
	header.horizontalUnits = 1; // 0: Degrees, 1: Meters, 2: Feet (international foot = .3048 meters), 3: Feet (U.S. survey foot = 1200/3937 meters)
	header.utmZone = 0; // ?
	header.datum = -1; // -1 UNKNOWN_DATUM
	header.leftExtent = 0.0; // ?
	header.rightExtent = width; // ?
	header.bottomExtent = height; // ?
	header.topExtent = 0.0; // ?

	int bytesWritten = fileBuffer.writeAtCurrentPosition(&header, sizeof(header));
	if (bytesWritten != sizeof(header))
	{
		ioError(SAVE_BT_ERROR(fileName, "Can't write enough bytes"));
		return false;
	}

	if (progressCallback != NULL)
	{
		const int lineCount = height * depth;
		const int linesPerWrite = lineCount / 10;
		const float ooLineCount1 = 1.0f / static_cast<float>(lineCount-1);
		for (int l = 0; l < lineCount; l += linesPerWrite)
		{
			if (progressCallback(l * ooLineCount1) == false) return false;

			bytesWritten = fileBuffer.writeAtCurrentPosition(offsetPointer(getBufferPointer(), l*bytesPerLine), linesPerWrite*bytesPerLine);
			if (bytesWritten != linesPerWrite*bytesPerLine)
			{
				ioError(SAVE_BT_ERROR(fileName, "Can't write enough bytes"));
				return false;
			}
		}
		const int modLines = lineCount % 10;
		if (modLines > 0)
		{
			bytesWritten = fileBuffer.writeAtCurrentPosition(offsetPointer(getBufferPointer(), linesPerWrite*10*bytesPerLine), modLines*bytesPerLine);
			if (bytesWritten != modLines*bytesPerLine)
			{
				ioError(SAVE_BT_ERROR(fileName, "Can't write enough bytes"));
				return false;
			}
		}

		if (progressCallback(1.0f) == false) return false;
	}
	else
	{
		const int totalBytes = bytesPerLine * height * depth;
		bytesWritten = fileBuffer.writeAtCurrentPosition(getBufferPointer(), totalBytes);
		if (bytesWritten != totalBytes)
		{
			ioError(SAVE_BT_ERROR(fileName, "Can't write enough bytes"));
			return false;
		}
	}

	return true;
}



Pixel PixelBuffer::pixel(int x, int y, int z)
{
	return *PixelIterator(pixelFormat, getBufferPointer(), bytesPerLine*8 * (y + z*height) + x * pixelFormat.totalBits);
}



const Pixel PixelBuffer::pixel(int x, int y, int z) const
{
	return *ConstPixelIterator(pixelFormat, const_cast<void*>(getBufferPointer()), bytesPerLine*8 * (y + z*height) + x * pixelFormat.totalBits);
}



void PixelBuffer::dumpAsSourceCode(const String& name, OutputStream& outputStream) const
{
	outputStream << "byte " << name << "Data[] = {";

	const int byteCount = buffer.getSizeAsInt();
	const byte * byteBuffer = static_cast<const byte *>(buffer.getPointer());
	for (int i = 0; i < byteCount; ++i)
	{
		if (i % 16 == 0)
		{
			outputStream << newLine << String('\t');
		}
		outputStream << byteBuffer[i];
		if (i < byteCount-1)
		{
			outputStream << ", ";
		}
	}
	outputStream << "};" << newLine << newLine;

	outputStream << "const BaseLib::Graphics::PixelBuffer " << name << "(\"" << pixelFormat.operator String() << "\", " << width << ", " << height << ", " << depth << ", 0, false, " << name << "Data);" << newLine << newLine;
}



#ifdef BL_PLATFORM_WIN32

HBITMAP PixelBuffer::createWin32Bitmap() const
{
	if (pixelFormat.colorType == PixelFormat::COLOR_TYPE_RGB && (pixelFormat.totalBits == 32/* || pixelFormat.totalBits == 24*/))
	{
		const BITMAP bitmap = {
			0,
			width,
			height,
			bytesPerLine,
			1,
			pixelFormat.totalBits,
			const_cast<void*>(buffer.getPointer())
		};
		return CreateBitmapIndirect(&bitmap);
	}
	else
	{
		return NULL;
	}
}



HICON PixelBuffer::createWin32Icon(HINSTANCE hInstance) const
{
	if (width != GetSystemMetrics(SM_CXICON) || height != GetSystemMetrics(SM_CYICON))
	{
		/// Gr��e anpassen
		BL_ASSERT_NEVER_REACHED
		return 0;
	}

	return CreateIcon(hInstance, width, height, 1, 1, NULL, static_cast<const BYTE*>(buffer.getPointer()));
}



HCURSOR PixelBuffer::createWin32Cursor(HINSTANCE hInstance, int hotSpotX, int hotSpotY) const
{
	if (width != GetSystemMetrics(SM_CXCURSOR) || height != GetSystemMetrics(SM_CYCURSOR))
	{
		/// Gr��e anpassen
		BL_ASSERT_NEVER_REACHED
		return 0;
	}

	return CreateCursor(hInstance, hotSpotX, hotSpotY, width, height, NULL, static_cast<const BYTE*>(buffer.getPointer()));
}

#endif



} // namespace Graphics
} // namespace BaseLib
