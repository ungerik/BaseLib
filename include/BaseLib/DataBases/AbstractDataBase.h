/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_DataBases_AbstractDataBase_h
#define BaseLib_DataBases_AbstractDataBase_h



#include "BaseLib/DataBases/AbstractTable.h"
#include "BaseLib/DataBases/AbstractCompiledQuery.h"
#include "BaseLib/Reflection/Object.h"



namespace BaseLib {
namespace DataBases {



using BaseLib::Strings::String;



class BL_EXPORT AbstractDataBase : public BaseLib::Reflection::Object {
public:

	BL_DECLARE_REFLECTION_BASELIB_BASE_CLASS(BaseLib::DataBases::AbstractDataBase);

	virtual ~AbstractDataBase();

	/**
	@throws SqlException
	*/
	virtual AbstractCompiledQuery* compileQuery(const String& sqlQuery) = 0;

	/**
	Execute a SQL Query with a result table.
	@param persistentTable If true, a table with a RAM-copy of the complete result is returned. If false, a table is returned which can only iterate over the result.
	@throws SqlException
	*/
	virtual AbstractTable* executeQuery(const String& sqlQuery, bool persistentTable) = 0;

	/**
	Execute a SQL Query without a result.
	@throws SqlException
	*/
	virtual void executeQuery(const String& sqlQuery) = 0;



protected:

	//String name;


};



} // namespace DataBases
} // namespace BaseLib



#endif // #ifndef BaseLib_DataBases_AbstractDataBase_h
