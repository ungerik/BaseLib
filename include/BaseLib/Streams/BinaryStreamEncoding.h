/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_StreamStringEncoding_h
#define BaseLib_StreamStringEncoding_h



#include "BaseLib/Common.h"
#include "BaseLib/Strings/String.h"
#include "BaseLib/Utilities/BitManipulation.h"



namespace BaseLib {
namespace Streams {



using namespace BaseLib::Strings;
using namespace BaseLib::Utilities;



/**
Encoding management for binary streams.
BinaryInputStream and BinaryOutputStream derive from this class.
Because at binary streams every read and write operation of any type is converted
into a binary read/write, there must be a definition what string-encoding (8bit or 16bit Unicode)
and endian should be used.
@see BinaryInputStream, BinaryOutputStream, @ref BuffersAndStreams
*/
class BL_EXPORT BinaryStreamEncoding {
public:

	/**
	String-encoding.
	@see getStringEncoding(), setStringEncoding()
	*/
	enum StringEncoding {
		STRING_IMPLEMENTATION = 0,
		CHAR8 = CHAR8_ENCODING,
		CHAR16 = CHAR16_ENCODING
	};

	/**
	Endian.
	@see getEndian(), setEndian()
	*/
	enum Endian {
		STREAM_IS_SMALL_ENDIAN = SMALL_ENDIAN,
		STREAM_IS_BIG_ENDIAN = BIG_ENDIAN,
		#ifdef BL_CPU_SMALL_ENDIAN
			STREAM_IS_SYSTEM_ENDIAN = SMALL_ENDIAN
		#else
			STREAM_IS_SYSTEM_ENDIAN = BIG_ENDIAN
		#endif
	};

	BinaryStreamEncoding(StringEncoding newStringEncoding = STRING_IMPLEMENTATION, Endian newEndian = STREAM_IS_SYSTEM_ENDIAN);
	virtual ~BinaryStreamEncoding();

	/**
	Returns the current string-encoding.
	@see StringEncoding, setStringEncoding()
	*/
	inline StringEncoding getStringEncoding() const
	{
		return stringEncoding;
	}

	/**
	Sets the current string-encoding.
	@see StringEncoding, getStringEncoding()
	*/
	virtual void setStringEncoding(StringEncoding newStringEncoding);

	/**
	Returns the current endian.
	@see Endian, setEndian()
	*/
	inline Endian getEndian() const
	{
		return endian;
	}

	/**
	Sets the current endian.
	@see Endian getEndian()
	*/
	virtual void setEndian(Endian newEndian);

protected:

	StringEncoding stringEncoding;
	Endian endian;

	inline bool shouldUseUnicode(const String& string) const
	{
		return stringEncoding == STRING_IMPLEMENTATION ? string.getEncoding() != CHAR8_ENCODING : shouldUseUnicode();
	}

	inline bool shouldUseUnicode() const
	{
		return stringEncoding != CHAR8_ENCODING;
	}

	/**
	Returns true if the endian of the stream differs from the system endian.
	@see correctEndian()
	*/
	inline bool mustCorrectEndian() const
	{
		return endian != SYSTEM_ENDIAN;
	}

	/**
	Corrects the endian, if the stream endian differs from the system endian.
	@see mustCorrectEndian(), swapEndian()
	*/
	template<typename T>
	inline T correctEndian(const T& value) const
	{
		return mustCorrectEndian() == true ? swapEndian(value) : value;
	}
};



} // namespace Streams
} // namespace BaseLib



#endif // #ifndef BaseLib_StreamStringEncoding_h