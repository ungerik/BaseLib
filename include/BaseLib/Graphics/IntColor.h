/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Graphics_IntColor_h
#define BaseLib_Graphics_IntColor_h



#include "BaseLib/Graphics/Colors.h"
#include "BaseLib/Strings/String.h"
#include "BaseLib/Utilities/BitManipulation.h"
#include "BaseLib/Math/Common.h"



namespace BaseLib {
namespace Graphics {



using BaseLib::Strings::String;



struct ByteColor;
struct FloatColor;



struct BL_EXPORT IntColor {
	union {
		struct {
			int r;
			int g;
			int b;
			int a;
		};
		int components[4];
	};

	IntColor()
	#ifdef DEBUG_INIT
	  : r(-1)
	  , g(-1)
	  , b(-1)
	  , a(-1)
	#endif
	{
	}

	IntColor(int newRed, int newGreen, int newBlue, int newAlpha = INT_MAX)
	  : r(newRed)
	  , g(newGreen)
	  , b(newBlue)
	  , a(newAlpha)
	{
	}

	IntColor(const ByteColor& byteColor)
	{
		operator=(byteColor);
	}

	IntColor& operator=(const ByteColor& right);

	IntColor(const FloatColor& floatColor)
	{
		operator=(floatColor);
	}

	IntColor& operator=(const FloatColor& right);

	IntColor(const String& colorString)
	{
		operator=(colorString);
	}

	IntColor& operator=(const String& right);
	operator String() const;

