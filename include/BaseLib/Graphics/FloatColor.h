/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Graphics_FloatColor_h
#define BaseLib_Graphics_FloatColor_h



#include "BaseLib/Graphics/Colors.h"
#include "BaseLib/Graphics/PixelFormat.h"
#include "BaseLib/Strings/String.h"
#include "BaseLib/Utilities/BitManipulation.h"
#include "BaseLib/Math/Common.h"



namespace BaseLib {
namespace Graphics {



using BaseLib::Strings::String;
using namespace BaseLib::Math;



struct ByteColor;



struct BL_EXPORT FloatColor {

	static const PixelFormat PIXEL_FORMAT;

	union {
		struct {
			float r;
			float g;
			float b;
			float a;
		};
		float components[4];
	};

	FloatColor()
	#ifdef DEBUG_INIT
	  : r(-1)
	  , g(-1)
	  , b(-1)
	  , a(-1)
	#endif
	{
	}

	FloatColor(float newRed, float newGreen, float newBlue, float newAlpha = 1.0f)
	  : r(newRed)
	  , g(newGreen)
	  , b(newBlue)
	  , a(newAlpha)
	{
	}

	FloatColor(uint8 newRed, uint8 newGreen, uint8 newBlue, uint8 newAlpha = 255)
	{
		set(newRed, newGreen, newBlue, newAlpha);
	}

	FloatColor(const ByteColor& byteColor)
	{
		operator=(byteColor);
	}

	FloatColor& operator =(const ByteColor& right);

	FloatColor(const String& colorString)
	{
		operator=(colorString);
	}

	FloatColor& operator =(const String& right);

	inline FloatColor& operator *=(float value)
	{
		r *= value;
		g *= value;
		b *= value;
		a *= value;
		return *this;
	}

	inline FloatColor& operator /=(float value)
	{
		value = 1.0f / value;
		r *= value;
		g *= value;
		b *= value;
		a *= value;
		return *this;
	}

	inline FloatColor& operator +=(float value)
	{
		r += value;
		g += value;
		b += value;
		a += value;
		return *this;
	}

	inline FloatColor& operator -=(float value)
	{
		r -= value;
		g -= value;
		b -= value;
		a -= value;
		return *this;
	}

	inline FloatColor& operator *=(const FloatColor& right)
	{
		r *= right.r;
		g *= right.g;
		b *= right.b;
		a *= right.a;
		return *this;
	}

	inline FloatColor& operator /=(const FloatColor& right)
	{
		r /= right.r;
		g /= right.g;
		b /= right.b;
		a /= right.a;
		return *this;
	}

	inline FloatColor& operator +=(const FloatColor& right)
	{
		r += right.r;
		g += right.g;
		b += right.b;
		a += right.a;
		return *this;
	}

	inline FloatColor& operator -=(const FloatColor& right)
	{
		r -= right.r;
		g -= right.g;
		b -= right.b;
		a -= right.a;
		return *this;
	}

	operator String() const;

	struct Addition {
		const FloatColor& left;
		const FloatColor& right;
		inline explicit Addition(const FloatColor& l, const FloatColor& r)
		  : left(l)
		  , right(r)
		{
		}
	};

	struct Subtraction {
		const FloatColor& left;
		const FloatColor& right;
		inline explicit Subtraction(const FloatColor& l, const FloatColor& r)
		  : left(l)
		  , right(r)
		{
		}
	};

	FloatColor(const Addition& other)
	{
		operator =(other);
	}

	FloatColor(const Subtraction& other)
	{
		operator =(other);
	}

	inline FloatColor& operator =(const Addition& right)
	{
		r = right.left.r + right.right.r;
		g = right.left.g + right.right.g;
		b = right.left.b + right.right.b;
		a = right.left.a + right.right.a;
		return *this;
	}

	inline FloatColor& operator =(const Subtraction& right)
	{
		r = right.left.r - right.right.r;
		g = right.left.g - right.right.g;
		b = right.left.b - right.right.b;
		a = right.left.a - right.right.a;
		return *this;
	}


