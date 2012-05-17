/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Functors_Functor1_h
#define BaseLib_Functors_Functor1_h



#include "BaseLib/Functors/FunctorType.h"
#include "BaseLib/Functors/EventObserver.h"
#include "BaseLib/Utilities/AutoPointer.h"



namespace BaseLib {
namespace Functors {



template<typename R, typename A0>
class Functor1 {
public:

	typedef R ResultType;
	typedef A0 Argument0Type;

	virtual ~Functor1<R, A0>() {}

	virtual R execute(A0 arg0) const = 0;

	inline R operator ()(A0 arg0) const
	{
		return execute(arg0);
	}

	virtual FunctorType getFunctorType() const = 0;
	virtual bool operator ==(const Functor1& right) const = 0;
	virtual Functor1<R, A0>* clone() const = 0;
};



template<typename A0>
class Event1 : public Functor1<void, A0> {
public:

	inline Event1()
		: Functor1<void, A0>()
		, event()
	{
	}

	virtual void execute(A0 arg0) const
	{
		const int count = event.getObserverCount();
		for (int i = 0; i < count; ++i)
		{
			event.getObserver(i)->getFunctor().execute(arg0);
		}
	}

	virtual FunctorType getFunctorType() const
	{
		return CUSTOM_FUNCTOR;
	}

	virtual bool operator ==(const Functor1<void, A0>& right) const
	{
		return false; // Can't compare
	}

	virtual Functor1<void, A0>* clone() const
	{
		return NULL; // Can't clone
	}

	inline operator EventManager<Functor1<void, A0> >&()
	{
		return event;
	}
	inline operator const EventManager<Functor1<void, A0> >&() const
	{
		return event;
	}

private:

	EventManager<Functor1<void, A0> > event;
};



template<typename R, typename A0>
class FunctionFunctor1 : public Functor1<R, A0> {
public:

	typedef R (*Function)(A0 arg0);

	FunctionFunctor1<R, A0>(Function forFunction)
		: function(forFunction)
	{
	}

	virtual R execute(A0 arg0) const
	{
		return (*function)(arg0);
	}

	virtual FunctorType getFunctorType() const
	{
		return FUNCTION_FUNCTOR;
	}

	virtual bool operator ==(const Functor1<R, A0>& right) const
	{
		return right.getFunctorType() == FUNCTION_FUNCTOR && function == static_cast<const FunctionFunctor1&>(right).function;
	}

	virtual FunctionFunctor1<R, A0>* clone() const
	{
		return new FunctionFunctor1<R, A0>(function);
	}

private:

	Function function;

};



template<typename R, typename A0>
class FunctionFunctor1Ignored : public Functor1<R, A0> {
public:

	typedef R (*Function)();

	FunctionFunctor1Ignored<R, A0>(Function forFunction)
		: function(forFunction)
	{
	}

	virtual R execute(A0 arg0) const
	{
		return (*function)();
	}

	virtual FunctorType getFunctorType() const
	{
		return FUNCTION_FUNCTOR;
	}

	virtual bool operator ==(const Functor1<R, A0>& right) const
	{
		return right.getFunctorType() == FUNCTION_FUNCTOR && function == static_cast<const FunctionFunctor1Ignored&>(right).function;
	}

	virtual FunctionFunctor1Ignored<R, A0>* clone() const
	{
		return new FunctionFunctor1Ignored<R, A0>(function);
	}

private:

	Function function;

};



template<class C, typename R, typename A0>
class MethodFunctor1 : public Functor1<R, A0> {
public:

	typedef R (C::*Method)(A0 arg0);

	MethodFunctor1<C, R, A0>(C* atObject, Method forMethod)
		: object(atObject)
		, method(forMethod)
	{
	}

