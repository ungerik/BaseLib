/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Graphics_Pixel_h
#define BaseLib_Graphics_Pixel_h



#include "BaseLib/Graphics/PixelFormat.h"



namespace BaseLib {
namespace Graphics {



template<typename T>
class BL_EXPORT PixelIteratorTemplate {
public:

	PixelIteratorTemplate<T>(const PixelFormat& newPixelFormat, void* newBaseAddress, int newBitOffset)
	  : pixel(newPixelFormat, newBaseAddress, newBitOffset)
	{
	}

	PixelIteratorTemplate<T>(const PixelIteratorTemplate<T>& other)
	  : pixel(other->getPixelFormat(), other->baseAddress, other->bitOffset)
	{
	}

	inline PixelIteratorTemplate<T>& operator=(const PixelIteratorTemplate<T>& rhs)
	{
		pixel.pixelFormat = rhs->pixelFormat;
		pixel.baseAddress = rhs->baseAddress;
		pixel.bitOffset = rhs->bitOffset;
		return *this;
	}

	inline PixelIteratorTemplate<T>& operator++()
	{
		pixel.bitOffset += pixel.getPixelFormat().totalBits;
		return *this;
	}

	inline PixelIteratorTemplate<T> operator++(int)
	{
		PixelIterator temp = *this;
		pixel.bitOffset += pixel.getPixelFormat().totalBits;
		return temp;
	}

	inline PixelIteratorTemplate<T>& operator--()
	{
		pixel.bitOffset -= pixel.getPixelFormat().totalBits;
		return *this;
	}

	inline PixelIteratorTemplate<T> operator--(int)
	{
		PixelIterator temp = *this;
		pixel.bitOffset -= pixel.getPixelFormat().totalBits;
		return temp;
	}

	inline T* operator->()
	{
		return &pixel;
	}

	inline T& operator*()
	{
		return pixel;
	}

	/*
	inline T* operator->() const
	{
		return &pixel;
	}

	inline T& operator*() const
	{
		return pixel;
	}

	T& get() { return pixel; }
	*/

protected:
	T pixel;
};



class BL_EXPORT Pixel;
typedef PixelIteratorTemplate<Pixel> PixelIterator;
typedef PixelIteratorTemplate<const Pixel> ConstPixelIterator;



class BL_EXPORT Pixel {
	friend PixelIterator;
	friend ConstPixelIterator;
public:

	Pixel(const PixelFormat& newPixelFormat, void* newBaseAddress = NULL, int newBitOffset = 0)
		: pixelFormat(&newPixelFormat)
		, baseAddress(newBaseAddress)
		, bitOffset(newBitOffset)
		, dataOwner(newBaseAddress == NULL)
	{
		if (dataOwner == true)
		{
			BL_ASSERT(bitOffset == 0);
			baseAddress = malloc(pixelFormat->byteSize());
		}
	}

	~Pixel()
	{
		if (dataOwner == true)
		{
			free(baseAddress);
		}
	}

	Pixel(const Pixel& otherPixel)
	{
		operator =(otherPixel);
	}

	inline Pixel& operator =(const Pixel& rhs)
	{
		BL_ASSERT(&rhs != this);
		pixelFormat = rhs.pixelFormat;
		baseAddress = rhs.baseAddress;
		bitOffset = rhs.bitOffset;
		dataOwner = rhs.dataOwner;
				
		return *this;
	}

	inline Pixel& operator =(const ByteColor& rhs)
	{
		pixelFormat->setColor(rhs, baseAddress, bitOffset);
		return *this;
	}

	inline Pixel& operator =(const IntColor& rhs)
	{
		pixelFormat->setColor(rhs, baseAddress, bitOffset);
		return *this;
	}

	inline Pixel& operator =(const FloatColor& rhs)
	{
		pixelFormat->setColor(rhs, baseAddress, bitOffset);
		return *this;
	}

	inline const PixelFormat& getPixelFormat() const { return *pixelFormat; }


	//inline ByteColor getByteColor() const
	//{
	//	return pixelFormat->getByteColor(baseAddress, bitOffset);
	//}

	//inline IntColor getIntColor() const
	//{
	//	return pixelFormat->getIntColor(baseAddress, bitOffset);
	//}

	//inline FloatColor getFloatColor() const
	//{
	//	return pixelFormat->getFloatColor(baseAddress, bitOffset);
	//}

	inline uint8 getRedAsByte() const
	{
		return pixelFormat->getRedAsByte(baseAddress, bitOffset);
	}

	inline uint8 getGreenAsByte() const
	{
		return pixelFormat->getGreenAsByte(baseAddress, bitOffset);
	}

	inline uint8 getBlueAsByte() const
	{
		return pixelFormat->getBlueAsByte(baseAddress, bitOffset);
	}

	inline uint8 getAlphaAsByte() const
	{
		return pixelFormat->getAlphaAsByte(baseAddress, bitOffset);
	}

	inline int getRedInt(int resultBits = 0) const
	{
		return pixelFormat->getRedInt(baseAddress, bitOffset, resultBits);
	}

	inline int getGreenInt(int resultBits = 0) const
	{
		return pixelFormat->getGreenInt(baseAddress, bitOffset, resultBits);
	}

