/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_DataBases_SQLite_SQLiteTable_h
#define BaseLib_DataBases_SQLite_SQLiteTable_h



#include "BaseLib/DataBases/AbstractTable.h"



struct sqlite3_stmt;



namespace BaseLib {
namespace DataBases {
namespace SQLite {



using BaseLib::DataBases::AbstractTable;
class SQLiteDataBase;
class SQLiteCompiledQuery;



class BL_EXPORT SQLiteTable : public AbstractTable {

	friend SQLiteDataBase;
	friend SQLiteCompiledQuery;

public:

	BL_DECLARE_REFLECTION_CLASS(BaseLib::DataBases::SQLite::SQLiteTable, AbstractTable);

	virtual ~SQLiteTable();

	virtual bool isPersistent() const;
	virtual bool moveToNextRow();
	virtual bool moveToPreviousRow();

	virtual int getCurrentRow() const;
	virtual void setCurrentRow(int newCurrentRow);

	virtual int getRowCount() const;
	virtual int getColumnCount() const;
	virtual String getColumnName(int columnIndex) const;
	virtual String getColumnBaseType(int columnIndex) const;
	virtual String getColumnExactType(int columnIndex) const;

	virtual int getSizeInBytes(int columnIndex) const;
	virtual const void* getBinary(int columnIndex) const;
	virtual String getString(int columnIndex) const;
	virtual bool getBool(int columnIndex) const;
	virtual int32 getInt(int columnIndex) const;
	virtual int64 getInt64(int columnIndex) const;
	virtual float getFloat(int columnIndex) const;
	virtual double getDouble(int columnIndex) const;

private:

	sqlite3_stmt* statement;
	int currentRow;
	bool firstStepDone;
	SQLiteCompiledQuery* compiledQuery;

	SQLiteTable(sqlite3_stmt* forStatement, SQLiteCompiledQuery* forCompiledQuery);

	static String sqliteTypeToString(int sqliteType);

};



} // namespace SQLite
} // namespace DataBases
} // namespace BaseLib



#endif // #ifndef BaseLib_DataBases_SQLite_SQLiteTable_h
