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



PersistentTable::BoolColumn::BoolColumn(const String& newName, const String& newBaseType, const String& newExactType)
	: AbstractColumn(newName, newBaseType, newExactType)
	, values()
{
}



void PersistentTable::BoolColumn::copyValueFrom(AbstractTable* sourceTable, int columnIndex)
{
	values += sourceTable->getBool(columnIndex);
}



int PersistentTable::BoolColumn::getSizeInBytes(int rowIndex) const
{
	return sizeof(bool);
}



const void* PersistentTable::BoolColumn::getBinary(int rowIndex) const
{
	return &values[rowIndex];
}



String PersistentTable::BoolColumn::getString(int rowIndex) const
{
	return String::createFrom(values[rowIndex]);
}



bool PersistentTable::BoolColumn::getBool(int rowIndex) const
{
	return values[rowIndex];
}



int32 PersistentTable::BoolColumn::getInt(int rowIndex) const
{
	return values[rowIndex];
}



int64 PersistentTable::BoolColumn::getInt64(int rowIndex) const
{
	return values[rowIndex];
}



float PersistentTable::BoolColumn::getFloat(int rowIndex) const
{
	return values[rowIndex];
}



double PersistentTable::BoolColumn::getDouble(int rowIndex) const
{
	return values[rowIndex];
}



} // namespace DataBases
} // namespace BaseLib