    inline FloatColor(Aliceblue) { aliceblue(); }
    inline FloatColor(Antiquewhite) { antiquewhite(); }
    inline FloatColor(Aqua) { aqua(); }
    inline FloatColor(Aquamarine) { aquamarine(); }
    inline FloatColor(Azure) { azure(); }
    inline FloatColor(Beige) { beige(); }
    inline FloatColor(Bisque) { bisque(); }
    inline FloatColor(Black) { black(); }
    inline FloatColor(Blanchedalmond) { blanchedalmond(); }
    inline FloatColor(Blue) { blue(); }
    inline FloatColor(Blueviolet) { blueviolet(); }
    inline FloatColor(Brown) { brown(); }
    inline FloatColor(Burlywood) { burlywood(); }
    inline FloatColor(Cadetblue) { cadetblue(); }
    inline FloatColor(Chartreuse) { chartreuse(); }
    inline FloatColor(Chocolate) { chocolate(); }
    inline FloatColor(Coral) { coral(); }
    inline FloatColor(Cornflowerblue) { cornflowerblue(); }
    inline FloatColor(Cornsilk) { cornsilk(); }
    inline FloatColor(Crimson) { crimson(); }
    inline FloatColor(Cyan) { cyan(); }
    inline FloatColor(Darkblue) { darkblue(); }
    inline FloatColor(Darkcyan) { darkcyan(); }
    inline FloatColor(Darkgoldenrod) { darkgoldenrod(); }
    inline FloatColor(Darkgray) { darkgray(); }
    inline FloatColor(Darkgreen) { darkgreen(); }
    inline FloatColor(Darkgrey) { darkgrey(); }
    inline FloatColor(Darkkhaki) { darkkhaki(); }
    inline FloatColor(Darkmagenta) { darkmagenta(); }
    inline FloatColor(Darkolivegreen) { darkolivegreen(); }
    inline FloatColor(Darkorange) { darkorange(); }
    inline FloatColor(Darkorchid) { darkorchid(); }
    inline FloatColor(Darkred) { darkred(); }
    inline FloatColor(Darksalmon) { darksalmon(); }
    inline FloatColor(Darkseagreen) { darkseagreen(); }
    inline FloatColor(Darkslateblue) { darkslateblue(); }
    inline FloatColor(Darkslategray) { darkslategray(); }
    inline FloatColor(Darkslategrey) { darkslategrey(); }
    inline FloatColor(Darkturquoise) { darkturquoise(); }
    inline FloatColor(Darkviolet) { darkviolet(); }
    inline FloatColor(Deeppink) { deeppink(); }
    inline FloatColor(Deepskyblue) { deepskyblue(); }
    inline FloatColor(Dimgray) { dimgray(); }
    inline FloatColor(Dimgrey) { dimgrey(); }
    inline FloatColor(Dodgerblue) { dodgerblue(); }
    inline FloatColor(Firebrick) { firebrick(); }
    inline FloatColor(Floralwhite) { floralwhite(); }
    inline FloatColor(Forestgreen) { forestgreen(); }
    inline FloatColor(Fuchsia) { fuchsia(); }
    inline FloatColor(Gainsboro) { gainsboro(); }
    inline FloatColor(Ghostwhite) { ghostwhite(); }
    inline FloatColor(Gold) { gold(); }
    inline FloatColor(Goldenrod) { goldenrod(); }
    inline FloatColor(Gray) { gray(); }
    inline FloatColor(Grey) { grey(); }
    inline FloatColor(Green) { green(); }
    inline FloatColor(Greenyellow) { greenyellow(); }
    inline FloatColor(Honeydew) { honeydew(); }
    inline FloatColor(Hotpink) { hotpink(); }
    inline FloatColor(Indianred) { indianred(); }
    inline FloatColor(Indigo) { indigo(); }
    inline FloatColor(Ivory) { ivory(); }
    inline FloatColor(Khaki) { khaki(); }
    inline FloatColor(Lavender) { lavender(); }
    inline FloatColor(Lavenderblush) { lavenderblush(); }
    inline FloatColor(Lawngreen) { lawngreen(); }
    inline FloatColor(Lemonchiffon) { lemonchiffon(); }
    inline FloatColor(Lightblue) { lightblue(); }
    inline FloatColor(Lightcoral) { lightcoral(); }
    inline FloatColor(Lightcyan) { lightcyan(); }
    inline FloatColor(Lightgoldenrodyellow) { lightgoldenrodyellow(); }
    inline FloatColor(Lightgray) { lightgray(); }
    inline FloatColor(Lightgreen) { lightgreen(); }
    inline FloatColor(Lightgrey) { lightgrey(); }
    inline FloatColor(Lightpink) { lightpink(); }
    inline FloatColor(Lightsalmon) { lightsalmon(); }
    inline FloatColor(Lightseagreen) { lightseagreen(); }
    inline FloatColor(Lightskyblue) { lightskyblue(); }
    inline FloatColor(Lightslategray) { lightslategray(); }
    inline FloatColor(Lightslategrey) { lightslategrey(); }
    inline FloatColor(Lightsteelblue) { lightsteelblue(); }
    inline FloatColor(Lightyellow) { lightyellow(); }
    inline FloatColor(Lime) { lime(); }
    inline FloatColor(Limegreen) { limegreen(); }
    inline FloatColor(Linen) { linen(); }
    inline FloatColor(Magenta) { magenta(); }
    inline FloatColor(Maroon) { maroon(); }
    inline FloatColor(Mediumaquamarine) { mediumaquamarine(); }
    inline FloatColor(Mediumblue) { mediumblue(); }
    inline FloatColor(Mediumorchid) { mediumorchid(); }
    inline FloatColor(Mediumpurple) { mediumpurple(); }
    inline FloatColor(Mediumseagreen) { mediumseagreen(); }
    inline FloatColor(Mediumslateblue) { mediumslateblue(); }
    inline FloatColor(Mediumspringgreen) { mediumspringgreen(); }
    inline FloatColor(Mediumturquoise) { mediumturquoise(); }
    inline FloatColor(Mediumvioletred) { mediumvioletred(); }
    inline FloatColor(Midnightblue) { midnightblue(); }
    inline FloatColor(Mintcream) { mintcream(); }
    inline FloatColor(Mistyrose) { mistyrose(); }
    inline FloatColor(Moccasin) { moccasin(); }
    inline FloatColor(Navajowhite) { navajowhite(); }
    inline FloatColor(Navy) { navy(); }
    inline FloatColor(Oldlace) { oldlace(); }
    inline FloatColor(Olive) { olive(); }
    inline FloatColor(Olivedrab) { olivedrab(); }
    inline FloatColor(Orange) { orange(); }
    inline FloatColor(Orangered) { orangered(); }
    inline FloatColor(Orchid) { orchid(); }
    inline FloatColor(Palegoldenrod) { palegoldenrod(); }
    inline FloatColor(Palegreen) { palegreen(); }
    inline FloatColor(Paleturquoise) { paleturquoise(); }
    inline FloatColor(Palevioletred) { palevioletred(); }
    inline FloatColor(Papayawhip) { papayawhip(); }
    inline FloatColor(Peachpuff) { peachpuff(); }
    inline FloatColor(Peru) { peru(); }
    inline FloatColor(Pink) { pink(); }
    inline FloatColor(Plum) { plum(); }
    inline FloatColor(Powderblue) { powderblue(); }
    inline FloatColor(Purple) { purple(); }
    inline FloatColor(Red) { red(); }
    inline FloatColor(Rosybrown) { rosybrown(); }
    inline FloatColor(Royalblue) { royalblue(); }
    inline FloatColor(Saddlebrown) { saddlebrown(); }
    inline FloatColor(Salmon) { salmon(); }
    inline FloatColor(Sandybrown) { sandybrown(); }
    inline FloatColor(Seagreen) { seagreen(); }
    inline FloatColor(Seashell) { seashell(); }
    inline FloatColor(Sienna) { sienna(); }
    inline FloatColor(Silver) { silver(); }
    inline FloatColor(Skyblue) { skyblue(); }
    inline FloatColor(Slateblue) { slateblue(); }
    inline FloatColor(Slategray) { slategray(); }
    inline FloatColor(Slategrey) { slategrey(); }
    inline FloatColor(Snow) { snow(); }
    inline FloatColor(Springgreen) { springgreen(); }
    inline FloatColor(Steelblue) { steelblue(); }
    inline FloatColor(Tan) { tan(); }
    inline FloatColor(Teal) { teal(); }
    inline FloatColor(Thistle) { thistle(); }
    inline FloatColor(Tomato) { tomato(); }
    inline FloatColor(Turquoise) { turquoise(); }
    inline FloatColor(Violet) { violet(); }
    inline FloatColor(Wheat) { wheat(); }
    inline FloatColor(White) { white(); }
    inline FloatColor(Whitesmoke) { whitesmoke(); }
    inline FloatColor(Yellow) { yellow(); }
    inline FloatColor(Yellowgreen) { yellowgreen(); }

