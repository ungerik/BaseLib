/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef SmtpServerConnection_h
#define SmtpServerConnection_h



#include "BaseLib/Network/IpNumber.h"



namespace BaseLib {
namespace Network {


/*
class BL_EXPORT SmtpServerConnection {
public:

	SmtpServerConnection(const IpAddress& newAddress);
	SmtpServerConnection(const std::string& newAddress, uint16 port = 0);
	SmtpServerConnection(const std::wstring& newAddress, uint16 port = 0);

	void setAddress(const IpAddress& newAddress);
	void setAddress(const std::string& newAddress, uint16 port = 0);
	void setAddress(const std::wstring& newAddress, uint16 port = 0);
	inline IpAddress getAddress() const { return address; }

	void setFrom(const String newFrom);
	inline const String& getFrom() const { return from; }

	void setFromDomain(const String& newClientDomain);
	String getFromDomain(const String& from = Empty()) const;

	typedef Array<String*> StringList;

	void send(const String& message, const String& to, const String& from = Empty(), const String& fromDomain = Empty());
	void send(const String& message, const StringList& to, const String& from = Empty(), const String& fromDomain = Empty());


protected:

	IpAddress address;
	String from;
	String fromDomain;

};
*/


} // namespace Network
} // namespace BaseLib


#endif // #ifndef SmtpServerConnection_h