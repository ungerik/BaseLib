/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_DataBases_PersistentTable_h
#define BaseLib_DataBases_PersistentTable_h



#include "BaseLib/DataBases/AbstractTable.h"
#include "BaseLib/Containers/Array.h"
#include "BaseLib/Buffers/BinaryMemBuffer.h"



namespace BaseLib {
namespace DataBases {



using BaseLib::Buffers::BinaryMemBuffer;
using BaseLib::Containers::Array;



class BL_EXPORT PersistentTable : public AbstractTable {
public:

	BL_DECLARE_REFLECTION_CLASS(BaseLib::DataBases::PersistentTable, AbstractTable);

	PersistentTable(AbstractTable* sourceTable);

	virtual ~PersistentTable();

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

protected:

	struct AbstractColumn {

		const String name;
		const String baseType;
		const String exactType;

		AbstractColumn(const String& newName, const String& newBaseType, const String& newExactType)
			: name(newName)
			, baseType(newBaseType)
			, exactType(newExactType)
		{
		}

		virtual ~AbstractColumn()
		{
		}

		virtual void copyValueFrom(AbstractTable* sourceTable, int columnIndex) = 0;

		virtual int getSizeInBytes(int rowIndex) const = 0;
		virtual const void* getBinary(int rowIndex) const = 0;
		virtual String getString(int rowIndex) const = 0;
		virtual bool getBool(int rowIndex) const = 0;
		virtual int32 getInt(int rowIndex) const = 0;
		virtual int64 getInt64(int rowIndex) const = 0;
		virtual float getFloat(int rowIndex) const = 0;
		virtual double getDouble(int rowIndex) const = 0;

	};

	#include "PersistentTable_IntColumn.inl.h"
	#include "PersistentTable_BoolColumn.inl.h"
	#include "PersistentTable_FloatColumn.inl.h"
	#include "PersistentTable_TextColumn.inl.h"
	#include "PersistentTable_BlobColumn.inl.h"
	#include "PersistentTable_NullColumn.inl.h"

	int rowCount;
	int currentRow;
	Array<AbstractColumn*> columns;
	bool firstRowFound;

	void initColumns(AbstractTable* sourceTable);
	void initRows(AbstractTable* sourceTable);
};



} // namespace DataBases
} // namespace BaseLib



#endif // #ifndef BaseLib_DataBases_PersistentTable_h