    inline IntColor(Aliceblue) { aliceblue(); }
    inline IntColor(Antiquewhite) { antiquewhite(); }
    inline IntColor(Aqua) { aqua(); }
    inline IntColor(Aquamarine) { aquamarine(); }
    inline IntColor(Azure) { azure(); }
    inline IntColor(Beige) { beige(); }
    inline IntColor(Bisque) { bisque(); }
    inline IntColor(Black) { black(); }
    inline IntColor(Blanchedalmond) { blanchedalmond(); }
    inline IntColor(Blue) { blue(); }
    inline IntColor(Blueviolet) { blueviolet(); }
    inline IntColor(Brown) { brown(); }
    inline IntColor(Burlywood) { burlywood(); }
    inline IntColor(Cadetblue) { cadetblue(); }
    inline IntColor(Chartreuse) { chartreuse(); }
    inline IntColor(Chocolate) { chocolate(); }
    inline IntColor(Coral) { coral(); }
    inline IntColor(Cornflowerblue) { cornflowerblue(); }
    inline IntColor(Cornsilk) { cornsilk(); }
    inline IntColor(Crimson) { crimson(); }
    inline IntColor(Cyan) { cyan(); }
    inline IntColor(Darkblue) { darkblue(); }
    inline IntColor(Darkcyan) { darkcyan(); }
    inline IntColor(Darkgoldenrod) { darkgoldenrod(); }
    inline IntColor(Darkgray) { darkgray(); }
    inline IntColor(Darkgreen) { darkgreen(); }
    inline IntColor(Darkgrey) { darkgrey(); }
    inline IntColor(Darkkhaki) { darkkhaki(); }
    inline IntColor(Darkmagenta) { darkmagenta(); }
    inline IntColor(Darkolivegreen) { darkolivegreen(); }
    inline IntColor(Darkorange) { darkorange(); }
    inline IntColor(Darkorchid) { darkorchid(); }
    inline IntColor(Darkred) { darkred(); }
    inline IntColor(Darksalmon) { darksalmon(); }
    inline IntColor(Darkseagreen) { darkseagreen(); }
    inline IntColor(Darkslateblue) { darkslateblue(); }
    inline IntColor(Darkslategray) { darkslategray(); }
    inline IntColor(Darkslategrey) { darkslategrey(); }
    inline IntColor(Darkturquoise) { darkturquoise(); }
    inline IntColor(Darkviolet) { darkviolet(); }
    inline IntColor(Deeppink) { deeppink(); }
    inline IntColor(Deepskyblue) { deepskyblue(); }
    inline IntColor(Dimgray) { dimgray(); }
    inline IntColor(Dimgrey) { dimgrey(); }
    inline IntColor(Dodgerblue) { dodgerblue(); }
    inline IntColor(Firebrick) { firebrick(); }
    inline IntColor(Floralwhite) { floralwhite(); }
    inline IntColor(Forestgreen) { forestgreen(); }
    inline IntColor(Fuchsia) { fuchsia(); }
    inline IntColor(Gainsboro) { gainsboro(); }
    inline IntColor(Ghostwhite) { ghostwhite(); }
    inline IntColor(Gold) { gold(); }
    inline IntColor(Goldenrod) { goldenrod(); }
    inline IntColor(Gray) { gray(); }
    inline IntColor(Grey) { grey(); }
    inline IntColor(Green) { green(); }
    inline IntColor(Greenyellow) { greenyellow(); }
    inline IntColor(Honeydew) { honeydew(); }
    inline IntColor(Hotpink) { hotpink(); }
    inline IntColor(Indianred) { indianred(); }
    inline IntColor(Indigo) { indigo(); }
    inline IntColor(Ivory) { ivory(); }
    inline IntColor(Khaki) { khaki(); }
    inline IntColor(Lavender) { lavender(); }
    inline IntColor(Lavenderblush) { lavenderblush(); }
    inline IntColor(Lawngreen) { lawngreen(); }
    inline IntColor(Lemonchiffon) { lemonchiffon(); }
    inline IntColor(Lightblue) { lightblue(); }
    inline IntColor(Lightcoral) { lightcoral(); }
    inline IntColor(Lightcyan) { lightcyan(); }
    inline IntColor(Lightgoldenrodyellow) { lightgoldenrodyellow(); }
    inline IntColor(Lightgray) { lightgray(); }
    inline IntColor(Lightgreen) { lightgreen(); }
    inline IntColor(Lightgrey) { lightgrey(); }
    inline IntColor(Lightpink) { lightpink(); }
    inline IntColor(Lightsalmon) { lightsalmon(); }
    inline IntColor(Lightseagreen) { lightseagreen(); }
    inline IntColor(Lightskyblue) { lightskyblue(); }
    inline IntColor(Lightslategray) { lightslategray(); }
    inline IntColor(Lightslategrey) { lightslategrey(); }
    inline IntColor(Lightsteelblue) { lightsteelblue(); }
    inline IntColor(Lightyellow) { lightyellow(); }
    inline IntColor(Lime) { lime(); }
    inline IntColor(Limegreen) { limegreen(); }
    inline IntColor(Linen) { linen(); }
    inline IntColor(Magenta) { magenta(); }
    inline IntColor(Maroon) { maroon(); }
    inline IntColor(Mediumaquamarine) { mediumaquamarine(); }
    inline IntColor(Mediumblue) { mediumblue(); }
    inline IntColor(Mediumorchid) { mediumorchid(); }
    inline IntColor(Mediumpurple) { mediumpurple(); }
    inline IntColor(Mediumseagreen) { mediumseagreen(); }
    inline IntColor(Mediumslateblue) { mediumslateblue(); }
    inline IntColor(Mediumspringgreen) { mediumspringgreen(); }
    inline IntColor(Mediumturquoise) { mediumturquoise(); }
    inline IntColor(Mediumvioletred) { mediumvioletred(); }
    inline IntColor(Midnightblue) { midnightblue(); }
    inline IntColor(Mintcream) { mintcream(); }
    inline IntColor(Mistyrose) { mistyrose(); }
    inline IntColor(Moccasin) { moccasin(); }
    inline IntColor(Navajowhite) { navajowhite(); }
    inline IntColor(Navy) { navy(); }
    inline IntColor(Oldlace) { oldlace(); }
    inline IntColor(Olive) { olive(); }
    inline IntColor(Olivedrab) { olivedrab(); }
    inline IntColor(Orange) { orange(); }
    inline IntColor(Orangered) { orangered(); }
    inline IntColor(Orchid) { orchid(); }
    inline IntColor(Palegoldenrod) { palegoldenrod(); }
    inline IntColor(Palegreen) { palegreen(); }
    inline IntColor(Paleturquoise) { paleturquoise(); }
    inline IntColor(Palevioletred) { palevioletred(); }
    inline IntColor(Papayawhip) { papayawhip(); }
    inline IntColor(Peachpuff) { peachpuff(); }
    inline IntColor(Peru) { peru(); }
    inline IntColor(Pink) { pink(); }
    inline IntColor(Plum) { plum(); }
    inline IntColor(Powderblue) { powderblue(); }
    inline IntColor(Purple) { purple(); }
    inline IntColor(Red) { red(); }
    inline IntColor(Rosybrown) { rosybrown(); }
    inline IntColor(Royalblue) { royalblue(); }
    inline IntColor(Saddlebrown) { saddlebrown(); }
    inline IntColor(Salmon) { salmon(); }
    inline IntColor(Sandybrown) { sandybrown(); }
    inline IntColor(Seagreen) { seagreen(); }
    inline IntColor(Seashell) { seashell(); }
    inline IntColor(Sienna) { sienna(); }
    inline IntColor(Silver) { silver(); }
    inline IntColor(Skyblue) { skyblue(); }
    inline IntColor(Slateblue) { slateblue(); }
    inline IntColor(Slategray) { slategray(); }
    inline IntColor(Slategrey) { slategrey(); }
    inline IntColor(Snow) { snow(); }
    inline IntColor(Springgreen) { springgreen(); }
    inline IntColor(Steelblue) { steelblue(); }
    inline IntColor(Tan) { tan(); }
    inline IntColor(Teal) { teal(); }
    inline IntColor(Thistle) { thistle(); }
    inline IntColor(Tomato) { tomato(); }
    inline IntColor(Turquoise) { turquoise(); }
    inline IntColor(Violet) { violet(); }
    inline IntColor(Wheat) { wheat(); }
    inline IntColor(White) { white(); }
    inline IntColor(Whitesmoke) { whitesmoke(); }
    inline IntColor(Yellow) { yellow(); }
    inline IntColor(Yellowgreen) { yellowgreen(); }

