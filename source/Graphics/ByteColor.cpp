/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Graphics/ByteColor.h"
#include "BaseLib/Graphics/FloatColor.h"
#include "BaseLib/Strings/StringTokenizer.h"
#include "BaseLib/Graphics/intern/Errors.h"



namespace BaseLib {
namespace Graphics {



using BaseLib::Strings::StringTokenizer;
using namespace BaseLib::ErrorHandling;



const PixelFormat ByteColor::PIXEL_FORMAT(8, 8, 8, 8, 0, 8, 16, 24, 32, false);



ByteColor::ColorNames colorNames;



const ByteColor::ColorNames& ByteColor::getColorNames()
{
	if (colorNames.empty() == true)
	{
		colorNames["aliceblue"] = Aliceblue();
		colorNames["antiquewhite"] = Antiquewhite();
		colorNames["aqua"] = Aqua();
		colorNames["aquamarine"] = Aquamarine();
		colorNames["azure"] = Azure();
		colorNames["beige"] = Beige();
		colorNames["bisque"] = Bisque();
		colorNames["black"] = Black();
		colorNames["blanchedalmond"] = Blanchedalmond();
		colorNames["blue"] = Blue();
		colorNames["blueviolet"] = Blueviolet();
		colorNames["brown"] = Brown();
		colorNames["burlywood"] = Burlywood();
		colorNames["cadetblue"] = Cadetblue();
		colorNames["chartreuse"] = Chartreuse();
		colorNames["chocolate"] = Chocolate();
		colorNames["coral"] = Coral();
		colorNames["cornflowerblue"] = Cornflowerblue();
		colorNames["cornsilk"] = Cornsilk();
		colorNames["crimson"] = Crimson();
		colorNames["cyan"] = Cyan();
		colorNames["darkblue"] = Darkblue();
		colorNames["darkcyan"] = Darkcyan();
		colorNames["darkgoldenrod"] = Darkgoldenrod();
		colorNames["darkgray"] = Darkgray();
		colorNames["darkgreen"] = Darkgreen();
		colorNames["darkgrey"] = Darkgrey();
		colorNames["darkkhaki"] = Darkkhaki();
		colorNames["darkmagenta"] = Darkmagenta();
		colorNames["darkolivegreen"] = Darkolivegreen();
		colorNames["darkorange"] = Darkorange();
		colorNames["darkorchid"] = Darkorchid();
		colorNames["darkred"] = Darkred();
		colorNames["darksalmon"] = Darksalmon();
		colorNames["darkseagreen"] = Darkseagreen();
		colorNames["darkslateblue"] = Darkslateblue();
		colorNames["darkslategray"] = Darkslategray();
		colorNames["darkslategrey"] = Darkslategrey();
		colorNames["darkturquoise"] = Darkturquoise();
		colorNames["darkviolet"] = Darkviolet();
		colorNames["deeppink"] = Deeppink();
		colorNames["deepskyblue"] = Deepskyblue();
		colorNames["dimgray"] = Dimgray();
		colorNames["dimgrey"] = Dimgrey();
		colorNames["dodgerblue"] = Dodgerblue();
		colorNames["firebrick"] = Firebrick();
		colorNames["floralwhite"] = Floralwhite();
		colorNames["forestgreen"] = Forestgreen();
		colorNames["fuchsia"] = Fuchsia();
		colorNames["gainsboro"] = Gainsboro();
		colorNames["ghostwhite"] = Ghostwhite();
		colorNames["gold"] = Gold();
		colorNames["goldenrod"] = Goldenrod();
		colorNames["gray"] = Gray();
		colorNames["grey"] = Grey();
		colorNames["green"] = Green();
		colorNames["greenyellow"] = Greenyellow();
		colorNames["honeydew"] = Honeydew();
		colorNames["hotpink"] = Hotpink();
		colorNames["indianred"] = Indianred();
		colorNames["indigo"] = Indigo();
		colorNames["ivory"] = Ivory();
		colorNames["khaki"] = Khaki();
		colorNames["lavender"] = Lavender();
		colorNames["lavenderblush"] = Lavenderblush();
		colorNames["lawngreen"] = Lawngreen();
		colorNames["lemonchiffon"] = Lemonchiffon();
		colorNames["lightblue"] = Lightblue();
		colorNames["lightcoral"] = Lightcoral();
		colorNames["lightcyan"] = Lightcyan();
		colorNames["lightgoldenrodyellow"] = Lightgoldenrodyellow();
		colorNames["lightgray"] = Lightgray();
		colorNames["lightgreen"] = Lightgreen();
		colorNames["lightgrey"] = Lightgrey();
		colorNames["lightpink"] = Lightpink();
		colorNames["lightsalmon"] = Lightsalmon();
		colorNames["lightseagreen"] = Lightseagreen();
		colorNames["lightskyblue"] = Lightskyblue();
		colorNames["lightslategray"] = Lightslategray();
		colorNames["lightslategrey"] = Lightslategrey();
		colorNames["lightsteelblue"] = Lightsteelblue();
		colorNames["lightyellow"] = Lightyellow();
		colorNames["lime"] = Lime();
		colorNames["limegreen"] = Limegreen();
		colorNames["linen"] = Linen();
		colorNames["magenta"] = Magenta();
		colorNames["maroon"] = Maroon();
		colorNames["mediumaquamarine"] = Mediumaquamarine();
		colorNames["mediumblue"] = Mediumblue();
		colorNames["mediumorchid"] = Mediumorchid();
		colorNames["mediumpurple"] = Mediumpurple();
		colorNames["mediumseagreen"] = Mediumseagreen();
		colorNames["mediumslateblue"] = Mediumslateblue();
		colorNames["mediumspringgreen"] = Mediumspringgreen();
		colorNames["mediumturquoise"] = Mediumturquoise();
		colorNames["mediumvioletred"] = Mediumvioletred();
		colorNames["midnightblue"] = Midnightblue();
		colorNames["mintcream"] = Mintcream();
		colorNames["mistyrose"] = Mistyrose();
		colorNames["moccasin"] = Moccasin();
		colorNames["navajowhite"] = Navajowhite();
		colorNames["navy"] = Navy();
		colorNames["oldlace"] = Oldlace();
		colorNames["olive"] = Olive();
		colorNames["olivedrab"] = Olivedrab();
		colorNames["orange"] = Orange();
		colorNames["orangered"] = Orangered();
		colorNames["orchid"] = Orchid();
		colorNames["palegoldenrod"] = Palegoldenrod();
		colorNames["palegreen"] = Palegreen();
		colorNames["paleturquoise"] = Paleturquoise();
		colorNames["palevioletred"] = Palevioletred();
		colorNames["papayawhip"] = Papayawhip();
		colorNames["peachpuff"] = Peachpuff();
		colorNames["peru"] = Peru();
		colorNames["pink"] = Pink();
		colorNames["plum"] = Plum();
		colorNames["powderblue"] = Powderblue();
		colorNames["purple"] = Purple();
		colorNames["red"] = Red();
		colorNames["rosybrown"] = Rosybrown();
		colorNames["royalblue"] = Royalblue();
		colorNames["saddlebrown"] = Saddlebrown();
		colorNames["salmon"] = Salmon();
		colorNames["sandybrown"] = Sandybrown();
		colorNames["seagreen"] = Seagreen();
		colorNames["seashell"] = Seashell();
		colorNames["sienna"] = Sienna();
		colorNames["silver"] = Silver();
		colorNames["skyblue"] = Skyblue();
		colorNames["slateblue"] = Slateblue();
		colorNames["slategray"] = Slategray();
		colorNames["slategrey"] = Slategrey();
		colorNames["snow"] = Snow();
		colorNames["springgreen"] = Springgreen();
		colorNames["steelblue"] = Steelblue();
		colorNames["tan"] = Tan();
		colorNames["teal"] = Teal();
		colorNames["thistle"] = Thistle();
		colorNames["tomato"] = Tomato();
		colorNames["turquoise"] = Turquoise();
		colorNames["violet"] = Violet();
		colorNames["wheat"] = Wheat();
		colorNames["white"] = White();
		colorNames["whitesmoke"] = Whitesmoke();
		colorNames["yellow"] = Yellow();
		colorNames["yellowgreen"] = Yellowgreen();
	}
	return colorNames;
}



ByteColor& ByteColor::operator =(const FloatColor& right)
{
	r = right.getRedAsByte();
	g = right.getGreenAsByte();
	b = right.getBlueAsByte();
	a = right.getAlphaAsByte();
	return *this;
}



ByteColor& ByteColor::operator =(const String& right)
{
	if (right.beginsWith('#') == true)
	{
		if (right.getLength() != 7)
		{
			argumentError("Invalid internet-color; Must have format #RRGGBB!" ERROR_AT);
			return *this;
		}
		componentsPackedAsInt = 0xFFFFFFFF;
		right.hexToBinary(&componentsPackedAsInt, false, 1);
	}
	else if (right.beginsWith("0x") == true)
	{
		componentsPackedAsInt = right.parseUint32();
	}
	else
	{
		StringTokenizer tokenizer(right);

		if (tokenizer.hasNextToken() == true)
		{
			String token = tokenizer.nextToken();
			if (token.isDec() == true)
			{
				components[0] = token.parseUint8();
			}
			else
			{
				ColorNames::ConstIterator i = getColorNames().find(token.lowerCase());
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
				components[i] = tokenizer.nextToken().parseUint8();
			}
			else
			{
				argumentError("Too less values for RGB-Color!" ERROR_AT);
				return *this;
			}
		}
		a = tokenizer.hasNextToken() == true ? tokenizer.nextToken().parseUint8() : 255;
	}
	return *this;
}



ByteColor::operator String() const
{
	return 
		String::createFrom(r) + ' ' +
		String::createFrom(g) + ' ' +
		String::createFrom(b) + ' ' +
		String::createFrom(a);
}



} // namespace Graphics
} // namespace BaseLib
