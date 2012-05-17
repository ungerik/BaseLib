/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Graphics_ByteColor_h
#define BaseLib_Graphics_ByteColor_h


#include "BaseLib/Graphics/Colors.h"
#include "BaseLib/Graphics/PixelFormat.h"
#include "BaseLib/Strings/String.h"
#include "BaseLib/Containers/StringMap.h"
#include "BaseLib/Utilities/BitManipulation.h"
#include "BaseLib/Math/Common.h"



namespace BaseLib {
namespace Graphics {



using BaseLib::Strings::String;
using BaseLib::Containers::StringMap;
using namespace BaseLib::Math;



struct FloatColor;



struct BL_EXPORT ByteColor {

	static const PixelFormat PIXEL_FORMAT;

	typedef StringMap<ByteColor> ColorNames;
	static const ColorNames& getColorNames();

	union {
		struct {
			uint8 r;
			uint8 g;
			uint8 b;
			uint8 a;
		};
		uint8 components[4];
		uint32 componentsPackedAsInt;
	};

	ByteColor()
	#ifdef DEBUG_INIT
	  : r(1)
	  , g(2)
	  , b(3)
	  , a(4)
	#endif
	{
	}

	ByteColor(uint8 newRed, uint8 newGreen, uint8 newBlue, uint8 newAlpha = 255)
	  : r(newRed)
	  , g(newGreen)
	  , b(newBlue)
	  , a(newAlpha)
	{
	}

	ByteColor(float newRed, float newGreen, float newBlue, float newAlpha = 1.0f)
	{
		set(newRed, newGreen, newBlue, newAlpha);
	}

	ByteColor(const uint32& colorPackedInInteger)
	{
		operator =(colorPackedInInteger);
	}

	inline ByteColor& operator =(const uint32& colorPackedInInteger)
	{
		componentsPackedAsInt = colorPackedInInteger;
		return *this;
	}

	ByteColor(const String& colorString)
	{
		operator =(colorString);
	}

	ByteColor& operator =(const String& right);

	operator String() const;

	ByteColor(const FloatColor& floatColor)
	{
		operator =(floatColor);
	}

	inline ByteColor& operator =(const FloatColor& right);

	inline ByteColor& operator *=(uint8 value)
	{
		r *= value;
		g *= value;
		b *= value;
		a *= value;
		return *this;
	}

	inline ByteColor& operator /=(uint8 value)
	{
		r /= value;
		g /= value;
		b /= value;
		a /= value;
		return *this;
	}

	inline ByteColor& operator +=(uint8 value)
	{
		r += value;
		g += value;
		b += value;
		a += value;
		return *this;
	}

	inline ByteColor& operator -=(uint8 value)
	{
		r -= value;
		g -= value;
		b -= value;
		a -= value;
		return *this;
	}

	inline ByteColor& operator *=(const ByteColor& right)
	{
		r = (uint8)(( (int)r * (int)right.r ) << 8);
		g = (uint8)(( (int)g * (int)right.g ) << 8);
		b = (uint8)(( (int)b * (int)right.b ) << 8);
		a = (uint8)(( (int)a * (int)right.a ) << 8);
		return *this;
	}

	inline ByteColor& operator /=(const ByteColor& right)
	{
		r = (uint8)( (((int)r) << 8) / (int)right.r);
		g = (uint8)( (((int)g) << 8) / (int)right.g);
		b = (uint8)( (((int)b) << 8) / (int)right.b);
		a = (uint8)( (((int)a) << 8) / (int)right.a);
		return *this;
	}

	inline ByteColor& operator +=(const ByteColor& right)
	{
		r += right.r;
		g += right.g;
		b += right.b;
		a += right.a;
		return *this;
	}

	inline ByteColor& operator -=(const ByteColor& right)
	{
		r -= right.r;
		g -= right.g;
		b -= right.b;
		a -= right.a;
		return *this;
	}