	virtual R execute(A0 arg0) const
	{
		return (object->*method)(arg0);
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

	virtual bool operator ==(const Functor1<R, A0>& right) const
	{
		return right.getFunctorType() == METHOD_FUNCTOR && object == static_cast<const MethodFunctor1&>(right).object && method == static_cast<const MethodFunctor1&>(right).method;
	}

	virtual MethodFunctor1<C, R, A0>* clone() const
	{
		return new MethodFunctor1<C, R, A0>(object, method);
	}

private:

	mutable C* object;
	Method method;

};



template<class C, typename R, typename A0>
class MethodFunctor1Ignored : public Functor1<R, A0> {
public:

	typedef R (C::*Method)();

	MethodFunctor1Ignored<C, R, A0>(C* atObject, Method forMethod)
		: object(atObject)
		, method(forMethod)
	{
	}

	virtual R execute(A0 arg0) const
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

	virtual bool operator ==(const Functor1<R, A0>& right) const
	{
		return right.getFunctorType() == METHOD_FUNCTOR && object == static_cast<const MethodFunctor1Ignored&>(right).object && method == static_cast<const MethodFunctor1Ignored&>(right).method;
	}

	virtual MethodFunctor1Ignored<C, R, A0>* clone() const
	{
		return new MethodFunctor1Ignored<C, R, A0>(object, method);
	}

private:

	mutable C* object;
	Method method;

};



template<class C, typename R, typename A0>
class ConstMethodFunctor1 : public Functor1<R, A0> {
public:

	typedef R (C::*Method)(A0 arg0) const;

	ConstMethodFunctor1<C, R, A0>(const C* atObject, Method forMethod)
		: object(atObject)
		, method(forMethod)
	{
	}

	virtual R execute(A0 arg0) const
	{
		return (object->*method)(arg0);
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

	virtual bool operator ==(const Functor1<R, A0>& right) const
	{
		return right.getFunctorType() == METHOD_FUNCTOR && object == static_cast<const ConstMethodFunctor1&>(right).object && method == static_cast<const ConstMethodFunctor1&>(right).method;
	}

	virtual ConstMethodFunctor1<C, R, A0>* clone() const
	{
		return new ConstMethodFunctor1<C, R, A0>(object, method);
	}

private:

	const C* object;
	Method method;

};



template<class C, typename R, typename A0>
class ConstMethodFunctor1Ignored : public Functor1<R, A0> {
public:

	typedef R (C::*Method)() const;

	ConstMethodFunctor1Ignored<C, R, A0>(const C* atObject, Method forMethod)
		: object(atObject)
		, method(forMethod)
	{
	}

	virtual R execute(A0 arg0) const
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

	virtual bool operator ==(const Functor1<R, A0>& right) const
	{
		return right.getFunctorType() == METHOD_FUNCTOR && object == static_cast<const ConstMethodFunctor1Ignored&>(right).object && method == static_cast<const ConstMethodFunctor1Ignored&>(right).method;
	}

	virtual ConstMethodFunctor1Ignored<C, R, A0>* clone() const
	{
		return new ConstMethodFunctor1Ignored<C, R, A0>(object, method);
	}

private:

	const C* object;
	Method method;

};



template<typename T>
class VariableSetterFunctor : public Functor1<void, T> {

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

	explicit VariableSetterFunctor<T>(VariableType* forVariable)
		: variable(forVariable)
	{
	}

	virtual void execute(T arg0) const
	{
		*variable = arg0;
	}

	virtual FunctorType getFunctorType() const
	{
		return VARIABLE_FUNCTOR;
	}

	virtual bool operator ==(const Functor1<void, T>& right) const
	{
		return right.getFunctorType() == VARIABLE_FUNCTOR && variable == static_cast<const VariableSetterFunctor&>(right).variable;
	}

	virtual VariableSetterFunctor<T>* clone() const
	{
		return new VariableSetterFunctor<T>(variable);
	}

	inline VariableType* getVariable() const
	{
		return variable;
	}

	inline void setVariable(VariableType* newVariable)
	{
		variable = newVariable;
	}


private:

	VariableType* variable;
};







} // namespace Functors
} // namespace BaseLib



#endif // #ifndef BaseLib_Functors_Functor1_h
