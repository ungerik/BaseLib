/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Functors_Functor2_h
#define BaseLib_Functors_Functor2_h



#include "BaseLib/Functors/FunctorType.h"
#include "BaseLib/Functors/EventObserver.h"



namespace BaseLib {
namespace Functors {



template<typename R, typename A0, typename A1>
class Functor2 {
public:

	typedef R ResultType;
	typedef A0 Argument0Type;
	typedef A1 Argument1Type;

	virtual ~Functor2<R, A0, A1>() {}

	virtual R execute(A0 arg0, A1 arg1) const = 0;

	inline R operator ()(A0 arg0, A1 arg1) const
	{
		return execute(arg0, arg1);
	}

	virtual FunctorType getFunctorType() const = 0;
	virtual bool operator ==(const Functor2& right) const = 0;
	virtual Functor2<R, A0, A1>* clone() const = 0;
};



template<typename A0, typename A1>
class Event2 : public Functor2<void, A0, A1> {
public:

	inline Event2()
		: Functor2<void, A0, A1>()
		, event()
	{
	}

	virtual void execute(A0 arg0, A1 arg1) const
	{
		const int count = event.getObserverCount();
		for (int i = 0; i < count; ++i)
		{
			event.getObserver(i)->getFunctor().execute(arg0, arg1);
		}
	}

	virtual FunctorType getFunctorType() const
	{
		return CUSTOM_FUNCTOR;
	}

	virtual bool operator ==(const Functor2<void, A0, A1>& right) const
	{
		return false; // Can't compare
	}

	virtual Functor2<void, A0, A1>* clone() const
	{
		return NULL; // Can't clone
	}

	inline operator EventManager<Functor2<void, A0, A1> >&()
	{
		return event;
	}
	inline operator const EventManager<Functor2<void, A0, A1> >&() const
	{
		return event;
	}

private:

	EventManager<Functor2<void, A0, A1> > event;
};



template<typename R, typename A0, typename A1>
class FunctionFunctor2 : public Functor2<R, A0, A1> {
public:

	typedef R (*Function)(A0 arg0, A1 arg1);

	FunctionFunctor2<R, A0, A1>(Function forFunction)
		: function(forFunction)
	{
	}

	virtual R execute(A0 arg0, A1 arg1) const
	{
		return (*function)(arg0, arg1);
	}

	virtual FunctorType getFunctorType() const
	{
		return FUNCTION_FUNCTOR;
	}

	virtual bool operator ==(const Functor2<R, A0, A1>& right) const
	{
		return right.getFunctorType() == FUNCTION_FUNCTOR && function == static_cast<const FunctionFunctor2&>(right).function;
	}

	virtual FunctionFunctor2<R, A0, A1>* clone() const
	{
		return new FunctionFunctor2<R, A0, A1>(function);
	}

private:

	Function function;

};



template<class C, typename R, typename A0, typename A1>
class MethodFunctor2 : public Functor2<R, A0, A1> {
public:

	typedef R (C::*Method)(A0 arg0, A1 arg1);

	MethodFunctor2<C, R, A0, A1>(C* atObject, Method forMethod)
		: object(atObject)
		, method(forMethod)
	{
	}

	virtual R execute(A0 arg0, A1 arg1) const
	{
		return (object->*method)(arg0, arg1);
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

	virtual bool operator ==(const Functor2<R, A0, A1>& right) const
	{
		return right.getFunctorType() == METHOD_FUNCTOR && object == static_cast<const MethodFunctor2&>(right).object && method == static_cast<const MethodFunctor2&>(right).method;
	}

	virtual MethodFunctor2<C, R, A0, A1>* clone() const
	{
		return new MethodFunctor2<C, R, A0, A1>(object, method);
	}

private:

	mutable C* object;
	Method method;

};



template<class C, typename R, typename A0, typename A1>
class ConstMethodFunctor2 : public Functor2<R, A0, A1> {
public:

	typedef R (C::*Method)(A0 arg0, A1 arg1) const;

	ConstMethodFunctor2<C, R, A0, A1>(const C* atObject, Method forMethod)
		: object(atObject)
		, method(forMethod)
	{
	}

	virtual R execute(A0 arg0, A1 arg1) const
	{
		return (object->*method)(arg0, arg1);
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

	virtual bool operator ==(const Functor2<R, A0, A1>& right) const
	{
		return right.getFunctorType() == METHOD_FUNCTOR && object == static_cast<const ConstMethodFunctor2&>(right).object && method == static_cast<const ConstMethodFunctor2&>(right).method;
	}

	virtual ConstMethodFunctor2<C, R, A0, A1>* clone() const
	{
		return new ConstMethodFunctor2<C, R, A0, A1>(object, method);
	}

private:

	const C* object;
	Method method;

};







} // namespace Functors
} // namespace BaseLib



#endif // #ifndef BaseLib_Functors_Functor2_h