    inline ByteColor(Aliceblue) { aliceblue(); }
    inline ByteColor(Antiquewhite) { antiquewhite(); }
    inline ByteColor(Aqua) { aqua(); }
    inline ByteColor(Aquamarine) { aquamarine(); }
    inline ByteColor(Azure) { azure(); }
    inline ByteColor(Beige) { beige(); }
    inline ByteColor(Bisque) { bisque(); }
    inline ByteColor(Black) { black(); }
    inline ByteColor(Blanchedalmond) { blanchedalmond(); }
    inline ByteColor(Blue) { blue(); }
    inline ByteColor(Blueviolet) { blueviolet(); }
    inline ByteColor(Brown) { brown(); }
    inline ByteColor(Burlywood) { burlywood(); }
    inline ByteColor(Cadetblue) { cadetblue(); }
    inline ByteColor(Chartreuse) { chartreuse(); }
    inline ByteColor(Chocolate) { chocolate(); }
    inline ByteColor(Coral) { coral(); }
    inline ByteColor(Cornflowerblue) { cornflowerblue(); }
    inline ByteColor(Cornsilk) { cornsilk(); }
    inline ByteColor(Crimson) { crimson(); }
    inline ByteColor(Cyan) { cyan(); }
    inline ByteColor(Darkblue) { darkblue(); }
    inline ByteColor(Darkcyan) { darkcyan(); }
    inline ByteColor(Darkgoldenrod) { darkgoldenrod(); }
    inline ByteColor(Darkgray) { darkgray(); }
    inline ByteColor(Darkgreen) { darkgreen(); }
    inline ByteColor(Darkgrey) { darkgrey(); }
    inline ByteColor(Darkkhaki) { darkkhaki(); }
    inline ByteColor(Darkmagenta) { darkmagenta(); }
    inline ByteColor(Darkolivegreen) { darkolivegreen(); }
    inline ByteColor(Darkorange) { darkorange(); }
    inline ByteColor(Darkorchid) { darkorchid(); }
    inline ByteColor(Darkred) { darkred(); }
    inline ByteColor(Darksalmon) { darksalmon(); }
    inline ByteColor(Darkseagreen) { darkseagreen(); }
    inline ByteColor(Darkslateblue) { darkslateblue(); }
    inline ByteColor(Darkslategray) { darkslategray(); }
    inline ByteColor(Darkslategrey) { darkslategrey(); }
    inline ByteColor(Darkturquoise) { darkturquoise(); }
    inline ByteColor(Darkviolet) { darkviolet(); }
    inline ByteColor(Deeppink) { deeppink(); }
    inline ByteColor(Deepskyblue) { deepskyblue(); }
    inline ByteColor(Dimgray) { dimgray(); }
    inline ByteColor(Dimgrey) { dimgrey(); }
    inline ByteColor(Dodgerblue) { dodgerblue(); }
    inline ByteColor(Firebrick) { firebrick(); }
    inline ByteColor(Floralwhite) { floralwhite(); }
    inline ByteColor(Forestgreen) { forestgreen(); }
    inline ByteColor(Fuchsia) { fuchsia(); }
    inline ByteColor(Gainsboro) { gainsboro(); }
    inline ByteColor(Ghostwhite) { ghostwhite(); }
    inline ByteColor(Gold) { gold(); }
    inline ByteColor(Goldenrod) { goldenrod(); }
    inline ByteColor(Gray) { gray(); }
    inline ByteColor(Grey) { grey(); }
    inline ByteColor(Green) { green(); }
    inline ByteColor(Greenyellow) { greenyellow(); }
    inline ByteColor(Honeydew) { honeydew(); }
    inline ByteColor(Hotpink) { hotpink(); }
    inline ByteColor(Indianred) { indianred(); }
    inline ByteColor(Indigo) { indigo(); }
    inline ByteColor(Ivory) { ivory(); }
    inline ByteColor(Khaki) { khaki(); }
    inline ByteColor(Lavender) { lavender(); }
    inline ByteColor(Lavenderblush) { lavenderblush(); }
    inline ByteColor(Lawngreen) { lawngreen(); }
    inline ByteColor(Lemonchiffon) { lemonchiffon(); }
    inline ByteColor(Lightblue) { lightblue(); }
    inline ByteColor(Lightcoral) { lightcoral(); }
    inline ByteColor(Lightcyan) { lightcyan(); }
    inline ByteColor(Lightgoldenrodyellow) { lightgoldenrodyellow(); }
    inline ByteColor(Lightgray) { lightgray(); }
    inline ByteColor(Lightgreen) { lightgreen(); }
    inline ByteColor(Lightgrey) { lightgrey(); }
    inline ByteColor(Lightpink) { lightpink(); }
    inline ByteColor(Lightsalmon) { lightsalmon(); }
    inline ByteColor(Lightseagreen) { lightseagreen(); }
    inline ByteColor(Lightskyblue) { lightskyblue(); }
    inline ByteColor(Lightslategray) { lightslategray(); }
    inline ByteColor(Lightslategrey) { lightslategrey(); }
    inline ByteColor(Lightsteelblue) { lightsteelblue(); }
    inline ByteColor(Lightyellow) { lightyellow(); }
    inline ByteColor(Lime) { lime(); }
    inline ByteColor(Limegreen) { limegreen(); }
    inline ByteColor(Linen) { linen(); }
    inline ByteColor(Magenta) { magenta(); }
    inline ByteColor(Maroon) { maroon(); }
    inline ByteColor(Mediumaquamarine) { mediumaquamarine(); }
    inline ByteColor(Mediumblue) { mediumblue(); }
    inline ByteColor(Mediumorchid) { mediumorchid(); }
    inline ByteColor(Mediumpurple) { mediumpurple(); }
    inline ByteColor(Mediumseagreen) { mediumseagreen(); }
    inline ByteColor(Mediumslateblue) { mediumslateblue(); }
    inline ByteColor(Mediumspringgreen) { mediumspringgreen(); }
    inline ByteColor(Mediumturquoise) { mediumturquoise(); }
    inline ByteColor(Mediumvioletred) { mediumvioletred(); }
    inline ByteColor(Midnightblue) { midnightblue(); }
    inline ByteColor(Mintcream) { mintcream(); }
    inline ByteColor(Mistyrose) { mistyrose(); }
    inline ByteColor(Moccasin) { moccasin(); }
    inline ByteColor(Navajowhite) { navajowhite(); }
    inline ByteColor(Navy) { navy(); }
    inline ByteColor(Oldlace) { oldlace(); }
    inline ByteColor(Olive) { olive(); }
    inline ByteColor(Olivedrab) { olivedrab(); }
    inline ByteColor(Orange) { orange(); }
    inline ByteColor(Orangered) { orangered(); }
    inline ByteColor(Orchid) { orchid(); }
    inline ByteColor(Palegoldenrod) { palegoldenrod(); }
    inline ByteColor(Palegreen) { palegreen(); }
    inline ByteColor(Paleturquoise) { paleturquoise(); }
    inline ByteColor(Palevioletred) { palevioletred(); }
    inline ByteColor(Papayawhip) { papayawhip(); }
    inline ByteColor(Peachpuff) { peachpuff(); }
    inline ByteColor(Peru) { peru(); }
    inline ByteColor(Pink) { pink(); }
    inline ByteColor(Plum) { plum(); }
    inline ByteColor(Powderblue) { powderblue(); }
    inline ByteColor(Purple) { purple(); }
    inline ByteColor(Red) { red(); }
    inline ByteColor(Rosybrown) { rosybrown(); }
    inline ByteColor(Royalblue) { royalblue(); }
    inline ByteColor(Saddlebrown) { saddlebrown(); }
    inline ByteColor(Salmon) { salmon(); }
    inline ByteColor(Sandybrown) { sandybrown(); }
    inline ByteColor(Seagreen) { seagreen(); }
    inline ByteColor(Seashell) { seashell(); }
    inline ByteColor(Sienna) { sienna(); }
    inline ByteColor(Silver) { silver(); }
    inline ByteColor(Skyblue) { skyblue(); }
    inline ByteColor(Slateblue) { slateblue(); }
    inline ByteColor(Slategray) { slategray(); }
    inline ByteColor(Slategrey) { slategrey(); }
    inline ByteColor(Snow) { snow(); }
    inline ByteColor(Springgreen) { springgreen(); }
    inline ByteColor(Steelblue) { steelblue(); }
    inline ByteColor(Tan) { tan(); }
    inline ByteColor(Teal) { teal(); }
    inline ByteColor(Thistle) { thistle(); }
    inline ByteColor(Tomato) { tomato(); }
    inline ByteColor(Turquoise) { turquoise(); }
    inline ByteColor(Violet) { violet(); }
    inline ByteColor(Wheat) { wheat(); }
    inline ByteColor(White) { white(); }
    inline ByteColor(Whitesmoke) { whitesmoke(); }
    inline ByteColor(Yellow) { yellow(); }
    inline ByteColor(Yellowgreen) { yellowgreen(); }

