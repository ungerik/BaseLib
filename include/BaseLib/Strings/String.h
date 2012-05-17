/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Strings_String_h
#define BaseLib_Strings_String_h



#include "BaseLib/Common.h"
#include "BaseLib/Strings/AbstractStringImplementation.h"
#include "BaseLib/Utilities/BitManipulation.h"
#include "BaseLib/Containers/Enumeration.h"
#include <string>



//#include "BaseLib/Reflection/Object.h" // circular
//#include "BaseLib/Containers/Array.h" //circular include!!



#ifdef BL_COMPILER_MSVC
	#pragma warning (disable:4348)	// disable redefinition of default parameter
#endif



namespace BaseLib {
	namespace Containers {
		template<typename T, int CAPACITY>
		class Array_BufferPolicy_Dynamic;

		#ifdef BL_COMILER_GCC
			template<typename T, int CAPACITY = -1, template<typename, int> class BufferPolicy = Array_BufferPolicy_Dynamic>
			class Array;
		#else
			template<typename T, int CAPACITY = -1, template<typename, int> class BufferPolicy = Array_BufferPolicy_Dynamic>
			class Array;
		#endif
	}
}



namespace BaseLib {
namespace Strings {



using BaseLib::Containers::Enumeration;
using BaseLib::Containers::Array;
using BaseLib::Containers::Array_BufferPolicy_Dynamic;
using BaseLib::Utilities::AutoPointer;



// Predefine Match
class RegExMatch;
class NumberFormat;



/**
String with an intern implementation object.
Via the intern implementation object String supports different
string-types as 8bit character and 16bit characters.
@see StringTokenizer

@note Be aware of http://msdn2.microsoft.com/en-us/library/ms364057(VS.80).aspx
@todo Test if it applies
*/
class BL_EXPORT String /*: public BaseLib::Reflection::Object*/ {
public:

	enum DefaultIndices {
		BEGIN = 0,
		END = -1
	};

	/**
	Returns the position of the reverse beginnig (length-1).
	@see reverseEnd()
	*/
	inline int reverseBegin() const
	{
		return getLength() - 1;
	}

	/**
	Returns the position of the reverse end (-1).
	@see reverseBegin()
	*/
	inline static int reverseEnd()
	{
		return -1;
	}

	/**
	Returns the default StringEncoding.
	This encoding is used as default parameter for all new String instances.
	@see setDefaultEncoding(), StringEncoding
	*/
	inline static StringEncoding getDefaultEncoding()
	{
		return defaultEncoding;
	}

	/**
	Sets the default StringEncoding.
	This encoding is used as default parameter for all new String instances.
	@see getDefaultEncoding(), StringEncoding
	*/
	static void setDefaultEncoding(StringEncoding newDefaultEncoding);


	#include "BaseLib/Strings/String_Char.inl.h"
	#include "BaseLib/Strings/String_ConstChar.inl.h"


	typedef Char ValueType;
	typedef Char& ReferenceType;

	//BL_DECLARE_REFLECTION_BASELIB_BASE_CLASS(BaseLib::Strings::String);

	#include "BaseLib/Strings/String_Constructors.inl.h"

	#include "BaseLib/Strings/String_Factories.inl.h"

	#include "BaseLib/Strings/String_Operators.inl.h"

	void* parsePointer(int start = 0, int length = END) const;
	bool parseBool(int start = 0, int length = END) const;
	uint parseUint(int start = 0, int length = END) const;
	int parseInt(int start = 0, int length = END) const;
	uint8 parseUint8(int start = 0, int length = END) const;
	int8 parseInt8(int start = 0, int length = END) const;
	uint16 parseUint16(int start = 0, int length = END) const;
	int16 parseInt16(int start = 0, int length = END) const;
	uint32 parseUint32(int start = 0, int length = END) const;
	int32 parseInt32(int start = 0, int length = END) const;
	uint64 parseUint64(int start = 0, int length = END) const;
	int64 parseInt64(int start = 0, int length = END) const;
	float parseFloat(int start = 0, int length = END) const;
	double parseDouble(int start = 0, int length = END) const;
	long double parseLongDouble(int start = 0, int length = END) const;

	inline void* const& parse(void*& result, int start = 0, int length = END) const
	{
		result = parsePointer(start, length);
		return result;
	}
	