    inline IntColor& operator=(Aliceblue) { return aliceblue(); }
    inline IntColor& operator=(Antiquewhite) { return antiquewhite(); }
    inline IntColor& operator=(Aqua) { return aqua(); }
    inline IntColor& operator=(Aquamarine) { return aquamarine(); }
    inline IntColor& operator=(Azure) { return azure(); }
    inline IntColor& operator=(Beige) { return beige(); }
    inline IntColor& operator=(Bisque) { return bisque(); }
    inline IntColor& operator=(Black) { return black(); }
    inline IntColor& operator=(Blanchedalmond) { return blanchedalmond(); }
    inline IntColor& operator=(Blue) { return blue(); }
    inline IntColor& operator=(Blueviolet) { return blueviolet(); }
    inline IntColor& operator=(Brown) { return brown(); }
    inline IntColor& operator=(Burlywood) { return burlywood(); }
    inline IntColor& operator=(Cadetblue) { return cadetblue(); }
    inline IntColor& operator=(Chartreuse) { return chartreuse(); }
    inline IntColor& operator=(Chocolate) { return chocolate(); }
    inline IntColor& operator=(Coral) { return coral(); }
    inline IntColor& operator=(Cornflowerblue) { return cornflowerblue(); }
    inline IntColor& operator=(Cornsilk) { return cornsilk(); }
    inline IntColor& operator=(Crimson) { return crimson(); }
    inline IntColor& operator=(Cyan) { return cyan(); }
    inline IntColor& operator=(Darkblue) { return darkblue(); }
    inline IntColor& operator=(Darkcyan) { return darkcyan(); }
    inline IntColor& operator=(Darkgoldenrod) { return darkgoldenrod(); }
    inline IntColor& operator=(Darkgray) { return darkgray(); }
    inline IntColor& operator=(Darkgreen) { return darkgreen(); }
    inline IntColor& operator=(Darkgrey) { return darkgrey(); }
    inline IntColor& operator=(Darkkhaki) { return darkkhaki(); }
    inline IntColor& operator=(Darkmagenta) { return darkmagenta(); }
    inline IntColor& operator=(Darkolivegreen) { return darkolivegreen(); }
    inline IntColor& operator=(Darkorange) { return darkorange(); }
    inline IntColor& operator=(Darkorchid) { return darkorchid(); }
    inline IntColor& operator=(Darkred) { return darkred(); }
    inline IntColor& operator=(Darksalmon) { return darksalmon(); }
    inline IntColor& operator=(Darkseagreen) { return darkseagreen(); }
    inline IntColor& operator=(Darkslateblue) { return darkslateblue(); }
    inline IntColor& operator=(Darkslategray) { return darkslategray(); }
    inline IntColor& operator=(Darkslategrey) { return darkslategrey(); }
    inline IntColor& operator=(Darkturquoise) { return darkturquoise(); }
    inline IntColor& operator=(Darkviolet) { return darkviolet(); }
    inline IntColor& operator=(Deeppink) { return deeppink(); }
    inline IntColor& operator=(Deepskyblue) { return deepskyblue(); }
    inline IntColor& operator=(Dimgray) { return dimgray(); }
    inline IntColor& operator=(Dimgrey) { return dimgrey(); }
    inline IntColor& operator=(Dodgerblue) { return dodgerblue(); }
    inline IntColor& operator=(Firebrick) { return firebrick(); }
    inline IntColor& operator=(Floralwhite) { return floralwhite(); }
    inline IntColor& operator=(Forestgreen) { return forestgreen(); }
    inline IntColor& operator=(Fuchsia) { return fuchsia(); }
    inline IntColor& operator=(Gainsboro) { return gainsboro(); }
    inline IntColor& operator=(Ghostwhite) { return ghostwhite(); }
    inline IntColor& operator=(Gold) { return gold(); }
    inline IntColor& operator=(Goldenrod) { return goldenrod(); }
    inline IntColor& operator=(Gray) { return gray(); }
    inline IntColor& operator=(Grey) { return grey(); }
    inline IntColor& operator=(Green) { return green(); }
    inline IntColor& operator=(Greenyellow) { return greenyellow(); }
    inline IntColor& operator=(Honeydew) { return honeydew(); }
    inline IntColor& operator=(Hotpink) { return hotpink(); }
    inline IntColor& operator=(Indianred) { return indianred(); }
    inline IntColor& operator=(Indigo) { return indigo(); }
    inline IntColor& operator=(Ivory) { return ivory(); }
    inline IntColor& operator=(Khaki) { return khaki(); }
    inline IntColor& operator=(Lavender) { return lavender(); }
    inline IntColor& operator=(Lavenderblush) { return lavenderblush(); }
    inline IntColor& operator=(Lawngreen) { return lawngreen(); }
    inline IntColor& operator=(Lemonchiffon) { return lemonchiffon(); }
    inline IntColor& operator=(Lightblue) { return lightblue(); }
    inline IntColor& operator=(Lightcoral) { return lightcoral(); }
    inline IntColor& operator=(Lightcyan) { return lightcyan(); }
    inline IntColor& operator=(Lightgoldenrodyellow) { return lightgoldenrodyellow(); }
    inline IntColor& operator=(Lightgray) { return lightgray(); }
    inline IntColor& operator=(Lightgreen) { return lightgreen(); }
    inline IntColor& operator=(Lightgrey) { return lightgrey(); }
    inline IntColor& operator=(Lightpink) { return lightpink(); }
    inline IntColor& operator=(Lightsalmon) { return lightsalmon(); }
    inline IntColor& operator=(Lightseagreen) { return lightseagreen(); }
    inline IntColor& operator=(Lightskyblue) { return lightskyblue(); }
    inline IntColor& operator=(Lightslategray) { return lightslategray(); }
    inline IntColor& operator=(Lightslategrey) { return lightslategrey(); }
    inline IntColor& operator=(Lightsteelblue) { return lightsteelblue(); }
    inline IntColor& operator=(Lightyellow) { return lightyellow(); }
    inline IntColor& operator=(Lime) { return lime(); }
    inline IntColor& operator=(Limegreen) { return limegreen(); }
    inline IntColor& operator=(Linen) { return linen(); }
    inline IntColor& operator=(Magenta) { return magenta(); }
    inline IntColor& operator=(Maroon) { return maroon(); }
    inline IntColor& operator=(Mediumaquamarine) { return mediumaquamarine(); }
    inline IntColor& operator=(Mediumblue) { return mediumblue(); }
    inline IntColor& operator=(Mediumorchid) { return mediumorchid(); }
    inline IntColor& operator=(Mediumpurple) { return mediumpurple(); }
    inline IntColor& operator=(Mediumseagreen) { return mediumseagreen(); }
    inline IntColor& operator=(Mediumslateblue) { return mediumslateblue(); }
    inline IntColor& operator=(Mediumspringgreen) { return mediumspringgreen(); }
    inline IntColor& operator=(Mediumturquoise) { return mediumturquoise(); }
    inline IntColor& operator=(Mediumvioletred) { return mediumvioletred(); }
    inline IntColor& operator=(Midnightblue) { return midnightblue(); }
    inline IntColor& operator=(Mintcream) { return mintcream(); }
    inline IntColor& operator=(Mistyrose) { return mistyrose(); }
    inline IntColor& operator=(Moccasin) { return moccasin(); }
    inline IntColor& operator=(Navajowhite) { return navajowhite(); }
    inline IntColor& operator=(Navy) { return navy(); }
    inline IntColor& operator=(Oldlace) { return oldlace(); }
    inline IntColor& operator=(Olive) { return olive(); }
    inline IntColor& operator=(Olivedrab) { return olivedrab(); }
    inline IntColor& operator=(Orange) { return orange(); }
    inline IntColor& operator=(Orangered) { return orangered(); }
    inline IntColor& operator=(Orchid) { return orchid(); }
    inline IntColor& operator=(Palegoldenrod) { return palegoldenrod(); }
    inline IntColor& operator=(Palegreen) { return palegreen(); }
    inline IntColor& operator=(Paleturquoise) { return paleturquoise(); }
    inline IntColor& operator=(Palevioletred) { return palevioletred(); }
    inline IntColor& operator=(Papayawhip) { return papayawhip(); }
    inline IntColor& operator=(Peachpuff) { return peachpuff(); }
    inline IntColor& operator=(Peru) { return peru(); }
    inline IntColor& operator=(Pink) { return pink(); }
    inline IntColor& operator=(Plum) { return plum(); }
    inline IntColor& operator=(Powderblue) { return powderblue(); }
    inline IntColor& operator=(Purple) { return purple(); }
    inline IntColor& operator=(Red) { return red(); }
    inline IntColor& operator=(Rosybrown) { return rosybrown(); }
    inline IntColor& operator=(Royalblue) { return royalblue(); }
    inline IntColor& operator=(Saddlebrown) { return saddlebrown(); }
    inline IntColor& operator=(Salmon) { return salmon(); }
    inline IntColor& operator=(Sandybrown) { return sandybrown(); }
    inline IntColor& operator=(Seagreen) { return seagreen(); }
    inline IntColor& operator=(Seashell) { return seashell(); }
    inline IntColor& operator=(Sienna) { return sienna(); }
    inline IntColor& operator=(Silver) { return silver(); }
    inline IntColor& operator=(Skyblue) { return skyblue(); }
    inline IntColor& operator=(Slateblue) { return slateblue(); }
    inline IntColor& operator=(Slategray) { return slategray(); }
    inline IntColor& operator=(Slategrey) { return slategrey(); }
    inline IntColor& operator=(Snow) { return snow(); }
    inline IntColor& operator=(Springgreen) { return springgreen(); }
    inline IntColor& operator=(Steelblue) { return steelblue(); }
    inline IntColor& operator=(Tan) { return tan(); }
    inline IntColor& operator=(Teal) { return teal(); }
    inline IntColor& operator=(Thistle) { return thistle(); }
    inline IntColor& operator=(Tomato) { return tomato(); }
    inline IntColor& operator=(Turquoise) { return turquoise(); }
    inline IntColor& operator=(Violet) { return violet(); }
    inline IntColor& operator=(Wheat) { return wheat(); }
    inline IntColor& operator=(White) { return white(); }
    inline IntColor& operator=(Whitesmoke) { return whitesmoke(); }
    inline IntColor& operator=(Yellow) { return yellow(); }
    inline IntColor& operator=(Yellowgreen) { return yellowgreen(); }

