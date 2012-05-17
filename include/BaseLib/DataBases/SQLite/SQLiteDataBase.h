/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_DataBases_SQLite_SQLiteDataBase_h
#define BaseLib_DataBases_SQLite_SQLiteDataBase_h



#include "BaseLib/DataBases/AbstractDataBase.h"



struct sqlite3;



namespace BaseLib {
namespace DataBases {

class DataBaseConnection;

namespace SQLite {



using BaseLib::DataBases::AbstractDataBase;
using BaseLib::Strings::String;



class BL_EXPORT SQLiteDataBase : public AbstractDataBase {

	friend BaseLib::DataBases::DataBaseConnection;

public:

	BL_DECLARE_REFLECTION_CLASS(BaseLib::DataBases::SQLite::SQLiteDataBase, AbstractDataBase);

	virtual ~SQLiteDataBase();

	virtual AbstractCompiledQuery* compileQuery(const String& sqlQuery);
	virtual AbstractTable* executeQuery(const String& sqlQuery, bool persistentTable);
	virtual void executeQuery(const String& sqlQuery);

private:

	sqlite3* handle;

	SQLiteDataBase(const String& newName);
};



} // namespace SQLite
} // namespace DataBases
} // namespace BaseLib



#endif // #ifndef BaseLib_DataBases_SQLite_SQLiteDataBase_h
