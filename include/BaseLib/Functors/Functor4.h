/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Functors_Functor4_h
#define BaseLib_Functors_Functor4_h



#include "BaseLib/Functors/FunctorType.h"
#include "BaseLib/Functors/EventObserver.h"



namespace BaseLib {
namespace Functors {



template<typename R, typename A0, typename A1, typename A2, typename A3>
class Functor4 {
public:

	typedef R ResultType;
	typedef A0 Argument0Type;
	typedef A1 Argument1Type;
	typedef A2 Argument2Type;
	typedef A3 Argument3Type;

	virtual ~Functor4<R, A0, A1, A2, A3>() {}

	virtual R execute(A0 arg0, A1 arg1, A2 arg2, A3 arg3) const = 0;

	inline R operator ()(A0 arg0, A1 arg1, A2 arg2, A3 arg3) const
	{
		return execute(arg0, arg1, arg2, arg3);
	}

	virtual FunctorType getFunctorType() const = 0;
	virtual bool operator ==(const Functor4& right) const = 0;
	virtual Functor4<R, A0, A1, A2, A3>* clone() const = 0;
};



template<typename A0, typename A1, typename A2, typename A3>
class Event4 : public Functor4<void, A0, A1, A2, A3> {
public:

	inline Event4()
		: Functor4<void, A0, A1, A2, A3>()
		, event()
	{
	}

	virtual void execute(A0 arg0, A1 arg1, A2 arg2, A3 arg3) const
	{
		const int count = event.getObserverCount();
		for (int i = 0; i < count; ++i)
		{
			event.getObserver(i)->getFunctor().execute(arg0, arg1, arg2, arg3);
		}
	}

	virtual FunctorType getFunctorType() const
	{
		return CUSTOM_FUNCTOR;
	}

	virtual bool operator ==(const Functor4<void, A0, A1, A2, A3>& right) const
	{
		return false; // Can't compare
	}

	virtual Functor4<void, A0, A1, A2, A3>* clone() const
	{
		return NULL; // Can't clone
	}

	inline operator EventManager<Functor4<void, A0, A1, A2, A3> >&()
	{
		return event;
	}
	inline operator const EventManager<Functor4<void, A0, A1, A2, A3> >&() const
	{
		return event;
	}

private:

	EventManager<Functor4<void, A0, A1, A2, A3> > event;
};



template<typename R, typename A0, typename A1, typename A2, typename A3>
class FunctionFunctor4 : public Functor4<R, A0, A1, A2, A3> {
public:

	typedef R (*Function)(A0 arg0, A1 arg1, A2 arg2, A3 arg3);

	FunctionFunctor4<R, A0, A1, A2, A3>(Function forFunction)
		: function(forFunction)
	{
	}

	virtual R execute(A0 arg0, A1 arg1, A2 arg2, A3 arg3) const
	{
		return (*function)(arg0, arg1, arg2, arg3);
	}

	virtual FunctorType getFunctorType() const
	{
		return FUNCTION_FUNCTOR;
	}

	virtual bool operator ==(const Functor4<R, A0, A1, A2, A3>& right) const
	{
		return right.getFunctorType() == FUNCTION_FUNCTOR && function == static_cast<const FunctionFunctor4&>(right).function;
	}

	virtual FunctionFunctor4<R, A0, A1, A2, A3>* clone() const
	{
		return new FunctionFunctor4<R, A0, A1, A2, A3>(function);
	}

private:

	Function function;

};



template<class C, typename R, typename A0, typename A1, typename A2, typename A3>
class MethodFunctor4 : public Functor4<R, A0, A1, A2, A3> {
public:

	typedef R (C::*Method)(A0 arg0, A1 arg1, A2 arg2, A3 arg3);

	MethodFunctor4<C, R, A0, A1, A2, A3>(C* atObject, Method forMethod)
		: object(atObject)
		, method(forMethod)
	{
	}

	virtual R execute(A0 arg0, A1 arg1, A2 arg2, A3 arg3) const
	{
		return (object->*method)(arg0, arg1, arg2, arg3);
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

	virtual bool operator ==(const Functor4<R, A0, A1, A2, A3>& right) const
	{
		return right.getFunctorType() == METHOD_FUNCTOR && object == static_cast<const MethodFunctor4&>(right).object && method == static_cast<const MethodFunctor4&>(right).method;
	}

	virtual MethodFunctor4<C, R, A0, A1, A2, A3>* clone() const
	{
		return new MethodFunctor4<C, R, A0, A1, A2, A3>(object, method);
	}

private:

	mutable C* object;
	Method method;

};



template<class C, typename R, typename A0, typename A1, typename A2, typename A3>
class ConstMethodFunctor4 : public Functor4<R, A0, A1, A2, A3> {
public:

	typedef R (C::*Method)(A0 arg0, A1 arg1, A2 arg2, A3 arg3) const;

	ConstMethodFunctor4<C, R, A0, A1, A2, A3>(const C* atObject, Method forMethod)
		: object(atObject)
		, method(forMethod)
	{
	}

	virtual R execute(A0 arg0, A1 arg1, A2 arg2, A3 arg3) const
	{
		return (object->*method)(arg0, arg1, arg2, arg3);
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

	virtual bool operator ==(const Functor4<R, A0, A1, A2, A3>& right) const
	{
		return right.getFunctorType() == METHOD_FUNCTOR && object == static_cast<const ConstMethodFunctor4&>(right).object && method == static_cast<const ConstMethodFunctor4&>(right).method;
	}

	virtual ConstMethodFunctor4<C, R, A0, A1, A2, A3>* clone() const
	{
		return new ConstMethodFunctor4<C, R, A0, A1, A2, A3>(object, method);
	}

private:

	const C* object;
	Method method;

};







} // namespace Functors
} // namespace BaseLib



#endif // #ifndef BaseLib_Functors_Functor4_h
