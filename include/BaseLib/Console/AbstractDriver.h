/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Console_AbstractDriver_h
#define BaseLib_Console_AbstractDriver_h


#include "BaseLib/Buffers/AbstractTextBuffer.h"
#include "BaseLib/Streams/StringInputStream.h"
#include "BaseLib/Streams/StringOutputStream.h"
#include "BaseLib/Functors/Functor1.h"
#include <deque>


namespace BaseLib {
namespace Console {



using BaseLib::Buffers::AbstractTextBuffer;
using BaseLib::Streams::StringInputStream;
using BaseLib::Streams::StringOutputStream;
using BaseLib::Streams::InputStream;
using BaseLib::Streams::OutputStream;
using namespace BaseLib::Containers;
using namespace BaseLib::Functors;
using namespace BaseLib::Strings;
using namespace BaseLib;



/**
Base-class for console-drivers.
@see DebugTraceDriver, ProxyDriver, StdioDriver, SystemDriver
*/
class BL_EXPORT AbstractDriver : public NonCopyable {
public:

	/**
	Functor type for the autocompletion-callback.
	*/
	typedef Functor1<void, String&> AutocompletionFunctor;
	typedef FunctionFunctor1<void, String&> AutocompletionFunctionFunctor;
	template<class C>
	struct AutocompletionMethodFunctor : MethodFunctor1<C, void, String&> {
		AutocompletionMethodFunctor<C>(C* atObject, Method forMethod)
			: MethodFunctor1<C, void, String&>(atObject, forMethod)
		{
		}
	};

	AbstractDriver();
	virtual ~AbstractDriver();

	virtual bool isInputAvailable() const = 0;
	virtual char16 peekChar() const = 0;

	virtual char16 getChar() = 0;

	//virtual bool newLine() = 0;
	virtual int write(const String& source) = 0;
	void writeUnchecked(const String& source);
	String read();
	/*
	virtual bool write(char8 source) = 0;
	virtual bool write(char16 source) = 0;
	virtual int backSpace(int backSpaces) = 0;
	*/

	inline InputStream& getInputStream() { return inputStream; }
	inline OutputStream& getOutputStream() { return outputStream; }

	/**
	Returns if the input is echoed by the output.
	@see setEchoInput
	*/
	inline bool isEchoInput() const
	{
		return echoInput;
	}

	/**
	Sets if the input is echoed by the output.
	@see isEchoInput
	*/
	inline void setEchoInput(bool newEchoInput)
	{
		echoInput = newEchoInput;
	}

	inline void setAutocompletionFunctor(const AutocompletionFunctor& newAutocompletionFunctor) { autocompletionFunctor = newAutocompletionFunctor.clone(); }
	inline void removeAutocompletionFunctor() { autocompletionFunctor = NULL; }

	inline int getMaxInputHistorySize() const { return maxInputHistorySize; }
	void setMaxInputHistorySize(int newMaxInputHistorySize);

	//inline InputHistory& getInputHistory() { return inputHistory; }

protected:

	StringInputStream inputStream;
	StringOutputStream outputStream;
	bool echoInput;
	bool insert;
	AutoPointer<AutocompletionFunctor> autocompletionFunctor;
	int maxInputHistorySize;
	typedef std::deque<String> InputHistory;
	InputHistory inputHistory;

	void addToInputHistory(const String& string);

};



} // namespace Console
} // namespace BaseLib



#endif // #ifndef BaseLib_Console_AbstractDriver_h
