/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Functors_Functor0_h
#define BaseLib_Functors_Functor0_h



#include "BaseLib/Functors/FunctorType.h"
#include "BaseLib/Functors/EventObserver.h"



namespace BaseLib {
namespace Functors {



template<typename R>
class Functor0 {
public:

	typedef R ResultType;

	virtual ~Functor0<R>() {}

	virtual R execute() const = 0;

	inline R operator ()() const
	{
		return execute();
	}

	virtual FunctorType getFunctorType() const = 0;
	virtual bool operator ==(const Functor0& right) const = 0;
	virtual Functor0<R>* clone() const = 0;
};



class Event0 : public Functor0<void> /*, public EventManager<class Functor0<void> >*/ { // Warum funktioniert Mehrfachvererbung nicht?
public:

	inline Event0()
		: Functor0<void>()
		//, EventManager()
		, event()
	{
	}

	virtual void execute() const
	{
		const int count = event.getObserverCount();
		for (int i = 0; i < count; ++i)
		{
			event.getObserver(i)->getFunctor().execute();
		}
	}

	virtual FunctorType getFunctorType() const
	{
		return CUSTOM_FUNCTOR;
	}

	virtual bool operator ==(const Functor0<void>& right) const
	{
		return false; // Can't compare
	}

	virtual Functor0<void>* clone() const
	{
		return NULL; // Can't clone
	}

	inline operator EventManager<Functor0<void> >&()
	{
		return event;
	}
	inline operator const EventManager<Functor0<void> >&() const
	{
		return event;
	}

private:

	EventManager<Functor0<void> > event; // Aggregation instead of multi-derivement
};



template<typename R>
class FunctionFunctor0 : public Functor0<R> {
public:

	typedef R (*Function)();

	FunctionFunctor0<R>(Function forFunction)
		: function(forFunction)
	{
	}

	virtual R execute() const
	{
		return (*function)();
	}

	virtual FunctorType getFunctorType() const
	{
		return FUNCTION_FUNCTOR;
	}

	virtual bool operator ==(const Functor0<R>& right) const
	{
		return right.getFunctorType() == FUNCTION_FUNCTOR && function == static_cast<const FunctionFunctor0&>(right).function;
	}

	virtual FunctionFunctor0<R>* clone() const
	{
		return new FunctionFunctor0<R>(function);
	}

private:

	Function function;

};



template<class C, typename R>
class MethodFunctor0 : public Functor0<R> {

	/*
	template<typename T>
	struct M {
		typedef R (C::*Method)();
	};

	template<typename T>
	struct M<const T> {
	};
*/

public:

	typedef R (C::*Method)();

	MethodFunctor0<C, R>(C* atObject, Method forMethod)
		: object(atObject)
		, method(forMethod)
	{
	}

	virtual R execute() const
	{
		return (object->*method)();
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

	virtual bool operator ==(const Functor0<R>& right) const
	{
		return right.getFunctorType() == METHOD_FUNCTOR && object == static_cast<const MethodFunctor0&>(right).object && method == static_cast<const MethodFunctor0&>(right).method;
	}

	virtual MethodFunctor0<C, R>* clone() const
	{
		return new MethodFunctor0<C, R>(object, method);
	}

private:

	mutable C* object;
	Method method;

};



template<class C, typename R>
class ConstMethodFunctor0 : public Functor0<R> {
public:

	typedef R (C::*Method)() const;

	ConstMethodFunctor0<C, R>(const C* atObject, Method forMethod)
		: object(atObject)
		, method(forMethod)
	{
	}

	virtual R execute() const
	{
		return (object->*method)();
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

	virtual bool operator ==(const Functor0<R>& right) const
	{
		return right.getFunctorType() == METHOD_FUNCTOR && object == static_cast<const ConstMethodFunctor0<C, R>&>(right).object && method == static_cast<const ConstMethodFunctor0<C, R>&>(right).method;
	}

	virtual ConstMethodFunctor0<C, R>* clone() const
	{
		return new ConstMethodFunctor0<C, R>(object, method);
	}

private:

	const C* object;
	Method method;

};



template<typename T>
class VariableGetterFunctor : public Functor0<T> {

	template<typename T_>
	struct NoConstRef {
		typedef T_ Type;
	};

	template<typename T_>
	struct NoConstRef<T_&> {
		typedef T_ Type;
	};

	template<typename T_>
	struct NoConstRef<const T_&> {
		typedef T_ Type;
	};

public:

	typedef typename NoConstRef<T>::Type VariableType;

	explicit VariableGetterFunctor<T>(const VariableType* forVariable)
		: variable(forVariable)
	{
	}

	virtual T execute() const
	{
		return *variable;
	}

	virtual FunctorType getFunctorType() const
	{
		return VARIABLE_FUNCTOR;
	}

	virtual bool operator ==(const Functor0<T>& right) const
	{
		return right.getFunctorType() == VARIABLE_FUNCTOR && variable == static_cast<const VariableGetterFunctor&>(right).variable;
	}

	virtual VariableGetterFunctor<T>* clone() const
	{
		return new VariableGetterFunctor<T>(variable);
	}

	inline const VariableType* getVariable() const
	{
		return variable;
	}

	inline void setVariable(const VariableType* newVariable)
	{
		variable = newVariable;
	}

private:

	const VariableType* variable;
};



template<typename T>
class ValueGetterFunctor : public Functor0<T> {
public:

	explicit ValueGetterFunctor<T>(const T& forValue)
		: value(forValue)
	{
	}

	virtual T execute() const
	{
		return value;
	}

	virtual FunctorType getFunctorType() const
	{
		return VARIABLE_FUNCTOR;
	}

	virtual bool operator ==(const Functor0<T>& right) const
	{
		return right.getFunctorType() == VALUE_FUNCTOR && value == static_cast<const ValueGetterFunctor<T>&>(right).value;
	}

	virtual ValueGetterFunctor<T>* clone() const
	{
		return new ValueGetterFunctor<T>(value);
	}

	inline const T& getValue() const
	{
		return value;
	}

	inline void setValue(const T& newValue)
	{
		value = newValue;
	}

private:

	T value;
};



} // namespace Functors
} // namespace BaseLib



#endif // #ifndef BaseLib_Functors_Functor0_h
