/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Graphics/FloatColor.h"
#include "BaseLib/Graphics/ByteColor.h"
#include "BaseLib/Strings/StringTokenizer.h"
#include "BaseLib/Graphics/intern/Errors.h"



namespace BaseLib {
namespace Graphics {



using BaseLib::Strings::StringTokenizer;
using namespace BaseLib::ErrorHandling;



const PixelFormat FloatColor::PIXEL_FORMAT(32, 32, 32, 32, 0, 32, 64, 96, 32*4, true);



FloatColor& FloatColor::operator =(const ByteColor& right)
{
	r = right.getRedAsFloat();
	g = right.getGreenAsFloat();
	b = right.getBlueAsFloat();
	a = right.getAlphaAsFloat();
	return *this;
}



FloatColor& FloatColor::operator =(const String& right)
{
	if (right.beginsWith('#') == true || right.beginsWith("0x") == true)
	{
		ByteColor byteColor = right;
		*this = byteColor;
	}
	else
	{
		StringTokenizer tokenizer(right);

		if (tokenizer.hasNextToken() == true)
		{
			String token = tokenizer.nextToken();
			if (token.isFloat() == true)
			{
				components[0] = token.parseFloat();
			}
			else
			{
				const ByteColor::ColorNames& colorNames = ByteColor::getColorNames();
				ByteColor::ColorNames::ConstIterator i = colorNames.find(token.lowerCase());
				if (i != colorNames.end())
				{
					*this = i->second;
				}
				else
				{
					argumentError("Invalid color-string!" ERROR_AT);
				}
				return *this;
			}
		}
		else
		{
			argumentError("Too less values for RGB-Color!" ERROR_AT);
			return *this;
		}

		for (int i = 1; i < 3; ++i)
		{
			if (tokenizer.hasNextToken() == true)
			{
				components[i] = tokenizer.nextToken().parseFloat();
			}
			else
			{
				argumentError("Too less values for RGB-Color!" ERROR_AT);
			}
		}
		a = tokenizer.hasNextToken() == true ? tokenizer.nextToken().parseFloat() : 1.0f;
	}
	return *this;
}



FloatColor::operator String() const
{
	return 
		String::createFrom(r) + ' ' +
		String::createFrom(g) + ' ' +
		String::createFrom(b) + ' ' +
		String::createFrom(a);
}



} // namespace Graphics
} // namespace BaseLib