    inline ByteColor& operator=(Aliceblue) { return aliceblue(); }
    inline ByteColor& operator=(Antiquewhite) { return antiquewhite(); }
    inline ByteColor& operator=(Aqua) { return aqua(); }
    inline ByteColor& operator=(Aquamarine) { return aquamarine(); }
    inline ByteColor& operator=(Azure) { return azure(); }
    inline ByteColor& operator=(Beige) { return beige(); }
    inline ByteColor& operator=(Bisque) { return bisque(); }
    inline ByteColor& operator=(Black) { return black(); }
    inline ByteColor& operator=(Blanchedalmond) { return blanchedalmond(); }
    inline ByteColor& operator=(Blue) { return blue(); }
    inline ByteColor& operator=(Blueviolet) { return blueviolet(); }
    inline ByteColor& operator=(Brown) { return brown(); }
    inline ByteColor& operator=(Burlywood) { return burlywood(); }
    inline ByteColor& operator=(Cadetblue) { return cadetblue(); }
    inline ByteColor& operator=(Chartreuse) { return chartreuse(); }
    inline ByteColor& operator=(Chocolate) { return chocolate(); }
    inline ByteColor& operator=(Coral) { return coral(); }
    inline ByteColor& operator=(Cornflowerblue) { return cornflowerblue(); }
    inline ByteColor& operator=(Cornsilk) { return cornsilk(); }
    inline ByteColor& operator=(Crimson) { return crimson(); }
    inline ByteColor& operator=(Cyan) { return cyan(); }
    inline ByteColor& operator=(Darkblue) { return darkblue(); }
    inline ByteColor& operator=(Darkcyan) { return darkcyan(); }
    inline ByteColor& operator=(Darkgoldenrod) { return darkgoldenrod(); }
    inline ByteColor& operator=(Darkgray) { return darkgray(); }
    inline ByteColor& operator=(Darkgreen) { return darkgreen(); }
    inline ByteColor& operator=(Darkgrey) { return darkgrey(); }
    inline ByteColor& operator=(Darkkhaki) { return darkkhaki(); }
    inline ByteColor& operator=(Darkmagenta) { return darkmagenta(); }
    inline ByteColor& operator=(Darkolivegreen) { return darkolivegreen(); }
    inline ByteColor& operator=(Darkorange) { return darkorange(); }
    inline ByteColor& operator=(Darkorchid) { return darkorchid(); }
    inline ByteColor& operator=(Darkred) { return darkred(); }
    inline ByteColor& operator=(Darksalmon) { return darksalmon(); }
    inline ByteColor& operator=(Darkseagreen) { return darkseagreen(); }
    inline ByteColor& operator=(Darkslateblue) { return darkslateblue(); }
    inline ByteColor& operator=(Darkslategray) { return darkslategray(); }
    inline ByteColor& operator=(Darkslategrey) { return darkslategrey(); }
    inline ByteColor& operator=(Darkturquoise) { return darkturquoise(); }
    inline ByteColor& operator=(Darkviolet) { return darkviolet(); }
    inline ByteColor& operator=(Deeppink) { return deeppink(); }
    inline ByteColor& operator=(Deepskyblue) { return deepskyblue(); }
    inline ByteColor& operator=(Dimgray) { return dimgray(); }
    inline ByteColor& operator=(Dimgrey) { return dimgrey(); }
    inline ByteColor& operator=(Dodgerblue) { return dodgerblue(); }
    inline ByteColor& operator=(Firebrick) { return firebrick(); }
    inline ByteColor& operator=(Floralwhite) { return floralwhite(); }
    inline ByteColor& operator=(Forestgreen) { return forestgreen(); }
    inline ByteColor& operator=(Fuchsia) { return fuchsia(); }
    inline ByteColor& operator=(Gainsboro) { return gainsboro(); }
    inline ByteColor& operator=(Ghostwhite) { return ghostwhite(); }
    inline ByteColor& operator=(Gold) { return gold(); }
    inline ByteColor& operator=(Goldenrod) { return goldenrod(); }
    inline ByteColor& operator=(Gray) { return gray(); }
    inline ByteColor& operator=(Grey) { return grey(); }
    inline ByteColor& operator=(Green) { return green(); }
    inline ByteColor& operator=(Greenyellow) { return greenyellow(); }
    inline ByteColor& operator=(Honeydew) { return honeydew(); }
    inline ByteColor& operator=(Hotpink) { return hotpink(); }
    inline ByteColor& operator=(Indianred) { return indianred(); }
    inline ByteColor& operator=(Indigo) { return indigo(); }
    inline ByteColor& operator=(Ivory) { return ivory(); }
    inline ByteColor& operator=(Khaki) { return khaki(); }
    inline ByteColor& operator=(Lavender) { return lavender(); }
    inline ByteColor& operator=(Lavenderblush) { return lavenderblush(); }
    inline ByteColor& operator=(Lawngreen) { return lawngreen(); }
    inline ByteColor& operator=(Lemonchiffon) { return lemonchiffon(); }
    inline ByteColor& operator=(Lightblue) { return lightblue(); }
    inline ByteColor& operator=(Lightcoral) { return lightcoral(); }
    inline ByteColor& operator=(Lightcyan) { return lightcyan(); }
    inline ByteColor& operator=(Lightgoldenrodyellow) { return lightgoldenrodyellow(); }
    inline ByteColor& operator=(Lightgray) { return lightgray(); }
    inline ByteColor& operator=(Lightgreen) { return lightgreen(); }
    inline ByteColor& operator=(Lightgrey) { return lightgrey(); }
    inline ByteColor& operator=(Lightpink) { return lightpink(); }
    inline ByteColor& operator=(Lightsalmon) { return lightsalmon(); }
    inline ByteColor& operator=(Lightseagreen) { return lightseagreen(); }
    inline ByteColor& operator=(Lightskyblue) { return lightskyblue(); }
    inline ByteColor& operator=(Lightslategray) { return lightslategray(); }
    inline ByteColor& operator=(Lightslategrey) { return lightslategrey(); }
    inline ByteColor& operator=(Lightsteelblue) { return lightsteelblue(); }
    inline ByteColor& operator=(Lightyellow) { return lightyellow(); }
    inline ByteColor& operator=(Lime) { return lime(); }
    inline ByteColor& operator=(Limegreen) { return limegreen(); }
    inline ByteColor& operator=(Linen) { return linen(); }
    inline ByteColor& operator=(Magenta) { return magenta(); }
    inline ByteColor& operator=(Maroon) { return maroon(); }
    inline ByteColor& operator=(Mediumaquamarine) { return mediumaquamarine(); }
    inline ByteColor& operator=(Mediumblue) { return mediumblue(); }
    inline ByteColor& operator=(Mediumorchid) { return mediumorchid(); }
    inline ByteColor& operator=(Mediumpurple) { return mediumpurple(); }
    inline ByteColor& operator=(Mediumseagreen) { return mediumseagreen(); }
    inline ByteColor& operator=(Mediumslateblue) { return mediumslateblue(); }
    inline ByteColor& operator=(Mediumspringgreen) { return mediumspringgreen(); }
    inline ByteColor& operator=(Mediumturquoise) { return mediumturquoise(); }
    inline ByteColor& operator=(Mediumvioletred) { return mediumvioletred(); }
    inline ByteColor& operator=(Midnightblue) { return midnightblue(); }
    inline ByteColor& operator=(Mintcream) { return mintcream(); }
    inline ByteColor& operator=(Mistyrose) { return mistyrose(); }
    inline ByteColor& operator=(Moccasin) { return moccasin(); }
    inline ByteColor& operator=(Navajowhite) { return navajowhite(); }
    inline ByteColor& operator=(Navy) { return navy(); }
    inline ByteColor& operator=(Oldlace) { return oldlace(); }
    inline ByteColor& operator=(Olive) { return olive(); }
    inline ByteColor& operator=(Olivedrab) { return olivedrab(); }
    inline ByteColor& operator=(Orange) { return orange(); }
    inline ByteColor& operator=(Orangered) { return orangered(); }
    inline ByteColor& operator=(Orchid) { return orchid(); }
    inline ByteColor& operator=(Palegoldenrod) { return palegoldenrod(); }
    inline ByteColor& operator=(Palegreen) { return palegreen(); }
    inline ByteColor& operator=(Paleturquoise) { return paleturquoise(); }
    inline ByteColor& operator=(Palevioletred) { return palevioletred(); }
    inline ByteColor& operator=(Papayawhip) { return papayawhip(); }
    inline ByteColor& operator=(Peachpuff) { return peachpuff(); }
    inline ByteColor& operator=(Peru) { return peru(); }
    inline ByteColor& operator=(Pink) { return pink(); }
    inline ByteColor& operator=(Plum) { return plum(); }
    inline ByteColor& operator=(Powderblue) { return powderblue(); }
    inline ByteColor& operator=(Purple) { return purple(); }
    inline ByteColor& operator=(Red) { return red(); }
    inline ByteColor& operator=(Rosybrown) { return rosybrown(); }
    inline ByteColor& operator=(Royalblue) { return royalblue(); }
    inline ByteColor& operator=(Saddlebrown) { return saddlebrown(); }
    inline ByteColor& operator=(Salmon) { return salmon(); }
    inline ByteColor& operator=(Sandybrown) { return sandybrown(); }
    inline ByteColor& operator=(Seagreen) { return seagreen(); }
    inline ByteColor& operator=(Seashell) { return seashell(); }
    inline ByteColor& operator=(Sienna) { return sienna(); }
    inline ByteColor& operator=(Silver) { return silver(); }
    inline ByteColor& operator=(Skyblue) { return skyblue(); }
    inline ByteColor& operator=(Slateblue) { return slateblue(); }
    inline ByteColor& operator=(Slategray) { return slategray(); }
    inline ByteColor& operator=(Slategrey) { return slategrey(); }
    inline ByteColor& operator=(Snow) { return snow(); }
    inline ByteColor& operator=(Springgreen) { return springgreen(); }
    inline ByteColor& operator=(Steelblue) { return steelblue(); }
    inline ByteColor& operator=(Tan) { return tan(); }
    inline ByteColor& operator=(Teal) { return teal(); }
    inline ByteColor& operator=(Thistle) { return thistle(); }
    inline ByteColor& operator=(Tomato) { return tomato(); }
    inline ByteColor& operator=(Turquoise) { return turquoise(); }
    inline ByteColor& operator=(Violet) { return violet(); }
    inline ByteColor& operator=(Wheat) { return wheat(); }
    inline ByteColor& operator=(White) { return white(); }
    inline ByteColor& operator=(Whitesmoke) { return whitesmoke(); }
    inline ByteColor& operator=(Yellow) { return yellow(); }
    inline ByteColor& operator=(Yellowgreen) { return yellowgreen(); }

