/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Network_IpNumber_h
#define BaseLib_Network_IpNumber_h



#include "BaseLib/Buffers/AbstractTextBuffer.h"
#include "BaseLib/Utilities/BitManipulation.h"
#include <winsock2.h>




namespace BaseLib {
namespace Network {



using BaseLib::Strings::String;



BL_EXPORT bool useBaseLibNetworking();
BL_EXPORT bool releaseBaseLibNetworking();



BL_EXPORT String getHostName();



#pragma pack(1)



class BL_EXPORT IpNumber {
public:	
	static IpNumber getBroadCastNumber();

	IpNumber(uint32 ip = 0);
	inline operator uint32() const
	{
		return combined;
	}

	inline IpNumber& operator=(uint32 ip)
	{
		combined = ip;
		return *this;
	}

	IpNumber(const String& address);
	//IpNumber(const char * address);
	IpNumber& operator =(const String& right);
	operator String() const;

	// index is from left to right (network byte-order):
	inline uint8& operator[](int index)
	{
		return part[BIG_ENDIAN ? index : 3-index];
	}
	inline const uint8& operator[](int index) const
	{
		return part[BIG_ENDIAN ? index : 3-index];
	}

	inline bool operator <(const IpNumber& right) const
	{
		return combined < right.combined;
	}

	inline bool operator ==(const IpNumber& right) const
	{
		return combined == right.combined;
	}

	inline bool operator !=(const IpNumber& right) const
	{
		return !operator ==(right);
	}

private:
	union {
		uint32 combined;
		uint8 part[4];
	};

};



class BL_EXPORT IpAddress {
public:

	IpAddress(IpNumber newIP = 0, uint16 newPort = 0);

	IpAddress(const sockaddr& addr);
	IpAddress& operator=(const sockaddr& right);
	operator sockaddr() const;

	IpAddress(const String& address);
	IpAddress& operator=(const String& right);

	inline bool operator ==(const IpAddress& right) const
	{
		return ip == right.getIP() && port == right.getPort();
	}

	inline bool operator !=(const IpAddress& right) const
	{
		return !operator ==(right);
	}

	inline bool operator <(const IpAddress& right) const
	{
		if (ip < right.getIP())
		{
			return true;
		}
		else if (ip == right.getIP())
		{
			return port < right.getPort();
		}
		else
		{
			return false;
		}
	}

	operator String() const;

	inline IpNumber getIP() const { return ip; }
	inline uint16 getPort() const { return port; }

	inline void setIP(IpNumber newIP) { ip = newIP; }
	inline void setPort(uint16 newPort) { port = newPort; }

	sockaddr* makeSockAddr(sockaddr& addr) const;

	double ping() const;

	String getName() const;

	/// type-cast check oder andere funktion!

protected:
	IpNumber ip;
	uint16 port;
};



#pragma pack()



/*
template<>
inline TextOutputStream& operator<<(TextOutputStream& outputStream, const IpAddress& source)
{
	return outputStream << (source.operator String());
}



template<>
inline const TextOutputStream& operator<<(const TextOutputStream& outputStream, const IpAddress& source)
{
	return outputStream << (source.operator String());
}
*/



String getWinsockErrorString(int errorCode);


inline String getLastWinsockError()
{
	return getWinsockErrorString(WSAGetLastError());
}



#define LAST_SOCKET_ERROR ( WINSOCK_ERROR(getLastWinsockError()) )



} // namespace Network
} // namespace BaseLib





#endif // #ifndef BaseLib_Network_IpNumber_h
