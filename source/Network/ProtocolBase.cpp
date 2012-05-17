/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Network/ProtocolBase.h"
#include "BaseLib/ErrorHandling.h"



namespace BaseLib {
namespace Network {



using namespace BaseLib::ErrorHandling;



ProtocolBase::ProtocolBase(Session* forSession)
	: session(forSession)
{
}



ProtocolBase::~ProtocolBase()
{
}



void ProtocolBase::setSession(Session* newSession)
{
	session = newSession;
}






} // namespace Network
} // namespace BaseLib
