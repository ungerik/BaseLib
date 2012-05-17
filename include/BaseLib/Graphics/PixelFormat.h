/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Graphics_PixelFormat_h
#define BaseLib_Graphics_PixelFormat_h



#include "BaseLib/Types.h"
#include "BaseLib/Strings/String.h"



namespace BaseLib {
namespace Graphics {



using BaseLib::Strings::String;
using namespace BaseLib::Utilities;



struct ByteColor;
struct FloatColor;
struct IntColor;



#pragma pack(1)



struct BL_EXPORT PixelFormat {

	static const int8 COLOR_TYPE_INVALID;
	static const int8 COLOR_TYPE_RGB;
	static const int8 COLOR_TYPE_RGB_FLOAT;
	static const int8 COLOR_TYPE_CMYK;
	static const int8 COLOR_TYPE_CMYK_FLOAT;
	static const int8 COLOR_TYPE_YUV;
	static const int8 COLOR_TYPE_YUV_FLOAT;
	//static const int8 COLOR_TYPE_ELEVATION;
	//static const int8 COLOR_TYPE_ELEVATION_FLOAT;

	static const PixelFormat R8_G8_B8;
	static const PixelFormat B8_G8_R8;
	static const PixelFormat R8_G8_B8_A8;
	static const PixelFormat B8_G8_R8_A8;

	int8 colorType;
	uint8 totalBits;

	union {
		struct {
			uint8 component0Bits;
			uint8 component0Shift;
			uint8 component1Bits;
			uint8 component1Shift;
			uint8 component2Bits;
			uint8 component2Shift;
			uint8 component3Bits;
			uint8 component3Shift;
		};
		struct {
			uint8 redBits;
			uint8 redShift;
			uint8 greenBits;
			uint8 greenShift;
			uint8 blueBits;
			uint8 blueShift;
		};
		struct {
			uint8 cyanBits;
			uint8 cyanShift;
			uint8 magentaBits;
			uint8 magentaShift;
			uint8 yellowBits;
			uint8 yellowShift;
			uint8 blackBits;
			uint8 blackShift;
		};
		struct {
			uint8 yLumaBits;
			uint8 yLumaShift;
			uint8 uChromaBits;
			uint8 uChromaShift;
			uint8 vChromaBits;
			uint8 vChromaShift;
		};
	};

	union {
		struct {
			uint8 component4Bits;
			uint8 component4Shift;
		};
		struct {
			uint8 alphaBits;
			uint8 alphaShift;
		};
		/*struct {
			uint8 elevationBits;
		};*/
	};

	PixelFormat()
	  : colorType(COLOR_TYPE_INVALID)
	  , totalBits(0)
	  , component0Bits(0)
	  , component0Shift(0)
	  , component1Bits(0)
	  , component1Shift(0)
	  , component2Bits(0)
	  , component2Shift(0)
	  , component3Bits(0)
	  , component3Shift(0)
	  , component4Bits(0)
	  , component4Shift(0)
	{
	}

	PixelFormat(uint8 rBits, uint8 gBits, uint8 bBits, uint8 aBits, uint8 rShift, uint8 gShift, uint8 bShift, uint8 aShift, uint8 bitsPerPixel = 0, bool floating = false)
	  : colorType(floating == true ? COLOR_TYPE_RGB_FLOAT : COLOR_TYPE_RGB)
	  , totalBits(bitsPerPixel)
	  , redBits(rBits)
	  , redShift(rShift)
	  , greenBits(gBits)
	  , greenShift(gShift)
	  , blueBits(bBits)
	  , blueShift(bShift)
	  , component3Bits(0)
	  , component3Shift(0)
	  , alphaBits(aBits)
	  , alphaShift(aShift)
	{
		calculateTotalBits();
		BL_ASSERT(isValid() == true);
	}

	PixelFormat(uint8 cBits, uint8 mBits, uint8 yBits, uint8 kBits, uint8 aBits, uint8 cShift, uint8 mShift, uint8 yShift, uint8 kShift, uint8 aShift, uint8 bitsPerPixel = 0, bool floating = false)
	  : colorType(floating == true ? COLOR_TYPE_CMYK_FLOAT : COLOR_TYPE_CMYK)
	  , totalBits(bitsPerPixel)
	  , cyanBits(cBits)
	  , cyanShift(cShift)
	  , magentaBits(mBits)
	  , magentaShift(mShift)
	  , yellowBits(yBits)
	  , yellowShift(yShift)
	  , blackBits(kBits)
	  , blackShift(kShift)
	  , alphaBits(aBits)
	  , alphaShift(aShift)
	{
		calculateTotalBits();
		BL_ASSERT(isValid() == true);
	}

	/*
	PixelFormat(uint8 elevBits, uint8 bitsPerPixel = 0, bool floating = false)
	  : colorType(floating == true ? COLOR_TYPE_ELEVATION_FLOAT : COLOR_TYPE_ELEVATION)
	  , totalBits(bitsPerPixel)
	  , component0Bits(0)
	  , component0Shift(0)
	  , component1Bits(0)
	  , component1Shift(0)
	  , component2Bits(0)
	  , component2Shift(0)
	  , component3Bits(0)
	  , component3Shift(0)
	  , elevationBits(elevBits)
	  , component4Shift(0)
	{
		calculateTotalBits();
		BL_ASSERT(isValid() == true);
	}
	*/

