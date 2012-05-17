/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/DataBases/DataBaseConnection.h"
#include "BaseLib/DataBases/SQLite/SQLiteDataBase.h"
#include "BaseLib/ErrorHandling.h"



namespace BaseLib {
namespace DataBases {



using namespace BaseLib::DataBases::SQLite;
using namespace BaseLib::ErrorHandling;



AbstractDataBase* DataBaseConnection::create(const String& type, const String& name)
{
	if (type.equalsCaseInsensitive("SQLite") == true)
	{
		return new SQLiteDataBase(name);
	}
	else
	{
		argumentError("Can't create data-base object of type '" + type + "' !" ERROR_AT);
		return NULL;
	}
}



} // namespace DataBases
} // namespace BaseLib