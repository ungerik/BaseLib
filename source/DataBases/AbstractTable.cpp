/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/DataBases/AbstractTable.h"
#include "BaseLib/ErrorHandling.h"



namespace BaseLib {
namespace DataBases {



using namespace BaseLib::ErrorHandling;



BL_DEFINE_REFLECTION_BASE_CLASS(AbstractTable)
{
}



AbstractTable::~AbstractTable()
{
}



int AbstractTable::getColumnIndex(const String& columnName, bool caseInsensitive) const
{
	int columnCount = getColumnCount();
	for (int i = 0; i < columnCount; ++i)
	{
		if (caseInsensitive == true)
		{
			if (getColumnName(i).equalsCaseInsensitive(columnName) == true)
			{
				return i;
			}
		}
		else
		{
			if (getColumnName(i) == columnName)
			{
				return i;
			}
		}
	}

	argumentError("Can't find column with name '" + columnName + "' !" ERROR_AT);
	return -1;
}



} // namespace DataBases
} // namespace BaseLib