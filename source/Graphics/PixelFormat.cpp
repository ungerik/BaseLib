/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Graphics/PixelFormat.h"
#include "BaseLib/Graphics/ByteColor.h"
#include "BaseLib/Graphics/IntColor.h"
#include "BaseLib/Graphics/FloatColor.h"
#include "BaseLib/Graphics/intern/Errors.h"



namespace BaseLib {
namespace Graphics {



using namespace BaseLib::ErrorHandling;



const int8 PixelFormat::COLOR_TYPE_INVALID = 0;
const int8 PixelFormat::COLOR_TYPE_RGB = 1;
const int8 PixelFormat::COLOR_TYPE_RGB_FLOAT = -1;
const int8 PixelFormat::COLOR_TYPE_CMYK = 2;
const int8 PixelFormat::COLOR_TYPE_CMYK_FLOAT = -2;
/*const int8 PixelFormat::COLOR_TYPE_ELEVATION = 3;
const int8 PixelFormat::COLOR_TYPE_ELEVATION_FLOAT = -3;*/
const PixelFormat PixelFormat::R8_G8_B8("R8_G8_B8");
const PixelFormat PixelFormat::B8_G8_R8("B8_G8_R8");
const PixelFormat PixelFormat::R8_G8_B8_A8("R8_G8_B8_A8");
const PixelFormat PixelFormat::B8_G8_R8_A8("B8_G8_R8_A8");



bool PixelFormat::isValid() const
{
	if (colorType == COLOR_TYPE_INVALID) return false;

	const bool floatingPoint = isFloatingPoint();
	const uint8 maxShift = (floatingPoint == true) ? 127 : 31;
	const uint8 maxBits = (floatingPoint == true) ? 32 : 16;

	if (colorType == COLOR_TYPE_RGB || colorType == COLOR_TYPE_RGB_FLOAT)
	{
		if (floatingPoint == true)
		{
			if ((redBits == 32 && greenBits == 32 && blueBits == 32 && alphaBits == 32) == false &&
				(redBits == 32 && greenBits == 32 && blueBits == 32 && alphaBits ==  0) == false &&
				(redBits ==  0 && greenBits ==  0 && blueBits ==  0 && alphaBits == 32) == false)
			{
				return false;
			}
		}
		
		return (hasColor() == true || hasAlpha() == true)
			&& (redShift <= maxShift && redBits <= maxBits)
			&& (greenShift <= maxShift && greenBits <= maxBits)
			&& (blueShift <= maxShift && blueBits <= maxBits)
			&& (alphaShift <= maxShift && alphaBits <= maxBits)
			&& (totalBits <= maxBits*4);
	}
	/*else if (colorType == COLOR_TYPE_ELEVATION || colorType == COLOR_TYPE_ELEVATION_FLOAT)
	{
		BL_ASSERT_NEVER_REACHED
		return false;
	}*/
	else
	{
		BL_ASSERT_NEVER_REACHED
		return false;
	}
}



int getComponentInt(const void* baseAddress, int bitOffset, int resultBits, int componentBits, int componentShift, bool floatingPoint)
{
	BL_ASSERT(bitOffset >= 0);
	BL_ASSERT(resultBits >= 0);
	BL_ASSERT(componentBits >= 0);
	BL_ASSERT(componentShift >= 0);
	const int offset = bitOffset + componentShift;
	if (floatingPoint == false)
	{
		int result = memoryAs<int>(baseAddress, offset >> 3);
		result >>= offset & 7;
		result &= bits(componentBits);
		if (resultBits != 0)
		{
			if (resultBits > componentBits)
			{
				result <<= resultBits - componentBits;
			}
			else
			{
				result >>= componentBits - resultBits;
			}
		}
		return result;
	}
	else
	{
		if (componentBits == 32)
		{
			BL_ASSERT((offset & 31) == 0);
			return round<int>(static_cast<const float*>(baseAddress)[offset >> 5] * bits(resultBits));
		}
		else
		{
			if (componentBits != 0)
			{
				argumentError(ILLEGAL_FLOATING_POINT_COMPONENT_SIZE(componentBits));
			}
			return 0;
		}
	}
}



int PixelFormat::getRedInt(const void* baseAddress, int bitOffset, int resultBits) const
{
	return getComponentInt(baseAddress, bitOffset, resultBits, redBits, redShift, isFloatingPoint());
}



int PixelFormat::getGreenInt(const void* baseAddress, int bitOffset, int resultBits) const
{
	return getComponentInt(baseAddress, bitOffset, resultBits, greenBits, greenShift, isFloatingPoint());
}



int PixelFormat::getBlueInt(const void* baseAddress, int bitOffset, int resultBits) const
{
	return getComponentInt(baseAddress, bitOffset, resultBits, blueBits, blueShift, isFloatingPoint());
}



int PixelFormat::getAlphaInt(const void* baseAddress, int bitOffset, int resultBits) const
{
	return getComponentInt(baseAddress, bitOffset, resultBits, alphaBits, alphaShift, isFloatingPoint());
}



inline float getComponentFloat(const void* baseAddress, int bitOffset, int componentBits, int componentShift, bool floatingPoint)
{
	BL_ASSERT(bitOffset >= 0);
	BL_ASSERT(componentBits >= 0);
	BL_ASSERT(componentShift >= 0);
	if (floatingPoint == false)
	{
		return getComponentInt(baseAddress, bitOffset, 0, componentBits, componentShift, floatingPoint) / static_cast<float>(bits(componentBits));
	}
	else
	{
		if (componentBits == 32)
		{
			BL_ASSERT((bitOffset & 31) == 0);
			BL_ASSERT((componentShift & 31) == 0);
			return static_cast<const float*>(baseAddress)[(bitOffset + componentShift) >> 5];
		}
		else
		{
			if (componentBits != 0)
			{
				argumentError(ILLEGAL_FLOATING_POINT_COMPONENT_SIZE(componentBits));
			}
			return 0;
		}
	}
}



float PixelFormat::getRedAsFloat(const void* baseAddress, int bitOffset) const
{
	return getComponentFloat(baseAddress, bitOffset, redBits, redShift, isFloatingPoint());
}



float PixelFormat::getGreenAsFloat(const void* baseAddress, int bitOffset) const
{
	return getComponentFloat(baseAddress, bitOffset, greenBits, greenShift, isFloatingPoint());
}



float PixelFormat::getBlueAsFloat(const void* baseAddress, int bitOffset) const
{
	return getComponentFloat(baseAddress, bitOffset, blueBits, blueShift, isFloatingPoint());
}



float PixelFormat::getAlphaAsFloat(const void* baseAddress, int bitOffset) const
{
	return getComponentFloat(baseAddress, bitOffset, alphaBits, alphaShift, isFloatingPoint());
}



inline void setComponentInt(int sourceComponent, void* baseAddress, int bitOffset, int sourceBits, int componentBits, int componentShift, bool floatingPoint)
{
	BL_ASSERT(sourceComponent >= 0);
	BL_ASSERT(bitOffset >= 0);
	BL_ASSERT(sourceBits >= 0);
	BL_ASSERT(componentBits >= 0);
	BL_ASSERT(componentShift >= 0);
	if (componentBits > 0)
	{
		if (sourceBits == 0) sourceBits = componentBits;
		const int offset = bitOffset + componentShift;
		if (floatingPoint == false)
		{
			const int shift = offset & 7;

			if (sourceBits > componentBits)
			{
				sourceComponent >>= sourceBits - componentBits;
				sourceComponent <<= shift;
			}
			else
			{
				sourceComponent <<= (componentBits - sourceBits) + shift;
			}

			int& result = memoryAs<int>(baseAddress, offset >> 3);

			result &= ~bits(componentBits) << shift;
			result |= sourceComponent;
		}
		else
		{
			if (componentBits == 32)
			{
				BL_ASSERT((offset & 31) == 0);
				static_cast<float*>(baseAddress)[offset >> 5] = sourceComponent / static_cast<float>(bits(sourceBits));
			}
			else if (componentBits != 0)
			{
				argumentError(ILLEGAL_FLOATING_POINT_COMPONENT_SIZE(componentBits));
			}
		}
	}
}



void PixelFormat::setRed(int red, void* baseAddress, int bitOffset, int sourceBits) const
{
	setComponentInt(red, baseAddress, bitOffset, sourceBits, redBits, redShift, isFloatingPoint());
}



void PixelFormat::setGreen(int green, void* baseAddress, int bitOffset, int sourceBits) const
{
	setComponentInt(green, baseAddress, bitOffset, sourceBits, greenBits, greenShift, isFloatingPoint());
}



void PixelFormat::setBlue(int blue, void* baseAddress, int bitOffset, int sourceBits) const
{
	setComponentInt(blue, baseAddress, bitOffset, sourceBits, blueBits, blueShift, isFloatingPoint());
}



void PixelFormat::setAlpha(int alpha, void* baseAddress, int bitOffset, int sourceBits) const
{
	setComponentInt(alpha, baseAddress, bitOffset, sourceBits, alphaBits, alphaShift, isFloatingPoint());
}



inline void setComponentFloat(float sourceComponent, void* baseAddress, int bitOffset, int componentBits, int componentShift, bool floatingPoint)
{
	BL_ASSERT(sourceComponent >= 0.0f);
	BL_ASSERT(bitOffset >= 0);
	BL_ASSERT(componentBits >= 0);
	BL_ASSERT(componentShift >= 0);
	if (componentBits > 0)
	{
		if (floatingPoint == false)
		{
			setComponentInt(round<int>(sourceComponent * bits(componentBits)), baseAddress, bitOffset, componentBits, componentBits, componentShift, floatingPoint);
		}
		else
		{
			if (componentBits == 32)
			{
				BL_ASSERT((bitOffset & 31) == 0);
				BL_ASSERT((componentShift & 31) == 0);
				static_cast<float*>(baseAddress)[(bitOffset + componentShift) >> 5] = sourceComponent;
			}
			else if (componentBits != 0)
			{
				argumentError(ILLEGAL_FLOATING_POINT_COMPONENT_SIZE(componentBits));
			}
		}
	}
}



void PixelFormat::setRed(float red, void* baseAddress, int bitOffset) const
{
	setComponentFloat(red, baseAddress, bitOffset, redBits, redShift, isFloatingPoint());
}



void PixelFormat::setGreen(float green, void* baseAddress, int bitOffset) const
{
	setComponentFloat(green, baseAddress, bitOffset, greenBits, greenShift, isFloatingPoint());
}



void PixelFormat::setBlue(float blue, void* baseAddress, int bitOffset) const
{
	setComponentFloat(blue, baseAddress, bitOffset, blueBits, blueShift, isFloatingPoint());
}



void PixelFormat::setAlpha(float alpha, void* baseAddress, int bitOffset) const
{
	setComponentFloat(alpha, baseAddress, bitOffset, alphaBits, alphaShift, isFloatingPoint());
}



PixelFormat& PixelFormat::operator =(const String& description)
{
	static const String numbers("0123456789");

	int rPos = description.findFirstCaseInsensitive('r');
	if (rPos != String::END)
	{
		++rPos;
		int rBitsLength = description.findFirstNotOf(numbers, rPos);
		rBitsLength = ( rBitsLength != String::END ? rBitsLength : description.getLength() ) - rPos;
		redBits = rBitsLength > 0 ? static_cast<uint8>(description.subString(rPos, rBitsLength).parseInt()) : 0; // can't use .parse<uint8>() because that's char
	}
	else
	{
		rPos = 0;
		redBits = 0;
	}

	int gPos = description.findFirstCaseInsensitive('g');
	if (gPos != String::END)
	{
		++gPos;
		int gBitsLength = description.findFirstNotOf(numbers, gPos);
		gBitsLength = ( gBitsLength != String::END ? gBitsLength : description.getLength() ) - gPos;
		greenBits = gBitsLength > 0 ? static_cast<uint8>(description.subString(gPos, gBitsLength).parseInt()) : 0;
	}
	else
	{
		gPos = 0;
		greenBits = 0;
	}

	int bPos = description.findFirstCaseInsensitive('b');
	if (bPos != String::END)
	{
		++bPos;
		int bBitsLength = description.findFirstNotOf(numbers, bPos);
		bBitsLength = ( bBitsLength != String::END ? bBitsLength : description.getLength() ) - bPos;
		blueBits = bBitsLength > 0 ? static_cast<uint8>(description.subString(bPos, bBitsLength).parseInt()) : 0;
	}
	else
	{
		bPos = 0;
		blueBits = 0;
	}

	int aPos = description.findFirstCaseInsensitive('a');
	if (aPos != String::END)
	{
		++aPos;
		int aBitsLength = description.findFirstNotOf(numbers, aPos);
		aBitsLength = ( aBitsLength != String::END ? aBitsLength : description.getLength() ) - aPos;
		alphaBits = aBitsLength > 0 ? static_cast<uint8>(description.subString(aPos, aBitsLength).parseInt()) : 0;
	}
	else
	{
		aPos = 0;
		alphaBits = 0;
	}

	int tPos = description.findFirstCaseInsensitive('t');
	if (tPos != String::END)
	{
		++tPos;
		int tBitsLength = description.findFirstNotOf(numbers, tPos);
		tBitsLength = ( tBitsLength != String::END ? tBitsLength : description.getLength() ) - tPos;
		totalBits = tBitsLength > 0 ? static_cast<uint8>(description.subString(tPos, tBitsLength).parseInt()) : 0;
	}
	else
	{
		totalBits = 0;
	}

	colorType = (description.findFirstCaseInsensitive('f') == String::END) ? COLOR_TYPE_RGB : COLOR_TYPE_RGB_FLOAT;
	component3Bits = 0;
	component3Shift = 0;

	redShift = 0;
	if (rPos > gPos) redShift += greenBits;
	if (rPos > bPos) redShift += blueBits;
	if (rPos > aPos) redShift += alphaBits;

	greenShift = 0;
	if (gPos > rPos) greenShift += redBits;
	if (gPos > bPos) greenShift += blueBits;
	if (gPos > aPos) greenShift += alphaBits;

	blueShift = 0;
	if (bPos > rPos) blueShift += redBits;
	if (bPos > gPos) blueShift += greenBits;
	if (bPos > aPos) blueShift += alphaBits;

	alphaShift = 0;
	if (aPos > rPos) alphaShift += redBits;
	if (aPos > gPos) alphaShift += greenBits;
	if (aPos > bPos) alphaShift += blueBits;

	if (totalBits == 0)
	{
		calculateTotalBits();
	}

	return *this;
}



PixelFormat::operator String() const
{
	if (isValid() == false) return "invalid";

	String result;

	if (colorType == COLOR_TYPE_RGB || colorType == COLOR_TYPE_RGB_FLOAT)
	{
		int redLength = 0;
		int greenLength = 0;
		int blueLength = 0;

		if (redBits > 0)
		{
			result = "r" + String::createFrom(redBits);
			redLength = result.getLength();
		}

		if (greenBits > 0)
		{
			String component = "g" + String::createFrom(greenBits);
			greenLength = component.getLength();
			int pos = (greenShift > redShift) ? redLength : 0;
			result.insert(component, pos);
		}

		if (blueBits > 0)
		{
			String component = "b" + String::createFrom(blueBits);
			blueLength = component.getLength();
			int pos = (blueShift > redShift) ? redLength : 0;
			if (blueShift > greenShift)
			{
				pos += greenLength;
			}
			result.insert(component, pos);
		}

		if (alphaBits > 0)
		{
			String component = "a" + String::createFrom(alphaBits);
			int pos = (alphaShift > redShift) ? redLength : 0;
			if (alphaShift > greenShift)
			{
				pos += greenLength;
			}
			if (alphaShift > blueShift)
			{
				pos += blueLength;
			}
			result.insert(component, pos);
		}
	}
	else
	{
		BL_ASSERT_NEVER_REACHED
		return "CMYK not implemented!";
	}

	if (isFloatingPoint() == true) result += 'f';

	return result;
}



bool PixelFormat::isJPEGCompatible() const
{
	if (colorType != COLOR_TYPE_RGB || isValid() == false) return false;

	return ((redBits == 8 && redShift == 0)
		&& (greenBits == 8 && greenShift == 8)
		&& (blueBits == 8 && blueShift == 16)
		&& (alphaBits == 0 && alphaShift == 0)
		) || ((redBits == 0 && redShift == 0)
		&& (greenBits == 0 && greenShift == 0)
		&& (blueBits == 0 && blueShift == 0)
		&& (alphaBits == 8 && alphaShift == 0));
}



bool PixelFormat::isPNGCompatible() const
{
	if (colorType != COLOR_TYPE_RGB || isValid() == false) return false;

	const bool color = hasColor();
	const bool alpha = hasAlpha();

	if (color == true)
	{
		if ((redBits == greenBits && greenBits == blueBits) == false) return false;
		if ((redShift == 0 && greenShift == redBits && blueShift == 2*redBits) == false) return false;
		if (alpha == true && (alphaBits != redBits || alphaShift != 3*redBits)) return false;
		if ((redBits == 1 || redBits == 2 || redBits == 4 || redBits == 8 || redBits == 16) == false) return false;
	}
	else
	{
		if (alpha == false) return false;
		if (alphaShift != 0) return false;
		if ((alphaBits == 1 || alphaBits == 2 || alphaBits == 4 || alphaBits == 8 || alphaBits == 16) == false) return false;
	}
	
	return true;
}



bool PixelFormat::isTGACompatible() const
{
	if (colorType != COLOR_TYPE_RGB || isValid() == false) return false;

	const bool color = hasColor();
	const bool alpha = hasAlpha();

	if (color == true)
	{
		if (((redBits == 8 && greenBits == 8 && blueBits == 8) || redBits == 5 && greenBits == 6 && blueBits == 5 && alpha == false) == false) return false;
		if ((redShift == 0 && greenShift == redBits && blueShift == redBits+blueBits) == false) return false;
		if (alpha == true && alphaBits != 8) return false;
	}
	else
	{
		if (alpha == false) return false;
		if (alphaShift != 0) return false;
		if (alphaBits != 8) return false;
	}
	
	return true;
}



bool PixelFormat::isBTCompatible() const
{
	if (isValid() == false) return false;
	if (hasColor() == true) return false;

	return (alphaBits == 16 && isFloatingPoint() == false) || (alphaBits == 32);
}



void PixelFormat::setColor(const ByteColor& color, void* baseAddress, int bitOffset) const
{
	setRed(color.r, baseAddress, bitOffset);
	setGreen(color.g, baseAddress, bitOffset);
	setBlue(color.b, baseAddress, bitOffset);
	setAlpha(color.a, baseAddress, bitOffset);
}



void PixelFormat::setColor(const IntColor& color, void* baseAddress, int bitOffset) const
{
	setRed(color.r, baseAddress, bitOffset);
	setGreen(color.g, baseAddress, bitOffset);
	setBlue(color.b, baseAddress, bitOffset);
	setAlpha(color.a, baseAddress, bitOffset);
}



void PixelFormat::setColor(const FloatColor& color, void* baseAddress, int bitOffset) const
{
	setRed(color.r, baseAddress, bitOffset);
	setGreen(color.g, baseAddress, bitOffset);
	setBlue(color.b, baseAddress, bitOffset);
	setAlpha(color.a, baseAddress, bitOffset);
}



} // namespace Graphics
} // namespace BaseLib
