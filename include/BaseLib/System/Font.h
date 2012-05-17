/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_System_Font_h
#define BaseLib_System_Font_h



#include "BaseLib/Reflection/Object.h"
#include "BaseLib/Strings/String.h"
#include "BaseLib/Functors/Enumerator.h"



struct FT_FaceRec_;



namespace BaseLib {
namespace System {



using namespace BaseLib;
using BaseLib::Strings::String;
using BaseLib::Functors::Enumerator;



class BL_EXPORT Font : public Reflection::Object {
public:

	static int cacheAllFontNames();
	static String getFontNameFromFile(const String& fontFile);
	static String getFontFileFromName(const String& fontName);
	static String getFontsDirectory();
	static void enumFontFiles(const Enumerator<String>& enumerator);
	static void enumFontNames(const Enumerator<String>& enumerator);
	static void enumFontFilesAndNames(const Enumerator<String>& fileEnumerator, const Enumerator<String>& nameEnumerator);

	inline static Font* createFromFontName(const String& fontName, int pixelSize)
	{
		return new Font(getFontFileFromName(fontName), pixelSize);
	}

	inline static Font* createFromFontFileName(const String& fontFileName, int pixelSize)
	{
		return new Font(fontFileName, pixelSize);
	}

	BL_DECLARE_REFLECTION_BASELIB_BASE_CLASS(BaseLib::System::Font);

	~Font();

	inline bool isLoaded() const
	{
		return face != NULL;
	}

	inline String getFileName() const
	{
		return fileName;
	}

	inline int getSize() const
	{
		return size;
	}

	bool isScaleable() const;
	bool isFixedWidth() const;
	bool hasFixedSizes() const;

	String getName() const;
	String getPostscriptName() const;

	float getLineAdvance() const;
	float getLineAscent() const;
	float getLineDescent() const;

	char32 getFirstSupportedCharacter() const;
	bool isCharacterSupported(char32 character) const;

	void measureCharacter(char32 character, float& width, float& height) const;
	void measureString(const String& string, float& width, float& height, int position = 0, int length = String::END) const;

	void calculateCharacterAdvance(char32 previousCharacter, char32 currentCharacter, float& advanceRight, float& advanceUp) const;

	void renderGlyph(char32 character, uint8* pixels, int lineStrideInBytes);
	inline void renderGlyph(char32 character, uint8* pixels)
	{
		renderGlyph(character, pixels, size);
	}

private:

	FT_FaceRec_* face;
	//char32 firstCharcter;
	//char32 previousCharacter;
	String fileName;
	int size;

	Font(const String& fontFile, int pixelSize);
};



} // namespace System
} // namespace BaseLib



#endif // #ifndef BaseLib_System_Font_h