	inline int getBlueInt(int resultBits = 0) const
	{
		return pixelFormat->getBlueInt(baseAddress, bitOffset, resultBits);
	}

	inline int getAlphaInt(int resultBits = 0) const
	{
		return pixelFormat->getAlphaInt(baseAddress, bitOffset, resultBits);
	}

	inline float getRedAsFloat() const
	{
		return pixelFormat->getRedAsFloat(baseAddress, bitOffset);
	}

	inline float getGreenAsFloat() const
	{
		return pixelFormat->getGreenAsFloat(baseAddress, bitOffset);
	}

	inline float getBlueAsFloat() const
	{
		return pixelFormat->getBlueAsFloat(baseAddress, bitOffset);
	}

	inline float getAlphaAsFloat() const
	{
		return pixelFormat->getAlphaAsFloat(baseAddress, bitOffset);
	}

	inline void setColor(float red, float green, float blue, float alpha = 1.0f)
	{
		pixelFormat->setColor(red, green, blue, alpha, baseAddress, bitOffset);
	}

	inline void setColor(int red, int green, int blue, int alpha = INT_MAX)
	{
		pixelFormat->setColor(red, green, blue, alpha, baseAddress, bitOffset);
	}

	inline void setColor(uint8 red, uint8 green, uint8 blue, uint8 alpha = 255)
	{
		pixelFormat->setColor(red, green, blue, alpha, baseAddress, bitOffset);
	}

	inline void setColor(const Pixel& otherPixel)
	{
		/*
		BL_ASSERT(&otherPixel != this);
		if (pixelFormat->floatingPoint == false)
		{
			setColor(	otherPixel.getRedInt(pixelFormat->redBits),
						otherPixel.getGreenInt(pixelFormat->greenBits),
						otherPixel.getBlueInt(pixelFormat->blueBits),
						otherPixel.getAlphaInt(pixelFormat->alphaBits));
		}
		else
		{
			setColor(	otherPixel.getRedAsFloat(),
						otherPixel.getGreenAsFloat(),
						otherPixel.getBlueAsFloat(),
						otherPixel.getAlphaAsFloat());
		}
		*/
	}

	inline void setColor(const ByteColor& newColor)
	{
		pixelFormat->setColor(newColor, baseAddress, bitOffset);
	}

	inline void setColor(const IntColor& newColor)
	{
		pixelFormat->setColor(newColor, baseAddress, bitOffset);
	}

	inline void setColor(const FloatColor& newColor)
	{
		pixelFormat->setColor(newColor, baseAddress, bitOffset);
	}

	inline void setColor(const uint8 newComponents[4])
	{
		pixelFormat->setColor(newComponents, baseAddress, bitOffset);
	}

	inline void setColor(const int newComponents[4])
	{
		pixelFormat->setColor(newComponents, baseAddress, bitOffset);
	}

	inline void setColor(const float newComponents[4])
	{
		pixelFormat->setColor(newComponents, baseAddress, bitOffset);
	}

	inline void setRed(int red, int sourceBits = 0)
	{
		pixelFormat->setRed(red, baseAddress, bitOffset, sourceBits);
	}

	inline void setGreen(int red, int sourceBits = 0)
	{
		pixelFormat->setGreen(red, baseAddress, bitOffset, sourceBits);
	}

	inline void setBlue(int red, int sourceBits = 0)
	{
		pixelFormat->setBlue(red, baseAddress, bitOffset, sourceBits);
	}

	inline void setAlpha(int red, int sourceBits = 0)
	{
		pixelFormat->setAlpha(red, baseAddress, bitOffset, sourceBits);
	}

	inline void setRed(float red)
	{
		pixelFormat->setRed(red, baseAddress, bitOffset);
	}

	inline void setGreen(float red)
	{
		pixelFormat->setGreen(red, baseAddress, bitOffset);
	}

	inline void setBlue(float red)
	{
		pixelFormat->setBlue(red, baseAddress, bitOffset);
	}

	inline void setAlpha(float red)
	{
		pixelFormat->setAlpha(red, baseAddress, bitOffset);
	}

	inline void swapRedAndBlueInt()
	{
		int red = getRedInt();
		int blue = getBlueInt();
		setRed(blue);
		setBlue(red);
	}

	inline void swapRedAndBlueFloat()
	{
		float red = getRedAsFloat();
		float blue = getBlueAsFloat();
		setRed(blue);
		setBlue(red);
	}

	inline void* getBaseAddress() { return baseAddress; }
	inline const void* getBaseAddress() const { return baseAddress; }
	inline int getBitOffset() const { return bitOffset; }
	inline void* getAlignedPointer() { return &reinterpret_cast<int8 *>(baseAddress)[bitOffset >> 3]; }
	inline const void* getAlignedPointer() const { return &reinterpret_cast<const int8 *>(baseAddress)[bitOffset >> 3]; }

protected:

	const PixelFormat* pixelFormat;
	void* baseAddress;
	mutable int bitOffset;
	bool dataOwner;

};



} // namespace Graphics
} // namespace BaseLib



#endif // #ifndef BaseLib_Graphics_Pixel_h