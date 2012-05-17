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
using namespace BaseLib::Utilities;



PersistentTable::BlobColumn::BlobColumn(const String& newName, const String& newBaseType, const String& newExactType)
	: AbstractColumn(newName, newBaseType, newExactType)
	, buffer()
	, values()
{
}



void PersistentTable::BlobColumn::copyValueFrom(AbstractTable* sourceTable, int columnIndex)
{
	int position = buffer.getSizeAsInt();
	int byteCount = sourceTable->getSizeInBytes(columnIndex);
	values += BlobInfo(position, byteCount);
	buffer.writeAtPosition(position, sourceTable->getBinary(columnIndex), byteCount);
}



int PersistentTable::BlobColumn::getSizeInBytes(int rowIndex) const
{
	return values[rowIndex].size;
}



const void* PersistentTable::BlobColumn::getBinary(int rowIndex) const
{
	return offsetPointer(buffer.getPointer(), values[rowIndex].start);
}



String PersistentTable::BlobColumn::getString(int rowIndex) const
{
	return Empty(); ///
}



bool PersistentTable::BlobColumn::getBool(int rowIndex) const
{
	return false; ///
}



int32 PersistentTable::BlobColumn::getInt(int rowIndex) const
{
	return 0; ///
}



int64 PersistentTable::BlobColumn::getInt64(int rowIndex) const
{
	return 0; ///
}



float PersistentTable::BlobColumn::getFloat(int rowIndex) const
{
	return 0; ///
}



double PersistentTable::BlobColumn::getDouble(int rowIndex) const
{
	return 0; ///
}



} // namespace DataBases
} // namespace BaseLib
