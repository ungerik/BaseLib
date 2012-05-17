/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef Gateway_h
#define Gateway_h



#include "BaseLib/Network/AbstractConnection.h"
#include "BaseLib/Buffers/BinaryMemBuffer.h"
#include <map>



namespace BaseLib {
namespace Network {



using BaseLib::Buffers::BinaryMemBuffer;



/**

Protocol:

+-----------+
| uint32    | byteCount
+-----------+
| uint16    | targetUserId
+-----------+
|           |
| byteCount | message-data
| - 2 bytes |
|           |
+-----------+
*/
class BL_EXPORT Gateway : public NonCopyable {
public:

	Gateway(AbstractConnection* useReceiveConnection); // takes ownership
	~Gateway();

	void addSendConnection(int targetUserId, AbstractConnection* sendConnection); // takes ownership
	void removeSendConnection(int targetUserId);

	void transferMessages() const;

private:

	AutoPointer<AbstractConnection> receiveConnection;

	typedef std::map<int, AbstractConnection*> Connections;
	Connections sendConnections;

	mutable BinaryMemBuffer transferBuffer;
};



} // namespace Network
} // namespace BaseLib



#endif // #ifndef Gateway_h