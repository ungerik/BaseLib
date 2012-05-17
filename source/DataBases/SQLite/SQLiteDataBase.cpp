/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/DataBases/SQLite/SQLiteDataBase.h"
#include "BaseLib/DataBases/SQLite/SQLiteTable.h"
#include "BaseLib/DataBases/SQLite/SQLiteCompiledQuery.h"
#include "BaseLib/DataBases/PersistentTable.h"
#include "BaseLib/DataBases/SqlException.h"
#include <sqlite3.h>



namespace BaseLib {
namespace DataBases {
namespace SQLite {



using namespace BaseLib::ErrorHandling;
using namespace BaseLib::DataBases;



BL_DEFINE_REFLECTION_CLASS(SQLiteDataBase, AbstractDataBase)
{
}



SQLiteDataBase::SQLiteDataBase(const String& newName)
	: AbstractDataBase()
	, handle(NULL)
{
	int result = sqlite3_open16(newName.getChar16CString(), &handle);
	if (result != SQLITE_OK)
	{
		resultError(String(static_cast<const char16 *>(sqlite3_errmsg16(handle))) + ERROR_AT);
	}
}



SQLiteDataBase::~SQLiteDataBase()
{
	int result = sqlite3_close(handle);
	if (result == SQLITE_BUSY)
	{
		stateError("Can't close data-base because prepared statements haven't been finalized!" ERROR_AT);
	}
	else if (result == SQLITE_ERROR)
	{
		stateError("Can't close data-base because handle is invalid or data-base has already been closed!" ERROR_AT);
	}
}



AbstractCompiledQuery* SQLiteDataBase::compileQuery(const String& sqlQuery)
{
	return new SQLiteCompiledQuery(sqlQuery, handle);
}



AbstractTable* SQLiteDataBase::executeQuery(const String& sqlQuery, bool persistentTable)
{
	sqlite3_stmt* statement;
	int result = sqlite3_prepare16(handle, sqlQuery.getChar16CString(), -1, &statement, NULL);
	if (result == SQLITE_OK)
	{
		AbstractTable* resultTable = new SQLiteTable(statement, NULL);
		if (persistentTable == true)
		{
			PersistentTable* table = new PersistentTable(resultTable);
			delete resultTable;
			resultTable = table;
		}
		return resultTable;
	}
	else
	{
		throw SqlException(String(static_cast<const char16 *>(sqlite3_errmsg16(handle))) + ERROR_AT); // TODO: must work without exceptions
	}
}



void SQLiteDataBase::executeQuery(const String& sqlQuery)
{
	sqlite3_stmt* statement;
	int result = sqlite3_prepare16(handle, sqlQuery.getChar16CString(), -1, &statement, NULL);
	if (result != SQLITE_OK)
	{
		throw SqlException(String(static_cast<const char16 *>(sqlite3_errmsg16(handle))) + ERROR_AT); // TODO: must work without exceptions
	}

	result = sqlite3_step(statement);
	if (result == SQLITE_ERROR || result == SQLITE_MISUSE)
	{
		throw SqlException(String(static_cast<const char16 *>(sqlite3_errmsg16(handle))) + ERROR_AT); // TODO: must work without exceptions
	}

	sqlite3_finalize(statement);
}



} // namespace SQLite
} // namespace DataBases
} // namespace BaseLib