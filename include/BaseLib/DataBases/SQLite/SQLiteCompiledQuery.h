/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_DataBases_SQLite_SQLiteCompiledQuery_h
#define BaseLib_DataBases_SQLite_SQLiteCompiledQuery_h



#include "BaseLib/DataBases/AbstractCompiledQuery.h"



struct sqlite3;
struct sqlite3_stmt;



namespace BaseLib {
namespace DataBases {
namespace SQLite {



using BaseLib::DataBases::AbstractCompiledQuery;
class SQLiteTable;
class SQLiteDataBase;



class BL_EXPORT SQLiteCompiledQuery : public AbstractCompiledQuery {
public:

	friend SQLiteTable;
	friend SQLiteDataBase;

	BL_DECLARE_REFLECTION_CLASS(BaseLib::DataBases::SQLite::SQLiteCompiledQuery, AbstractCompiledQuery);

	virtual ~SQLiteCompiledQuery();

	virtual AbstractTable* execute(bool persistentTable);
	virtual void execute();

private:

	String sqlQuery;
	sqlite3* dbHandle;
	sqlite3_stmt* statement;

	SQLiteCompiledQuery(const String& newSqlQuery, sqlite3* newDbHandle);
};



} // namespace SQLite
} // namespace DataBases
} // namespace BaseLib



#endif // #ifndef BaseLib_DataBases_SQLite_SQLiteCompiledQuery_h
