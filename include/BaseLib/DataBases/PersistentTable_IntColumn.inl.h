/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

// #included by BaseLib/DataBases/PersistentTable.h"



template<typename T>
struct IntColumn : AbstractColumn {

	Array<T> values;

	IntColumn<T>(const String& newName, const String& newBaseType, const String& newExactType)
		: AbstractColumn(newName, newBaseType, newExactType)
		, values()
	{
	}

	virtual void copyValueFrom(AbstractTable* sourceTable, int columnIndex)
	{
		if (sizeof(T) < sizeof(int64))
		{
			values += static_cast<T>(sourceTable->getInt(columnIndex));
		}
		else
		{
			values += static_cast<T>(sourceTable->getInt64(columnIndex));
		}
	}

	virtual int getSizeInBytes(int rowIndex) const
	{
		return sizeof(T);
	}

	virtual const void* getBinary(int rowIndex) const
	{
		return &values[rowIndex];
	}

	virtual String getString(int rowIndex) const
	{
		return String::createFrom(values[rowIndex]);
	}

	virtual bool getBool(int rowIndex) const
	{
		return values[rowIndex] != 0;
	}

	virtual int32 getInt(int rowIndex) const
	{
		return static_cast<int32>(values[rowIndex]);
	}

	virtual int64 getInt64(int rowIndex) const
	{
		return values[rowIndex];
	}

	virtual float getFloat(int rowIndex) const
	{
		return static_cast<float>(values[rowIndex]);
	}

	virtual double getDouble(int rowIndex) const
	{
		return static_cast<double>(values[rowIndex]);
	}

};
