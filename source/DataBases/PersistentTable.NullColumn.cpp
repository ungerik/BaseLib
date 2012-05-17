/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/DataBases/PersistentTable.h"
#include "BaseLib/ErrorHandling.h"



namespace BaseLib {
namespace DataBases {



using namespace BaseLib::ErrorHandling;



PersistentTable::NullColumn::NullColumn(const String& newName, const String& newBaseType, const String& newExactType)
	: AbstractColumn(newName, newBaseType, newExactType)
{
}



void PersistentTable::NullColumn::copyValueFrom(AbstractTable* sourceTable, int columnIndex)
{
}



int PersistentTable::NullColumn::getSizeInBytes(int rowIndex) const
{
	return 0;
}



const void* PersistentTable::NullColumn::getBinary(int rowIndex) const
{
	return NULL;
}



String PersistentTable::NullColumn::getString(int rowIndex) const
{
	return Empty();
}



bool PersistentTable::NullColumn::getBool(int rowIndex) const
{
	return false;
}



int32 PersistentTable::NullColumn::getInt(int rowIndex) const
{
	return 0; 
}



int64 PersistentTable::NullColumn::getInt64(int rowIndex) const
{
	return 0;
}



float PersistentTable::NullColumn::getFloat(int rowIndex) const
{
	return 0;
}



double PersistentTable::NullColumn::getDouble(int rowIndex) const
{
	return 0;
}



} // namespace DataBases
} // namespace BaseLib