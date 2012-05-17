/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef ProtocolBase_h
#define ProtocolBase_h



#include "BaseLib/Network/Session.h"



namespace BaseLib {
namespace Network {



/**

Protocol:


*/
class BL_EXPORT ProtocolBase : public NonCopyable {
public:

	ProtocolBase(Session* forSession = NULL);
	~ProtocolBase();

	inline Session* getSession() const
	{
		return session;
	}

	void setSession(Session* newSession);

protected:

	Session* session;
	
};



} // namespace Network
} // namespace BaseLib



#endif // #ifndef ProtocolBase_h