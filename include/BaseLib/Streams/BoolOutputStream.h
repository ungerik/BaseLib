/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Streams_BoolOutputStream_h
#define BaseLib_Streams_BoolOutputStream_h



#include "BaseLib/Streams/OutputStream.h"
#include "BaseLib/Functors/Functor1.h"




namespace BaseLib {
namespace Streams {



using namespace BaseLib::Functors;



/**
Converts every write call to a write(bool) call.
Beside output-streams the stream can be connected to one or more a functors.
Write-calls of every type get converted into write(bool) calls.
@see @ref BuffersAndStreams, BoolInputStream, OutputStream, connectToFunctor()
*/
class BL_EXPORT BoolOutputStream : public OutputStream {
public:

	typedef bool OutputType;
	typedef Functor1<void, OutputType> Functor;
	typedef FunctionFunctor1<void, OutputType> FunctionFunctor;
	template<class C>
	class MethodFunctor : MethodFunctor1<typename C, void, OutputType> {
	public:
		MethodFunctor<C>(C* atObject, Method forMethod)
			: MethodFunctor1<C, void, OutputType>(atObject, forMethod)
		{
		}
	};
	typedef VariableSetterFunctor<OutputType> VariableFunctor;

	BoolOutputStream();
	explicit BoolOutputStream(const OutputStream& connectToOutputStream);
	BoolOutputStream(const OutputStream& connectToOutputStream1, const OutputStream& connectToOutputStream2);
	explicit BoolOutputStream(const Functor& connectToSetterFunctor);
	explicit BoolOutputStream(bool* value);
	virtual ~BoolOutputStream();

	virtual void writeBinary(const void* source, int byteCount) const;
	virtual void write(bool source) const;
	virtual void write(const void* source) const;
	virtual void write(int8 source) const;
	virtual void write(uint8 source) const;
	virtual void write(int16 source) const;
	virtual void write(uint16 source) const;
	virtual void write(int32 source) const;
	virtual void write(uint32 source) const;
	virtual void write(int64 source) const;
	virtual void write(uint64 source) const;
	virtual void write(float source) const;
	virtual void write(double source) const;
	virtual void write(long double source) const;
	virtual void write(const String& source) const;

	void connectToFunctor(const Functor& newFunctor);
	void disconnectFromFunctor(const Functor& oldFunctor);
	void disconnectFromAllFunctors();

	virtual bool isConnected() const;

protected:
	
	typedef Array<Functor*> ConnectedFunctors;
	ConnectedFunctors connectedFunctors;

};



} // namespace Streams
} // namespace BaseLib


#endif // #ifndef BaseLib_Streams_BoolOutputStream_h
