/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Network/SmtpServerConnection.h"

namespace BaseLib {
namespace Network {


/*
SmtpServerConnection::SmtpServerConnection(const IpAddress& newAddress)
  : address(newAddress)
  , from()
  , fromDomain()
{
	if (address.getPort() == 0) address.setPort(25);
}



SmtpServerConnection::SmtpServerConnection(const String& newAddress, uint16 port)
  : address(newAddress)
  , from()
  , fromDomain()
{
	if (port == 0) port = 25;
	if (address.getPort() == 0) address.setPort(port);
}



SmtpServerConnection::SmtpServerConnection(const std::wstring& newAddress, uint16 port)
  : address(newAddress)
  , from()
  , fromDomain()
{
	if (port == 0) port = 25;
	if (address.getPort() == 0) address.setPort(port);
}



void SmtpServerConnection::setAddress(const IpAddress& newAddress)
{
	address = newAddress;
	if (address.getPort() == 0) address.setPort(25);
}



void SmtpServerConnection::setAddress(const String& newAddress, uint16 port)
{
	address = newAddress;
	if (port == 0) port = 25;
	if (address.getPort() == 0) address.setPort(port);
}



void SmtpServerConnection::setAddress(const std::wstring& newAddress, uint16 port)
{
	address = newAddress;
	if (port == 0) port = 25;
	if (address.getPort() == 0) address.setPort(port);
}



void SmtpServerConnection::setFrom(const String newFrom)
{
	from = newFrom;
}



void SmtpServerConnection::setFromDomain(const String& newFromDomain)
{
	fromDomain = newFromDomain;
}



String SmtpServerConnection::getFromDomain(const String& from) const
{
	String result = from;
	if (result.empty() == true) result = fromDomain;
	if (result.empty() == true) result = this->from;
	if (result.empty() == true) result = "unknown";

	const size_t pos = result.find('@');
	if (pos != String::npos && pos < result.length()-1) result = result.substr(pos+1);

	return result;
}



void SmtpServerConnection::send(const String& message, const String& to, const String& from, const String& fromDomain)
{
	send(message, StringList(1, to), from, fromDomain);
}



void SmtpServerConnection::send(const String& message, const StringList& to, const String& from, const String& fromDomain)
{
	const String lineEnd = "\r\n";
	Socket socket(Socket::TCP);
	if (socket.connect(address) == true)
	{
		/// sendTextLine

		socket.send("helo " + (fromDomain.empty() ? getFromDomain(from) : fromDomain) + lineEnd);
		socket.send("mail from:" + (from.empty() ? getFrom() : from) + lineEnd);
		for (StringList::const_iterator i = to.begin(); i != to.end(); ++i)
		{
			socket.send("rcpt to:" + *i + lineEnd);
		}
		socket.send("data" + lineEnd);
		socket.send(message + lineEnd + "." + lineEnd);
		socket.send("quit" + lineEnd);
	}
	else
	{
		error("");
	}
}

*/

} // namespace Network
} // namespace BaseLib