	inline IntColor& aliceblue() { r = 240<<24; g = 248<<24; b = 255<<24; a = 255<<24; return *this; }
    inline IntColor& antiquewhite() { r = 250<<24; g = 235<<24; b = 215<<24; a = 255<<24; return *this; }
    inline IntColor& aqua() { r = 0<<24; g = 255<<24; b = 255<<24; a = 255<<24; return *this; }
    inline IntColor& aquamarine() { r = 127<<24; g = 255<<24; b = 212<<24; a = 255<<24; return *this; }
    inline IntColor& azure() { r = 240<<24; g = 255<<24; b = 255<<24; a = 255<<24; return *this; }
    inline IntColor& beige() { r = 245<<24; g = 245<<24; b = 220<<24; a = 255<<24; return *this; }
    inline IntColor& bisque() { r = 255<<24; g = 228<<24; b = 196<<24; a = 255<<24; return *this; }
    inline IntColor& black() { r = 0<<24; g = 0<<24; b = 0<<24; a = 255<<24; return *this; }
    inline IntColor& blanchedalmond() { r = 255<<24; g = 235<<24; b = 205<<24; a = 255<<24; return *this; }
    inline IntColor& blue() { r = 0<<24; g = 0<<24; b = 255<<24; a = 255<<24; return *this; }
    inline IntColor& blueviolet() { r = 138<<24; g = 43<<24; b = 226<<24; a = 255<<24; return *this; }
    inline IntColor& brown() { r = 165<<24; g = 42<<24; b = 42<<24; a = 255<<24; return *this; }
    inline IntColor& burlywood() { r = 222<<24; g = 184<<24; b = 135<<24; a = 255<<24; return *this; }
    inline IntColor& cadetblue() { r = 95<<24; g = 158<<24; b = 160<<24; a = 255<<24; return *this; }
    inline IntColor& chartreuse() { r = 127<<24; g = 255<<24; b = 0<<24; a = 255<<24; return *this; }
    inline IntColor& chocolate() { r = 210<<24; g = 105<<24; b = 30<<24; a = 255<<24; return *this; }
    inline IntColor& coral() { r = 255<<24; g = 127<<24; b = 80<<24; a = 255<<24; return *this; }
    inline IntColor& cornflowerblue() { r = 100<<24; g = 149<<24; b = 237<<24; a = 255<<24; return *this; }
    inline IntColor& cornsilk() { r = 255<<24; g = 248<<24; b = 220<<24; a = 255<<24; return *this; }
    inline IntColor& crimson() { r = 220<<24; g = 20<<24; b = 60<<24; a = 255<<24; return *this; }
    inline IntColor& cyan() { r = 0<<24; g = 255<<24; b = 255<<24; a = 255<<24; return *this; }
    inline IntColor& darkblue() { r = 0<<24; g = 0<<24; b = 139<<24; a = 255<<24; return *this; }
    inline IntColor& darkcyan() { r = 0<<24; g = 139<<24; b = 139<<24; a = 255<<24; return *this; }
    inline IntColor& darkgoldenrod() { r = 184<<24; g = 134<<24; b = 11<<24; a = 255<<24; return *this; }
    inline IntColor& darkgray() { r = 169<<24; g = 169<<24; b = 169<<24; a = 255<<24; return *this; }
    inline IntColor& darkgreen() { r = 0<<24; g = 100<<24; b = 0<<24; a = 255<<24; return *this; }
    inline IntColor& darkgrey() { r = 169<<24; g = 169<<24; b = 169<<24; a = 255<<24; return *this; }
    inline IntColor& darkkhaki() { r = 189<<24; g = 183<<24; b = 107<<24; a = 255<<24; return *this; }
    inline IntColor& darkmagenta() { r = 139<<24; g = 0<<24; b = 139<<24; a = 255<<24; return *this; }
    inline IntColor& darkolivegreen() { r = 85<<24; g = 107<<24; b = 47<<24; a = 255<<24; return *this; }
    inline IntColor& darkorange() { r = 255<<24; g = 140<<24; b = 0<<24; a = 255<<24; return *this; }
    inline IntColor& darkorchid() { r = 153<<24; g = 50<<24; b = 204<<24; a = 255<<24; return *this; }
    inline IntColor& darkred() { r = 139<<24; g = 0<<24; b = 0<<24; a = 255<<24; return *this; }
    inline IntColor& darksalmon() { r = 233<<24; g = 150<<24; b = 122<<24; a = 255<<24; return *this; }
    inline IntColor& darkseagreen() { r = 143<<24; g = 188<<24; b = 143<<24; a = 255<<24; return *this; }
    inline IntColor& darkslateblue() { r = 72<<24; g = 61<<24; b = 139<<24; a = 255<<24; return *this; }
    inline IntColor& darkslategray() { r = 47<<24; g = 79<<24; b = 79<<24; a = 255<<24; return *this; }
    inline IntColor& darkslategrey() { r = 47<<24; g = 79<<24; b = 79<<24; a = 255<<24; return *this; }
    inline IntColor& darkturquoise() { r = 0<<24; g = 206<<24; b = 209<<24; a = 255<<24; return *this; }
    inline IntColor& darkviolet() { r = 148<<24; g = 0<<24; b = 211<<24; a = 255<<24; return *this; }
    inline IntColor& deeppink() { r = 255<<24; g = 20<<24; b = 147<<24; a = 255<<24; return *this; }
    inline IntColor& deepskyblue() { r = 0<<24; g = 191<<24; b = 255<<24; a = 255<<24; return *this; }
    inline IntColor& dimgray() { r = 105<<24; g = 105<<24; b = 105<<24; a = 255<<24; return *this; }
    inline IntColor& dimgrey() { r = 105<<24; g = 105<<24; b = 105<<24; a = 255<<24; return *this; }
    inline IntColor& dodgerblue() { r = 30<<24; g = 144<<24; b = 255<<24; a = 255<<24; return *this; }
    inline IntColor& firebrick() { r = 178<<24; g = 34<<24; b = 34<<24; a = 255<<24; return *this; }
    inline IntColor& floralwhite() { r = 255<<24; g = 250<<24; b = 240<<24; a = 255<<24; return *this; }
    inline IntColor& forestgreen() { r = 34<<24; g = 139<<24; b = 34<<24; a = 255<<24; return *this; }
    inline IntColor& fuchsia() { r = 255<<24; g = 0<<24; b = 255<<24; a = 255<<24; return *this; }
    inline IntColor& gainsboro() { r = 220<<24; g = 220<<24; b = 220<<24; a = 255<<24; return *this; }
    inline IntColor& ghostwhite() { r = 248<<24; g = 248<<24; b = 255<<24; a = 255<<24; return *this; }
    inline IntColor& gold() { r = 255<<24; g = 215<<24; b = 0<<24; a = 255<<24; return *this; }
    inline IntColor& goldenrod() { r = 218<<24; g = 165<<24; b = 32<<24; a = 255<<24; return *this; }
    inline IntColor& gray() { r = 128<<24; g = 128<<24; b = 128<<24; a = 255<<24; return *this; }
    inline IntColor& grey() { r = 128<<24; g = 128<<24; b = 128<<24; a = 255<<24; return *this; }
    inline IntColor& green() { r = 0<<24; g = 128<<24; b = 0<<24; a = 255<<24; return *this; }
	inline IntColor& greenyellow() { r = 173<<24; g = 255<<24; b = 47<<24; a = 255<<24; return *this; }
    inline IntColor& honeydew() { r = 240<<24; g = 255<<24; b = 240<<24; a = 255<<24; return *this; }
    inline IntColor& hotpink() { r = 255<<24; g = 105<<24; b = 180<<24; a = 255<<24; return *this; }
    inline IntColor& indianred() { r = 205<<24; g = 92<<24; b = 92<<24; a = 255<<24; return *this; }
    inline IntColor& indigo() { r = 75<<24; g = 0<<24; b = 130<<24; a = 255<<24; return *this; }
    inline IntColor& ivory() { r = 255<<24; g = 255<<24; b = 240<<24; a = 255<<24; return *this; }
    inline IntColor& khaki() { r = 240<<24; g = 230<<24; b = 140<<24; a = 255<<24; return *this; }
    inline IntColor& lavender() { r = 230<<24; g =230<<24; b = 250<<24; a = 255<<24; return *this; }
    inline IntColor& lavenderblush() { r = 255<<24; g = 240<<24; b = 245<<24; a = 255<<24; return *this; }
    inline IntColor& lawngreen() { r = 124<<24; g = 252<<24; b = 0<<24; a = 255<<24; return *this; }
    inline IntColor& lemonchiffon() { r = 255<<24; g = 250<<24; b = 205<<24; a = 255<<24; return *this; }
    inline IntColor& lightblue() { r = 173<<24; g = 216<<24; b = 230<<24; a = 255<<24; return *this; }
    inline IntColor& lightcoral() { r = 240<<24; g = 128<<24; b = 128<<24; a = 255<<24; return *this; }
    inline IntColor& lightcyan() { r = 224<<24; g = 255<<24; b = 255<<24; a = 255<<24; return *this; }
    inline IntColor& lightgoldenrodyellow() { r = 250<<24; g = 250<<24; b = 210<<24; a = 255<<24; return *this; }
    inline IntColor& lightgray() { r = 211<<24; g = 211<<24; b = 211<<24; a = 255<<24; return *this; }
    inline IntColor& lightgreen() { r = 144<<24; g = 238<<24; b = 144<<24; a = 255<<24; return *this; }
    inline IntColor& lightgrey() { r = 211<<24; g = 211<<24; b = 211<<24; a = 255<<24; return *this; }
    inline IntColor& lightpink() { r = 255<<24; g = 182<<24; b = 193<<24; a = 255<<24; return *this; }
    inline IntColor& lightsalmon() { r = 255<<24; g = 160<<24; b = 122<<24; a = 255<<24; return *this; }
    inline IntColor& lightseagreen() { r = 32<<24; g = 178<<24; b = 170<<24; a = 255<<24; return *this; }
    inline IntColor& lightskyblue() { r = 135<<24; g = 206<<24; b = 250<<24; a = 255<<24; return *this; }
    inline IntColor& lightslategray() { r = 119<<24; g = 136<<24; b = 153<<24; a = 255<<24; return *this; }
    inline IntColor& lightslategrey() { r = 119<<24; g = 136<<24; b = 153<<24; a = 255<<24; return *this; }
    inline IntColor& lightsteelblue() { r = 176<<24; g = 196<<24; b = 222<<24; a = 255<<24; return *this; }
    inline IntColor& lightyellow() { r = 255<<24; g = 255<<24; b = 224<<24; a = 255<<24; return *this; }
    inline IntColor& lime() { r = 0<<24; g = 255<<24; b = 0<<24; a = 255<<24; return *this; }
    inline IntColor& limegreen() { r = 50<<24; g = 205<<24; b = 50<<24; a = 255<<24; return *this; }
    inline IntColor& linen() { r = 250<<24; g = 240<<24; b = 230<<24; a = 255<<24; return *this; }
    inline IntColor& magenta() { r = 255<<24; g = 0<<24; b = 255<<24; a = 255<<24; return *this; }
    inline IntColor& maroon() { r = 128<<24; g = 0<<24; b = 0<<24; a = 255<<24; return *this; }
    inline IntColor& mediumaquamarine() { r = 102<<24; g = 205<<24; b = 170<<24; a = 255<<24; return *this; }
    inline IntColor& mediumblue() { r = 0<<24; g = 0<<24; b = 205<<24; a = 255<<24; return *this; }
    inline IntColor& mediumorchid() { r = 186<<24; g = 85<<24; b = 211<<24; a = 255<<24; return *this; }
    inline IntColor& mediumpurple() { r = 147<<24; g = 112<<24; b = 219<<24; a = 255<<24; return *this; }
    inline IntColor& mediumseagreen() { r = 60<<24; g = 179<<24; b = 113<<24; a = 255<<24; return *this; }
    inline IntColor& mediumslateblue() { r = 123<<24; g = 104<<24; b = 238<<24; a = 255<<24; return *this; }
    inline IntColor& mediumspringgreen() { r = 0<<24; g = 250<<24; b = 154<<24; a = 255<<24; return *this; }
    inline IntColor& mediumturquoise() { r = 72<<24; g = 209<<24; b = 204<<24; a = 255<<24; return *this; }
    inline IntColor& mediumvioletred() { r = 199<<24; g = 21<<24; b = 133<<24; a = 255<<24; return *this; }
    inline IntColor& midnightblue() { r = 25<<24; g = 25<<24; b = 112<<24; a = 255<<24; return *this; }
    inline IntColor& mintcream() { r = 245<<24; g = 255<<24; b = 250<<24; a = 255<<24; return *this; }
    inline IntColor& mistyrose() { r = 255<<24; g = 228<<24; b = 225<<24; a = 255<<24; return *this; }
    inline IntColor& moccasin() { r = 255<<24; g = 228<<24; b = 181<<24; a = 255<<24; return *this; }
	inline IntColor& navajowhite() { r = 255<<24; g = 222<<24; b = 173<<24; a = 255<<24; return *this; }
    inline IntColor& navy() { r = 0<<24; g = 0<<24; b = 128<<24; a = 255<<24; return *this; }
    inline IntColor& oldlace() { r = 253<<24; g = 245<<24; b = 230<<24; a = 255<<24; return *this; }
    inline IntColor& olive() { r = 128<<24; g = 128<<24; b = 0<<24; a = 255<<24; return *this; }
    inline IntColor& olivedrab() { r = 107<<24; g = 142<<24; b = 35<<24; a = 255<<24; return *this; }
    inline IntColor& orange() { r = 255<<24; g = 165<<24; b = 0<<24; a = 255<<24; return *this; }
    inline IntColor& orangered() { r = 255<<24; g = 69<<24; b = 0<<24; a = 255<<24; return *this; }
    inline IntColor& orchid() { r = 218<<24; g = 112<<24; b = 214<<24; a = 255<<24; return *this; }
    inline IntColor& palegoldenrod() { r = 238<<24; g = 232<<24; b = 170<<24; a = 255<<24; return *this; }
    inline IntColor& palegreen() { r = 152<<24; g = 251<<24; b = 152<<24; a = 255<<24; return *this; }
    inline IntColor& paleturquoise() { r = 175<<24; g = 238<<24; b = 238<<24; a = 255<<24; return *this; }
    inline IntColor& palevioletred() { r = 219<<24; g = 112<<24; b = 147<<24; a = 255<<24; return *this; }
    inline IntColor& papayawhip() { r = 255<<24; g = 239<<24; b = 213<<24; a = 255<<24; return *this; }
    inline IntColor& peachpuff() { r = 255<<24; g = 218<<24; b = 185<<24; a = 255<<24; return *this; }
    inline IntColor& peru() { r = 205<<24; g = 133<<24; b = 63<<24; a = 255<<24; return *this; }
    inline IntColor& pink() { r = 255<<24; g = 192<<24; b = 203<<24; a = 255<<24; return *this; }
    inline IntColor& plum() { r = 221<<24; g = 160<<24; b = 221<<24; a = 255<<24; return *this; }
    inline IntColor& powderblue() { r = 176<<24; g = 224<<24; b = 230<<24; a = 255<<24; return *this; }
    inline IntColor& purple() { r = 128<<24; g = 0<<24; b = 128<<24; a = 255<<24; return *this; }
    inline IntColor& red() { r = 255<<24; g = 0<<24; b = 0<<24; a = 255<<24; return *this; }
    inline IntColor& rosybrown() { r = 188<<24; g = 143<<24; b = 143<<24; a = 255<<24; return *this; }
    inline IntColor& royalblue() { r = 65<<24; g = 105<<24; b = 225<<24; a = 255<<24; return *this; }
    inline IntColor& saddlebrown() { r = 139<<24; g = 69<<24; b = 19<<24; a = 255<<24; return *this; }
    inline IntColor& salmon() { r = 250<<24; g = 128<<24; b = 114<<24; a = 255<<24; return *this; }
    inline IntColor& sandybrown() { r = 244<<24; g = 164<<24; b = 96<<24; a = 255<<24; return *this; }
    inline IntColor& seagreen() { r = 46<<24; g = 139<<24; b = 87<<24; a = 255<<24; return *this; }
    inline IntColor& seashell() { r = 255<<24; g = 245<<24; b = 238<<24; a = 255<<24; return *this; }
    inline IntColor& sienna() { r = 160<<24; g = 82<<24; b = 45<<24; a = 255<<24; return *this; }
    inline IntColor& silver() { r = 192<<24; g = 192<<24; b = 192<<24; a = 255<<24; return *this; }
    inline IntColor& skyblue() { r = 135<<24; g = 206<<24; b = 235<<24; a = 255<<24; return *this; }
    inline IntColor& slateblue() { r = 106<<24; g = 90<<24; b = 205<<24; a = 255<<24; return *this; }
    inline IntColor& slategray() { r = 112<<24; g = 128<<24; b = 144<<24; a = 255<<24; return *this; }
    inline IntColor& slategrey() { r = 112<<24; g = 128<<24; b = 144<<24; a = 255<<24; return *this; }
    inline IntColor& snow() { r = 255<<24; g = 250<<24; b = 250<<24; a = 255<<24; return *this; }
    inline IntColor& springgreen() { r = 0<<24; g = 255<<24; b = 127<<24; a = 255<<24; return *this; }
    inline IntColor& steelblue() { r = 70<<24; g = 130<<24; b = 180<<24; a = 255<<24; return *this; }
    inline IntColor& tan() { r = 210<<24; g = 180<<24; b = 140<<24; a = 255<<24; return *this; }
    inline IntColor& teal() { r = 0<<24; g = 128<<24; b = 128<<24; a = 255<<24; return *this; }
    inline IntColor& thistle() { r = 216<<24; g = 191<<24; b = 216<<24; a = 255<<24; return *this; }
    inline IntColor& tomato() { r = 255<<24; g = 99<<24; b = 71<<24; a = 255<<24; return *this; }
    inline IntColor& turquoise() { r = 64<<24; g = 224<<24; b = 208<<24; a = 255<<24; return *this; }
    inline IntColor& violet() { r = 238<<24; g = 130<<24; b = 238<<24; a = 255<<24; return *this; }
    inline IntColor& wheat() { r = 245<<24; g = 222<<24; b = 179<<24; a = 255<<24; return *this; }
    inline IntColor& white() { r = 255<<24; g = 255<<24; b = 255<<24; a = 255<<24; return *this; }
    inline IntColor& whitesmoke() { r = 245<<24; g = 245<<24; b = 245<<24; a = 255<<24; return *this; }
    inline IntColor& yellow() { r = 255<<24; g = 255<<24; b = 0<<24; a = 255<<24; return *this; }
    inline IntColor& yellowgreen() { r = 154<<24; g = 205<<24; b = 50<<24; a = 255<<24; return *this; }

	inline void set(int newRed, int newGreen, int newBlue, int newAlpha = 255)
	{
		r = newRed;
		g = newGreen;
		b = newBlue;
		a = newAlpha;
	}

	inline void set(const int newComponents[4])
	{
		components[0] = newComponents[0];
		components[1] = newComponents[1];
		components[2] = newComponents[2];
		components[3] = newComponents[3];
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

	String getAsString() const;
	void setAsString(const String& rgba);
};



inline bool operator ==(const IntColor& left, const IntColor& right)
{
	return
		left.r == right.r &&
		left.g == right.g &&
		left.b == right.b &&
		left.a == right.a;
}



inline bool operator !=(const IntColor& left, const IntColor& right)
{
	return !(left == right);
}




} // namespace Graphics
} // namespace BaseLib



#endif // #ifndef BaseLib_Graphics_IntColor_h