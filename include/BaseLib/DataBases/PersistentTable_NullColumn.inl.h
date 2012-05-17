/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

// #included by BaseLib/DataBases/PersistentTable.h"



struct NullColumn : AbstractColumn {

	NullColumn(const String& newName, const String& newBaseType, const String& newExactType);

	virtual void copyValueFrom(AbstractTable* sourceTable, int columnIndex);

	virtual int getSizeInBytes(int rowIndex) const;
	virtual const void* getBinary(int rowIndex) const;
	virtual String getString(int rowIndex) const;
	virtual bool getBool(int rowIndex) const;
	virtual int32 getInt(int rowIndex) const;
	virtual int64 getInt64(int rowIndex) const;
	virtual float getFloat(int rowIndex) const;
	virtual double getDouble(int rowIndex) const;
};
