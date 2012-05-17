/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/


/*
#include "CppPropertiesRemoteProxy.h"
#include "CppPropertiesRemoteConnection.h"

*/
/*
using namespace CppPropertiesRemoteProtocol;



CppPropertiesRemoteProxy::CppPropertiesRemoteProxy(CppPropertiesRemoteConnection& remoteConnection)
  : AbstractCppProperties()
  , connection(remoteConnection)
{
}



const std::string CppPropertiesRemoteProxy::getProperty(const std::string& propertyName, int index) const
{
	DefaultGetPropertyMessage message;
	message.messageType = GET_PROPERTY;
	message.index = index;
	message.propertyNameLength = propertyName.length();

	connection.getSocket().sendAll(&message, sizeof(message));
	connection.getSocket().sendAll(propertyName);

	char buffer[65536];

	connection.getSocket().receive(buffer, sizeof(buffer));

	const GetPropertyResponseMessage& response = memoryAs<GetPropertyResponseMessage>(buffer);
	
	if (response.messageType == GET_PROPERTY_RESPONSE)
	{
		if (response.errorDescriptionLength == 0 && response.errorNumber == 0)
		{
			return std::string(&buffer[sizeof(GetPropertyResponseMessage)], response.resultLength);
		}
		else
		{
			error(std::string(&buffer[sizeof(GetPropertyResponseMessage)], response.errorDescriptionLength), response.errorNumber);
			return std::string();
		}
	}
	else
	{
		error(CPP_PROPERTIES_REMOTE_CONNECTION_WRONG_RESPONSE);
		return std::string();
	}
}



int CppPropertiesRemoteProxy::getPropertyInt(const std::string& propertyName, int index) const
{
	return 0;
}



bool CppPropertiesRemoteProxy::getPropertyBool(const std::string& propertyName, int index) const
{
	return 0;
}



float CppPropertiesRemoteProxy::getPropertyFloat(const std::string& propertyName, int index) const
{
	return 0;
}




void CppPropertiesRemoteProxy::setProperty(const std::string& propertyName, const std::string& propertyValue, int index)
{
}



void CppPropertiesRemoteProxy::setPropertyInt(const std::string& propertyName, int propertyValue, int index)
{
}



void CppPropertiesRemoteProxy::setPropertyBool(const std::string& propertyName, bool propertyValue, int index)
{
}



void CppPropertiesRemoteProxy::setPropertyFloat(const std::string& propertyName, float propertyValue, int index)
{
}



int CppPropertiesRemoteProxy::getAggregationMemberCount() const
{
	return 0;
}



const std::string CppPropertiesRemoteProxy::getAggregationMemberName(int aggregationMemberIndex) const
{
	return std::string();
}



int CppPropertiesRemoteProxy::getPropertyCount() const
{
	return 0;
}



const std::string CppPropertiesRemoteProxy::getPropertyName(int propertyIndex) const
{
	return std::string();
}



const std::string CppPropertiesRemoteProxy::getPropertyType(const std::string& propertyName) const
{
	return std::string();
}



bool CppPropertiesRemoteProxy::isInvisibleInPropertyExplorer(const std::string& propertyName) const
{
	return 0;
}



bool CppPropertiesRemoteProxy::isArrayProperty(const std::string& propertyName) const
{
	return 0;
}



bool CppPropertiesRemoteProxy::isPropertyArraySizeReadOnly(const std::string& propertyName) const
{
	return 0;
}



int CppPropertiesRemoteProxy::getPropertyArraySize(const std::string& propertyName) const
{
	return 0;
}



void CppPropertiesRemoteProxy::setPropertyArraySize(const std::string& propertyName, int newArraySize)
{
}



const std::string CppPropertiesRemoteProxy::getPropertyDescription(const std::string& propertyName) const
{
	return std::string();
}



void CppPropertiesRemoteProxy::setPropertyDescription(const std::string& propertyName, const std::string& newDescription) const
{
}



int CppPropertiesRemoteProxy::getPropertyEnumNameCount(const std::string& propertyName) const
{
	return 0;
}



const std::string CppPropertiesRemoteProxy::getPropertyEnumName(const std::string& propertyName, int index) const
{
	return std::string();
}



*/