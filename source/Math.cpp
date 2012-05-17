/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Math/Common.h"


#include "BaseLib/Math.h"
#include <map>
#include <string>
#include "BaseLib/ErrorHandling.h"
#include "BaseLib/Containers/Array.h"



namespace BaseLib {
namespace Math {



const NaN NAN;


using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Utilities;
using namespace BaseLib::Containers;



template<typename T, int COUNT>
class BL_EXPORT Enum {
public:

	typedef T ValueType;

	inline static int getCount() { return COUNT; }

	class Iterator {
	};

protected:

	inline Enum<T, COUNT>()
	{
		BL_STATIC_ASSERT(::BaseLib::TypeTraits::IsValueType<T>::VALUE == true, EnumTypeMustBeValueType);
	}

	inline Enum<T, COUNT>(T newValue)
		: value(newValue)
	{
		BL_STATIC_ASSERT(::BaseLib::TypeTraits::IsValueType<T>::VALUE == true, EnumTypeMustBeValueType);
	}

public:

	inline const T& getValue() const
	{
		return value;
	}

	inline bool operator ==(const Enum<T, COUNT>& right)
	{
		return value == right.getValue();
	}

	inline bool operator !=(const Enum<T, COUNT>& right)
	{
		return !operator ==(right);
	}

protected:

	T value;

	typedef std::map<std::string, ValueType> NameValueMap;
	typedef std::map<ValueType, const char*> ValueNameMap;

};



#define BL_DEFINE_ENUM_MARKER(EnumName, Enum_, value_) \
	struct Enum_ {}; \
	inline EnumName(Enum_) : BasisType(value) {} \
	inline EnumName& operator =(Enum_) { value = value_; return *this; }


#define BL_DECLARE_ENUM_2(EnumName, T, Enum0, value0, Enum1, value1) \
	class EnumName : public Enum<T, 2> { \
	public: \
		struct EnumValueInfoDefiner { \
			EnumValueInfoDefiner(NameValueMap& nameValueMap, ValueNameMap& valueNameMap) \
			{ \
				nameValueMap[#Enum0] = value0; valueNameMap[value0] = #Enum0; \
				nameValueMap[#Enum1] = value1; valueNameMap[value1] = #Enum1; \
			} \
		}; \
		\
		BL_DEFINE_ENUM_MARKER(EnumName, Enum0, value0) \
		BL_DEFINE_ENUM_MARKER(EnumName, Enum1, value1) \
		\
		inline explicit EnumName() \
			: BasisType() \
		{ \
			BL_STATIC_ASSERT(value0 != value1, EnumValuesMustBeUnique); \
		} \
		\
		inline explicit EnumName(T forValue) : BasisType(forValue) {} \
		\
		inline EnumName(const EnumName& other) : BasisType(other.getValue()) {} \
		\
		inline EnumName& operator =(const EnumName& right) { value = right.getValue(); return *this; } \
		\
		inline const char* toStringWithoutType() const \
		{ \
			return getNameByValue(value); \
		} \
		\
		inline const char* toString() const \
		{ \
			return (std::string(#EnumName"::") + getNameByValue(value)).c_str(); \
		} \
		\
		inline static const char* getNameByValue(T value) \
		{ \
			ValueNameMap::iterator i = valueNameMap.find(value); \
			return i != valueNameMap.end() ? i->second : NULL; \
		} \
		\
		inline static T getValueByName(const char* name) \
		{ \
			NameValueMap::iterator i = nameValueMap.find(name); \
			return i != nameValueMap.end() ? i->second : T(); \
		} \
		\
		inline static bool hasName(const char* name) \
		{ \
			return nameValueMap.count(name) != 0; \
		} \
		\
		inline static bool hasValue(T value) \
		{ \
			return valueNameMap.count(value) != 0; \
		} \
		\
	private: \
		typedef Enum<T, 2> BasisType; \
		static NameValueMap nameValueMap; \
		static ValueNameMap valueNameMap; \
		static const EnumValueInfoDefiner enumValueInfoDefiner; \
	}



#define BL_DEFINE_ENUM(EnumName) \
	EnumName::NameValueMap EnumName::nameValueMap; \
	EnumName::ValueNameMap EnumName::valueNameMap; \
	const EnumName::EnumValueInfoDefiner enumValueInfoDefiner();


BL_DECLARE_ENUM_2(Color, int, Red, 0, Green, 1);


BL_DEFINE_ENUM(Color);


template<class T>
class PoolAllocated {
public:

	void* operator new(size_t byteCount)
	{
		return malloc(byteCount);
	}

	static T* allocate()
	{
		return new(NULL) T();
	}

};



template<class T>
class InstanceListed {
private:

	typedef Array<T*> Instances;

public:

	typedef typename Instances::Iterator Iterator;

	inline static int getInstanceCount()
	{
		return instances.getCount();
	}

	inline static Iterator begin()
	{
		return instances.begin();
	}

	inline static Iterator end()
	{
		return instances.end();
	}

	static void deleteAllInstances()
	{
		deletingAllInstances = true;
		try
		{
			foreach (Iterator, i, instances)
			{
				delete *i;
			}
			instances.setCount(0);
			deletingAllInstances = false;
		}
		catch (...)
		{
			deletingAllInstances = false;
			throw;
		}
	}

	inline InstanceListed()
	{
		instances += static_cast<T*>(this);
	}

	inline ~InstanceListed()
	{
		if (deletingAllInstances == false)
		{
			instances -= static_cast<T*>(this);
		}
	}

private:
	static Instances instances;
	static bool deletingAllInstances;
};

template<class T>
typename InstanceListed<T>::Instances InstanceListed<T>::instances;

template<class T>
bool InstanceListed<T>::deletingAllInstances = false;



class MySingletonClass : public Singleton<MySingletonClass>, public PoolAllocated<MySingletonClass>, public InstanceListed<MySingletonClass> {
public:

	MySingletonClass() {}

private:
	int x;

};


void test()
{
	Color c0 = Color::Red();
	Color c1 = Color::Green();

	bool equals = c1 == c0;

	c1 = c0;

	MySingletonClass& s = MySingletonClass::getSingleton();
	MySingletonClass::deleteAllInstances();

}





} // namespace Math
} // namespace BaseLib