	inline const bool& parse(bool& result, int start = 0, int length = END) const
	{
		result = parseBool(start, length);
		return result;
	}
	
	inline const uint8& parse(uint8& result, int start = 0, int length = END) const
	{
		result = parseUint8(start, length);
		return result;
	}
	
	inline const int8& parse(int8& result, int start = 0, int length = END) const
	{
		result = parseInt8(start, length);
		return result;
	}

	inline const uint16& parse(uint16& result, int start = 0, int length = END) const
	{
		result = parseUint16(start, length);
		return result;
	}
	
	inline const int16& parse(int16& result, int start = 0, int length = END) const
	{
		result = parseInt16(start, length);
		return result;
	}

	inline const uint32& parse(uint32& result, int start = 0, int length = END) const
	{
		result = parseUint32(start, length);
		return result;
	}
	
	inline const int32& parse(int32& result, int start = 0, int length = END) const
	{
		result = parseInt32(start, length);
		return result;
	}

	inline const uint64& parse(uint64& result, int start = 0, int length = END) const
	{
		result = parseUint64(start, length);
		return result;
	}
	
	inline const int64& parse(int64& result, int start = 0, int length = END) const
	{
		result = parseInt64(start, length);
		return result;
	}

	inline const float& parse(float& result, int start = 0, int length = END) const
	{
		result = parseFloat(start, length);
		return result;
	}

	inline const double& parse(double& result, int start = 0, int length = END) const
	{
		result = parseDouble(start, length);
		return result;
	}

	inline const long double& parse(long double& result, int start = 0, int length = END) const
	{
		result = parseLongDouble(start, length);
		return result;
	}


	bool tryParse(const void*& result, int start = 0, int length = END) const;
	bool tryParse(bool& result, int start = 0, int length = END) const;
	bool tryParse(uint8& result, int start = 0, int length = END) const;
	bool tryParse(int8& result, int start = 0, int length = END) const;
	bool tryParse(uint16& result, int start = 0, int length = END) const;
	bool tryParse(int16& result, int start = 0, int length = END) const;
	bool tryParse(uint32& result, int start = 0, int length = END) const;
	bool tryParse(int32& result, int start = 0, int length = END) const;
	bool tryParse(uint64& result, int start = 0, int length = END) const;
	bool tryParse(int64& result, int start = 0, int length = END) const;
	bool tryParse(float& result, int start = 0, int length = END) const;
	bool tryParse(double& result, int start = 0, int length = END) const;
	bool tryParse(long double& result, int start = 0, int length = END) const;
	


	template<class T>
	String& assign(const T& value)
	{
		*this = String::createFrom(value);
		return *this;
	}

	// Direct mapping from AbstractStringImplementation:


	inline StringEncoding getEncoding() const
	{
		return implementation->getEncoding();
	}

	inline int getByteSize() const
	{
		#ifdef NO_SUBSTRING_OPTIMIZATION
			return implementation->getByteSize();
		#else
			int length = implementation->getLength();
			BL_ASSERT(start + range <= length);
			return length != 0 ? implementation->getCharacterByteSize() * range : 0;
		#endif
	}

	inline bool isEmpty() const
	{
		return getLength() == 0;
	}

	inline int getLength() const
	{
		#ifdef NO_SUBSTRING_OPTIMIZATION
			return implementation->getLength();
		#else
			return range;
		#endif
	}

	inline String& setLength(int newLength)
	{
		if (newLength != getLength() && newLength != END)
		{
			#ifdef NO_SUBSTRING_OPTIMIZATION
				getUnsharedImplementation(newLength);
			#else
				if (newLength < range || newLength <= implementation->getLength())
				{
					range = newLength;
				}
				else
				{
					getUnsharedImplementation(newLength);
				}
			#endif
		}
		return *this;
	}

	inline String& insert(int position, int length = 1)
	{
		if (length > 0)
		{
			getUnsharedImplementation()->insert(position, length);
			#ifndef NO_SUBSTRING_OPTIMIZATION
				range += length;
			#endif
		}
		return *this;
	}

	inline String& remove(int position, int length = 1)
	{
		if (length > 0)
		{
			getUnsharedImplementation()->remove(position, length);
			#ifndef NO_SUBSTRING_OPTIMIZATION
				range -= length;
			#endif
		}
		return *this;
	}

