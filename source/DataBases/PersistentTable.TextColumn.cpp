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



PersistentTable::TextColumn::TextColumn(const String& newName, const String& newBaseType, const String& newExactType)
	: AbstractColumn(newName, newBaseType, newExactType)
	, values()
{
}



void PersistentTable::TextColumn::copyValueFrom(AbstractTable* sourceTable, int columnIndex)
{
	values += sourceTable->getString(columnIndex);
}



int PersistentTable::TextColumn::getSizeInBytes(int rowIndex) const
{
	return values[rowIndex].getByteSize();
}



const void* PersistentTable::TextColumn::getBinary(int rowIndex) const
{
	return values[rowIndex].getPointer();
}



String PersistentTable::TextColumn::getString(int rowIndex) const
{
	return values[rowIndex];
}



bool PersistentTable::TextColumn::getBool(int rowIndex) const
{
	return values[rowIndex].parseBool();
}



int32 PersistentTable::TextColumn::getInt(int rowIndex) const
{
	return values[rowIndex].parseInt();
}



int64 PersistentTable::TextColumn::getInt64(int rowIndex) const
{
	return values[rowIndex].parseInt64();
}



float PersistentTable::TextColumn::getFloat(int rowIndex) const
{
	return values[rowIndex].parseFloat();
}



double PersistentTable::TextColumn::getDouble(int rowIndex) const
{
	return values[rowIndex].parseDouble();
}



} // namespace DataBases
} // namespace BaseLib