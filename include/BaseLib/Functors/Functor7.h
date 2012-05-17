/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Functors_Functor7_h
#define BaseLib_Functors_Functor7_h



#include "BaseLib/Functors/FunctorType.h"
#include "BaseLib/Functors/EventObserver.h"



namespace BaseLib {
namespace Functors {



template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
class Functor7 {
public:

	typedef R ResultType;
	typedef A0 Argument0Type;
	typedef A1 Argument1Type;
	typedef A2 Argument2Type;
	typedef A3 Argument3Type;
	typedef A4 Argument4Type;
	typedef A5 Argument5Type;
	typedef A6 Argument6Type;

	virtual ~Functor7<R, A0, A1, A2, A3, A4, A5, A6>() {}

	virtual R execute(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6) const = 0;

	inline R operator ()(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6) const
	{
		return execute(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
	}

	virtual FunctorType getFunctorType() const = 0;
	virtual bool operator ==(const Functor7& right) const = 0;
	virtual Functor7<R, A0, A1, A2, A3, A4, A5, A6>* clone() const = 0;
};



template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
class FunctionFunctor7 : public Functor7<R, A0, A1, A2, A3, A4, A5, A6> {
public:

	typedef R (*Function)(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6);

	FunctionFunctor7<R, A0, A1, A2, A3, A4, A5, A6>(Function forFunction)
		: function(forFunction)
	{
	}

	virtual R execute(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6) const
	{
		return (*function)(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
	}

	virtual FunctorType getFunctorType() const
	{
		return FUNCTION_FUNCTOR;
	}

	virtual bool operator ==(const Functor7<R, A0, A1, A2, A3, A4, A5, A6>& right) const
	{
		return right.getFunctorType() == FUNCTION_FUNCTOR && function == static_cast<const FunctionFunctor7&>(right).function;
	}

	virtual FunctionFunctor7<R, A0, A1, A2, A3, A4, A5, A6>* clone() const
	{
		return new FunctionFunctor7<R, A0, A1, A2, A3, A4, A5, A6>(function);
	}

private:

	Function function;

};



template<class C, typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
class MethodFunctor7 : public Functor7<R, A0, A1, A2, A3, A4, A5, A6> {
public:

	typedef R (C::*Method)(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6);

	MethodFunctor7<C, R, A0, A1, A2, A3, A4, A5, A6>(C* atObject, Method forMethod)
		: object(atObject)
		, method(forMethod)
	{
	}

	virtual R execute(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6) const
	{
		return (object->*method)(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
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

	virtual bool operator ==(const Functor7<R, A0, A1, A2, A3, A4, A5, A6>& right) const
	{
		return right.getFunctorType() == METHOD_FUNCTOR && object == static_cast<const MethodFunctor7&>(right).object && method == static_cast<const MethodFunctor7&>(right).method;
	}

	virtual MethodFunctor7<C, R, A0, A1, A2, A3, A4, A5, A6>* clone() const
	{
		return new MethodFunctor7<C, R, A0, A1, A2, A3, A4, A5, A6>(object, method);
	}

private:

	mutable C* object;
	Method method;

};



template<class C, typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
class ConstMethodFunctor7 : public Functor7<R, A0, A1, A2, A3, A4, A5, A6> {
public:

	typedef R (C::*Method)(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6) const;

	ConstMethodFunctor7<C, R, A0, A1, A2, A3, A4, A5, A6>(const C* atObject, Method forMethod)
		: object(atObject)
		, method(forMethod)
	{
	}

	virtual R execute(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6) const
	{
		return (object->*method)(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
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

	virtual bool operator ==(const Functor7<R, A0, A1, A2, A3, A4, A5, A6>& right) const
	{
		return right.getFunctorType() == METHOD_FUNCTOR && object == static_cast<const ConstMethodFunctor7&>(right).object && method == static_cast<const ConstMethodFunctor7&>(right).method;
	}

	virtual ConstMethodFunctor7<C, R, A0, A1, A2, A3, A4, A5, A6>* clone() const
	{
		return new ConstMethodFunctor7<C, R, A0, A1, A2, A3, A4, A5, A6>(object, method);
	}

private:

	const C* object;
	Method method;

};







} // namespace Functors
} // namespace BaseLib



#endif // #ifndef BaseLib_Functors_Functor7_h
