/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_InputStream_h
#define BaseLib_InputStream_h


#include <string>
#include "BaseLib/Common.h"
#include "BaseLib/Streams/OutputStream.h"


namespace BaseLib {
namespace Streams {



using BaseLib::Strings::String;



/**
Base-class for all input-streams.
From an InputStream data of any type can be read with the stream operator <<
or by calling one of the read() functions. The read() functions returns true
if anything has been read within the (optional) timeoutSeconds.
If such information is needed, the stream operators can't be used.
Every InputStream can be connected to another InputStream or a derived class.
InputStream itself actually does nothing but redirecting read-calls to the
corresponding function at the connected InputStream.
An OutputStream can also be connected. Then the data of every read call gets
written to the OutputStream with the corresponding write function.
@see @ref BuffersAndStreams, OutputStream
*/
class BL_EXPORT InputStream {
public:

	InputStream();
	explicit InputStream(const InputStream& connectToInputStream);
	virtual ~InputStream();

	virtual int readBinary(void* destination, int byteCount, double timeoutSeconds) const;
	virtual bool readBinaryComplete(void* destination, int byteCount, double timeoutSeconds) const;
	virtual bool read(bool& destination, double timeoutSeconds) const;
	virtual bool read(void*& destination, double timeoutSeconds) const;
	virtual bool read(int8& destination, double timeoutSeconds) const;
	virtual bool read(uint8& destination, double timeoutSeconds) const;
	virtual bool read(int16& destination, double timeoutSeconds) const;
	virtual bool read(uint16& destination, double timeoutSeconds) const;
	virtual bool read(int32& destination, double timeoutSeconds) const;
	virtual bool read(uint32& destination, double timeoutSeconds) const;
	virtual bool read(int64& destination, double timeoutSeconds) const;
	virtual bool read(uint64& destination, double timeoutSeconds) const;
	virtual bool read(float& destination, double timeoutSeconds) const;
	virtual bool read(double& destination, double timeoutSeconds) const;
	virtual bool read(long double& destination, double timeoutSeconds) const;
	virtual bool read(String& destination, double timeoutSeconds) const;

	inline int readBinary(void* destination, int byteCount) const { return readBinary(destination, byteCount, readTimeoutSeconds); }
	inline bool readBinaryComplete(void* destination, int byteCount) const { return readBinaryComplete(destination, byteCount, readTimeoutSeconds); }
	inline bool read(bool& destination) const { return read(destination, readTimeoutSeconds); }
	inline bool read(void*& destination) const { return read(destination, readTimeoutSeconds); }
	inline bool read(int8& destination) const { return read(destination, readTimeoutSeconds); }
	inline bool read(uint8& destination) const { return read(destination, readTimeoutSeconds); }
	inline bool read(int16& destination) const { return read(destination, readTimeoutSeconds); }
	inline bool read(uint16& destination) const { return read(destination, readTimeoutSeconds); }
	inline bool read(int32& destination) const { return read(destination, readTimeoutSeconds); }
	inline bool read(uint32& destination) const { return read(destination, readTimeoutSeconds); }
	inline bool read(int64& destination) const { return read(destination, readTimeoutSeconds); }
	inline bool read(uint64& destination) const { return read(destination, readTimeoutSeconds); }
	inline bool read(float& destination) const { return read(destination, readTimeoutSeconds); }
	inline bool read(double& destination) const { return read(destination, readTimeoutSeconds); }
	inline bool read(long double& destination) const { return read(destination, readTimeoutSeconds); }
	inline bool read(String& destination) const { return read(destination, readTimeoutSeconds); }

	virtual void unreadBinary(const void* source, int byteCount) const; 
	virtual void unread(bool source) const;
	virtual void unread(const void* source) const;
	virtual void unread(int8 source) const;
	virtual void unread(uint8 source) const;
	virtual void unread(int16 source) const;
	virtual void unread(uint16 source) const;
	virtual void unread(int32 source) const;
	virtual void unread(uint32 source) const;
	virtual void unread(int64 source) const;
	virtual void unread(uint64 source) const;
	virtual void unread(float source) const;
	virtual void unread(double source) const;
	virtual void unread(long double source) const;
	virtual void unread(const String& source) const;

	template <typename T>
	inline bool operator >>(T& destination) const
	{
		return read(destination);
	}	

	/**
	Connects the stream to an other InputStream.
	All read-calls get redirected to the corresponding functions of the connected stream.
	@see disconnectFromStream(), isConnected()
	*/
	virtual void connectToStream(const InputStream& newInputStream);

	/**
	Disconnects the stream from the connected InputStream.
	@see connectToStream(), isConnected()
	*/
	void disconnectFromStream();

	/**
	Connects an OutpustStream to the InputStream.
	The data of every read call gets written to the OutputStream with the corresponding write function.
	@see disconnectOutputStream(), connectToStream()
	*/
	void connectOutputStream(const OutputStream& newOutputStream);

	/**
	Disconnects the OutpustStream from the InputStream.
	The data of every read call gets written to the OutputStream with the corresponding write function.
	@see disconnectOutputStream(), disconnectFromStream()
	*/
	void disconnectOutputStream();

	/**
	Returns if the stream is connected to an other InputStream.
	@see connectToStream(), disconnectFromStream()
	*/
	virtual bool isConnected() const;

	/**
	Returns if there is data available for the next read call.
	*/
	virtual bool isInputAvailable() const;

	/**
	Returns the read-timeout in seconds.
	The timeout can be zero. In this case the read-calls return immediately.
	@see setReadTimeoutSeconds()
	*/
	inline double getReadTimeoutSeconds() const
	{
		return readTimeoutSeconds;
	}

	/**
	Sets the read-timeout in seconds.
	The timeout can be zero. In this case the read-calls return immediately.
	@see getReadTimeoutSeconds()
	*/
	void setReadTimeoutSeconds(double newReadTimeoutSeconds);

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
	Returns the value of a read byte counter.
	@see getTotalBytesRead() setTotalBytesRead()
	*/
	inline int getTotalBytesReadAsInt() const
	{
		return static_cast<int>(totalBytesRead);
	}

	/**
	Returns the value of a read byte counter.
	@see getTotalBytesReadAsInt() setTotalBytesRead()
	*/
	inline int64 getTotalBytesRead() const
	{
		return totalBytesRead;
	}

	/**
	Sets the value of the read byte counter.
	@see getTotalBytesRead()
	*/
	inline void setTotalBytesRead(int64 newTotalBytesRead)
	{
		totalBytesRead = newTotalBytesRead;
	}

protected:
	
	const InputStream* connectedStream;
	mutable const OutputStream* echoStream;

	double readTimeoutSeconds;
	mutable int64 totalBytesRead;
	///bool unicode;
	bool ownerOfConnectedObjects;

private:

	template<typename T>
	bool readTemplate(T& destination, double timeoutSeconds) const;

	template<typename T>
	void unreadTemplate(T source) const;

};



template <>
inline bool InputStream::operator >>(std::string& destination) const
{
	String stringDestination = destination;
	const bool result = read(stringDestination);
	if (result == true)	destination = stringDestination;
	return result;
}	



template <>
inline bool InputStream::operator >>(std::wstring& destination) const
{
	String stringDestination = destination;
	const bool result = read(stringDestination);
	if (result == true)	destination = stringDestination;
	return result;
}	




} // namespace Streams
} // namespace BaseLib




#endif // #ifndef BaseLib_InputStream_h
