/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Streams_StringInputStream_h
#define BaseLib_Streams_StringInputStream_h



#include "BaseLib/Streams/InputStream.h"
#include "BaseLib/Functors/Functor0.h"
#include "BaseLib/Containers/Stack.h"



namespace BaseLib {
namespace Streams {



using BaseLib::Containers::Stack;
using namespace BaseLib::Functors;
using namespace BaseLib::Utilities;



/**
Converts every read call to a read(String) call.
Beside an InputStream the stream can be connected to a functor alternatively.
Read-calls of every type get converted into read(String) calls.
@see @ref BuffersAndStreams, StringOutputStream, InputStream, connectToFunctor()
*/
class BL_EXPORT StringInputStream : public InputStream {
public:

	typedef String InputType;
	typedef Functor0<InputType> Functor;
	typedef FunctionFunctor0<InputType> FunctionFunctor;
	template<class C>
	struct MethodFunctor : ConstMethodFunctor0<C, InputType> {
		MethodFunctor<C>(const C* atObject, Method forMethod)
			: ConstMethodFunctor0<C, InputType>(atObject, forMethod)
		{
		}
	};
	template<class C>
	struct NoConstMethodFunctor : MethodFunctor0<C, InputType> {
		NoConstMethodFunctor<C>(C* atObject, Method forMethod)
			: MethodFunctor0<C, InputType>(atObject, forMethod)
		{
		}
	};
	typedef VariableGetterFunctor<InputType> VariableFunctor;
	typedef ValueGetterFunctor<InputType> ValueFunctor;


	typedef Functor0<bool> InputAvailableFunctor;
	typedef FunctionFunctor0<bool> InputAvailableFunctionFunctor;
	template<class C>
	struct InputAvailableMethodFunctor : ConstMethodFunctor0<C, bool> {
		InputAvailableMethodFunctor<C>(const C* atObject, Method forMethod)
			: ConstMethodFunctor0<C, bool>(atObject, forMethod)
		{
		}
	};


	StringInputStream();
	explicit StringInputStream(const InputStream& connectToInputStream);
	explicit StringInputStream(const Functor& connectToGetterFunctor);
	explicit StringInputStream(const String* value);
	explicit StringInputStream(const String& value);

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

	/**
	The streams uses this functor to determine in input is available.
	@see disconnectInputAvailableFromFunctor()
	*/
	void connectToInputAvailableFunctor(const InputAvailableFunctor& newInputAvailableFunctor);

	/*
	Disconnects from the input-available functor.
	@see connectToInputAvailableFunctor()
	*/
	void disconnectFromFunctorInputAvailable();

	enum ReadBinaryMethode {
		INTERPRET_STRING_AS_BINARY_DATA,
		INTERPRET_STRING_AS_HEX_STRING,
		INTERPRET_STRING_AS_BIN_STRING,
		INTERPRET_STRING_AS_BASE64_STRING
	};

	inline ReadBinaryMethode getReadBinaryMethode() const {	return readBinaryMethode; }
	inline void setReadBinaryMethode(ReadBinaryMethode newReadBinaryMethode) { readBinaryMethode = newReadBinaryMethode; }

protected:

	AutoPointer<Functor> connectedFunctor;
	AutoPointer<InputAvailableFunctor> inputAvailableFunctor;
	ReadBinaryMethode readBinaryMethode;

	//typedef Stack<InputType> UnreadStack;
	//mutable UnreadStack unreadStack;

};



} // namespace Streams
} // namespace BaseLib



#endif // #ifndef BaseLib_Streams_StringInputStream_h
