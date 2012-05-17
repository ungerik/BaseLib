/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/


#include "BaseLib/Network/IpNumber.h"
#include "BaseLib/intern/Errors.h"
#include "BaseLib/Strings/Manipulation.h"
#include "BaseLib/System/Time.h"



namespace BaseLib {
namespace Network {


using namespace BaseLib::Containers;
using namespace BaseLib::System;
using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Strings;



int networkingCounter = 0;



bool useBaseLibNetworking()
{
	if (networkingCounter <= 0)
	{
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)
		{
			resultError("");
			return false;
		}
		networkingCounter = 1;
		return true;
	}
	else
	{
		++networkingCounter;
		return false;
	}
}



bool releaseBaseLibNetworking()
{
	--networkingCounter;
	if (networkingCounter <= 0)
	{
		if (WSACleanup() != 0)
		{
			resultError("");
			return false;
		}
		return true;
	}
	else
	{
		return false;
	}
}



String getHostName()
{
	char8 buffer[256];
	useBaseLibNetworking();
	int res = gethostname(buffer, sizeof(buffer));
	releaseBaseLibNetworking();
	if (res == 0)
	{
		return buffer;
	}
	else
	{
		ioError(LAST_SOCKET_ERROR);
		return Empty();
	}
}



IpNumber IpNumber::getBroadCastNumber()
{
	return IpNumber(0xFFFFFFFF);
}



IpNumber::IpNumber(uint32 ip)
{
	combined = ip;
}



IpNumber::IpNumber(const String& number)
{
	combined = 0;
	operator=(number);
}



IpNumber::operator String() const
{
	return String::createFrom(
		static_cast<uint>(part[0]))+ '.' + 
		String::createFrom(static_cast<uint>(part[1]))+ '.' + 
		String::createFrom(static_cast<uint>(part[2]))+ '.' + 
		String::createFrom(static_cast<uint>(part[3]));
}



IpNumber& IpNumber::operator =(const String& right)
{
	IpAddress ipAddress = right;
	return *this = ipAddress.getIP();
}



/////////////////////////////////



IpAddress::IpAddress(IpNumber newIP, uint16 newPort)
  : ip(newIP)
  , port(newPort)
{
}



IpAddress::IpAddress(const String& address)
  : ip(0)
  , port(0)
{
	operator=(address);
}



//IpAddress::IpAddress(const char * address)
//  : ip(0)
//  , port(0)
//{
//	operator=(address);
//}



IpAddress::operator String() const
{
	String result;
	if (ip > 0)
	{
		result = String::createFrom(
			static_cast<uint>(ip[0])) + '.' + 
			String::createFrom(static_cast<uint>(ip[1])) + '.' + 
			String::createFrom(static_cast<uint>(ip[2])) + '.' + 
			String::createFrom(static_cast<uint>(ip[3]));
	}
	if (port > 0)
	{
		result += ':' + String::createFrom(port);
	}
	return result;
}



IpAddress& IpAddress::operator =(const String& right)
{
	IpNumber newIP = 0;
	uint16 newPort = 0;

	int i = 0;
	bool isName = false;
	while (i < right.getLength())
	{
		if ((isNumber(right[i].operator char8()) || right[i] == '.' || right[i] == ':') == false)
		{
			isName = true;
			break;
		}
		++i;
	}

	if (isName == true)
	{
		int pos = right.findFirst(':');
		String addr = right.subString(0, pos);
		if (pos != String::END && pos+1 < right.getLength())
		{
			newPort = static_cast<uint16>(String(right.subString(pos+1)).parseInt());
		}

		useBaseLibNetworking();
		hostent* hostData = gethostbyname(addr.getChar8CString());
		if (hostData == NULL)
		{
			ioError("");
			return *this;
		}
		releaseBaseLibNetworking();

		newIP[0] = hostData->h_addr_list[0][0];
		newIP[1] = hostData->h_addr_list[0][1];
		newIP[2] = hostData->h_addr_list[0][2];
		newIP[3] = hostData->h_addr_list[0][3];

		ip = newIP;
		port = newPort;
	}
	else
	{
		char8 number[5];
		int numberCount = 0;
		i = 0;
		int factor;

		for(int part = 0; part < 3; ++part, ++i)
		{
			while (right[i] != '.')
			{			
				if (isNumber(right[i].operator char8()) == false || numberCount > 3 || i == right.getLength())
				{
					argumentError(INVALID_NET_ADDRESS_STRING(right));
					return *this;
				}
				number[numberCount] = right[i];
				++numberCount;
				++i;
			}
			factor = 1;
			while (numberCount > 0)
			{
				--numberCount;
				const uint value = char2Number(number[numberCount]) * factor + newIP[part];
				if (value > 255)
				{
					argumentError(INVALID_NET_ADDRESS_STRING(right));
					return *this;
				}
				newIP[part] = static_cast<uint8>(value);
				factor *= 10;
			}
		}

		while (right[i] != ':' && i < right.getLength())
		{			
			char c = right[i];
			if (isNumber(right[i].operator char8()) == false || numberCount > 3)
			{
				argumentError(INVALID_NET_ADDRESS_STRING(right));
				return *this;
			}
			number[numberCount] = right[i];
			++numberCount;
			++i;
		}
		factor = 1;
		while (numberCount > 0)
		{
			--numberCount;
			const uint value = char2Number(number[numberCount]) * factor + newIP[3];
			if (value > 255)
			{
				argumentError(INVALID_NET_ADDRESS_STRING(right));
				return *this;
			}
			newIP[3] = static_cast<uint8>(value);
			factor *= 10;
		}
		++i;


		while (i < right.getLength())
		{			
			char c = right[i];
			if (isNumber(right[i].operator char8()) == false || numberCount > 5)
			{
				argumentError(INVALID_NET_ADDRESS_STRING(right));
				return *this;
			}
			number[numberCount] = right[i];
			++numberCount;
			++i;
		}
		factor = 1;
		while (numberCount > 0)
		{
			--numberCount;
			const uint value = char2Number(number[numberCount]) * factor + newPort;
			if (value > 65535)
			{
				argumentError(INVALID_NET_ADDRESS_STRING(right));
				return *this;
			}
			newPort = static_cast<uint16>(value);
			factor *= 10;
		}

		ip = newIP;
		port = newPort;
	}
	return *this;
}



sockaddr* IpAddress::makeSockAddr(sockaddr& addr) const
{
	sockaddr_in& addr_in = memoryAs<sockaddr_in>(&addr, 0);

    addr_in.sin_family = AF_INET;       
    addr_in.sin_port = bigEndian(port);     
    addr_in.sin_addr.s_addr = ip; // we already use big endian via the array byte order
    memset(&addr_in.sin_zero, 0, sizeof(addr_in.sin_zero));

	return &addr;
}



IpAddress::IpAddress(const sockaddr& addr)
{
	operator=(addr);
}



IpAddress& IpAddress::operator=(const sockaddr& right)
{
	const sockaddr_in& addr_in = memoryAs<const sockaddr_in>(&right, 0);
	ip = addr_in.sin_addr.s_addr; // we already use big endian via the array byte order
	port = bigEndian(addr_in.sin_port);
	return *this;
}



IpAddress::operator sockaddr() const
{
	sockaddr addr;
	return *makeSockAddr(addr);
}



String IpAddress::getName() const
{
	const char addr[] = { ip[0], ip[1], ip[2], ip[3] };
	const HOSTENT* res = gethostbyaddr(addr, sizeof(addr), AF_INET);
	if (res != NULL)
	{
		return res->h_name;
	}
	else
	{
		return Empty();
	}
}


//
// Mike Muuss' in_cksum() function
// and his comments from the original
// ping program
//
// * Author -
// *	Mike Muuss
// *	U. S. Army Ballistic Research Laboratory
// *	December, 1983

/*
 *			I N _ C K S U M
 *
 * Checksum routine for Internet Protocol family headers (C Version)
 *
 */
u_short in_cksum(u_short *addr, int len)
{
	register int nleft = len;
	register u_short *w = addr;
	register u_short answer;
	register int sum = 0;

	/*
	 *  Our algorithm is simple, using a 32 bit accumulator (sum),
	 *  we add sequential 16 bit words to it, and at the end, fold
	 *  back all the carry bits from the top 16 bits into the lower
	 *  16 bits.
	 */
	while( nleft > 1 )  {
		sum += *w++;
		nleft -= 2;
	}

	/* mop up an odd byte, if necessary */
	if( nleft == 1 ) {
		u_short	u = 0;

		*(u_char *)(&u) = *(u_char *)w ;
		sum += u;
	}

	/*
	 * add back carry outs from top 16 bits to low 16 bits
	 */
	sum = (sum >> 16) + (sum & 0xffff);	/* add hi 16 to low 16 */
	sum += (sum >> 16);			/* add carry */
	answer = ~sum;				/* truncate to 16 bits */
	return (answer);
}



double IpAddress::ping() const
{
	const int ICMP_ECHOREPLY = 0;
	const int ICMP_ECHOREQ = 8;

	#pragma pack(1)

	// IP Header -- RFC 791
	struct IPHeader	{
		uint8  VIHL;			// Version and IHL
		uint8	TOS;			// Type Of Service
		int16	TotLen;			// Total Length
		int16	ID;				// Identification
		int16	FlagOff;		// Flags and Fragment Offset
		uint8	TTL;			// Time To Live
		uint8	Protocol;		// Protocol
		uint16	Checksum;		// Checksum
		struct	in_addr iaSrc;	// Internet Address - Source
		struct	in_addr iaDst;	// Internet Address - Destination
	};


	// ICMP Header - RFC 792
	struct ICMPHeader {
		uint8	Type;			// Type
		uint8	Code;			// Code
		uint16	Checksum;		// Checksum
		uint16	ID;				// Identification
		uint16	Seq;			// Sequence
		int8	Data;			// Data
	};


	const int REQ_DATASIZE  = 32;		// Echo Request Data size

	// ICMP Echo Request
	struct EchoRequest {
		ICMPHeader icmpHeader;
		uint32	dwTime;
		int8	cData[REQ_DATASIZE];
	};

	// ICMP Echo Reply
	struct EchoReply
	{
		IPHeader ipHeader;
		EchoRequest echoRequest;
		int8 cFiller[256];
	};

	#pragma pack()

	useBaseLibNetworking();

	SOCKET rawSocket;
	rawSocket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (rawSocket == SOCKET_ERROR) 
	{
		String errorString = LAST_SOCKET_ERROR;
		releaseBaseLibNetworking();
		ioError(errorString);
		return 0.0;
	}

	EchoRequest echoRequest;
	int nId = 1;
	int nSeq = 1;

	// Fill in echo request
	echoRequest.icmpHeader.Type		= ICMP_ECHOREQ;
	echoRequest.icmpHeader.Code		= 0;
	echoRequest.icmpHeader.Checksum	= 0;
	echoRequest.icmpHeader.ID		= nId++;
	echoRequest.icmpHeader.Seq		= nSeq++;

	// Fill in some data to send
	for (int i = 0; i < REQ_DATASIZE; ++i)
	{
		echoRequest.cData[i] = ' '+i;
	}

	// Save tick count when sent
	echoRequest.dwTime = 0; //round<uint32>(Time::nowInSeconds() * 1000.0);
	double sendTime = Time::nowInSeconds();

	// Put data in packet and compute checksum
	echoRequest.icmpHeader.Checksum = in_cksum((u_short *)&echoRequest, sizeof(EchoRequest));

	sockaddr addr;

	// Send the echo request  								  
	int res = sendto(rawSocket,					/* socket */
				 (LPSTR)&echoRequest,			/* buffer */
				 sizeof(EchoRequest),
				 0,							/* flags */
				 makeSockAddr(addr), /* destination */
				 sizeof(SOCKADDR_IN));   /* address length */

	if (res == SOCKET_ERROR)
	{
		String errorString = LAST_SOCKET_ERROR;
		closesocket(rawSocket);
		releaseBaseLibNetworking();
		ioError(errorString);
		return 0.0;
	}


	struct timeval timeout;
	fd_set readfds;

	readfds.fd_count = 1;
	readfds.fd_array[0] = rawSocket;
	timeout.tv_sec = 5; ///
    timeout.tv_usec = 0;

	res = select(1, &readfds, NULL, NULL, &timeout);

	if (res == SOCKET_ERROR)
	{
		closesocket(rawSocket);
		releaseBaseLibNetworking();
		ioError(WINSOCK_ERROR("select() in ping() failed"));
		return 0.0;
	}
	else if (res == 0)
	{
		closesocket(rawSocket);
		releaseBaseLibNetworking();
		ioError(WINSOCK_ERROR("timeout in ping()")); ///
		return 0.0;
	}

	EchoReply echoReply;
	int nAddrLen = sizeof(sockaddr_in);

	sockaddr_in saFrom;

	// Receive the echo reply	
	res = recvfrom(rawSocket,			// socket
					(LPSTR)&echoReply,	// buffer
					sizeof(EchoReply),	// size of buffer
					0,					// flags
					(LPSOCKADDR)&saFrom,	// From address
					&nAddrLen);			// pointer to address len

	// Check return value
	if (res == SOCKET_ERROR)
	{
		closesocket(rawSocket);
		releaseBaseLibNetworking();
		ioError(WINSOCK_ERROR("recvfrom() in ping() failed"));
		return 0.0;
	}

	// return time sent and IP TTL
	uint8 ttl = echoReply.ipHeader.TTL;

	// Calculate elapsed time
	//DWORD dwTimeSent = echoReply.echoRequest.dwTime;
	//DWORD dwElapsed = GetTickCount() - dwTimeSent;

	double result = Time::nowInSeconds() - sendTime;

	res = closesocket(rawSocket);
	if (res == SOCKET_ERROR)
	{
		String errorString = LAST_SOCKET_ERROR;
		releaseBaseLibNetworking();
		ioError(errorString);
		return 0.0;
	}

	releaseBaseLibNetworking();
	return result;
}



String getWinsockErrorString(int errorCode)
{
	switch(errorCode)
	{
		case WSAEACCES:
			return "Permission denied.";
		case WSAEADDRINUSE:
			return "Address already in use.";
		case WSAEADDRNOTAVAIL:
			return "Cannot assign requested address.";
		case WSAEAFNOSUPPORT:
			return "Address family not supported by protocol family.";
		case WSAEALREADY:
			return "Operation already in progress.";
		case WSAECONNABORTED:
			return "Software caused connection abort.";
		case WSAECONNREFUSED:
			return "Connection refused.";
		case WSAECONNRESET:
			return "Connection reset by peer.";
		case WSAEDESTADDRREQ:
			return "Destination address required.";
		case WSAEFAULT:
			return "Bad address.";
		case WSAEHOSTDOWN:
			return "Host is down.";
		case WSAEHOSTUNREACH:
			return "No route to host.";
		case WSAEINPROGRESS:
			return "Operation now in progress.";
		case WSAEINTR:
			return "Interrupted function call.";
		case WSAEINVAL:
			return "Invalid argument.";
		case WSAEISCONN:
			return "Socket is already connected.";
		case WSAEMFILE:
			return "Too many open files.";
		case WSAEMSGSIZE:
			return "Message too long.";
		case WSAENETDOWN:
			return "Network is down.";
		case WSAENETRESET:
			return "Network dropped connection on reset.";
		case WSAENETUNREACH:
			return "Network is unreachable.";
		case WSAENOBUFS:
			return "No buffer space available.";
		case WSAENOPROTOOPT:
			return "Bad protocol option.";
		case WSAENOTCONN:
			return "Socket is not connected.";
		case WSAENOTSOCK:
			return "Socket operation on nonsocket.";
		case WSAEOPNOTSUPP:
			return "Operation not supported.";
		case WSAEPFNOSUPPORT:
			return "Protocol family not supported.";
		case WSAEPROCLIM:
			return "Too many processes.";
		case WSAEPROTONOSUPPORT:
			return "Protocol not supported.";
		case WSAEPROTOTYPE:
			return "Protocol wrong type for socket.";
		case WSAESHUTDOWN:
			return "Cannot send after socket shutdown.";
		case WSAESOCKTNOSUPPORT:
			return "Socket type not supported.";
		case WSAETIMEDOUT:
			return "Connection timed out.";
		case WSATYPE_NOT_FOUND:
			return "Class type not found.";
		case WSAEWOULDBLOCK:
			return "Resource temporarily unavailable.";
		case WSAHOST_NOT_FOUND:
			return "Host not found.";
		case WSA_INVALID_HANDLE:
			return "Specified event object handle is invalid.";
		case WSA_INVALID_PARAMETER:
			return "One or more parameters are invalid.";
		//case WSAINVALIDPROCTABLE:
			//return "Invalid procedure table from service provider.";
		//case WSAINVALIDPROVIDER:
			//return "Invalid service provider version number.";
		case WSA_IO_INCOMPLETE:
			return "Overlapped I/O event object not in signaled state.";
		case WSA_IO_PENDING:
			return "Overlapped operations will complete later.";
		case WSA_NOT_ENOUGH_MEMORY:
			return "Insufficient memory available.";
		case WSANOTINITIALISED:
			return "Successful WSAStartup not yet performed.";
		case WSANO_DATA:
			return "Valid name, no data record of requested type.";
		case WSANO_RECOVERY:
			return "This is a nonrecoverable ioError.";
		//case WSAPROVIDERFAILEDINIT:
			//return "Unable to initialize a service provider.";
		case WSASYSCALLFAILURE:
			return "System call failure.";
		case WSASYSNOTREADY:
			return "Network subsystem is unavailable.";
		case WSATRY_AGAIN:
			return "Nonauthoritative host not found.";
		case WSAVERNOTSUPPORTED:
			return "Winsock.dll version out of range.";
		case WSAEDISCON:
			return "Graceful shutdown in progress.";
		case WSA_OPERATION_ABORTED:
			return "Overlapped operation aborted.";
		default:
			return "Unknown Winsock ioError.";
	}
}



} // namespace Network
} // namespace BaseLib
