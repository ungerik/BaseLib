/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Functors_StreamWriter_h
#define BaseLib_Functors_StreamWriter_h



#include "BaseLib/Functors/Enumerator.h"
#include "BaseLib/Strings/String.h"



namespace BaseLib {
namespace Functors {



using BaseLib::Strings::String;



template<typename S, typename T>
class StreamWriter : public Enumerator<T> {
public:

	StreamWriter<S, T>(S& forStream, const String& useEndString = Empty())
		: stream(forStream)
		, endString(useEndString)
	{
	}

	virtual void enumerate(const T& value) const
	{
		stream << value;
		if (endString.isEmpty() == false)
		{
			stream << endString;
		}
	}

private:

	S& stream;
	String endString;
};



} // namespace Functors
} // namespace BaseLib



#endif // #ifndef BaseLib_Functors_StreamWriter_h
