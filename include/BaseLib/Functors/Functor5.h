/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Functors_Functor5_h
#define BaseLib_Functors_Functor5_h



#include "BaseLib/Functors/FunctorType.h"
#include "BaseLib/Functors/EventObserver.h"



namespace BaseLib {
namespace Functors {



template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
class Functor5 {
public:

	typedef R ResultType;
	typedef A0 Argument0Type;
	typedef A1 Argument1Type;
	typedef A2 Argument2Type;
	typedef A3 Argument3Type;
	typedef A4 Argument4Type;

	virtual ~Functor5<R, A0, A1, A2, A3, A4>() {}

	virtual R execute(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4) const = 0;

	inline R operator ()(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4) const
	{
		return execute(arg0, arg1, arg2, arg3, arg4);
	}

	virtual FunctorType getFunctorType() const = 0;
	virtual bool operator ==(const Functor5& right) const = 0;
	virtual Functor5<R, A0, A1, A2, A3, A4>* clone() const = 0;
};



template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
class FunctionFunctor5 : public Functor5<R, A0, A1, A2, A3, A4> {
public:

	typedef R (*Function)(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4);

	FunctionFunctor5<R, A0, A1, A2, A3, A4>(Function forFunction)
		: function(forFunction)
	{
	}

	virtual R execute(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4) const
	{
		return (*function)(arg0, arg1, arg2, arg3, arg4);
	}

	virtual FunctorType getFunctorType() const
	{
		return FUNCTION_FUNCTOR;
	}

	virtual bool operator ==(const Functor5<R, A0, A1, A2, A3, A4>& right) const
	{
		return right.getFunctorType() == FUNCTION_FUNCTOR && function == static_cast<const FunctionFunctor5&>(right).function;
	}

	virtual FunctionFunctor5<R, A0, A1, A2, A3, A4>* clone() const
	{
		return new FunctionFunctor5<R, A0, A1, A2, A3, A4>(function);
	}

private:

	Function function;

};



template<class C, typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
class MethodFunctor5 : public Functor5<R, A0, A1, A2, A3, A4> {
public:

	typedef R (C::*Method)(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4);

	MethodFunctor5<C, R, A0, A1, A2, A3, A4>(C* atObject, Method forMethod)
		: object(atObject)
		, method(forMethod)
	{
	}

	virtual R execute(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4) const
	{
		return (object->*method)(arg0, arg1, arg2, arg3, arg4);
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

	virtual bool operator ==(const Functor5<R, A0, A1, A2, A3, A4>& right) const
	{
		return right.getFunctorType() == METHOD_FUNCTOR && object == static_cast<const MethodFunctor5&>(right).object && method == static_cast<const MethodFunctor5&>(right).method;
	}

	virtual MethodFunctor5<C, R, A0, A1, A2, A3, A4>* clone() const
	{
		return new MethodFunctor5<C, R, A0, A1, A2, A3, A4>(object, method);
	}

private:

	mutable C* object;
	Method method;

};



template<class C, typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
class ConstMethodFunctor5 : public Functor5<R, A0, A1, A2, A3, A4> {
public:

	typedef R (C::*Method)(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4) const;

	ConstMethodFunctor5<C, R, A0, A1, A2, A3, A4>(const C* atObject, Method forMethod)
		: object(atObject)
		, method(forMethod)
	{
	}

	virtual R execute(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4) const
	{
		return (object->*method)(arg0, arg1, arg2, arg3, arg4);
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

	virtual bool operator ==(const Functor5<R, A0, A1, A2, A3, A4>& right) const
	{
		return right.getFunctorType() == METHOD_FUNCTOR && object == static_cast<const ConstMethodFunctor5&>(right).object && method == static_cast<const ConstMethodFunctor5&>(right).method;
	}

	virtual ConstMethodFunctor5<C, R, A0, A1, A2, A3, A4>* clone() const
	{
		return new ConstMethodFunctor5<C, R, A0, A1, A2, A3, A4>(object, method);
	}

private:

	const C* object;
	Method method;

};







} // namespace Functors
} // namespace BaseLib



#endif // #ifndef BaseLib_Functors_Functor5_h
