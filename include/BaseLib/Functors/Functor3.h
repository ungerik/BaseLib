/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Functors_Functor3_h
#define BaseLib_Functors_Functor3_h



#include "BaseLib/Functors/FunctorType.h"
#include "BaseLib/Functors/EventObserver.h"



namespace BaseLib {
namespace Functors {



template<typename R, typename A0, typename A1, typename A2>
class Functor3 {
public:

	typedef R ResultType;
	typedef A0 Argument0Type;
	typedef A1 Argument1Type;
	typedef A2 Argument2Type;

	virtual ~Functor3<R, A0, A1, A2>() {}

	virtual R execute(A0 arg0, A1 arg1, A2 arg2) const = 0;

	inline R operator ()(A0 arg0, A1 arg1, A2 arg2) const
	{
		return execute(arg0, arg1, arg2);
	}

	virtual FunctorType getFunctorType() const = 0;
	virtual bool operator ==(const Functor3& right) const = 0;
	virtual Functor3<R, A0, A1, A2>* clone() const = 0;
};



template<typename A0, typename A1, typename A2>
class Event3 : public Functor3<void, A0, A1, A2> {
public:

	inline Event3()
		: Functor3<void, A0, A1, A2>()
		, event()
	{
	}

	virtual void execute(A0 arg0, A1 arg1, A2 arg2) const
	{
		const int count = event.getObserverCount();
		for (int i = 0; i < count; ++i)
		{
			event.getObserver(i)->getFunctor().execute(arg0, arg1, arg2);
		}
	}

	virtual FunctorType getFunctorType() const
	{
		return CUSTOM_FUNCTOR;
	}

	virtual bool operator ==(const Functor3<void, A0, A1, A2>& right) const
	{
		return false; // Can't compare
	}

	virtual Functor3<void, A0, A1, A2>* clone() const
	{
		return NULL; // Can't clone
	}

	inline operator EventManager<Functor3<void, A0, A1, A2> >&()
	{
		return event;
	}
	inline operator const EventManager<Functor3<void, A0, A1, A2> >&() const
	{
		return event;
	}

private:

	EventManager<Functor3<void, A0, A1, A2> > event;
};



template<typename R, typename A0, typename A1, typename A2>
class FunctionFunctor3 : public Functor3<R, A0, A1, A2> {
public:

	typedef R (*Function)(A0 arg0, A1 arg1, A2 arg2);

	FunctionFunctor3<R, A0, A1, A2>(Function forFunction)
		: function(forFunction)
	{
	}

	virtual R execute(A0 arg0, A1 arg1, A2 arg2) const
	{
		return (*function)(arg0, arg1, arg2);
	}

	virtual FunctorType getFunctorType() const
	{
		return FUNCTION_FUNCTOR;
	}

	virtual bool operator ==(const Functor3<R, A0, A1, A2>& right) const
	{
		return right.getFunctorType() == FUNCTION_FUNCTOR && function == static_cast<const FunctionFunctor3&>(right).function;
	}

	virtual FunctionFunctor3<R, A0, A1, A2>* clone() const
	{
		return new FunctionFunctor3<R, A0, A1, A2>(function);
	}

private:

	Function function;

};



template<class C, typename R, typename A0, typename A1, typename A2>
class MethodFunctor3 : public Functor3<R, A0, A1, A2> {
public:

	typedef R (C::*Method)(A0 arg0, A1 arg1, A2 arg2);

	MethodFunctor3<C, R, A0, A1, A2>(C* atObject, Method forMethod)
		: object(atObject)
		, method(forMethod)
	{
	}

	virtual R execute(A0 arg0, A1 arg1, A2 arg2) const
	{
		return (object->*method)(arg0, arg1, arg2);
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

	virtual bool operator ==(const Functor3<R, A0, A1, A2>& right) const
	{
		return right.getFunctorType() == METHOD_FUNCTOR && object == static_cast<const MethodFunctor3&>(right).object && method == static_cast<const MethodFunctor3&>(right).method;
	}

	virtual MethodFunctor3<C, R, A0, A1, A2>* clone() const
	{
		return new MethodFunctor3<C, R, A0, A1, A2>(object, method);
	}

private:

	mutable C* object;
	Method method;

};



template<class C, typename R, typename A0, typename A1, typename A2>
class ConstMethodFunctor3 : public Functor3<R, A0, A1, A2> {
public:

	typedef R (C::*Method)(A0 arg0, A1 arg1, A2 arg2) const;

	ConstMethodFunctor3<C, R, A0, A1, A2>(const C* atObject, Method forMethod)
		: object(atObject)
		, method(forMethod)
	{
	}

	virtual R execute(A0 arg0, A1 arg1, A2 arg2) const
	{
		return (object->*method)(arg0, arg1, arg2);
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

	virtual bool operator ==(const Functor3<R, A0, A1, A2>& right) const
	{
		return right.getFunctorType() == METHOD_FUNCTOR && object == static_cast<const ConstMethodFunctor3&>(right).object && method == static_cast<const ConstMethodFunctor3&>(right).method;
	}

	virtual ConstMethodFunctor3<C, R, A0, A1, A2>* clone() const
	{
		return new ConstMethodFunctor3<C, R, A0, A1, A2>(object, method);
	}

private:

	const C* object;
	Method method;

};







} // namespace Functors
} // namespace BaseLib



#endif // #ifndef BaseLib_Functors_Functor3_h
