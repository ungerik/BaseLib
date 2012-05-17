/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Graphics/IntColor.h"
#include "BaseLib/Graphics/ByteColor.h"
#include "BaseLib/Graphics/FloatColor.h"
#include "BaseLib/Strings/StringTokenizer.h"
#include "BaseLib/Graphics/intern/Errors.h"



namespace BaseLib {
namespace Graphics {



using BaseLib::Strings::StringTokenizer;
using namespace BaseLib::ErrorHandling;



IntColor& IntColor::operator =(const ByteColor& right)
{
	r = right.r << 24;
	g = right.g << 24;
	b = right.b << 24;
	a = right.a << 24;
	return *this;
}



IntColor& IntColor::operator =(const FloatColor& right)
{
	r = static_cast<int>(INT_MAX * right.r);
	g = static_cast<int>(INT_MAX * right.g);
	b = static_cast<int>(INT_MAX * right.b);
	a = static_cast<int>(INT_MAX * right.a);
	return *this;
}



IntColor::operator String() const
{
	return 
		String::createFrom(r) + ' ' +
		String::createFrom(g) + ' ' +
		String::createFrom(b) + ' ' +
		String::createFrom(a);
}



IntColor& IntColor::operator =(const String& right)
{
	if (right.beginsWith('#') == true)
	{
		BL_ASSERT_NEVER_REACHED
		/// ...
	}
	else
	{
		StringTokenizer tokenizer(right);

		if (tokenizer.hasNextToken() == true)
		{
			String token = tokenizer.nextToken();
			if (token.isDec() == true)
			{
				components[0] = token.parseInt();
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
				components[i] = tokenizer.nextToken().parseInt();
			}
			else
			{
				argumentError("Too less values for RGB-Color!" ERROR_AT);
			}
		}
		a = tokenizer.hasNextToken() == true ? tokenizer.nextToken().parseInt() : INT_MAX;
	}
	return *this;
}



} // namespace Graphics
} // namespace BaseLib