	inline String& fill(char8 fillerChar, int position = 0, int length = END)
	{
		if (length == END) length = getLength() - position;
		if (length > 0)
		{
			getUnsharedImplementation()->fill(fillerChar, position, length);
		}
		return *this;
	}

	inline String& fill(char16 fillerChar, int position = 0, int length = END)
	{
		if (length > 0)
		{
			getUnsharedImplementation()->fill(fillerChar, position, length);
		}
		return *this;
	}

	inline String& lowerCase(int position = 0, int length = END)
	{
		if (length == END) length = getLength() - position;
		if (length > 0)
		{
			getUnsharedImplementation()->lowerCase(position, length);
		}
		return *this;
	}

	inline String& upperCase(int position = 0, int length = END)
	{
		if (length == END) length = getLength() - position;
		if (length > 0)
		{
			getUnsharedImplementation()->upperCase(position, length);
		}
		return *this;
	}

	inline char8 getLowerCaseChar8(int position) const
	{
		#ifndef NO_SUBSTRING_OPTIMIZATION
			position += start;
		#endif
		return implementation->getLowerCaseChar8(position);
	}

	inline char16 getLowerCaseChar16(int position) const
	{
		#ifndef NO_SUBSTRING_OPTIMIZATION
			position += start;
		#endif
		return implementation->getLowerCaseChar16(position);
	}

	inline char32 getLowerCaseChar32(int position) const
	{
		#ifndef NO_SUBSTRING_OPTIMIZATION
			position += start;
		#endif
		return implementation->getLowerCaseChar32(position);
	}

	inline char8 getUpperCaseChar8(int position) const
	{
		#ifndef NO_SUBSTRING_OPTIMIZATION
			position += start;
		#endif
		return implementation->getUpperCaseChar8(position);
	}

	inline char16 getUpperCaseChar16(int position) const
	{
		#ifndef NO_SUBSTRING_OPTIMIZATION
			position += start;
		#endif
		return implementation->getUpperCaseChar16(position);
	}

	inline char32 getUpperCaseChar32(int position) const
	{
		#ifndef NO_SUBSTRING_OPTIMIZATION
			position += start;
		#endif
		return implementation->getUpperCaseChar32(position);
	}

	inline char8 getChar8(int position) const
	{
		#ifndef NO_SUBSTRING_OPTIMIZATION
			position += start;
		#endif
		return implementation->getChar8(position);
	}

	inline char16 getChar16(int position) const
	{
		#ifndef NO_SUBSTRING_OPTIMIZATION
			position += start;
		#endif
		return implementation->getChar16(position);
	}

	inline char32 getChar32(int position) const
	{
		#ifndef NO_SUBSTRING_OPTIMIZATION
			position += start;
		#endif
		return implementation->getChar32(position);
	}

	inline String& setChar(int position, char8 character)
	{
		getUnsharedImplementation()->setChar(position, character);
		return *this;
	}

	inline String& setChar(int position, char16 character)
	{
		getUnsharedImplementation()->setChar(position, character);
		return *this;
	}

	inline String& setChar(int position, char32 character)
	{
		getUnsharedImplementation()->setChar(position, character);
		return *this;
	}

	String& copyFromString(const String& source, int sourcePosition = 0, int destPosition = 0, int length = END);

	inline String& copyFromCharArray(const char8 * source, int destStartPosition, int length)
	{
		if (length > 0)
		{
			getUnsharedImplementation()->copyFromCharArray(source, destStartPosition, length);
		}
		return *this;
	}

	/*
	inline void copyToCharArray(char8 * destination) const // size+1 as length allowed -> copies terminating 0
	{
		implementation->copyToCharArray(destination, sourceStartPosition, length);
	}
	*/

	inline void copyToCharArray(char8 * destination, int sourceStartPosition, int length) const // size+1 as length allowed -> copies terminating 0
	{
		#ifndef NO_SUBSTRING_OPTIMIZATION
			sourceStartPosition += start;
		#endif
		implementation->copyToCharArray(destination, sourceStartPosition, length);
	}

	inline String& copyFromCharArray(const char16 * source, int destStartPosition, int length)
	{
		if (length > 0)
		{
			getUnsharedImplementation()->copyFromCharArray(source, destStartPosition, length);
		}
		return *this;
	}