	PixelFormat(const String& description)
	{
		operator =(description);
	}

	PixelFormat& operator =(const String& description);

	inline PixelFormat(const char * description)
	{
		operator =(String(description));
	}

	inline PixelFormat& operator =(const char * description)
	{
		operator =(String(description));
		return *this;
	}

	operator String() const;

	inline bool operator ==(const PixelFormat& rhs) const
	{
		return memoryAs<int64>(&colorType, 0) == memoryAs<int64>(&rhs.colorType, 0)
			&& memoryAs<int32>(&component3Bits, 0) == memoryAs<int32>(&rhs.component3Bits, 0);
		/*
		return colorType == rhs.colorType
			&& component0Bits == rhs.component0Bits
			&& totalBits == rhs.totalBits
			&& component0Shift == rhs.component0Shift
			&& component1Bits == rhs.component1Bits
			&& component1Shift == rhs.component1Shift
			&& component2Bits == rhs.component2Bits
			&& component2Shift == rhs.component2Shift
			&& component3Bits == rhs.component3Bits
			&& component3Shift == rhs.component3Shift
			&& component4Bits == rhs.component4Bits
			&& component4Shift == rhs.component4Shift;
		*/
	}

	inline bool operator !=(const PixelFormat& rhs) const
	{
		return !operator ==(rhs);
	}

	inline bool hasColor() const
	{
		return (component0Bits | component1Bits | component2Bits | component3Bits) != 0;
	}

	inline bool hasAlpha() const
	{
		return alphaBits != 0;
	}

	inline bool isFloatingPoint() const
	{
		return colorType < 0;
	}

	inline void setFloatingPoint(bool floatingPoint)
	{
		if (isFloatingPoint() != floatingPoint)
		{
			colorType *= -1;
		}
	}

	inline int getComponentCount() const
	{
		int componentCount = 0;
		if (component0Bits != 0) ++componentCount;
		if (component1Bits != 0) ++componentCount;
		if (component2Bits != 0) ++componentCount;
		if (component3Bits != 0) ++componentCount;
		if (component4Bits != 0) ++componentCount;
		return componentCount;
	}

	bool isValid() const;


	inline uint8 calculateTotalBits()
	{
		uint8 neededBitsPerPixel = component0Bits + component0Shift;
		uint8 bits = component1Bits + component1Shift;
		if (bits > neededBitsPerPixel) neededBitsPerPixel = bits;
		bits = component2Bits + component2Shift;
		if (bits > neededBitsPerPixel) neededBitsPerPixel = bits;
		bits = component3Bits + component3Shift;
		if (bits > neededBitsPerPixel) neededBitsPerPixel = bits;
		bits = component4Bits + component4Shift;
		if (bits > neededBitsPerPixel) neededBitsPerPixel = bits;
		
		if (totalBits < neededBitsPerPixel) totalBits = neededBitsPerPixel;

		return neededBitsPerPixel;
	}

	inline int byteSize() const
	{
		return (totalBits + 7) >> 3;
	}

	inline bool isByteAligned() const
	{
		return (totalBits & 7) == 0;
	}

	//inline ByteColor getColorByte(const void* baseAddress, int bitOffset = 0) const
	//{
	//	return ByteColor(getRedAsByte(baseAddress, bitOffset), getGreenAsByte(baseAddress, bitOffset), getBlueAsByte(baseAddress, bitOffset), getAlphaAsByte(baseAddress, bitOffset));
	//}

	//inline IntColor getColorInt(const void* baseAddress, int bitOffset = 0) const
	//{
	//	return IntColor(getRedInt(baseAddress, bitOffset), getGreenInt(baseAddress, bitOffset), getBlueInt(baseAddress, bitOffset), getAlphaInt(baseAddress, bitOffset));
	//}

	//inline FloatColor getColorFloat(const void* baseAddress, int bitOffset = 0) const
	//{
	//	return FloatColor(getRedAsFloat(baseAddress, bitOffset), getGreenAsFloat(baseAddress, bitOffset), getBlueAsFloat(baseAddress, bitOffset), getAlphaAsFloat(baseAddress, bitOffset));
	//}

	inline uint8 getRedAsByte(const void* baseAddress, int bitOffset = 0) const
	{
		return static_cast<uint8>(getRedInt(baseAddress, bitOffset, 8));
	}

	inline uint8 getGreenAsByte(const void* baseAddress, int bitOffset = 0) const
	{
		return static_cast<uint8>(getGreenInt(baseAddress, bitOffset, 8));
	}

	inline uint8 getBlueAsByte(const void* baseAddress, int bitOffset = 0) const
	{
		return static_cast<uint8>(getBlueInt(baseAddress, bitOffset, 8));
	}

	inline uint8 getAlphaAsByte(const void* baseAddress, int bitOffset = 0) const
	{
		return static_cast<uint8>(getAlphaInt(baseAddress, bitOffset, 8));
	}

