/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_HTTP_Message_h
#define BaseLib_HTTP_Message_h



#include "BaseLib/Network/Socket.h"
#include "BaseLib/Streams/InputStream.h"
#include "BaseLib/Streams/OutputStream.h"
#include <map>


namespace BaseLib {
namespace Network {
namespace HTTP {


using BaseLib::Streams::InputStream;
using BaseLib::Streams::OutputStream;
class HeaderField;



class Message {
public:

	String getHeaderField(const String& headerFieldName) const;
	void setHeaderField(const String& headerFieldName, const String& newHeaderFieldValue);

	void send() const;
	void send(OutputStream& outputStream) const;
	inline void send(Socket& socket) const
	{
		send( socket.outputStream() );
	}

	Message* receive();
	Message* receive(InputStream& inputStream);


protected:

	typedef std::map<String, HeaderField*> HeaderFields;
	HeaderFields headerFields;
};



/*
inline InputStream& operator>>(InputStream& inputStream, Message& destination)
{
	/// ?
	return inputStream;
}



inline OutputStream& operator<<(OutputStream& outputStream, const Message& source)
{
	source.send(outputStream);
	return outputStream;
}
*/


} // namespace HTTP
} // namespace Network
} // namespace BaseLib


#endif // #ifndef BaseLib_HTTP_Message_h
