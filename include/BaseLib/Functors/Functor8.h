/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Functors_Functor8_h
#define BaseLib_Functors_Functor8_h



#include "BaseLib/Functors/FunctorType.h"
#include "BaseLib/Functors/EventObserver.h"



namespace BaseLib {
namespace Functors {



template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
class Functor8 {
public:

	typedef R ResultType;
	typedef A0 Argument0Type;
	typedef A1 Argument1Type;
	typedef A2 Argument2Type;
	typedef A3 Argument3Type;
	typedef A4 Argument4Type;
	typedef A5 Argument5Type;
	typedef A6 Argument6Type;
	typedef A7 Argument7Type;

	virtual ~Functor8<R, A0, A1, A2, A3, A4, A5, A6, A7>() {}

	virtual R execute(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6, A7 arg7) const = 0;

	inline R operator ()(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6, A7 arg7) const
	{
		return execute(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	}

	virtual FunctorType getFunctorType() const = 0;
	virtual bool operator ==(const Functor8& right) const = 0;
	virtual Functor8<R, A0, A1, A2, A3, A4, A5, A6, A7>* clone() const = 0;
};



template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
class FunctionFunctor8 : public Functor8<R, A0, A1, A2, A3, A4, A5, A6, A7> {
public:

	typedef R (*Function)(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6, A7 arg7);

	FunctionFunctor8<R, A0, A1, A2, A3, A4, A5, A6, A7>(Function forFunction)
		: function(forFunction)
	{
	}

	virtual R execute(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6, A7 arg7) const
	{
		return (*function)(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	}

	virtual FunctorType getFunctorType() const
	{
		return FUNCTION_FUNCTOR;
	}

	virtual bool operator ==(const Functor8<R, A0, A1, A2, A3, A4, A5, A6, A7>& right) const
	{
		return right.getFunctorType() == FUNCTION_FUNCTOR && function == static_cast<const FunctionFunctor8&>(right).function;
	}

	virtual FunctionFunctor8<R, A0, A1, A2, A3, A4, A5, A6, A7>* clone() const
	{
		return new FunctionFunctor8<R, A0, A1, A2, A3, A4, A5, A6, A7>(function);
	}

private:

	Function function;

};



template<class C, typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
class MethodFunctor8 : public Functor8<R, A0, A1, A2, A3, A4, A5, A6, A7> {
public:

	typedef R (C::*Method)(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6, A7 arg7);

	MethodFunctor8<C, R, A0, A1, A2, A3, A4, A5, A6, A7>(C* atObject, Method forMethod)
		: object(atObject)
		, method(forMethod)
	{
	}

	virtual R execute(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6, A7 arg7) const
	{
		return (object->*method)(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	}

	inline C* getObject() const
	{
		return object;
	}

	inline void setObject(C* newObject)
	{
		object = newObject;
	}

	inline Method getMethod() const
	{
		return method;
	}

	inline void setMethod(Method newMethod)
	{
		method = newMethod;
	}

	virtual FunctorType getFunctorType() const
	{
		return METHOD_FUNCTOR;
	}

	virtual bool operator ==(const Functor8<R, A0, A1, A2, A3, A4, A5, A6, A7>& right) const
	{
		return right.getFunctorType() == METHOD_FUNCTOR && object == static_cast<const MethodFunctor8&>(right).object && method == static_cast<const MethodFunctor8&>(right).method;
	}

	virtual MethodFunctor8<C, R, A0, A1, A2, A3, A4, A5, A6, A7>* clone() const
	{
		return new MethodFunctor8<C, R, A0, A1, A2, A3, A4, A5, A6, A7>(object, method);
	}

private:

	mutable C* object;
	Method method;

};



template<class C, typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
class ConstMethodFunctor8 : public Functor8<R, A0, A1, A2, A3, A4, A5, A6, A7> {
public:

	typedef R (C::*Method)(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6, A7 arg7) const;

	ConstMethodFunctor8<C, R, A0, A1, A2, A3, A4, A5, A6, A7>(const C* atObject, Method forMethod)
		: object(atObject)
		, method(forMethod)
	{
	}

	virtual R execute(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6, A7 arg7) const
	{
		return (object->*method)(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	}

	inline const C* getObject() const
	{
		return object;
	}

	inline void setObject(const C* newObject)
	{
		object = newObject;
	}

	inline Method getMethod() const
	{
		return method;
	}

	inline void setMethod(Method newMethod)
	{
		method = newMethod;
	}

	virtual FunctorType getFunctorType() const
	{
		return METHOD_FUNCTOR;
	}

	virtual bool operator ==(const Functor8<R, A0, A1, A2, A3, A4, A5, A6, A7>& right) const
	{
		return right.getFunctorType() == METHOD_FUNCTOR && object == static_cast<const ConstMethodFunctor8&>(right).object && method == static_cast<const ConstMethodFunctor8&>(right).method;
	}

	virtual ConstMethodFunctor8<C, R, A0, A1, A2, A3, A4, A5, A6, A7>* clone() const
	{
		return new ConstMethodFunctor8<C, R, A0, A1, A2, A3, A4, A5, A6, A7>(object, method);
	}

private:

	const C* object;
	Method method;

};







} // namespace Functors
} // namespace BaseLib



#endif // #ifndef BaseLib_Functors_Functor8_h