	int getRedInt(const void* baseAddress, int bitOffset = 0, int resultBits = 0) const;
	int getGreenInt(const void* baseAddress, int bitOffset = 0, int resultBits = 0) const;
	int getBlueInt(const void* baseAddress, int bitOffset = 0, int resultBits = 0) const;
	int getAlphaInt(const void* baseAddress, int bitOffset = 0, int resultBits = 0) const;

	float getRedAsFloat(const void* baseAddress, int bitOffset = 0) const;
	float getGreenAsFloat(const void* baseAddress, int bitOffset = 0) const;
	float getBlueAsFloat(const void* baseAddress, int bitOffset = 0) const;
	float getAlphaAsFloat(const void* baseAddress, int bitOffset = 0) const;

	inline void setColor(float red, float green, float blue, float alpha, void* baseAddress, int bitOffset = 0) const
	{
		setRed(red, baseAddress, bitOffset);
		setGreen(green, baseAddress, bitOffset);
		setBlue(blue, baseAddress, bitOffset);
		setAlpha(alpha, baseAddress, bitOffset);
	}

	inline void setColor(uint8 red, uint8 green, uint8 blue, uint8 alpha, void* baseAddress, int bitOffset = 0) const
	{
		setRed(red, baseAddress, bitOffset);
		setGreen(green, baseAddress, bitOffset);
		setBlue(blue, baseAddress, bitOffset);
		setAlpha(alpha, baseAddress, bitOffset);
	}

	inline void setColor(int red, int green, int blue, int alpha, void* baseAddress, int bitOffset = 0) const
	{
		setRed(red, baseAddress, bitOffset);
		setGreen(green, baseAddress, bitOffset);
		setBlue(blue, baseAddress, bitOffset);
		setAlpha(alpha, baseAddress, bitOffset);
	}

	void setColor(const ByteColor& color, void* baseAddress, int bitOffset = 0) const;
	void setColor(const IntColor& color, void* baseAddress, int bitOffset = 0) const;
	void setColor(const FloatColor& color, void* baseAddress, int bitOffset = 0) const;

	inline void setColor(const uint8 newComponents[4], void* baseAddress, int bitOffset = 0) const
	{
		setRed(newComponents[0], baseAddress, bitOffset);
		setGreen(newComponents[1], baseAddress, bitOffset);
		setBlue(newComponents[2], baseAddress, bitOffset);
		setAlpha(newComponents[3], baseAddress, bitOffset);
	}

	inline void setColor(const int newComponents[4], void* baseAddress, int bitOffset = 0) const
	{
		setRed(newComponents[0], baseAddress, bitOffset);
		setGreen(newComponents[1], baseAddress, bitOffset);
		setBlue(newComponents[2], baseAddress, bitOffset);
		setAlpha(newComponents[3], baseAddress, bitOffset);
	}

	inline void setColor(const float newComponents[4], void* baseAddress, int bitOffset = 0) const
	{
		setRed(newComponents[0], baseAddress, bitOffset);
		setGreen(newComponents[1], baseAddress, bitOffset);
		setBlue(newComponents[2], baseAddress, bitOffset);
		setAlpha(newComponents[3], baseAddress, bitOffset);
	}

	inline void setRed(uint8 red, void* baseAddress, int bitOffset = 0, int sourceBits = 0) const
	{
		setRed(static_cast<int>(red), baseAddress, bitOffset, sourceBits);
	}

	inline void setGreen(uint8 green, void* baseAddress, int bitOffset = 0, int sourceBits = 0) const
	{
		setRed(static_cast<int>(green), baseAddress, bitOffset, sourceBits);
	}

	inline void setBlue(uint8 blue, void* baseAddress, int bitOffset = 0, int sourceBits = 0) const
	{
		setRed(static_cast<int>(blue), baseAddress, bitOffset, sourceBits);
	}

	inline void setAlpha(uint8 alpha, void* baseAddress, int bitOffset = 0, int sourceBits = 0) const
	{
		setRed(static_cast<int>(alpha), baseAddress, bitOffset, sourceBits);
	}

	void setRed(int red, void* baseAddress, int bitOffset = 0, int sourceBits = 0) const;
	void setGreen(int green, void* baseAddress, int bitOffset = 0, int sourceBits = 0) const;
	void setBlue(int blue, void* baseAddress, int bitOffset = 0, int sourceBits = 0) const;
	void setAlpha(int alpha, void* baseAddress, int bitOffset = 0, int sourceBits = 0) const;

	void setRed(float red, void* baseAddress, int bitOffset = 0) const;
	void setGreen(float green, void* baseAddress, int bitOffset = 0) const;
	void setBlue(float blue, void* baseAddress, int bitOffset = 0) const;
	void setAlpha(float alpha, void* baseAddress, int bitOffset = 0) const;

	bool isJPEGCompatible() const;
	bool isPNGCompatible() const;
	bool isTGACompatible() const;
	bool isBTCompatible() const;

};


#pragma pack()



} // namespace Graphics
} // namespace BaseLib



#endif // #ifndef BaseLib_Graphics_PixelFormat_h