	inline ByteColor& aliceblue() { r = 240; g = 248; b = 255; a = 255; return *this; }
    inline ByteColor& antiquewhite() { r = 250; g = 235; b = 215; a = 255; return *this; }
    inline ByteColor& aqua() { r = 0; g = 255; b = 255; a = 255; return *this; }
    inline ByteColor& aquamarine() { r = 127; g = 255; b = 212; a = 255; return *this; }
    inline ByteColor& azure() { r = 240; g = 255; b = 255; a = 255; return *this; }
    inline ByteColor& beige() { r = 245; g = 245; b = 220; a = 255; return *this; }
    inline ByteColor& bisque() { r = 255; g = 228; b = 196; a = 255; return *this; }
    inline ByteColor& black() { r = 0; g = 0; b = 0; a = 255; return *this; }
    inline ByteColor& blanchedalmond() { r = 255; g = 235; b = 205; a = 255; return *this; }
    inline ByteColor& blue() { r = 0; g = 0; b = 255; a = 255; return *this; }
    inline ByteColor& blueviolet() { r = 138; g = 43; b = 226; a = 255; return *this; }
    inline ByteColor& brown() { r = 165; g = 42; b = 42; a = 255; return *this; }
    inline ByteColor& burlywood() { r = 222; g = 184; b = 135; a = 255; return *this; }
    inline ByteColor& cadetblue() { r = 95; g = 158; b = 160; a = 255; return *this; }
    inline ByteColor& chartreuse() { r = 127; g = 255; b = 0; a = 255; return *this; }
    inline ByteColor& chocolate() { r = 210; g = 105; b = 30; a = 255; return *this; }
    inline ByteColor& coral() { r = 255; g = 127; b = 80; a = 255; return *this; }
    inline ByteColor& cornflowerblue() { r = 100; g = 149; b = 237; a = 255; return *this; }
    inline ByteColor& cornsilk() { r = 255; g = 248; b = 220; a = 255; return *this; }
    inline ByteColor& crimson() { r = 220; g = 20; b = 60; a = 255; return *this; }
    inline ByteColor& cyan() { r = 0; g = 255; b = 255; a = 255; return *this; }
    inline ByteColor& darkblue() { r = 0; g = 0; b = 139; a = 255; return *this; }
    inline ByteColor& darkcyan() { r = 0; g = 139; b = 139; a = 255; return *this; }
    inline ByteColor& darkgoldenrod() { r = 184; g = 134; b = 11; a = 255; return *this; }
    inline ByteColor& darkgray() { r = 169; g = 169; b = 169; a = 255; return *this; }
    inline ByteColor& darkgreen() { r = 0; g = 100; b = 0; a = 255; return *this; }
    inline ByteColor& darkgrey() { r = 169; g = 169; b = 169; a = 255; return *this; }
    inline ByteColor& darkkhaki() { r = 189; g = 183; b = 107; a = 255; return *this; }
    inline ByteColor& darkmagenta() { r = 139; g = 0; b = 139; a = 255; return *this; }
    inline ByteColor& darkolivegreen() { r = 85; g = 107; b = 47; a = 255; return *this; }
    inline ByteColor& darkorange() { r = 255; g = 140; b = 0; a = 255; return *this; }
    inline ByteColor& darkorchid() { r = 153; g = 50; b = 204; a = 255; return *this; }
    inline ByteColor& darkred() { r = 139; g = 0; b = 0; a = 255; return *this; }
    inline ByteColor& darksalmon() { r = 233; g = 150; b = 122; a = 255; return *this; }
    inline ByteColor& darkseagreen() { r = 143; g = 188; b = 143; a = 255; return *this; }
    inline ByteColor& darkslateblue() { r = 72; g = 61; b = 139; a = 255; return *this; }
    inline ByteColor& darkslategray() { r = 47; g = 79; b = 79; a = 255; return *this; }
    inline ByteColor& darkslategrey() { r = 47; g = 79; b = 79; a = 255; return *this; }
    inline ByteColor& darkturquoise() { r = 0; g = 206; b = 209; a = 255; return *this; }
    inline ByteColor& darkviolet() { r = 148; g = 0; b = 211; a = 255; return *this; }
    inline ByteColor& deeppink() { r = 255; g = 20; b = 147; a = 255; return *this; }
    inline ByteColor& deepskyblue() { r = 0; g = 191; b = 255; a = 255; return *this; }
    inline ByteColor& dimgray() { r = 105; g = 105; b = 105; a = 255; return *this; }
    inline ByteColor& dimgrey() { r = 105; g = 105; b = 105; a = 255; return *this; }
    inline ByteColor& dodgerblue() { r = 30; g = 144; b = 255; a = 255; return *this; }
    inline ByteColor& firebrick() { r = 178; g = 34; b = 34; a = 255; return *this; }
    inline ByteColor& floralwhite() { r = 255; g = 250; b = 240; a = 255; return *this; }
    inline ByteColor& forestgreen() { r = 34; g = 139; b = 34; a = 255; return *this; }
    inline ByteColor& fuchsia() { r = 255; g = 0; b = 255; a = 255; return *this; }
    inline ByteColor& gainsboro() { r = 220; g = 220; b = 220; a = 255; return *this; }
    inline ByteColor& ghostwhite() { r = 248; g = 248; b = 255; a = 255; return *this; }
    inline ByteColor& gold() { r = 255; g = 215; b = 0; a = 255; return *this; }
    inline ByteColor& goldenrod() { r = 218; g = 165; b = 32; a = 255; return *this; }
    inline ByteColor& gray() { r = 128; g = 128; b = 128; a = 255; return *this; }
    inline ByteColor& grey() { r = 128; g = 128; b = 128; a = 255; return *this; }
    inline ByteColor& green() { r = 0; g = 128; b = 0; a = 255; return *this; }
	inline ByteColor& greenyellow() { r = 173; g = 255; b = 47; a = 255; return *this; }
    inline ByteColor& honeydew() { r = 240; g = 255; b = 240; a = 255; return *this; }
    inline ByteColor& hotpink() { r = 255; g = 105; b = 180; a = 255; return *this; }
    inline ByteColor& indianred() { r = 205; g = 92; b = 92; a = 255; return *this; }
    inline ByteColor& indigo() { r = 75; g = 0; b = 130; a = 255; return *this; }
    inline ByteColor& ivory() { r = 255; g = 255; b = 240; a = 255; return *this; }
    inline ByteColor& khaki() { r = 240; g = 230; b = 140; a = 255; return *this; }
    inline ByteColor& lavender() { r = 230; g =230; b = 250; a = 255; return *this; }
    inline ByteColor& lavenderblush() { r = 255; g = 240; b = 245; a = 255; return *this; }
    inline ByteColor& lawngreen() { r = 124; g = 252; b = 0; a = 255; return *this; }
    inline ByteColor& lemonchiffon() { r = 255; g = 250; b = 205; a = 255; return *this; }
    inline ByteColor& lightblue() { r = 173; g = 216; b = 230; a = 255; return *this; }
    inline ByteColor& lightcoral() { r = 240; g = 128; b = 128; a = 255; return *this; }
    inline ByteColor& lightcyan() { r = 224; g = 255; b = 255; a = 255; return *this; }
    inline ByteColor& lightgoldenrodyellow() { r = 250; g = 250; b = 210; a = 255; return *this; }
    inline ByteColor& lightgray() { r = 211; g = 211; b = 211; a = 255; return *this; }
    inline ByteColor& lightgreen() { r = 144; g = 238; b = 144; a = 255; return *this; }
    inline ByteColor& lightgrey() { r = 211; g = 211; b = 211; a = 255; return *this; }
    inline ByteColor& lightpink() { r = 255; g = 182; b = 193; a = 255; return *this; }
    inline ByteColor& lightsalmon() { r = 255; g = 160; b = 122; a = 255; return *this; }
    inline ByteColor& lightseagreen() { r = 32; g = 178; b = 170; a = 255; return *this; }
    inline ByteColor& lightskyblue() { r = 135; g = 206; b = 250; a = 255; return *this; }
    inline ByteColor& lightslategray() { r = 119; g = 136; b = 153; a = 255; return *this; }
    inline ByteColor& lightslategrey() { r = 119; g = 136; b = 153; a = 255; return *this; }
    inline ByteColor& lightsteelblue() { r = 176; g = 196; b = 222; a = 255; return *this; }
    inline ByteColor& lightyellow() { r = 255; g = 255; b = 224; a = 255; return *this; }
    inline ByteColor& lime() { r = 0; g = 255; b = 0; a = 255; return *this; }
    inline ByteColor& limegreen() { r = 50; g = 205; b = 50; a = 255; return *this; }
    inline ByteColor& linen() { r = 250; g = 240; b = 230; a = 255; return *this; }
    inline ByteColor& magenta() { r = 255; g = 0; b = 255; a = 255; return *this; }
    inline ByteColor& maroon() { r = 128; g = 0; b = 0; a = 255; return *this; }
    inline ByteColor& mediumaquamarine() { r = 102; g = 205; b = 170; a = 255; return *this; }
    inline ByteColor& mediumblue() { r = 0; g = 0; b = 205; a = 255; return *this; }
    inline ByteColor& mediumorchid() { r = 186; g = 85; b = 211; a = 255; return *this; }
    inline ByteColor& mediumpurple() { r = 147; g = 112; b = 219; a = 255; return *this; }
    inline ByteColor& mediumseagreen() { r = 60; g = 179; b = 113; a = 255; return *this; }
    inline ByteColor& mediumslateblue() { r = 123; g = 104; b = 238; a = 255; return *this; }
    inline ByteColor& mediumspringgreen() { r = 0; g = 250; b = 154; a = 255; return *this; }
    inline ByteColor& mediumturquoise() { r = 72; g = 209; b = 204; a = 255; return *this; }
    inline ByteColor& mediumvioletred() { r = 199; g = 21; b = 133; a = 255; return *this; }
    inline ByteColor& midnightblue() { r = 25; g = 25; b = 112; a = 255; return *this; }
    inline ByteColor& mintcream() { r = 245; g = 255; b = 250; a = 255; return *this; }
    inline ByteColor& mistyrose() { r = 255; g = 228; b = 225; a = 255; return *this; }
    inline ByteColor& moccasin() { r = 255; g = 228; b = 181; a = 255; return *this; }
	inline ByteColor& navajowhite() { r = 255; g = 222; b = 173; a = 255; return *this; }
    inline ByteColor& navy() { r = 0; g = 0; b = 128; a = 255; return *this; }
    inline ByteColor& oldlace() { r = 253; g = 245; b = 230; a = 255; return *this; }
    inline ByteColor& olive() { r = 128; g = 128; b = 0; a = 255; return *this; }
    inline ByteColor& olivedrab() { r = 107; g = 142; b = 35; a = 255; return *this; }
    inline ByteColor& orange() { r = 255; g = 165; b = 0; a = 255; return *this; }
    inline ByteColor& orangered() { r = 255; g = 69; b = 0; a = 255; return *this; }
    inline ByteColor& orchid() { r = 218; g = 112; b = 214; a = 255; return *this; }
    inline ByteColor& palegoldenrod() { r = 238; g = 232; b = 170; a = 255; return *this; }
    inline ByteColor& palegreen() { r = 152; g = 251; b = 152; a = 255; return *this; }
    inline ByteColor& paleturquoise() { r = 175; g = 238; b = 238; a = 255; return *this; }
    inline ByteColor& palevioletred() { r = 219; g = 112; b = 147; a = 255; return *this; }
    inline ByteColor& papayawhip() { r = 255; g = 239; b = 213; a = 255; return *this; }
    inline ByteColor& peachpuff() { r = 255; g = 218; b = 185; a = 255; return *this; }
    inline ByteColor& peru() { r = 205; g = 133; b = 63; a = 255; return *this; }
    inline ByteColor& pink() { r = 255; g = 192; b = 203; a = 255; return *this; }
    inline ByteColor& plum() { r = 221; g = 160; b = 221; a = 255; return *this; }
    inline ByteColor& powderblue() { r = 176; g = 224; b = 230; a = 255; return *this; }
    inline ByteColor& purple() { r = 128; g = 0; b = 128; a = 255; return *this; }
    inline ByteColor& red() { r = 255; g = 0; b = 0; a = 255; return *this; }
    inline ByteColor& rosybrown() { r = 188; g = 143; b = 143; a = 255; return *this; }
    inline ByteColor& royalblue() { r = 65; g = 105; b = 225; a = 255; return *this; }
    inline ByteColor& saddlebrown() { r = 139; g = 69; b = 19; a = 255; return *this; }
    inline ByteColor& salmon() { r = 250; g = 128; b = 114; a = 255; return *this; }
    inline ByteColor& sandybrown() { r = 244; g = 164; b = 96; a = 255; return *this; }
    inline ByteColor& seagreen() { r = 46; g = 139; b = 87; a = 255; return *this; }
    inline ByteColor& seashell() { r = 255; g = 245; b = 238; a = 255; return *this; }
    inline ByteColor& sienna() { r = 160; g = 82; b = 45; a = 255; return *this; }
    inline ByteColor& silver() { r = 192; g = 192; b = 192; a = 255; return *this; }
    inline ByteColor& skyblue() { r = 135; g = 206; b = 235; a = 255; return *this; }
    inline ByteColor& slateblue() { r = 106; g = 90; b = 205; a = 255; return *this; }
    inline ByteColor& slategray() { r = 112; g = 128; b = 144; a = 255; return *this; }
    inline ByteColor& slategrey() { r = 112; g = 128; b = 144; a = 255; return *this; }
    inline ByteColor& snow() { r = 255; g = 250; b = 250; a = 255; return *this; }
    inline ByteColor& springgreen() { r = 0; g = 255; b = 127; a = 255; return *this; }
    inline ByteColor& steelblue() { r = 70; g = 130; b = 180; a = 255; return *this; }
    inline ByteColor& tan() { r = 210; g = 180; b = 140; a = 255; return *this; }
    inline ByteColor& teal() { r = 0; g = 128; b = 128; a = 255; return *this; }
    inline ByteColor& thistle() { r = 216; g = 191; b = 216; a = 255; return *this; }
    inline ByteColor& tomato() { r = 255; g = 99; b = 71; a = 255; return *this; }
    inline ByteColor& turquoise() { r = 64; g = 224; b = 208; a = 255; return *this; }
    inline ByteColor& violet() { r = 238; g = 130; b = 238; a = 255; return *this; }
    inline ByteColor& wheat() { r = 245; g = 222; b = 179; a = 255; return *this; }
    inline ByteColor& white() { r = 255; g = 255; b = 255; a = 255; return *this; }
    inline ByteColor& whitesmoke() { r = 245; g = 245; b = 245; a = 255; return *this; }
    inline ByteColor& yellow() { r = 255; g = 255; b = 0; a = 255; return *this; }
    inline ByteColor& yellowgreen() { r = 154; g = 205; b = 50; a = 255; return *this; }
  


