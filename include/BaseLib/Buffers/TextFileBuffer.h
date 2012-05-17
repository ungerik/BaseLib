/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Buffers_TextFileBuffer_h
#define BaseLib_Buffers_TextFileBuffer_h



#include "BaseLib/Buffers/TextBuffer.h"
#include "BaseLib/Buffers/BinaryFileBuffer.h"



namespace BaseLib {
namespace Buffers {



/**
Not implemented yet.
*/
class BL_EXPORT TextFileBuffer : public TextBuffer {
public:

	explicit TextFileBuffer(const String& fileName, bool read = true, bool write = true);
	virtual ~TextFileBuffer();

	virtual bool isReadable() const;
	virtual bool isWriteable() const;

	virtual void flush();

	virtual void close();

	inline const String& getFileName()
	{
		return name;
	}

protected:

	const String name;
	const bool readable;
	const bool writeable;
};



} // namespace Buffers
} // namespace BaseLib



#endif // #ifndef BaseLib_Buffers_TextFileBuffer_h
