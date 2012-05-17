/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/System/Font.h"
#include "BaseLib/ErrorHandling.h"
#include "BaseLib/Files/LocalFile.h"
#include "BaseLib/Functors/Adder.h"
#include "BaseLib/Functors/StreamWriter.h"
#include "BaseLib/Containers/StringMap.h"
#include "BaseLib/Console.h"
#include <ft2build.h>
#include <freetype/freetype.h>



namespace BaseLib {
namespace System {



#define FONT_NOT_LOADED ("Font '" + fileName + "' with size " + String::createFrom(size) + " is not loaded!" ERROR_AT)



using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Files;
using namespace BaseLib::Functors;
using namespace BaseLib::Utilities;
using BaseLib::Containers::StringMap;



FT_Library freetype;
bool freetypeInitialized = false;



inline void ensureFreetypeIsInitialized()
{
	if (freetypeInitialized == false)
	{
		FT_Error error = FT_Init_FreeType(&freetype);
		if (error == 0)
		{
			freetypeInitialized = true;
		}
		else
		{
			resultError("Error while initializing freetype library" ERROR_AT);
		}
	}
}



StringMap<String> nameFileMap;
StringMap<String> fileNameMap;



int Font::cacheAllFontNames()
{
	nameFileMap.clear();
	fileNameMap.clear();

	Array<String> fontFiles;
	Array<String> fontNames;
	enumFontFilesAndNames(Adder<Array<String>, String>(fontFiles), Adder<Array<String>, String>(fontNames));

	int count = fontFiles.getCount();
	BL_ASSERT(count == fontNames.getCount());
	for (int i = 0; i < count; ++i)
	{
		BaseLib::Console::trace << fontNames[i] << ": " << fontFiles[i] << BaseLib::Streams::newLine;
		nameFileMap[fontNames[i]] = fontFiles[i];
		fileNameMap[fontFiles[i]] = fontNames[i];
	}

	return count;
}



String Font::getFontNameFromFile(const String& fontFile)
{
	StringMap<String>::Iterator i = fileNameMap.find(fontFile);
	if (i != fileNameMap.end())
	{
		return i->second;
	}

	String fileName = fontFile;

	if (LocalFile::exists(fileName) == false)
	{
		fileName = getFontsDirectory() + fileName;

		if (LocalFile::exists(fileName) == false)
		{
			argumentError("File '" + fontFile + "' does not exist!" ERROR_AT);
			return Empty();
		}
	}

	ensureFreetypeIsInitialized();

	FT_Face fontFace;
	FT_Error error = FT_New_Face(freetype, fileName.getChar8CString(), 0, &fontFace);
	if (error == FT_Err_Unknown_File_Format)
	{
		///resultError("Unsupported font format of file '" + fontFile + "' !" ERROR_AT);
		return Empty();
	}
	else if (error != 0)
	{
		resultError("Unknown error opening font file '" + fontFile + "' !" ERROR_AT);
		return Empty();
	}

	return String(fontFace->family_name) + " (" + String(fontFace->style_name) + ')';
}



String Font::getFontFileFromName(const String& fontName)
{
	if (nameFileMap.empty() == true)
	{
		cacheAllFontNames();
	}

	StringMap<String>::Iterator i = nameFileMap.find(fontName);
	if (i != nameFileMap.end())
	{
		return i->second;
	}
	else
	{
		return Empty();
	}
}



String Font::getFontsDirectory()
{
	#ifdef BL_PLATFORM_WIN32
		char16 buffer[1024];
		GetWindowsDirectoryW(buffer, 1024);
		String windowsDirectory(buffer);
		return windowsDirectory + "/Fonts/";
	#endif
}



class FontFileEnumerator : public Enumerator<String> {
public:

	FontFileEnumerator(const Enumerator<String>& forEnumerator)
		: otherEnumerator(forEnumerator)
	{
	}

	virtual void enumerate(const String& value) const
	{
		#ifdef BL_PLATFORM_WIN32
			if (value.endsCaseInsensitiveWith(".fon") == false)
			{
				otherEnumerator.enumerate(value);
			}
		#else
			otherEnumerator.enumerate(value);
		#endif
	}

private:

	const Enumerator<String>& otherEnumerator;

};



void Font::enumFontFiles(const Enumerator<String>& enumerator)
{
	LocalFile::enumFileNames(FontFileEnumerator(enumerator), getFontsDirectory(), false, true);
}



void Font::enumFontNames(const Enumerator<String>& enumerator)
{
	Array<String> fontFileNames;
	enumFontFiles(Adder<Array<String>, String>(fontFileNames));

	int count = fontFileNames.getCount();
	for (int i = 0; i < count && enumerator.stop() == false; ++i)
	{
		enumerator.enumerate(getFontNameFromFile(fontFileNames[i]));
	}
}



void Font::enumFontFilesAndNames(const Enumerator<String>& fileEnumerator, const Enumerator<String>& nameEnumerator)
{
	Array<String> fontFileNames;
	enumFontFiles(Adder<Array<String>, String>(fontFileNames));

	int count = fontFileNames.getCount();
	for (int i = 0; i < count; ++i)
	{
		if (fileEnumerator.stop() == true || nameEnumerator.stop() == true)
		{
			return;
		}
		const String fontName = getFontNameFromFile(fontFileNames[i]);
		if (fontName.isEmpty() == false)
		{
			fileEnumerator.enumerate(fontFileNames[i]);
			nameEnumerator.enumerate(fontName);
		}
	}
}



BL_DEFINE_REFLECTION_BASE_CLASS(BaseLib::System::Font)
{
	registerProperty("name", &Font::getName);
	registerProperty("file", &Font::getFileName);
	registerProperty("size", &Font::getSize);
	registerProperty("loaded", &Font::isLoaded);
	registerProperty("scalable", &Font::isScaleable);
	registerProperty("fixedWidth", &Font::isFixedWidth);
	registerProperty("hasFixedSizes", &Font::hasFixedSizes);
	registerProperty("postscriptName", &Font::getPostscriptName);
	registerProperty("lineAdvance", &Font::getLineAdvance);
	registerProperty("lineAscent", &Font::getLineAscent);
	registerProperty("lineDescent", &Font::getLineDescent);
}



Font::Font(const String& fontFile, int pixelSize)
	: face(NULL)
	//, firstCharcter(0)
	//, previousCharacter(0)
	, fileName(fontFile)
	, size(pixelSize)
{
	ensureFreetypeIsInitialized();

	String path = getFontsDirectory() + fileName;
	FT_Error error = FT_New_Face(freetype, path.getChar8CString(), 0, &face);
	if (error == FT_Err_Unknown_File_Format)
	{
		face = NULL;
		resultError("Unsupported font format of file '" + fileName + "' !" ERROR_AT);
		return;
	}
	else if (error != 0)
	{
		face = NULL;
		resultError("Unknown error opening font file '" + fileName + "' !" ERROR_AT);
		return;
	}

	//error = FT_Set_Char_Size(face, 0, size*64, 0, 0);
	error = FT_Set_Pixel_Sizes(face, 0, size);
	if (error != 0)
	{
		face = NULL;
		resultError("Unknown error opening font file '" + fileName + "' !" ERROR_AT);
		return;
	}	
}



Font::~Font()
{
}



bool Font::isScaleable() const
{
	if (isLoaded() == true)
	{
		return FT_IS_SCALABLE(face) != 0;
	}
	else
	{
		stateError(FONT_NOT_LOADED);
		return false;
	}
}



bool Font::isFixedWidth() const
{
	if (isLoaded() == true)
	{
		return FT_IS_FIXED_WIDTH(face) != 0;
	}
	else
	{
		stateError(FONT_NOT_LOADED);
		return false;
	}
}



bool Font::hasFixedSizes() const
{
	if (isLoaded() == true)
	{
		return FT_HAS_FIXED_SIZES(face) != 0;
	}
	else
	{
		stateError(FONT_NOT_LOADED);
		return false;
	}
}



String Font::getName() const
{
	if (isLoaded() == true)
	{
		return String(face->family_name) + " (" + String(face->style_name) + ')';
	}
	else
	{
		stateError(FONT_NOT_LOADED);
		return Empty();
	}
}



String Font::getPostscriptName() const
{
	if (isLoaded() == true)
	{
		const char* postscriptName = FT_Get_Postscript_Name(face);
		return postscriptName != NULL ? postscriptName : "";
	}
	else
	{
		stateError(FONT_NOT_LOADED);
		return Empty();
	}
}



float Font::getLineAdvance() const
{
	if (isLoaded() == true)
	{
		return face->size->metrics.height / 64.0f;
	}
	else
	{
		stateError(FONT_NOT_LOADED);
		return 0.0f;
	}
}



float Font::getLineAscent() const
{
	if (isLoaded() == true)
	{
		return face->size->metrics.ascender / 64.0f;
	}
	else
	{
		stateError(FONT_NOT_LOADED);
		return 0.0f;
	}
}



float Font::getLineDescent() const
{
	if (isLoaded() == true)
	{
		return face->size->metrics.descender / 64.0f;
	}
	else
	{
		stateError(FONT_NOT_LOADED);
		return 0.0f;
	}
}



bool Font::isCharacterSupported(char32 character) const
{
	if (isLoaded() == true)
	{
		return FT_Get_Char_Index(face, character) != 0;
	}
	else
	{
		stateError(FONT_NOT_LOADED);
		return false;
	}
}



char32 Font::getFirstSupportedCharacter() const
{
	if (isLoaded() == true)
	{
		FT_UInt glyphIndex;
		return FT_Get_First_Char(face, &glyphIndex);
	}
	else
	{
		stateError(FONT_NOT_LOADED);
		return 0;
	}
}



void Font::measureCharacter(char32 character, float& width, float& height) const
{
	if (isLoaded() == true)
	{
		FT_UInt glyphIndex = FT_Get_Char_Index(face, character);

		FT_Error error = FT_Load_Glyph(face, glyphIndex, FT_LOAD_DEFAULT);
		if (error != 0)
		{
			width = 0.0f;
			height = 0.0f;
			return;
		}

		width = face->glyph->metrics.width / 64.0f;
		height = face->glyph->metrics.height / 64.0f;
	}
	else
	{
		stateError(FONT_NOT_LOADED);
	}
}



void Font::measureString(const String& string, float& width, float& height, int position, int length) const
{
	if (isLoaded() == true)
	{
		if (length == String::END)
		{
			length = string.getLength() - position;
		}

		if (length == 0)
		{
			width = 0.0f;
			height = 0.0f;
			return;
		}
		else if (length == 1)
		{
			measureCharacter(string[0], width, height);
			return;
		}
		else
		{
			const float lineAdvance = getLineAdvance(); 

			float x = 0.0f;
			float y = 0.0f;
			float xMin = 0.0f;
			float xMax = 0.0f;
			float yMin = 0.0f;
			float yMax = 0.0f;

			int endIndex = position + length;
			char32 previousCharacter = 0;
			for (int i = position; i < endIndex; ++i)
			{
				const char32 character = string.getChar32(i);

				if (character == '\n')
				{
					x = 0.0f;
					y += lineAdvance;
				}
				else
				{
					float advanceRight;
					float advanceUp;
					calculateCharacterAdvance(previousCharacter, character, advanceRight, advanceUp);
					x += advanceRight;
					y += advanceUp;
				}

				xMin = min(x, xMin);
				xMax = max(x, xMax);
				yMin = min(y, yMin);
				yMax = max(y, yMax);

				previousCharacter = character;
			}

			width = xMax - xMin;
			height = yMax - yMin + getLineAscent() + getLineAscent();
		}
	}
	else
	{
		stateError(FONT_NOT_LOADED);
	}
}



const float OO_64 = 1.0f / 64.0f;



void Font::calculateCharacterAdvance(char32 previousCharacter, char32 currentCharacter, float& advanceRight, float& advanceUp) const
{
	if (isLoaded() == true)
	{
		FT_UInt currentGlyph = FT_Get_Char_Index(face, currentCharacter);
		FT_Load_Glyph(face, currentGlyph, FT_LOAD_DEFAULT);
		advanceRight = face->glyph->advance.x * OO_64;
		advanceUp = face->glyph->advance.y * OO_64;
		if (FT_HAS_KERNING(face))
		{
			FT_Vector kerning;
			FT_UInt previousGlyph = FT_Get_Char_Index(face, previousCharacter);
			FT_Error error = FT_Get_Kerning(face, previousGlyph, currentGlyph, FT_KERNING_UNFITTED, &kerning); // FT_KERNING_DEFAULT, FT_KERNING_UNFITTED, FT_KERNING_UNSCALED
			if (error == 0)
			{
				advanceRight += kerning.x * OO_64;
				advanceUp += kerning.y * OO_64;
			}
			else
			{
				resultError("calculateCharacterAdvance()" ERROR_AT);
			}
		}
	}
	else
	{
		stateError(FONT_NOT_LOADED);
	}
}



void Font::renderGlyph(char32 character, uint8 * pixels, int lineStrideInBytes)
{
	if (isLoaded() == true)
	{
		FT_UInt glyphIndex = FT_Get_Char_Index(face, character);

		FT_Error error = FT_Load_Glyph(face, glyphIndex, FT_LOAD_DEFAULT);
		if (error != 0)
		{
			resultError("Error while loading glyph for character " + String::createFrom(character) + " !" ERROR_AT);
			return;
		}

		error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
		if (error != 0)
		{
			resultError("Error while rendering glyph for character " + String::createFrom(character) + " !" ERROR_AT);
			return;
		}

		const FT_Bitmap& glyphBitmap = face->glyph->bitmap;
		const int left = 0; //face->glyph->bitmap_left + 1;
		const int top = size - face->glyph->bitmap_top + face->descender * size / face->units_per_EM;

		//BL_ASSERT(left >= 0);
		//BL_ASSERT(top + glyphBitmap.rows <= size);

		pixels = &pixels[top * lineStrideInBytes + left];
		for (int y = 0; y < glyphBitmap.rows; ++y)
		{
			for (int x = 0; x < glyphBitmap.width; ++x)
			{
				pixels[y * lineStrideInBytes + x] = memoryAs<uint8>(glyphBitmap.buffer, y * glyphBitmap.pitch + x);
			}
		}
	}
	else
	{
		stateError(FONT_NOT_LOADED);
	}
}



} // namespace System
} // namespace BaseLib