    inline FloatColor& operator=(Aliceblue) { return aliceblue(); }
    inline FloatColor& operator=(Antiquewhite) { return antiquewhite(); }
    inline FloatColor& operator=(Aqua) { return aqua(); }
    inline FloatColor& operator=(Aquamarine) { return aquamarine(); }
    inline FloatColor& operator=(Azure) { return azure(); }
    inline FloatColor& operator=(Beige) { return beige(); }
    inline FloatColor& operator=(Bisque) { return bisque(); }
    inline FloatColor& operator=(Black) { return black(); }
    inline FloatColor& operator=(Blanchedalmond) { return blanchedalmond(); }
    inline FloatColor& operator=(Blue) { return blue(); }
    inline FloatColor& operator=(Blueviolet) { return blueviolet(); }
    inline FloatColor& operator=(Brown) { return brown(); }
    inline FloatColor& operator=(Burlywood) { return burlywood(); }
    inline FloatColor& operator=(Cadetblue) { return cadetblue(); }
    inline FloatColor& operator=(Chartreuse) { return chartreuse(); }
    inline FloatColor& operator=(Chocolate) { return chocolate(); }
    inline FloatColor& operator=(Coral) { return coral(); }
    inline FloatColor& operator=(Cornflowerblue) { return cornflowerblue(); }
    inline FloatColor& operator=(Cornsilk) { return cornsilk(); }
    inline FloatColor& operator=(Crimson) { return crimson(); }
    inline FloatColor& operator=(Cyan) { return cyan(); }
    inline FloatColor& operator=(Darkblue) { return darkblue(); }
    inline FloatColor& operator=(Darkcyan) { return darkcyan(); }
    inline FloatColor& operator=(Darkgoldenrod) { return darkgoldenrod(); }
    inline FloatColor& operator=(Darkgray) { return darkgray(); }
    inline FloatColor& operator=(Darkgreen) { return darkgreen(); }
    inline FloatColor& operator=(Darkgrey) { return darkgrey(); }
    inline FloatColor& operator=(Darkkhaki) { return darkkhaki(); }
    inline FloatColor& operator=(Darkmagenta) { return darkmagenta(); }
    inline FloatColor& operator=(Darkolivegreen) { return darkolivegreen(); }
    inline FloatColor& operator=(Darkorange) { return darkorange(); }
    inline FloatColor& operator=(Darkorchid) { return darkorchid(); }
    inline FloatColor& operator=(Darkred) { return darkred(); }
    inline FloatColor& operator=(Darksalmon) { return darksalmon(); }
    inline FloatColor& operator=(Darkseagreen) { return darkseagreen(); }
    inline FloatColor& operator=(Darkslateblue) { return darkslateblue(); }
    inline FloatColor& operator=(Darkslategray) { return darkslategray(); }
    inline FloatColor& operator=(Darkslategrey) { return darkslategrey(); }
    inline FloatColor& operator=(Darkturquoise) { return darkturquoise(); }
    inline FloatColor& operator=(Darkviolet) { return darkviolet(); }
    inline FloatColor& operator=(Deeppink) { return deeppink(); }
    inline FloatColor& operator=(Deepskyblue) { return deepskyblue(); }
    inline FloatColor& operator=(Dimgray) { return dimgray(); }
    inline FloatColor& operator=(Dimgrey) { return dimgrey(); }
    inline FloatColor& operator=(Dodgerblue) { return dodgerblue(); }
    inline FloatColor& operator=(Firebrick) { return firebrick(); }
    inline FloatColor& operator=(Floralwhite) { return floralwhite(); }
    inline FloatColor& operator=(Forestgreen) { return forestgreen(); }
    inline FloatColor& operator=(Fuchsia) { return fuchsia(); }
    inline FloatColor& operator=(Gainsboro) { return gainsboro(); }
    inline FloatColor& operator=(Ghostwhite) { return ghostwhite(); }
    inline FloatColor& operator=(Gold) { return gold(); }
    inline FloatColor& operator=(Goldenrod) { return goldenrod(); }
    inline FloatColor& operator=(Gray) { return gray(); }
    inline FloatColor& operator=(Grey) { return grey(); }
    inline FloatColor& operator=(Green) { return green(); }
    inline FloatColor& operator=(Greenyellow) { return greenyellow(); }
    inline FloatColor& operator=(Honeydew) { return honeydew(); }
    inline FloatColor& operator=(Hotpink) { return hotpink(); }
    inline FloatColor& operator=(Indianred) { return indianred(); }
    inline FloatColor& operator=(Indigo) { return indigo(); }
    inline FloatColor& operator=(Ivory) { return ivory(); }
    inline FloatColor& operator=(Khaki) { return khaki(); }
    inline FloatColor& operator=(Lavender) { return lavender(); }
    inline FloatColor& operator=(Lavenderblush) { return lavenderblush(); }
    inline FloatColor& operator=(Lawngreen) { return lawngreen(); }
    inline FloatColor& operator=(Lemonchiffon) { return lemonchiffon(); }
    inline FloatColor& operator=(Lightblue) { return lightblue(); }
    inline FloatColor& operator=(Lightcoral) { return lightcoral(); }
    inline FloatColor& operator=(Lightcyan) { return lightcyan(); }
    inline FloatColor& operator=(Lightgoldenrodyellow) { return lightgoldenrodyellow(); }
    inline FloatColor& operator=(Lightgray) { return lightgray(); }
    inline FloatColor& operator=(Lightgreen) { return lightgreen(); }
    inline FloatColor& operator=(Lightgrey) { return lightgrey(); }
    inline FloatColor& operator=(Lightpink) { return lightpink(); }
    inline FloatColor& operator=(Lightsalmon) { return lightsalmon(); }
    inline FloatColor& operator=(Lightseagreen) { return lightseagreen(); }
    inline FloatColor& operator=(Lightskyblue) { return lightskyblue(); }
    inline FloatColor& operator=(Lightslategray) { return lightslategray(); }
    inline FloatColor& operator=(Lightslategrey) { return lightslategrey(); }
    inline FloatColor& operator=(Lightsteelblue) { return lightsteelblue(); }
    inline FloatColor& operator=(Lightyellow) { return lightyellow(); }
    inline FloatColor& operator=(Lime) { return lime(); }
    inline FloatColor& operator=(Limegreen) { return limegreen(); }
    inline FloatColor& operator=(Linen) { return linen(); }
    inline FloatColor& operator=(Magenta) { return magenta(); }
    inline FloatColor& operator=(Maroon) { return maroon(); }
    inline FloatColor& operator=(Mediumaquamarine) { return mediumaquamarine(); }
    inline FloatColor& operator=(Mediumblue) { return mediumblue(); }
    inline FloatColor& operator=(Mediumorchid) { return mediumorchid(); }
    inline FloatColor& operator=(Mediumpurple) { return mediumpurple(); }
    inline FloatColor& operator=(Mediumseagreen) { return mediumseagreen(); }
    inline FloatColor& operator=(Mediumslateblue) { return mediumslateblue(); }
    inline FloatColor& operator=(Mediumspringgreen) { return mediumspringgreen(); }
    inline FloatColor& operator=(Mediumturquoise) { return mediumturquoise(); }
    inline FloatColor& operator=(Mediumvioletred) { return mediumvioletred(); }
    inline FloatColor& operator=(Midnightblue) { return midnightblue(); }
    inline FloatColor& operator=(Mintcream) { return mintcream(); }
    inline FloatColor& operator=(Mistyrose) { return mistyrose(); }
    inline FloatColor& operator=(Moccasin) { return moccasin(); }
    inline FloatColor& operator=(Navajowhite) { return navajowhite(); }
    inline FloatColor& operator=(Navy) { return navy(); }
    inline FloatColor& operator=(Oldlace) { return oldlace(); }
    inline FloatColor& operator=(Olive) { return olive(); }
    inline FloatColor& operator=(Olivedrab) { return olivedrab(); }
    inline FloatColor& operator=(Orange) { return orange(); }
    inline FloatColor& operator=(Orangered) { return orangered(); }
    inline FloatColor& operator=(Orchid) { return orchid(); }
    inline FloatColor& operator=(Palegoldenrod) { return palegoldenrod(); }
    inline FloatColor& operator=(Palegreen) { return palegreen(); }
    inline FloatColor& operator=(Paleturquoise) { return paleturquoise(); }
    inline FloatColor& operator=(Palevioletred) { return palevioletred(); }
    inline FloatColor& operator=(Papayawhip) { return papayawhip(); }
    inline FloatColor& operator=(Peachpuff) { return peachpuff(); }
    inline FloatColor& operator=(Peru) { return peru(); }
    inline FloatColor& operator=(Pink) { return pink(); }
    inline FloatColor& operator=(Plum) { return plum(); }
    inline FloatColor& operator=(Powderblue) { return powderblue(); }
    inline FloatColor& operator=(Purple) { return purple(); }
    inline FloatColor& operator=(Red) { return red(); }
    inline FloatColor& operator=(Rosybrown) { return rosybrown(); }
    inline FloatColor& operator=(Royalblue) { return royalblue(); }
    inline FloatColor& operator=(Saddlebrown) { return saddlebrown(); }
    inline FloatColor& operator=(Salmon) { return salmon(); }
    inline FloatColor& operator=(Sandybrown) { return sandybrown(); }
    inline FloatColor& operator=(Seagreen) { return seagreen(); }
    inline FloatColor& operator=(Seashell) { return seashell(); }
    inline FloatColor& operator=(Sienna) { return sienna(); }
    inline FloatColor& operator=(Silver) { return silver(); }
    inline FloatColor& operator=(Skyblue) { return skyblue(); }
    inline FloatColor& operator=(Slateblue) { return slateblue(); }
    inline FloatColor& operator=(Slategray) { return slategray(); }
    inline FloatColor& operator=(Slategrey) { return slategrey(); }
    inline FloatColor& operator=(Snow) { return snow(); }
    inline FloatColor& operator=(Springgreen) { return springgreen(); }
    inline FloatColor& operator=(Steelblue) { return steelblue(); }
    inline FloatColor& operator=(Tan) { return tan(); }
    inline FloatColor& operator=(Teal) { return teal(); }
    inline FloatColor& operator=(Thistle) { return thistle(); }
    inline FloatColor& operator=(Tomato) { return tomato(); }
    inline FloatColor& operator=(Turquoise) { return turquoise(); }
    inline FloatColor& operator=(Violet) { return violet(); }
    inline FloatColor& operator=(Wheat) { return wheat(); }
    inline FloatColor& operator=(White) { return white(); }
    inline FloatColor& operator=(Whitesmoke) { return whitesmoke(); }
    inline FloatColor& operator=(Yellow) { return yellow(); }
    inline FloatColor& operator=(Yellowgreen) { return yellowgreen(); }

