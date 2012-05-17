/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_DataBases_DataBaseConnection_h
#define BaseLib_DataBases_DataBaseConnection_h



#include "BaseLib/DataBases/AbstractDataBase.h"



namespace BaseLib {
namespace DataBases {



using BaseLib::Strings::String;



class BL_EXPORT DataBaseConnection : public StaticClass {
public:

	static AbstractDataBase* create(const String& type, const String& name);

};



} // namespace DataBases
} // namespace BaseLib



#endif // #ifndef BaseLib_DataBases_DataBaseConnection_h
