/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Buffers_h
#define BaseLib_Buffers_h

/**
@page BuffersAndStreams

@section buffersandstreams Buffers and Streams

@subsection connecting Connecting buffers and streams

Streams have read and write operations for all simple types and String.
Buffers and streams can be connected. If a stream is connected with an other
stream, every read or write call at the front of the connection-line gets duplicated
to the corresponding read and write calls with the same type at the connected streams.

Here an example:
@code
OutputStream firstStream;
OutputStream secondStream;
OutputStream thirdStream;

firstStream.connectToStream(secondStream);
firstStream.connectToStream(thirdStream);

int value = 42;
firstStream.write(value); // calls secondStream.write(value) and thirdStream.write(value)
firstStream << value; // same as above
@endcode

Output-stream can be connected to one or more other output-streams and buffers.
Input-streams can only be connected to one input-stream or buffer.

@subsection converting Converting types

OutputStream and InputStream do nothing else but handing over read and write calls to
connected streams. For doing something special with the data, there are special stream-classes
derived from InputStream and OutputStream. Generaly these streams convert read or write calls
to calls of other types and perform type-casting as good as possible.
IntOutputStream converts write calls of every type into write(int) calls at the connected stream,
StringOutputStream calls write(String) at connected streams and so on.
At the special streams for simple types and String there can also be functors connected,
that get called for every read or write operation.

Even more special are BinaryInputStreams and BinaryOutputStream. The convert every read/write
call into a BinaryInputStream::readBinary()/BinaryOutputStream::writeBinary() call.
Especially reading from binary data isn't trivial with strings (8 bit or unicode, endian,
tokenizing, reading with fixed length). So BinaryInputStreams has
some functions to configure how a String should be read from binary data.

BinaryInputStream an BinaryOutputStream are also needed to read from or write to
binary buffers (AbstractBinaryBuffer), because the read and write calls are converted to the matching
binary read/write calls.

@subsection resizebuffers Resizing buffers

Buffers have the special capability to handle write operations before the beginning and after
the end position of the buffer. The buffer gets resized automatically, and the content is moved
if necessary.

@see BaseLib::Buffers, BaseLib::Streams, BaseLib::Functors
*/


#include "BaseLib/Buffers/AbstractBinaryBuffer.h"
#include "BaseLib/Buffers/AbstractTextBuffer.h"
#include "BaseLib/Buffers/BinaryFileBuffer.h"
#include "BaseLib/Buffers/BinaryMemBuffer.h"
#include "BaseLib/Buffers/VoidBinaryBuffer.h"
#include "BaseLib/Buffers/DefaultTextBuffer.h"
#include "BaseLib/Buffers/TextBuffer.h"
#include "BaseLib/Buffers/TextFileBuffer.h"



#endif // #ifndef BaseLib_Buffers_h