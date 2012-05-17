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
using namespace BaseLib::Math;



BL_DEFINE_REFLECTION_CLASS(PersistentTable, AbstractTable)
{
}



PersistentTable::PersistentTable(AbstractTable* sourceTable)
	: AbstractTable()
	, rowCount(0)
	, currentRow(-1)
	, columns()
	, firstRowFound(false)
{
	if (checkArgumentNotNull(NAME_VALUE(sourceTable)) == true)
	{		
		firstRowFound = sourceTable->moveToNextRow(); // We need this step for SQLite, because else we won't get column information

		initColumns(sourceTable);
		initRows(sourceTable);
	}
}



void PersistentTable::initColumns(AbstractTable* sourceTable)
{
	BL_ASSERT(sourceTable != NULL);

	const int columnCount = sourceTable->getColumnCount();
	columns.setCount(columnCount);
	for (int i = 0; i < columnCount; ++i)
	{
		String name = sourceTable->getColumnName(i);
		String baseType = sourceTable->getColumnBaseType(i);
		String exactType = sourceTable->getColumnExactType(i);

		String type = baseType.lowerCase();
		if (type == "int" || type == "integer")
		{
			switch (sourceTable->getSizeInBytes(i))
			{
				case 1:
					columns[i] = new IntColumn<int8>(name, baseType, exactType);
					break;

				case 2:
					columns[i] = new IntColumn<int16>(name, baseType, exactType);
					break;

				case 3:
				case 4:
					columns[i] = new IntColumn<int32>(name, baseType, exactType);
					break;

				case 8:
					columns[i] = new IntColumn<int64>(name, baseType, exactType);
					break;

				default:
					BL_ASSERT_NEVER_REACHED
					columns[i] = new NullColumn(name, baseType, exactType);
					break;
			}
		}
		else if (type == "bool" || type == "boolean")
		{
			columns[i] = new BoolColumn(name, baseType, exactType);
		}
		else if (type == "float" || type == "double" || type == "real")
		{
			switch (sourceTable->getSizeInBytes(i))
			{
				case 4:
					columns[i] = new FloatColumn<float32>(name, baseType, exactType);
					break;

				case 8:
					columns[i] = new FloatColumn<float64>(name, baseType, exactType);
					break;

				default:
					BL_ASSERT_NEVER_REACHED
					columns[i] = new NullColumn(name, baseType, exactType);
					break;
			}
		}
		else if (type == "text" || type == "string" || type == "char" || type == "character")
		{
			columns[i] = new TextColumn(name, baseType, exactType);
		}
		else if (type == "blob" || type == "binary")
		{
			columns[i] = new BlobColumn(name, baseType, exactType);
		}
		else if (type == "null" || type == "void")
		{
			columns[i] = new NullColumn(name, baseType, exactType);
		}
		else
		{
			BL_ASSERT_NEVER_REACHED
			columns[i] = new NullColumn(name, baseType, exactType);
		}
	}
}



void PersistentTable::initRows(AbstractTable* sourceTable)
{
	BL_ASSERT(sourceTable != NULL);

	const int columnCount = columns.getCount();
	if (columnCount > 0 && firstRowFound == true)
	{
		do
		{
			++rowCount;
			for (int i = 0; i < columnCount; ++i)
			{
				columns[i]->copyValueFrom(sourceTable, i);
			}
		}
		while (sourceTable->moveToNextRow() == true);
	}
}



PersistentTable::~PersistentTable()
{
	int columnCount = columns.getCount();
	for (int i = 0; i < columnCount; ++i)
	{
		delete columns[i];
	}
}



bool PersistentTable::isPersistent() const
{
	return true;
}



bool PersistentTable::moveToNextRow()
{
	if (currentRow < rowCount-1)
	{
		++currentRow;
		return true;
	}
	else
	{
		return false;
	}
}



bool PersistentTable::moveToPreviousRow()
{
	if (currentRow > 0)
	{
		--currentRow;
		return true;
	}
	else
	{
		return false;
	}
}



int PersistentTable::getCurrentRow() const
{
	return currentRow;
}



void PersistentTable::setCurrentRow(int newCurrentRow)
{
	if (checkArgumentRange(NAME_VALUE(newCurrentRow), 0, getRowCount()-1) == true)
	{
		currentRow = newCurrentRow;
	}
}



int PersistentTable::getRowCount() const
{
	return rowCount;
}



int PersistentTable::getColumnCount() const
{
	return columns.getCount();
}



String PersistentTable::getColumnName(int columnIndex) const
{
	if (checkArgumentRange(NAME_VALUE(columnIndex), 0, getColumnCount()-1) == true)
	{
		return columns[columnIndex]->name;
	}
	else
	{
		return Empty();
	}
}



String PersistentTable::getColumnBaseType(int columnIndex) const
{
	if (checkArgumentRange(NAME_VALUE(columnIndex), 0, getColumnCount()-1) == true)
	{
		return columns[columnIndex]->baseType;
	}
	else
	{
		return Empty();
	}
}



String PersistentTable::getColumnExactType(int columnIndex) const
{
	if (checkArgumentRange(NAME_VALUE(columnIndex), 0, getColumnCount()-1) == true)
	{
		return columns[columnIndex]->exactType;
	}
	else
	{
		return Empty();
	}
}



int PersistentTable::getSizeInBytes(int columnIndex) const
{
	if (checkArgumentRange(NAME_VALUE(columnIndex), 0, getColumnCount()-1) == true)
	{
		return columns[columnIndex]->getSizeInBytes(currentRow);
	}
	else
	{
		return 0;
	}
}



const void* PersistentTable::getBinary(int columnIndex) const
{
	if (checkArgumentRange(NAME_VALUE(columnIndex), 0, getColumnCount()-1) == true)
	{
		return columns[columnIndex]->getBinary(currentRow);
	}
	else
	{
		return NULL;
	}
}



String PersistentTable::getString(int columnIndex) const
{
	if (checkArgumentRange(NAME_VALUE(columnIndex), 0, getColumnCount()-1) == true)
	{
		return columns[columnIndex]->getString(currentRow);
	}
	else
	{
		return Empty();
	}
}



bool PersistentTable::getBool(int columnIndex) const
{
	if (checkArgumentRange(NAME_VALUE(columnIndex), 0, getColumnCount()-1) == true)
	{
		return columns[columnIndex]->getBool(currentRow);
	}
	else
	{
		return false;
	}
}



int32 PersistentTable::getInt(int columnIndex) const
{
	if (checkArgumentRange(NAME_VALUE(columnIndex), 0, getColumnCount()-1) == true)
	{
		return columns[columnIndex]->getInt(currentRow);
	}
	else
	{
		return -1;
	}
}



int64 PersistentTable::getInt64(int columnIndex) const
{
	if (checkArgumentRange(NAME_VALUE(columnIndex), 0, getColumnCount()-1) == true)
	{
		return columns[columnIndex]->getInt64(currentRow);
	}
	else
	{
		return -1;
	}
}



float PersistentTable::getFloat(int columnIndex) const
{
	if (checkArgumentRange(NAME_VALUE(columnIndex), 0, getColumnCount()-1) == true)
	{
		return columns[columnIndex]->getFloat(currentRow);
	}
	else
	{
		return NAN;
	}
}



double PersistentTable::getDouble(int columnIndex) const
{
	if (checkArgumentRange(NAME_VALUE(columnIndex), 0, getColumnCount()-1) == true)
	{
		return columns[columnIndex]->getDouble(currentRow);
	}
	else
	{
		return NAN;
	}
}



} // namespace DataBases
} // namespace BaseLib