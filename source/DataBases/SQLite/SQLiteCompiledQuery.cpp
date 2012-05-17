/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/DataBases/SQLite/SQLiteCompiledQuery.h"
#include "BaseLib/DataBases/SQLite/SQLiteTable.h"
#include "BaseLib/DataBases/PersistentTable.h"
#include "BaseLib/DataBases/SqlException.h"
#include <sqlite3.h>



namespace BaseLib {
namespace DataBases {
namespace SQLite {



using namespace BaseLib::ErrorHandling;
using namespace BaseLib::DataBases;



BL_DEFINE_REFLECTION_CLASS(SQLiteCompiledQuery, AbstractCompiledQuery)
{
}



SQLiteCompiledQuery::SQLiteCompiledQuery(const String& newSqlQuery, sqlite3* newDbHandle)
	: AbstractCompiledQuery()
	, sqlQuery(newSqlQuery)
	, dbHandle(newDbHandle)
	, statement(NULL)
{
}



SQLiteCompiledQuery::~SQLiteCompiledQuery()
{
	if (statement != NULL)
	{
		sqlite3_finalize(statement);
	}
}



AbstractTable* SQLiteCompiledQuery::execute(bool persistentTable)
{
	if (statement == NULL)
	{
		int result = sqlite3_prepare16(dbHandle, sqlQuery.getChar16CString(), -1, &statement, NULL);
		if (result != SQLITE_OK)
		{
			throw SqlException(String(static_cast<const char16 *>(sqlite3_errmsg16(dbHandle))) + ERROR_AT); // TODO: must work without exceptions
		}
	}

	AbstractTable* resultTable = new SQLiteTable(statement, this);
	if (persistentTable == true)
	{
		PersistentTable* table = new PersistentTable(resultTable);
		delete resultTable;
		resultTable = table;
	}
	else
	{
		// statement is NULL as long as SQLiteTable is alive,
		// so calling execute() again before the returned SQLiteTable is deleted
		// will create a new statement.
		// SQLiteTable will give back it's statement in it's destructor,
		// if the compiled queries statement is NULL:
		statement = NULL;
	}
	return resultTable;
}



void SQLiteCompiledQuery::execute()
{
	if (statement == NULL)
	{
		int result = sqlite3_prepare16(dbHandle, sqlQuery.getChar16CString(), -1, &statement, NULL);
		if (result != SQLITE_OK)
		{
			throw SqlException(String(static_cast<const char16 *>(sqlite3_errmsg16(dbHandle))) + ERROR_AT); // TODO: must work without exceptions
		}
	}

	int result = sqlite3_step(statement);
	if (result == SQLITE_ERROR || result == SQLITE_MISUSE)
	{
		throw SqlException(String(static_cast<const char16 *>(sqlite3_errmsg16(dbHandle))) + ERROR_AT); // TODO: must work without exceptions
	}

	sqlite3_finalize(statement);
}



} // namespace SQLite
} // namespace DataBases
} // namespace BaseLib