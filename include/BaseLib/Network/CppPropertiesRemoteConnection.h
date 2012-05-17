/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef CppPropertiesRemoteConnection_h
#define CppPropertiesRemoteConnection_h


/*
#include "Socket.h"
#include "BaseLib/Utilities/AutoPointer.h"



class AMAZONAS CppPropertiesRemoteConnection {
public:

	inline const Socket& getSocket() const { return *socket; }

protected:

	AutoPointer<Socket> socket;

};





#pragma pack(1)


namespace CppPropertiesRemoteProtocol {


	struct Message {
		uint8 messageType;
	};

	struct ResponseMessage : Message {
		uint8 errorDescriptionLength;
		int32 errorNumber;
	};

	struct DefaultGetPropertyMessage : Message {
		int32 index;
		uint8 propertyNameLength;
	};

	struct GetPropertyResponseMessage : ResponseMessage {
		uint32 resultLength;
	};

	struct GetPropertyIntResponseMessage : ResponseMessage {
		int32 result;
	};

	struct GetPropertyBoolResponseMessage : ResponseMessage {
		bool8 result;
	};

	struct GetPropertyFloatResponseMessage : ResponseMessage {
		float32 result;
	};

	struct GenericSetPropertyMessage : Message {
		int32 index;
		uint8 propertyNameLength;
	};
	
	struct SetPropertyMessage : GenericSetPropertyMessage {
		uint32 valueLength;
	};

	struct SetPropertyIntMessage : GenericSetPropertyMessage {
		int32 value;
	};

	struct SetPropertyBoolMessage : GenericSetPropertyMessage {
		bool8 value;
	};

	struct SetPropertyFloatMessage : GenericSetPropertyMessage {
		float32 value;
	};


	///...

	enum MessageType {

		INVALID,

		GET_PROPERTY,
		GET_PROPERTY_RESPONSE,

		GET_PROPERTY_INT,
		GET_PROPERTY_INT_RESPONSE,

		GET_PROPERTY_BOOL,
		GET_PROPERTY_BOOL_RESPONSE,

		GET_PROPERTY_FLOAT,
		GET_PROPERTY_FLOAT_RESPONSE,

		SET_PROPERTY,
		SET_PROPERTY_RESPONSE,

		SET_PROPERTY_INT,
		SET_PROPERTY_INT_RESPONSE,

		SET_PROPERTY_BOOL,
		SET_PROPERTY_BOOL_RESPONSE,

		SET_PROPERTY_FLOAT,
		SET_PROPERTY_FLOAT_RESPONSE,

		GET_AGGREGATION_MEMBER_COUNT,
		GET_AGGREGATION_MEMBER_COUNT_RESPONSE,

		GET_AGGREGATION_MEMBER_NAME,
		GET_AGGREGATION_MEMBER_NAME_RESPONSE,

		GET_PROPERTY_COUNT,
		GET_PROPERTY_COUNT_RESPONSE,

		GET_PROPERTY_NAME,
		GET_PROPERTY_NAME_RESPONSE,

		GET_PROPERTY_TYPE,
		GET_PROPERTY_TYPE_RESPONSE,

		IS_INVISIBLE_IN_PROPERTY_EXPLORER,
		IS_INVISIBLE_IN_PROPERTY_EXPLORER_RESPONSE,

		IS_ARRAY_PROPERTY,
		IS_ARRAY_PROPERTY_RESPONSE,

		IS_PROPERTY_ARRAY_SIZE_READ_ONLY,
		IS_PROPERTY_ARRAY_SIZE_READ_ONLY_RESPONSE,

		GET_PROPERTY_ARRAY_SIZE,
		GET_PROPERTY_ARRAY_SIZE_RESPONSE,

		SET_PROPERTY_ARRAY_SIZE,
		SET_PROPERTY_ARRAY_SIZE_RESPONSE,

		GET_PROPERTY_DESCRIPTION,
		GET_PROPERTY_DESCRIPTION_RESPONSE,

		SET_PROPERTY_DESCRIPTION,
		SET_PROPERTY_DESCRIPTION_RESPONSE,

		GET_PROPERTY_ENUM_NAME_COUNT,
		GET_PROPERTY_ENUM_NAME_COUNT_RESPONSE,

		GET_PROPERTY_ENUM_NAME,
		GET_PROPERTY_ENUM_NAME_RESPONSE
	};


}; // namespace CppPropertiesRemoteProtocol



#pragma pack()

*/


#endif // #ifndef CppPropertiesRemoteConnection_h