/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Streams_BoolInputStream_h
#define BaseLib_Streams_BoolInputStream_h



#include "BaseLib/Streams/InputStream.h"
#include "BaseLib/Functors/Functor0.h"
#include "BaseLib/Containers/Stack.h"



namespace BaseLib {
namespace Streams {



using BaseLib::Containers::Stack;
using BaseLib::Utilities::AutoPointer;
using namespace BaseLib::Functors;



/**
Converts every read call to a read(bool) call.
Beside an InputStream the stream can be connected to a functor alternatively.
Read-calls of every type get converted into read(bool) calls.
@see @ref BuffersAndStreams, BoolOutputStream, InputStream, connectToFunctor()
*/
class BL_EXPORT BoolInputStream : public InputStream {
public:

	typedef bool InputType;
	typedef Functor0<InputType> Functor;
	typedef FunctionFunctor0<InputType> FunctionFunctor;
	template<class C>
	struct MethodFunctor : ConstMethodFunctor0<C, InputType> {
		MethodFunctor<C>(const C* atObject, Method forMethod)
			: ConstMethodFunctor0<C, InputType>(atObject, forMethod)
		{
		}
	};
	typedef VariableGetterFunctor<InputType> VariableFunctor;
	typedef ValueGetterFunctor<InputType> ValueFunctor;

	BoolInputStream();
	explicit BoolInputStream(const InputStream& connectToInputStream);
	explicit BoolInputStream(const Functor& connectToGetterFunctor);
	explicit BoolInputStream(const bool* value);
	explicit BoolInputStream(bool value);

	virtual int readBinary(void* destination, int byteCount, double timeoutSeconds) const;
	virtual bool readBinaryComplete(void* destination, int byteCount, double timeoutSeconds) const;
	virtual bool read(bool& destination, double timeoutSeconds) const;
	virtual bool read(void*& destination, double timeoutSeconds) const;
	virtual bool read(int8& destination, double timeoutSeconds) const;
	virtual bool read(uint8& destination, double timeoutSeconds) const;
	virtual bool read(int16& destination, double timeoutSeconds) const;
	virtual bool read(uint16& destination, double timeoutSeconds) const;
	virtual bool read(int32& destination, double timeoutSeconds) const;
	virtual bool read(uint32& destination, double timeoutSeconds) const;
	virtual bool read(int64& destination, double timeoutSeconds) const;
	virtual bool read(uint64& destination, double timeoutSeconds) const;
	virtual bool read(float& destination, double timeoutSeconds) const;
	virtual bool read(double& destination, double timeoutSeconds) const;
	virtual bool read(long double& destination, double timeoutSeconds) const;
	virtual bool read(String& destination, double timeoutSeconds) const;

	// Unread doesn't work for readonly functors:
	//virtual void unreadBinary(const void* source, int byteCount) const; 
	//virtual void unread(bool source) const;
	//virtual void unread(const void* source) const;
	//virtual void unread(int8 source) const;
	//virtual void unread(uint8 source) const;
	//virtual void unread(int16 source) const;
	//virtual void unread(uint16 source) const;
	//virtual void unread(int32 source) const;
	//virtual void unread(uint32 source) const;
	//virtual void unread(int64 source) const;
	//virtual void unread(uint64 source) const;
	//virtual void unread(float source) const;
	//virtual void unread(double source) const;
	//virtual void unread(long double source) const;
	//virtual void unread(const String& source) const;


	virtual bool isInputAvailable() const;

	virtual bool isConnected() const;

	virtual void connectToStream(const InputStream& newInputStream);

	/**
	Connects the stram to a Functor.
	A connected input-stream gets disconnected.
	Every read-call of the stream gets converted into a Functor::execute() call.
	@see disconnectFromFunctor(), Functor
	*/
	void connectToFunctor(const Functor& newFunctor);

	/**
	Disconnects the stram from a Functor.
	@see connectToFunctor(), Functor
	*/
	void disconnectFromFunctor();


protected:

	AutoPointer<Functor> connectedFunctor;


	//typedef Stack<InputType> UnreadStack;
	//mutable UnreadStack unreadStack;

};



} // namespace Streams
} // namespace BaseLib



#endif // #ifndef BaseLib_Streams_BoolInputStream_h
