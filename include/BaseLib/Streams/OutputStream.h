/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Streams_OutputStream_h
#define BaseLib_Streams_OutputStream_h


#include "BaseLib/Strings/String.h"
#include "BaseLib/Containers/Array.h"



namespace BaseLib {
namespace Streams {



using BaseLib::Strings::String;
using BaseLib::Containers::Array;



class OutputStream;

typedef OutputStream& (*OutputStreamManipulator)(OutputStream& outputStream);
typedef const OutputStream& (*ConstOutputStreamManipulator)(const OutputStream& outputStream);



/**
Base-class for all output-streams.
To an OutputStream data of any type can be written with the stream operator >>
or by calling one of the write() functions.
Every OutputStream can be connected to one or more other output-streams.
OutputStream itself actually does nothing but redirecting write-calls to the
corresponding functions at the connected output-streams.
@see @ref BuffersAndStreams InputStream
*/
class BL_EXPORT OutputStream {
public:

	OutputStream();
	explicit OutputStream(const OutputStream& connectToOutputStream);
	OutputStream(const OutputStream& connectToOutputStream1, const OutputStream& connectToOutputStream2);
	virtual ~OutputStream();

	//virtual void close();

	/**
	Flushes all cached write-data of this an all connected streams.
	*/
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
	inline void write(const char8 * source) const { write(String(source)); }
	inline void write(const char16 * source) const { write(String(source)); }

	/**
	Connects the stream to an other OutputStream.
	All write-calls get redirected to the corresponding functions of the connected stream.
	@see disconnectFromStream(), isConnected(), disconnectFromAllStreams()
	*/
	void connectToStream(const OutputStream& newOutputStream);

	/**
	Disconnects the stream from the connected OutputStream.
	@see connectToStream(), isConnected(), disconnectFromAllStreams()
	*/
	void disconnectFromStream(const OutputStream& oldOutputStream);

	/**
	Disconnects the stream from all connected output-stream.
	@see disconnectFromStream(), isConnected(), connectToStream()
	*/
	void disconnectFromAllStreams();

	/**
	Returns if the stream is connected to other output-streams.
	@see connectToStream(), disconnectFromStream()
	*/
	virtual bool isConnected() const;

	/**
	Returns if connected objects get destroyed with this stream.
	@see setOwnerOfConnectedObjects()
	*/
	inline bool isOwnerOfConnectedObjects() const
	{
		return ownerOfConnectedObjects;
	}

	/**
	Sets if connected objects get destroyed with this stream.
	@see isOwnerOfConnectedObjects()
	*/
	inline void setOwnerOfConnectedObjects(bool newOwnerOfConnectedObjects)
	{
		ownerOfConnectedObjects = newOwnerOfConnectedObjects;
	}

	/**
	@todo doku
	*/
	inline int64 getTotalBytesWritten() const
	{
		return totalBytesWritten;
	}

protected:
	
	typedef Array<const OutputStream*> ConnectedStreams;
	ConnectedStreams connectedStreams;
	bool ownerOfConnectedObjects;
	mutable int64 totalBytesWritten;

private:

	template<typename T>
	void writeTemplate(T source) const;
};



template <class T>
inline OutputStream& operator <<(OutputStream& outputStream, const T& source)
{
	outputStream.write(source);
	return outputStream;
}


template <class T>
inline const OutputStream& operator <<(const OutputStream& outputStream, const T& source)
{
	outputStream.write(source);
	return outputStream;
}



inline OutputStream& operator <<(OutputStream& outputStream, const void* source)
{
	outputStream.write(source);
	return outputStream;
}



inline const OutputStream& operator <<(const OutputStream& outputStream, const void* source)
{
	outputStream.write(source);
	return outputStream;
}



inline OutputStream& operator <<(OutputStream& outputStream, const char8 * source)
{
	outputStream.write(String(source));
	return outputStream;
}



inline const OutputStream& operator <<(const OutputStream& outputStream, const char8 * source)
{
	outputStream.write(String(source));
	return outputStream;
}



inline OutputStream& operator <<(OutputStream& outputStream, const char16 * source)
{
	outputStream.write(String(source));
	return outputStream;
}



inline const OutputStream& operator <<(const OutputStream& outputStream, const char16 * source)
{
	outputStream.write(String(source));
	return outputStream;
}



inline OutputStream& operator <<(OutputStream& outputStream, char8 source)
{
	outputStream.write(String(source));
	return outputStream;
}



inline const OutputStream& operator <<(const OutputStream& outputStream, char8 source)
{
	outputStream.write(String(source));
	return outputStream;
}



inline OutputStream& operator <<(OutputStream& outputStream, char16 source)
{
	outputStream.write(String(source));
	return outputStream;
}



inline const OutputStream& operator <<(const OutputStream& outputStream, char16 source)
{
	outputStream.write(String(source));
	return outputStream;
}



inline OutputStream& operator <<(OutputStream& outputStream, OutputStreamManipulator manipulator)
{
	return (*manipulator)(outputStream);
}



inline const OutputStream& operator <<(const OutputStream& outputStream, ConstOutputStreamManipulator manipulator)
{
	return (*manipulator)(outputStream);
}





BL_EXPORT OutputStream& newLine(OutputStream& outputStream);
BL_EXPORT const OutputStream& newLine(const OutputStream& outputStream);

BL_EXPORT OutputStream& backSpace(OutputStream& outputStream);
BL_EXPORT const OutputStream& backSpace(const OutputStream& outputStream);

BL_EXPORT OutputStream& flush(OutputStream& outputStream);
BL_EXPORT const OutputStream& flush(const OutputStream& outputStream);




inline String backSpaces(int count)
{
	BL_ASSERT(count >= 0);
	String result('\b', count);
	result.append(' ', count);
	result.append('\b', count);
	return result;
}



} // namespace Streams
} // namespace BaseLib



#endif // #ifndef BaseLib_Streams_OutputStream_h
