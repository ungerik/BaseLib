/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Network_Socket_h
#define BaseLib_Network_Socket_h


#include "BaseLib/Buffers/AbstractTextBuffer.h"
#include "BaseLib/Streams/BinaryInputStream.h"
#include "BaseLib/Streams/BinaryOutputStream.h"
#include "BaseLib/NetWork/IpNumber.h"
#include "BaseLib/Functors/Functor1.h"
#include "BaseLib/System/Time.h"
#include "BaseLib/System/Thread.h"
#include "BaseLib/Utilities/AutoPointer.h"



#ifdef DELETE
	#undef DELETE
#endif



namespace BaseLib {
namespace Network {



using BaseLib::Streams::BinaryInputStream;
using BaseLib::Streams::BinaryOutputStream;
using BaseLib::Streams::BinaryStreamEncoding;
using BaseLib::Utilities::AutoPointer;
using BaseLib::System::Thread;
using BaseLib::Functors::Functor1;
using BaseLib::Functors::FunctionFunctor1;
using BaseLib::Functors::MethodFunctor1;



class BinarySocketBuffer;



class BL_EXPORT Socket : public NonCopyable {
public:

	enum ProtocolType {
		TCP,
		UDP
	};

	typedef Functor1<void, Socket*> AcceptCallbackFunctor;
	typedef FunctionFunctor1<void, Socket*> AcceptCallbackFuntionFunctor;
	template<class C>
	class BL_EXPORT AcceptCallbackMethodFunctor : public MethodFunctor1<C, void, Socket*> {
	public:
		AcceptCallbackMethodFunctor(C* atObject, Method forMethod)
			: MethodFunctor1(atObject, forMethod)
		{
		}
	};


	Socket(ProtocolType newProtocolType, uint16 bindToPort = 0);
	Socket(int newHandle, ProtocolType newProtocolType);
	~Socket();

	void close();

	inline bool isHandleValid() const { return handle != INVALID_SOCKET; }

	IpAddress getAddress() const;
	IpAddress getPeerAddress() const;

	void bind(uint16 portNumber);
	bool connect(const IpAddress& ipAddress);
	void listen();
	//void listenAsynchron();
	//void listenAsynchron(const CallbackFunctor& callbackFunctor);
	//bool isListeningAsynchron() const;
	//void endListenAsynchron();
	Socket* accept();
	void acceptAsynchron();
	void acceptAsynchron(const AcceptCallbackFunctor& callbackFunctor);
	inline bool isAcceptAsynchronRunning() const
	{
		return acceptThread != NULL;
	}
	inline Socket* getAcceptAsynchronResult() const
	{
		return acceptAsynchronResult;
	}

	int send(const void* source, int bytesToSend) const;
	void sendAll(const void* source, int bytesToSend, double timeout = BaseLib::System::Time::VERY_LONG) const;

	int receive(void* destination, int destinationSize, double timeout) const;
	inline int receive(void* destination, int destinationSize) const { return receive(destination, destinationSize, readTimeoutSeconds); }
	int peek(void* destination, int destinationSize) const;

	int sendTo(const void* source, int bytesToSend, const IpAddress& toAddress) const;
	void sendAllTo(const void* source, int bytesToSend, const IpAddress& toAddress, double timeout) const;
	int receiveFrom(void* destination, int destinationSize, IpAddress& fromAddress, double timeout) const;
	inline int receiveFrom(void* destination, int destinationSize, IpAddress& fromAddress) const { return receiveFrom(destination, destinationSize, fromAddress, readTimeoutSeconds); }
	int peekFrom(void* destination, int destinationSize, IpAddress& fromAddress) const;

	inline ProtocolType getProtocolType() const { return protocolType; }
	inline uint16 getBoundPort() const { return port; }

	BinaryInputStream& inputStream();
	BinaryOutputStream& outputStream();

	const BinaryInputStream& inputStream() const;
	const BinaryOutputStream& outputStream() const;

	inline int getHandle() const { return handle; }

	inline double getReadTimeoutSeconds() const { return readTimeoutSeconds; }
	void setReadTimeoutSeconds(double newReadTimeoutSeconds);

	int getBytesAvailable() const;
	int getBytesAvailable(double timeout) const;

	int getMaxMessageSize() const;
	int getReceiveBufferSize() const;
	bool setReceiveBufferSize(int size);
	int getSendBufferSize() const;
	bool setSendBufferSize(int size);
	bool isBroadcastEnabled() const;
	void setBroadcastEnabled(bool enableBroadcast);
	bool isBlocking() const;
	void setBlocking(bool enableBlocking);

	inline double ping() const { return getAddress().ping(); }

protected:

	const ProtocolType protocolType;
	int handle;
	uint16 port;
	double readTimeoutSeconds;
	AutoPointer<Thread> acceptThread;
	AutoPointer<AcceptCallbackFunctor> acceptCallbackFunctor;
	Socket* acceptAsynchronResult;

	mutable BinarySocketBuffer* binarySocketBuffer;
	mutable AutoPointer<BinaryInputStream> binaryInputStream;
	mutable AutoPointer<BinaryOutputStream> binaryOutputStream;
	BinaryStreamEncoding::StringEncoding stringEncoding;
	BinaryStreamEncoding::Endian endian;

	bool blocking;

	void acceptAsynchronThreadFunction();
};



} // namespace Network
} // namespace BaseLib



#endif // #ifndef BaseLib_Network_Socket_h
