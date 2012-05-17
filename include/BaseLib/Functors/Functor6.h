/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Functors_Functor6_h
#define BaseLib_Functors_Functor6_h



#include "BaseLib/Functors/FunctorType.h"
#include "BaseLib/Functors/EventObserver.h"



namespace BaseLib {
namespace Functors {



template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
class Functor6 {
public:

	typedef R ResultType;
	typedef A0 Argument0Type;
	typedef A1 Argument1Type;
	typedef A2 Argument2Type;
	typedef A3 Argument3Type;
	typedef A4 Argument4Type;
	typedef A5 Argument5Type;

	virtual ~Functor6<R, A0, A1, A2, A3, A4, A5>() {}

	virtual R execute(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5) const = 0;

	inline R operator ()(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5) const
	{
		return execute(arg0, arg1, arg2, arg3, arg4, arg5);
	}

	virtual FunctorType getFunctorType() const = 0;
	virtual bool operator ==(const Functor6& right) const = 0;
	virtual Functor6<R, A0, A1, A2, A3, A4, A5>* clone() const = 0;
};



template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
class FunctionFunctor6 : public Functor6<R, A0, A1, A2, A3, A4, A5> {
public:

	typedef R (*Function)(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5);

	FunctionFunctor6<R, A0, A1, A2, A3, A4, A5>(Function forFunction)
		: function(forFunction)
	{
	}

	virtual R execute(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5) const
	{
		return (*function)(arg0, arg1, arg2, arg3, arg4, arg5);
	}

	virtual FunctorType getFunctorType() const
	{
		return FUNCTION_FUNCTOR;
	}

	virtual bool operator ==(const Functor6<R, A0, A1, A2, A3, A4, A5>& right) const
	{
		return right.getFunctorType() == FUNCTION_FUNCTOR && function == static_cast<const FunctionFunctor6&>(right).function;
	}

	virtual FunctionFunctor6<R, A0, A1, A2, A3, A4, A5>* clone() const
	{
		return new FunctionFunctor6<R, A0, A1, A2, A3, A4, A5>(function);
	}

private:

	Function function;

};



template<class C, typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
class MethodFunctor6 : public Functor6<R, A0, A1, A2, A3, A4, A5> {
public:

	typedef R (C::*Method)(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5);

	MethodFunctor6<C, R, A0, A1, A2, A3, A4, A5>(C* atObject, Method forMethod)
		: object(atObject)
		, method(forMethod)
	{
	}

	virtual R execute(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5) const
	{
		return (object->*method)(arg0, arg1, arg2, arg3, arg4, arg5);
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

	virtual bool operator ==(const Functor6<R, A0, A1, A2, A3, A4, A5>& right) const
	{
		return right.getFunctorType() == METHOD_FUNCTOR && object == static_cast<const MethodFunctor6&>(right).object && method == static_cast<const MethodFunctor6&>(right).method;
	}

	virtual MethodFunctor6<C, R, A0, A1, A2, A3, A4, A5>* clone() const
	{
		return new MethodFunctor6<C, R, A0, A1, A2, A3, A4, A5>(object, method);
	}

private:

	mutable C* object;
	Method method;

};



template<class C, typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
class ConstMethodFunctor6 : public Functor6<R, A0, A1, A2, A3, A4, A5> {
public:

	typedef R (C::*Method)(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5) const;

	ConstMethodFunctor6<C, R, A0, A1, A2, A3, A4, A5>(const C* atObject, Method forMethod)
		: object(atObject)
		, method(forMethod)
	{
	}

	virtual R execute(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5) const
	{
		return (object->*method)(arg0, arg1, arg2, arg3, arg4, arg5);
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

	virtual bool operator ==(const Functor6<R, A0, A1, A2, A3, A4, A5>& right) const
	{
		return right.getFunctorType() == METHOD_FUNCTOR && object == static_cast<const ConstMethodFunctor6&>(right).object && method == static_cast<const ConstMethodFunctor6&>(right).method;
	}

	virtual ConstMethodFunctor6<C, R, A0, A1, A2, A3, A4, A5>* clone() const
	{
		return new ConstMethodFunctor6<C, R, A0, A1, A2, A3, A4, A5>(object, method);
	}

private:

	const C* object;
	Method method;

};







} // namespace Functors
} // namespace BaseLib



#endif // #ifndef BaseLib_Functors_Functor6_h