	inline void copyToCharArray(char16 * destination, int sourceStartPosition, int length) const // size+1 as length allowed -> copies terminating 0
	{
		#ifndef NO_SUBSTRING_OPTIMIZATION
			sourceStartPosition += start;
		#endif
		implementation->copyToCharArray(destination, sourceStartPosition, length);
	}

	inline const void * getPointer() const
	{
		#ifdef NO_SUBSTRING_OPTIMIZATION
			return implementation->getPointer();
		#else
			return offsetPointer(implementation->getPointer(), start * implementation->getCharacterByteSize());
		#endif
	}

	inline const char8 * getChar8Array() const
	{
		#ifdef NO_SUBSTRING_OPTIMIZATION
			return implementation->getChar8Array();
		#else
			return offsetPointer(implementation->getChar8Array(), start * sizeof(char8));
		#endif
	}

	inline const char16 * getChar16Array() const
	{
		#ifdef NO_SUBSTRING_OPTIMIZATION
			return implementation->getChar16Array();
		#else
			return offsetPointer(implementation->getChar16Array(), start * sizeof(char16));
		#endif
	}

	inline const char8 * getChar8CString() const
	{
		#ifdef NO_SUBSTRING_OPTIMIZATION
			return implementation->getChar8CString();
		#else
			if (start + range == implementation->getLength())
			{
				return offsetPointer(implementation->getChar8CString(), start * sizeof(char8));
			}
			else
			{
				return const_cast<String*>(this)->getUnsharedImplementation()->getChar8CString();
			}
		#endif
	}

	inline const char16 * getChar16CString() const
	{
		#ifdef NO_SUBSTRING_OPTIMIZATION
			return implementation->getChar16CString();
		#else
			if (start + range == implementation->getLength())
			{
				return offsetPointer(implementation->getChar16CString(), start * sizeof(char16));
			}
			else
			{
				return const_cast<String*>(this)->getUnsharedImplementation()->getChar16CString();
			}
		#endif
	}


	// STL compatibility functions:

	/*inline int length() const
	{
		return getLength();
	}

	inline const char16 * data() const
	{
		return getChar16Array();
	}

	inline const char16 * c_str() const
	{
		return getChar16CString();
	}

	inline Char front()
	{
		return operator[](0);
	}

	inline Char back()
	{
		return operator[](length()-1);
	}*/

	inline void swap(String& other)
	{
		BaseLib::swap(implementation, other.implementation);

		#ifndef NO_SUBSTRING_OPTIMIZATION
			BaseLib::swap(start, other.start);
			BaseLib::swap(range, other.range);
		#endif
	}

	// Additional functions:

	String& insert(String stringToInsert, int position = 0, int count = 1);
	String& insert(char8 charToInsert, int position = 0, int count = 1);
	String& insert(char16 charToInsert, int position = 0, int count = 1);
	String& insert(const Char& charToInsert, int position = 0, int count = 1);
	String& insert(const ConstChar& charToInsert, int position = 0, int count = 1);

	String& fill(const Char& fillerChar, int position = 0, int length = END);
	String& fill(const ConstChar& fillerChar, int position = 0, int length = END);

	inline AbstractStringImplementation* getImplementation()
	{
		return implementation;
	}

	inline const AbstractStringImplementation* getImplementation() const
	{
		return implementation;
	}
	
	virtual void setImplementation(AbstractStringImplementation* newImplementation, bool releaseOldImplementation = true);

	String& append(char8 character, int count = 1);
	String& append(char16 character, int count = 1);
	String& append(const String& string, int count = 1);

	inline String subString(int position, int length = END) const
	{
		if (position == END)
		{
			position = 0;
			length = 0;
		}
		else if (length == END)
		{
			length = getLength() - position;
		}

		#ifndef NO_SUBSTRING_OPTIMIZATION
			implementation->addReference();
			return String(implementation, position + start, length);
		#else
			return String(implementation->clone(position, length));
		#endif
	}

	String lowerCaseSubString(int position, int length = END) const;
	String upperCaseSubString(int position, int length = END) const;

	inline String lowerCaseString() const
	{
		return lowerCaseSubString(0, END);
	}

	inline String upperCaseString() const
	{
		return upperCaseSubString(0, END);
	}

	void replace(int position, int length, const String& replaceString);