	inline FloatColor& aliceblue() { r = 240/255.0f; g = 248/255.0f; b = 255/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& antiquewhite() { r = 250/255.0f; g = 235/255.0f; b = 215/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& aqua() { r = 0/255.0f; g = 255/255.0f; b = 255/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& aquamarine() { r = 127/255.0f; g = 255/255.0f; b = 212/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& azure() { r = 240/255.0f; g = 255/255.0f; b = 255/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& beige() { r = 245/255.0f; g = 245/255.0f; b = 220/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& bisque() { r = 255/255.0f; g = 228/255.0f; b = 196/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& black() { r = 0/255.0f; g = 0/255.0f; b = 0/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& blanchedalmond() { r = 255/255.0f; g = 235/255.0f; b = 205/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& blue() { r = 0/255.0f; g = 0/255.0f; b = 255/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& blueviolet() { r = 138/255.0f; g = 43/255.0f; b = 226/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& brown() { r = 165/255.0f; g = 42/255.0f; b = 42/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& burlywood() { r = 222/255.0f; g = 184/255.0f; b = 135/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& cadetblue() { r = 95/255.0f; g = 158/255.0f; b = 160/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& chartreuse() { r = 127/255.0f; g = 255/255.0f; b = 0/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& chocolate() { r = 210/255.0f; g = 105/255.0f; b = 30/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& coral() { r = 255/255.0f; g = 127/255.0f; b = 80/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& cornflowerblue() { r = 100/255.0f; g = 149/255.0f; b = 237/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& cornsilk() { r = 255/255.0f; g = 248/255.0f; b = 220/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& crimson() { r = 220/255.0f; g = 20/255.0f; b = 60/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& cyan() { r = 0/255.0f; g = 255/255.0f; b = 255/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& darkblue() { r = 0/255.0f; g = 0/255.0f; b = 139/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& darkcyan() { r = 0/255.0f; g = 139/255.0f; b = 139/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& darkgoldenrod() { r = 184/255.0f; g = 134/255.0f; b = 11/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& darkgray() { r = 169/255.0f; g = 169/255.0f; b = 169/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& darkgreen() { r = 0/255.0f; g = 100/255.0f; b = 0/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& darkgrey() { r = 169/255.0f; g = 169/255.0f; b = 169/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& darkkhaki() { r = 189/255.0f; g = 183/255.0f; b = 107/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& darkmagenta() { r = 139/255.0f; g = 0/255.0f; b = 139/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& darkolivegreen() { r = 85/255.0f; g = 107/255.0f; b = 47/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& darkorange() { r = 255/255.0f; g = 140/255.0f; b = 0/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& darkorchid() { r = 153/255.0f; g = 50/255.0f; b = 204/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& darkred() { r = 139/255.0f; g = 0/255.0f; b = 0/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& darksalmon() { r = 233/255.0f; g = 150/255.0f; b = 122/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& darkseagreen() { r = 143/255.0f; g = 188/255.0f; b = 143/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& darkslateblue() { r = 72/255.0f; g = 61/255.0f; b = 139/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& darkslategray() { r = 47/255.0f; g = 79/255.0f; b = 79/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& darkslategrey() { r = 47/255.0f; g = 79/255.0f; b = 79/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& darkturquoise() { r = 0/255.0f; g = 206/255.0f; b = 209/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& darkviolet() { r = 148/255.0f; g = 0/255.0f; b = 211/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& deeppink() { r = 255/255.0f; g = 20/255.0f; b = 147/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& deepskyblue() { r = 0/255.0f; g = 191/255.0f; b = 255/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& dimgray() { r = 105/255.0f; g = 105/255.0f; b = 105/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& dimgrey() { r = 105/255.0f; g = 105/255.0f; b = 105/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& dodgerblue() { r = 30/255.0f; g = 144/255.0f; b = 255/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& firebrick() { r = 178/255.0f; g = 34/255.0f; b = 34/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& floralwhite() { r = 255/255.0f; g = 250/255.0f; b = 240/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& forestgreen() { r = 34/255.0f; g = 139/255.0f; b = 34/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& fuchsia() { r = 255/255.0f; g = 0/255.0f; b = 255/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& gainsboro() { r = 220/255.0f; g = 220/255.0f; b = 220/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& ghostwhite() { r = 248/255.0f; g = 248/255.0f; b = 255/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& gold() { r = 255/255.0f; g = 215/255.0f; b = 0/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& goldenrod() { r = 218/255.0f; g = 165/255.0f; b = 32/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& gray() { r = 128/255.0f; g = 128/255.0f; b = 128/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& grey() { r = 128/255.0f; g = 128/255.0f; b = 128/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& green() { r = 0/255.0f; g = 128/255.0f; b = 0/255.0f; a = 255/255.0f; return *this; }
	inline FloatColor& greenyellow() { r = 173/255.0f; g = 255/255.0f; b = 47/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& honeydew() { r = 240/255.0f; g = 255/255.0f; b = 240/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& hotpink() { r = 255/255.0f; g = 105/255.0f; b = 180/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& indianred() { r = 205/255.0f; g = 92/255.0f; b = 92/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& indigo() { r = 75/255.0f; g = 0/255.0f; b = 130/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& ivory() { r = 255/255.0f; g = 255/255.0f; b = 240/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& khaki() { r = 240/255.0f; g = 230/255.0f; b = 140/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& lavender() { r = 230/255.0f; g =230/255.0f; b = 250/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& lavenderblush() { r = 255/255.0f; g = 240/255.0f; b = 245/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& lawngreen() { r = 124/255.0f; g = 252/255.0f; b = 0/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& lemonchiffon() { r = 255/255.0f; g = 250/255.0f; b = 205/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& lightblue() { r = 173/255.0f; g = 216/255.0f; b = 230/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& lightcoral() { r = 240/255.0f; g = 128/255.0f; b = 128/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& lightcyan() { r = 224/255.0f; g = 255/255.0f; b = 255/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& lightgoldenrodyellow() { r = 250/255.0f; g = 250/255.0f; b = 210/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& lightgray() { r = 211/255.0f; g = 211/255.0f; b = 211/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& lightgreen() { r = 144/255.0f; g = 238/255.0f; b = 144/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& lightgrey() { r = 211/255.0f; g = 211/255.0f; b = 211/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& lightpink() { r = 255/255.0f; g = 182/255.0f; b = 193/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& lightsalmon() { r = 255/255.0f; g = 160/255.0f; b = 122/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& lightseagreen() { r = 32/255.0f; g = 178/255.0f; b = 170/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& lightskyblue() { r = 135/255.0f; g = 206/255.0f; b = 250/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& lightslategray() { r = 119/255.0f; g = 136/255.0f; b = 153/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& lightslategrey() { r = 119/255.0f; g = 136/255.0f; b = 153/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& lightsteelblue() { r = 176/255.0f; g = 196/255.0f; b = 222/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& lightyellow() { r = 255/255.0f; g = 255/255.0f; b = 224/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& lime() { r = 0/255.0f; g = 255/255.0f; b = 0/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& limegreen() { r = 50/255.0f; g = 205/255.0f; b = 50/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& linen() { r = 250/255.0f; g = 240/255.0f; b = 230/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& magenta() { r = 255/255.0f; g = 0/255.0f; b = 255/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& maroon() { r = 128/255.0f; g = 0/255.0f; b = 0/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& mediumaquamarine() { r = 102/255.0f; g = 205/255.0f; b = 170/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& mediumblue() { r = 0/255.0f; g = 0/255.0f; b = 205/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& mediumorchid() { r = 186/255.0f; g = 85/255.0f; b = 211/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& mediumpurple() { r = 147/255.0f; g = 112/255.0f; b = 219/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& mediumseagreen() { r = 60/255.0f; g = 179/255.0f; b = 113/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& mediumslateblue() { r = 123/255.0f; g = 104/255.0f; b = 238/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& mediumspringgreen() { r = 0/255.0f; g = 250/255.0f; b = 154/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& mediumturquoise() { r = 72/255.0f; g = 209/255.0f; b = 204/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& mediumvioletred() { r = 199/255.0f; g = 21/255.0f; b = 133/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& midnightblue() { r = 25/255.0f; g = 25/255.0f; b = 112/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& mintcream() { r = 245/255.0f; g = 255/255.0f; b = 250/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& mistyrose() { r = 255/255.0f; g = 228/255.0f; b = 225/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& moccasin() { r = 255/255.0f; g = 228/255.0f; b = 181/255.0f; a = 255/255.0f; return *this; }
	inline FloatColor& navajowhite() { r = 255/255.0f; g = 222/255.0f; b = 173/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& navy() { r = 0/255.0f; g = 0/255.0f; b = 128/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& oldlace() { r = 253/255.0f; g = 245/255.0f; b = 230/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& olive() { r = 128/255.0f; g = 128/255.0f; b = 0/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& olivedrab() { r = 107/255.0f; g = 142/255.0f; b = 35/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& orange() { r = 255/255.0f; g = 165/255.0f; b = 0/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& orangered() { r = 255/255.0f; g = 69/255.0f; b = 0/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& orchid() { r = 218/255.0f; g = 112/255.0f; b = 214/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& palegoldenrod() { r = 238/255.0f; g = 232/255.0f; b = 170/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& palegreen() { r = 152/255.0f; g = 251/255.0f; b = 152/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& paleturquoise() { r = 175/255.0f; g = 238/255.0f; b = 238/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& palevioletred() { r = 219/255.0f; g = 112/255.0f; b = 147/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& papayawhip() { r = 255/255.0f; g = 239/255.0f; b = 213/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& peachpuff() { r = 255/255.0f; g = 218/255.0f; b = 185/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& peru() { r = 205/255.0f; g = 133/255.0f; b = 63/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& pink() { r = 255/255.0f; g = 192/255.0f; b = 203/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& plum() { r = 221/255.0f; g = 160/255.0f; b = 221/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& powderblue() { r = 176/255.0f; g = 224/255.0f; b = 230/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& purple() { r = 128/255.0f; g = 0/255.0f; b = 128/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& red() { r = 255/255.0f; g = 0/255.0f; b = 0/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& rosybrown() { r = 188/255.0f; g = 143/255.0f; b = 143/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& royalblue() { r = 65/255.0f; g = 105/255.0f; b = 225/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& saddlebrown() { r = 139/255.0f; g = 69/255.0f; b = 19/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& salmon() { r = 250/255.0f; g = 128/255.0f; b = 114/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& sandybrown() { r = 244/255.0f; g = 164/255.0f; b = 96/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& seagreen() { r = 46/255.0f; g = 139/255.0f; b = 87/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& seashell() { r = 255/255.0f; g = 245/255.0f; b = 238/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& sienna() { r = 160/255.0f; g = 82/255.0f; b = 45/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& silver() { r = 192/255.0f; g = 192/255.0f; b = 192/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& skyblue() { r = 135/255.0f; g = 206/255.0f; b = 235/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& slateblue() { r = 106/255.0f; g = 90/255.0f; b = 205/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& slategray() { r = 112/255.0f; g = 128/255.0f; b = 144/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& slategrey() { r = 112/255.0f; g = 128/255.0f; b = 144/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& snow() { r = 255/255.0f; g = 250/255.0f; b = 250/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& springgreen() { r = 0/255.0f; g = 255/255.0f; b = 127/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& steelblue() { r = 70/255.0f; g = 130/255.0f; b = 180/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& tan() { r = 210/255.0f; g = 180/255.0f; b = 140/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& teal() { r = 0/255.0f; g = 128/255.0f; b = 128/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& thistle() { r = 216/255.0f; g = 191/255.0f; b = 216/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& tomato() { r = 255/255.0f; g = 99/255.0f; b = 71/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& turquoise() { r = 64/255.0f; g = 224/255.0f; b = 208/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& violet() { r = 238/255.0f; g = 130/255.0f; b = 238/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& wheat() { r = 245/255.0f; g = 222/255.0f; b = 179/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& white() { r = 255/255.0f; g = 255/255.0f; b = 255/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& whitesmoke() { r = 245/255.0f; g = 245/255.0f; b = 245/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& yellow() { r = 255/255.0f; g = 255/255.0f; b = 0/255.0f; a = 255/255.0f; return *this; }
    inline FloatColor& yellowgreen() { r = 154/255.0f; g = 205/255.0f; b = 50/255.0f; a = 255/255.0f; return *this; }


	inline uint8 getRedAsByte() const { return round<uint8>(r * 255.0f); }
	inline uint8 getGreenAsByte() const { return round<uint8>(g * 255.0f); }
	inline uint8 getBlueAsByte() const { return round<uint8>(b * 255.0f); }
	inline uint8 getAlphaAsByte() const { return round<uint8>(a * 255.0f); }

	inline void setRed(uint8 newRed) { r = newRed * (1.0f / 255.0f); }
	inline void setGreen(uint8 newGreen) { g = newGreen * (1.0f / 255.0f); }
	inline void setBlue(uint8 newBlue) { b = newBlue * (1.0f / 255.0f); }
	inline void setAlpha(uint8 newAlpha) { a = newAlpha * (1.0f / 255.0f); }

	inline void set(uint8 newRed, uint8 newGreen, uint8 newBlue, uint8 newAlpha = 255)
	{
		setRed(newRed);
		setGreen(newGreen);
		setBlue(newBlue);
		setAlpha(newAlpha);
	}

	inline void set(float newRed, float newGreen, float newBlue, float newAlpha = 1.0f)
	{
		r = newRed;
		g = newGreen;
		b = newBlue;
		a = newAlpha;
	}

	inline void set(const uint8 newComponents[4])
	{
		setRed(newComponents[0]);
		setGreen(newComponents[1]);
		setBlue(newComponents[2]);
		setAlpha(newComponents[3]);
	}

	inline void set(const float newComponents[4])
	{
		components[0] = newComponents[0];
		components[1] = newComponents[1];
		components[2] = newComponents[2];
		components[3] = newComponents[3];
	}

	operator const ByteColor() const;

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



inline const FloatColor::Addition operator +(const FloatColor& left, const FloatColor& right)
{
	return FloatColor::Addition(left, right);
}



inline const FloatColor::Subtraction operator -(const FloatColor& left, const FloatColor& right)
{
	return FloatColor::Subtraction(left, right);
}



inline bool operator ==(const FloatColor& left, const FloatColor& right)
{
	return
		left.r == right.r &&
		left.g == right.g &&
		left.b == right.b &&
		left.a == right.a;
}



inline bool operator !=(const FloatColor& left, const FloatColor& right)
{
	return !(left == right);
}



} // namespace Graphics
} // namespace BaseLib



#endif // #ifndef BaseLib_Graphics_FloatColor_h