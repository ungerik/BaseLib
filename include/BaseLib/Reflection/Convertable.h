/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_Convertable_h
#define BaseLib_Reflection_Convertable_h



//#include "BaseLib/Containers/StringMap.h"
#include "BaseLib/Reflection/Object.h"



namespace BaseLib {
namespace Reflection {


/*
template<typename T>
class BL_EXPORT Convertable : public Object {
public:

	BL_DECLARE_REFLECTION_BASELIB_BASE_CLASS(BaseLib::Reflection::Convertable);

	Convertable();

    operator String() const;
    operator int() const;
    operator bool() const;
    operator float() const;
    operator double() const;

	template<typename V>
	inline Convertable& operator=(const String& propertyValue)
	{
		set(propertyValue);
		return *this;
	}

private:

	T value;
	const Property* property;

	void set(const String& propertyValue);
    void set(int propertyValue);
    void set(bool propertyValue);
    void set(float propertyValue);
    void set(double propertyValue);
};
*/


} // namespace Reflection
} // namespace BaseLib




#endif // #ifndef BaseLib_Reflection_Convertable_h