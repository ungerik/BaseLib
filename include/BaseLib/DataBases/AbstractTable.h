/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_DataBases_AbstractTable_h
#define BaseLib_DataBases_AbstractTable_h



//#include "BaseLib/Containers/StringMap.h"
#include "BaseLib/Reflection/Object.h"



namespace BaseLib {
namespace DataBases {



using BaseLib::Strings::String;



class BL_EXPORT AbstractTable : public BaseLib::Reflection::Object {
public:

	BL_DECLARE_REFLECTION_BASELIB_BASE_CLASS(BaseLib::DataBases::AbstractTable);

	virtual ~AbstractTable();

	virtual bool isPersistent() const = 0;
	virtual bool moveToNextRow() = 0;
	virtual bool moveToPreviousRow() = 0;

	virtual int getCurrentRow() const = 0;
	virtual void setCurrentRow(int newCurrentRow) = 0;

	virtual int getRowCount() const = 0;
	virtual int getColumnCount() const = 0;
	virtual int getColumnIndex(const String& columnName, bool caseInsensitive = true) const;
	virtual String getColumnName(int columnIndex) const = 0;
	virtual String getColumnBaseType(int columnIndex) const = 0;
	virtual String getColumnExactType(int columnIndex) const = 0;

	inline bool isNull(int columnIndex) const
	{
		return getSizeInBytes(columnIndex) == 0;
	}
	virtual int getSizeInBytes(int columnIndex) const = 0;
	virtual const void* getBinary(int columnIndex) const = 0;
	virtual String getString(int columnIndex) const = 0;
	virtual bool getBool(int columnIndex) const = 0;
	virtual int32 getInt(int columnIndex) const = 0;
	virtual int64 getInt64(int columnIndex) const = 0;
	virtual float getFloat(int columnIndex) const = 0;
	virtual double getDouble(int columnIndex) const = 0;


};



} // namespace DataBases
} // namespace BaseLib



#endif // #ifndef BaseLib_DataBases_AbstractTable_h
