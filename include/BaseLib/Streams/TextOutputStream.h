/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_TextOutputStream_h
#define BaseLib_TextOutputStream_h


#include "BaseLib/Streams/OutputStream.h"



namespace BaseLib {
namespace Buffers { class AbstractTextBuffer; }
namespace Streams {

using BaseLib::Buffers::AbstractTextBuffer;


class TextOutputStream;

typedef TextOutputStream& (*TextOutputStreamManipulator)(TextOutputStream& textOutputStream);
typedef const TextOutputStream& (*ConstTextOutputStreamManipulator)(const TextOutputStream& textOutputStream);



/**
Not implemented.
*/
class BL_EXPORT TextOutputStream : public OutputStream {
public:

	TextOutputStream();
	explicit TextOutputStream(const OutputStream& connectToOutputStream);
	TextOutputStream(const OutputStream& connectToOutputStream1, const OutputStream& connectToOutputStream2);
	explicit TextOutputStream(AbstractTextBuffer& connectToBuffer);

	virtual ~TextOutputStream();

	//virtual void close();
	virtual void flush() const;

	virtual void writeBinary(const void* source, int byteCount) const;
	virtual void write(bool source) const;
	virtual void write(const void* source) const;
	virtual void write(int8 source) const;
	virtual void write(uint8 source) const;
	virtual void write(int16 source) const;
	virtual void write(uint16 source) const;
	virtual void write(int32 source) const;
	virtual void write(uint32 source) const;
	virtual void write(int64 source) const;
	virtual void write(uint64 source) const;
	virtual void write(float source) const;
	virtual void write(double source) const;
	virtual void write(long double source) const;
	virtual void write(const String& source) const;

	///virtual void writeNewLine() const;

	void connectToTextBuffer(AbstractTextBuffer& newBuffer);
	virtual void disconnectFromTextBuffer(AbstractTextBuffer& oldBuffer);

	virtual bool isConnected() const;

	String stringTerminator;

	bool useWideString;

	enum WriteBinaryMethod {
		WRITE_BINARY_AS_HEX_STRING,
		WRITE_BINARY_AS_BIN_STRING
	};

	inline WriteBinaryMethod getWriteBinaryMethod() const { return writeBinaryMethod; }
	inline void setWriteBinaryMethod(WriteBinaryMethod newWriteBinaryMethod) { writeBinaryMethod = newWriteBinaryMethod; }


	/// insert loggin functionality! (indent etc.)


protected:
	
	typedef Array<AbstractTextBuffer*> ConnectedTextBuffers;
	ConnectedTextBuffers connectedTextBuffers;

	WriteBinaryMethod writeBinaryMethod;

private:

	template<typename T>
	void writeTemplate(const T source) const;
};



template <class T>
inline TextOutputStream& operator <<(TextOutputStream& textOutputStream, const T& source)
{
	textOutputStream.write(source);
	return textOutputStream;
}



template <class T>
inline const TextOutputStream& operator <<(const TextOutputStream& textOutputStream, const T& source)
{
	textOutputStream.write(source);
	return textOutputStream;
}



inline TextOutputStream& operator<<(TextOutputStream& textOutputStream, OutputStreamManipulator manipulator)
{
	(*manipulator)(textOutputStream);
	return textOutputStream;
}



inline const TextOutputStream& operator<<(const TextOutputStream& textOutputStream, ConstOutputStreamManipulator manipulator)
{
	(*manipulator)(textOutputStream);
	return textOutputStream;
}



inline TextOutputStream& operator<<(TextOutputStream& textOutputStream, TextOutputStreamManipulator manipulator)
{
	return (*manipulator)(textOutputStream);
}



inline const TextOutputStream& operator<<(const TextOutputStream& textOutputStream, ConstTextOutputStreamManipulator manipulator)
{
	return (*manipulator)(textOutputStream);
}



inline TextOutputStream& operator<<(TextOutputStream& textOutputStream, const void* source)
{
	textOutputStream.write(source);
	return textOutputStream;
}



inline const TextOutputStream& operator<<(const TextOutputStream& textOutputStream, const void* source)
{
	textOutputStream.write(source);
	return textOutputStream;
}



inline TextOutputStream& operator<<(TextOutputStream& textOutputStream, const char8 * source)
{
	textOutputStream.write(String(source));
	return textOutputStream;
}



inline const TextOutputStream& operator<<(const TextOutputStream& textOutputStream, const char8 * source)
{
	textOutputStream.write(String(source));
	return textOutputStream;
}



inline TextOutputStream& operator<<(TextOutputStream& textOutputStream, const char16 * source)
{
	textOutputStream.write(String(source));
	return textOutputStream;
}



inline const TextOutputStream& operator<<(const TextOutputStream& textOutputStream, const char16 * source)
{
	textOutputStream.write(String(source));
	return textOutputStream;
}



} // namespace Streams
} // namespace BaseLib



#endif // #ifndef BaseLib_TextOutputStream_h