	inline float getRedAsFloat() const { return r * (1.0f / 255.0f); }
	inline float getGreenAsFloat() const { return g * (1.0f / 255.0f); }
	inline float getBlueAsFloat() const { return b * (1.0f / 255.0f); }
	inline float getAlphaAsFloat() const { return a * (1.0f / 255.0f); }

	inline void setRed(float newRed) { r = round<uint8>(newRed * 255.0f); }
	inline void setGreen(float newGreen) { g = round<uint8>(newGreen * 255.0f); }
	inline void setBlue(float newBlue) { b = round<uint8>(newBlue * 255.0f); }
	inline void setAlpha(float newAlpha) { a = round<uint8>(newAlpha * 255.0f); }

	inline void set(uint8 newRed, uint8 newGreen, uint8 newBlue, uint8 newAlpha = 255)
	{
		r = newRed;
		g = newGreen;
		b = newBlue;
		a = newAlpha;
	}

	inline void set(float newRed, float newGreen, float newBlue, float newAlpha = 1.0f)
	{
		setRed(newRed);
		setGreen(newGreen);
		setBlue(newBlue);
		setAlpha(newAlpha);
	}

	inline void set(const uint8 newComponents[4])
	{
		components[0] = newComponents[0];
		components[1] = newComponents[1];
		components[2] = newComponents[2];
		components[3] = newComponents[3];
	}

	inline void set(const float newComponents[4])
	{
		setRed(newComponents[0]);
		setGreen(newComponents[1]);
		setBlue(newComponents[2]);
		setAlpha(newComponents[3]);
	}


	inline void swapRedBlue()
	{
		swap(r, b);
	}

	inline void swapComponentOrder()
	{
		swap(r, a);
		swap(g, b);
	}

};



inline bool operator ==(const ByteColor& left, const ByteColor& right)
{
	return
		left.r == right.r &&
		left.g == right.g &&
		left.b == right.b &&
		left.a == right.a;
}



inline bool operator !=(const ByteColor& left, const ByteColor& right)
{
	return !(left == right);
}



} // namespace Graphics
} // namespace BaseLib



#endif // #ifndef BaseLib_Graphics_ByteColor_h