	int searchAndReplace(const String& searchString, const String& replaceString);
	int searchAndReplaceCaseInsensitive(const String& searchString, const String& replaceString);

	int searchAndRemove(const String& searchString);
	int searchAndRemoveCaseInsensitive(const String& searchString);

	int findFirst(char8 character, int position = 0, int length = END) const;
	int findFirst(char16 character, int position = 0, int length = END) const;
	int findFirst(const String& findString, int position = 0, int length = END) const;

	int findFirstCaseInsensitive(char8 character, int position = 0, int length = END) const;
	int findFirstCaseInsensitive(char16 character, int position = 0, int length = END) const;
	int findFirstCaseInsensitive(const String& findString, int position = 0, int length = END) const;

	inline int findFirst(const Char& character, int position = 0, int length = END) const
	{
		return findFirst(character.operator char16(), position, length);
	}

	inline int findFirst(const ConstChar& character, int position = 0, int length = END) const
	{
		return findFirst(character.operator char16(), position, length);
	}

	inline int findFirstCaseInsensitive(const Char& character, int position = 0, int length = END) const
	{
		return findFirstCaseInsensitive(character.operator char16(), position, length);
	}

	inline int findFirstCaseInsensitive(const ConstChar& character, int position = 0, int length = END) const
	{
		return findFirstCaseInsensitive(character.operator char16(), position, length);
	}

	int findLast(char8 character, int position = 0, int length = END) const;
	int findLast(char16 character, int position = 0, int length = END) const;
	int findLast(const String& findString, int position = 0, int length = END) const;

	int findLastCaseInsensitive(char8 character, int position = 0, int length = END) const;
	int findLastCaseInsensitive(char16 character, int position = 0, int length = END) const;
	int findLastCaseInsensitive(const String& findString, int position = 0, int length = END) const;

	inline int findLast(const Char& character, int position = 0, int length = END) const
	{
		return findLast(character.operator char16(), position, length);
	}

	inline int findLast(const ConstChar& character, int position = 0, int length = END) const
	{
		return findLast(character.operator char16(), position, length);
	}

	inline int findLastCaseInsensitive(const Char& character, int position = 0, int length = END) const
	{
		return findLastCaseInsensitive(character.operator char16(), position, length);
	}

	inline int findLastCaseInsensitive(const ConstChar& character, int position = 0, int length = END) const
	{
		return findLastCaseInsensitive(character.operator char16(), position, length);
	}

	int findFirstOf(const String& findChars, int position = 0, int length = END) const;
	int findFirstNotOf(const String& findChars, int position = 0, int length = END) const;
	int findLastOf(const String& findChars, int position = 0, int length = END) const;
	int findLastNotOf(const String& findChars, int position = 0, int length = END) const;

	int findFirstOfCaseInsensitive(const String& findChars, int position = 0, int length = END) const;
	int findFirstNotOfCaseInsensitive(const String& findChars, int position = 0, int length = END) const;
	int findLastOfCaseInsensitive(const String& findChars, int position = 0, int length = END) const;
	int findLastNotOfCaseInsensitive(const String& findChars, int position = 0, int length = END) const;


	bool isBin() const;
	bool isDec() const;
	bool isFloat() const;
	bool isHex() const;
	void hexToBinary(void* resultBuffer, bool rightToLeft = false, int position = 0, int length = END) const;
	void base64ToBinary(void* resultBuffer, int position = 0, int length = END) const; /// not implemented!
	void binNumberToBinary(void* resultBuffer, bool rightToLeft = false, int position = 0, int length = END) const; /// not implemented!

	static String binaryToHex(const void* sourceBuffer, int length, bool rightToLeft = false, StringEncoding stringEncoding = getDefaultEncoding()); /// not implemented!
	static String binaryToBase64(const void* sourceBuffer, int length, StringEncoding stringEncoding = getDefaultEncoding()); /// not implemented!
	static String binaryToBinNumber(const void* sourceBuffer, int length, StringEncoding stringEncoding = getDefaultEncoding()); /// not implemented!
	
	String& trimFrontAndTail(const String& charsToTrim = " \b\f\n\r\t");
	String& trimFrontAndTail(const String& charsToTrimAtFront, const String& charsToTrimAtTail);
	String& trimFront(const String& charsToTrim = " \b\f\n\r\t");
	String& trimTail(const String& charsToTrim = " \b\f\n\r\t");

