/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_DataBases_AbstractCompiledQuery_h
#define BaseLib_DataBases_AbstractCompiledQuery_h



#include "BaseLib/DataBases/AbstractTable.h"
#include "BaseLib/Reflection/Object.h"



namespace BaseLib {
namespace DataBases {



class BL_EXPORT AbstractCompiledQuery : public BaseLib::Reflection::Object {
public:

	BL_DECLARE_REFLECTION_BASELIB_BASE_CLASS(BaseLib::DataBases::AbstractCompiledQuery);

	virtual ~AbstractCompiledQuery();

	virtual AbstractTable* execute(bool persistentTable) = 0;
	virtual void execute() = 0;

};



} // namespace DataBases
} // namespace BaseLib



#endif // #ifndef BaseLib_DataBases_AbstractCompiledQuery_h
