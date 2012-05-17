/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/DataBases/SQLite/SQLiteTable.h"
#include "BaseLib/DataBases/SQLite/SQLiteCompiledQuery.h"
#include "BaseLib/ErrorHandling.h"
#include <sqlite3.h>



namespace BaseLib {
namespace DataBases {
namespace SQLite {



using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Math;



BL_DEFINE_REFLECTION_CLASS(SQLiteTable, AbstractTable)
{
}



SQLiteTable::SQLiteTable(sqlite3_stmt* forStatement, SQLiteCompiledQuery* forCompiledQuery)
	: AbstractTable()
	, statement(forStatement)
	, currentRow(-1)
	, firstStepDone(false)
	, compiledQuery(forCompiledQuery)
{
	checkArgumentNotNull(NAME_VALUE(forStatement));
}



SQLiteTable::~SQLiteTable()
{
	if (compiledQuery != NULL && compiledQuery->statement == NULL)
	{
		// If statement is from a compiled query,
		// and the compiled query doesn't have one,
		// reset it and give it back:
		sqlite3_reset(statement);
		compiledQuery->statement = statement;
	}
	else
	{
		sqlite3_finalize(statement);
	}
}



bool SQLiteTable::isPersistent() const
{
	return false;
}



bool SQLiteTable::moveToNextRow()
{
	if (sqlite3_step(statement) == SQLITE_ROW)
	{
		++currentRow;
		return true;
	}
	else
	{
		return false;
	}
}



bool SQLiteTable::moveToPreviousRow()
{
	return false;
}



int SQLiteTable::getCurrentRow() const
{
	return currentRow;
}



void SQLiteTable::setCurrentRow(int newCurrentRow)
{
	if (newCurrentRow != currentRow)
	{
		if (newCurrentRow == -1)
		{
			sqlite3_reset(statement);
			currentRow = newCurrentRow;
		}
		else
		{
			argumentError("Transient tables can only change the current row with moveToNextRow()!" ERROR_AT);
		}
	}
}



int SQLiteTable::getRowCount() const
{
	return currentRow + 1;
}



int SQLiteTable::getColumnCount() const
{
	return sqlite3_column_count(statement);
}



String SQLiteTable::getColumnName(int columnIndex) const
{
	if (checkArgumentRange(NAME_VALUE(columnIndex), 0, getColumnCount()-1) == true)
	{
		return String(static_cast<const char16 *>(sqlite3_column_name16(statement, columnIndex)));
	}
	else
	{
		return Empty();
	}
}



String SQLiteTable::getColumnBaseType(int columnIndex) const
{
	if (checkArgumentRange(NAME_VALUE(columnIndex), 0, getColumnCount()-1) == true)
	{
		int result = sqlite3_column_type(statement, columnIndex);		
		return result != 0 ? sqliteTypeToString(result) : getColumnExactType(columnIndex);
	}
	else
	{
		return Empty();
	}
}



String SQLiteTable::getColumnExactType(int columnIndex) const
{
	if (checkArgumentRange(NAME_VALUE(columnIndex), 0, getColumnCount()-1) == true)
	{
		return String(static_cast<const char16 *>(sqlite3_column_decltype16(statement, columnIndex)));
	}
	else
	{
		return Empty();
	}
}



int SQLiteTable::getSizeInBytes(int columnIndex) const
{
	if (checkArgumentRange(NAME_VALUE(columnIndex), 0, getColumnCount()-1) == true)
	{
		return sqlite3_column_bytes16(statement, columnIndex);
	}
	else
	{
		return 0;
	}
}



const void* SQLiteTable::getBinary(int columnIndex) const
{
	if (checkArgumentRange(NAME_VALUE(columnIndex), 0, getColumnCount()-1) == true)
	{
		return sqlite3_column_blob(statement, columnIndex);
	}
	else
	{
		return NULL;
	}
}



String SQLiteTable::getString(int columnIndex) const
{
	if (checkArgumentRange(NAME_VALUE(columnIndex), 0, getColumnCount()-1) == true)
	{
		if (sqlite3_column_type(statement, columnIndex) == SQLITE_TEXT)
		{
			return String(static_cast<const char16*>(sqlite3_column_text16(statement, columnIndex)));
		}
		else
		{
			return String(reinterpret_cast<const char8*>(sqlite3_column_text(statement, columnIndex)));
		}
	}
	else
	{
		return Empty();
	}
}



bool SQLiteTable::getBool(int columnIndex) const
{
	if (checkArgumentRange(NAME_VALUE(columnIndex), 0, getColumnCount()-1) == true)
	{
		return sqlite3_column_int(statement, columnIndex) != 0;
	}
	else
	{
		return false;
	}
}



int32 SQLiteTable::getInt(int columnIndex) const
{
	if (checkArgumentRange(NAME_VALUE(columnIndex), 0, getColumnCount()-1) == true)
	{
		return sqlite3_column_int(statement, columnIndex);
	}
	else
	{
		return -1;
	}
}



int64 SQLiteTable::getInt64(int columnIndex) const
{
	if (checkArgumentRange(NAME_VALUE(columnIndex), 0, getColumnCount()-1) == true)
	{
		return sqlite3_column_int64(statement, columnIndex);
	}
	else
	{
		return -1;
	}
}



float SQLiteTable::getFloat(int columnIndex) const
{
	if (checkArgumentRange(NAME_VALUE(columnIndex), 0, getColumnCount()-1) == true)
	{
		return static_cast<float>(sqlite3_column_double(statement, columnIndex));
	}
	else
	{
		return NAN;
	}
}



double SQLiteTable::getDouble(int columnIndex) const
{
	if (checkArgumentRange(NAME_VALUE(columnIndex), 0, getColumnCount()-1) == true)
	{
		return sqlite3_column_double(statement, columnIndex);
	}
	else
	{
		return NAN;
	}
}



String SQLiteTable::sqliteTypeToString(int sqliteType)
{
	switch (sqliteType)
	{
		case SQLITE_INTEGER:
			return "int";

		case SQLITE_FLOAT:
			return "float";

		case SQLITE_TEXT:
			return "string";

		case SQLITE_BLOB:
			return "binary";

		case SQLITE_NULL:
			return "null";

		case 0:
			return Empty();

		default:
			BL_ASSERT_NEVER_REACHED
			return Empty();
	}
}



} // namespace SQLite
} // namespace DataBases
} // namespace BaseLib