	String& trimFrontAndTailCaseInsensitive(const String& charsToTrim = " \b\f\n\r\t");
	String& trimFrontAndTailCaseInsensitive(const String& charsToTrimAtFront, const String& charsToTrimAtTail);
	String& trimFrontCaseInsensitive(const String& charsToTrim = " \b\f\n\r\t");
	String& trimTailCaseInsensitive(const String& charsToTrim = " \b\f\n\r\t");

	String& trimFrontAndTailBy(int frontChars, int tailChars);

	inline String& trimFrontBy(int frontChars)
	{
		BL_ASSERT(frontChars >= 0);
		return remove(0, frontChars);
	}

	inline String& trimTailBy(int tailChars)
	{
		BL_ASSERT(tailChars >= 0);
		return setLength(getLength() - tailChars);
	}

	bool equalsCaseInsensitive(const String& compareString) const;

	int compare(const String& compareString) const;

	bool regExMatch(const String& expression, BaseLib::Functors::Enumerator<RegExMatch*>& matches) const;
	bool regExSearch(const String& expression, BaseLib::Functors::Enumerator<RegExMatch*>& matches) const;
//	bool regExSearch(const String& expression, RegExMultipleMatches& results) const;
	bool regExSearch(const String& expression, BaseLib::Functors::Enumerator<BaseLib::Containers::Enumeration<RegExMatch*>*>& results) const;
	String regExReplace(const String& expression, const String& replace);

	bool beginsWith(const String& compareString, int compareStringPosition = 0, int compareStringLength = END) const;
	bool endsWith(const String& compareString, int compareStringPosition = 0, int compareStringLength = END) const;

	bool beginsCaseInsensitiveWith(const String& compareString, int compareStringPosition = 0, int compareStringLength = END) const;
	bool endsCaseInsensitiveWith(const String& compareString, int compareStringPosition = 0, int compareStringLength = END) const;

	void ensureBeginsWith(const String& compareString, int compareStringPosition = 0, int compareStringLength = END);
	void ensureEndsWith(const String& compareString, int compareStringPosition = 0, int compareStringLength = END);

	void ensureBeginsCaseInsensitiveWith(const String& compareString, int compareStringPosition = 0, int compareStringLength = END);
	void ensureEndsCaseInsensitiveWith(const String& compareString, int compareStringPosition = 0, int compareStringLength = END);

	inline int hash() const
	{
		#ifdef NO_SUBSTRING_OPTIMIZATION
			return getImplementation()->hash(0, getLength());
		#else
			return getImplementation()->hash(start, range);
		#endif
	}


#ifndef BL_COMPILER_GCC

protected:
	#include "BaseLib/Strings/String_CharIterator.inl.h"

protected:
	#include "BaseLib/Strings/String_CharEnumeration.inl.h"

#endif

protected:

	static StringEncoding defaultEncoding;

	AbstractStringImplementation* implementation;

	#ifndef NO_SUBSTRING_OPTIMIZATION
		int start;
		int range;
	#endif

	inline AbstractStringImplementation* getUnsharedImplementation()
	{
		#ifdef NO_SUBSTRING_OPTIMIZATION
			return implementation = implementation->getUnsharedInstance();
		#else
			implementation = implementation->getUnsharedInstance(start, range);
			start = 0;
			return implementation;
		#endif
	}

	inline AbstractStringImplementation* getUnsharedImplementation(int length)
	{
		#ifdef NO_SUBSTRING_OPTIMIZATION
			return implementation = implementation->getUnsharedInstance(length);
		#else
			implementation = implementation->getUnsharedInstance(start, length);
			start = 0;
			range = length;
			return implementation;
		#endif
	}

};



template<typename T>
inline int zeroTerminatedStringLength(const T * string)
{
	int l = 0;
	while (string[l] != 0) ++l;
	return l;
}



typedef BaseLib::Containers::EnumerationForCArray<String> StringArrayEnumeration;



#include "BaseLib/Strings/String_GlobalOperators.inl.h"
#include "BaseLib/Strings/String_Matches.inl.h"



} // namespace Strings



namespace Utilities {



//template<>
//inline int hash(const BaseLib::Strings::String& string)
//{
//	return string.hash();
//}



} // namespace Utilities



} // namespace BaseLib



#endif // #ifndef BaseLib_Strings_String_h
