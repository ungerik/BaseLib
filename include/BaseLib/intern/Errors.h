/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Errors_h
#define BaseLib_Errors_h


#include "BaseLib/ErrorHandling.h"
#include "BaseLib/Strings/String.h"

//using namespace BaseLib::ErrorHandling;
using BaseLib::Strings::String;



#define STREAM_TO_DISCONNECT_NOT_FOUND ( String("Stream to disconnect from not found in list of connected streams !").append(ERROR_AT) )
#define BUFFER_TO_DISCONNECT_NOT_FOUND ( String("Buffer to disconnect from not found in list of connected buffers !").append(ERROR_AT) )
#define FILE_NOT_FOUND(f) ( String("File: \"").append(String(f)).append(String("\" not found !")).append(SYSTEM_ERROR).append(ERROR_AT) )
#define CANT_OPEN_FILE(f) ( String("Can't open file: \"").append(String(f)).append(String("\" !")).append(SYSTEM_ERROR).append(ERROR_AT) )
#define CANT_CREATE_DIRECTORY(d) ( String("Can't create directory: \"").append(String(d)).append(String("\" !")).append(SYSTEM_ERROR).append(ERROR_AT) )
#define CANT_REMOVE_DIRECTORY(d) ( String("Can't remove directory: \"").append(String(d)).append(String("\" !")).append(SYSTEM_ERROR).append(ERROR_AT) )
#define CANT_REMOVE_FILE(f) ( String("Can't remove file: \"").append(String(f)).append(String("\" !")).append(SYSTEM_ERROR).append(ERROR_AT) )
#define CANT_COPY_FILE(f1, f2) ( String("Can't copy file from: \"").append(String(f1)).append(String("\" to: \"")).append(String(f2)).append(String("\" !")).append(SYSTEM_ERROR).append(ERROR_AT) )
#define CANT_MOVE_FILE(f1, f2) ( String("Can't move file from: \"").append(String(f1)).append(String("\" to: \"")).append(String(f2)).append(String("\" !")).append(SYSTEM_ERROR).append(ERROR_AT) )
#define CANT_SET_CURRENT_POSITION(p) (String("Can't set current position: \"").append(String::createFrom(p)).append(String("\" !")).append(SYSTEM_ERROR).append(ERROR_AT) )
#define CANT_CHANGE_FILE(f) ( String("Can't change file: \"").append(String(f)).append(String("\" !")).append(ERROR_AT) )
#define CANT_CHANGE_FILE_ATTRIBUTES(f) ( String("Can't change attributes of file: \"").append(String(f)).append(String("\" !")).append(ERROR_AT) )
#define INVALID_POSITION_IN_BUFFER ( String("Invalid position in buffer !").append(ERROR_AT) )
#define DISTANCE_TO_END_OF_BUFFER_TOO_LARGE(d, m) ( String("Distance to end of buffer too large (Distance: ").append(String::createFrom(d)).append(String(" bytes, max: ")).append(String::createFrom(m)).append(String(" !")).append(ERROR_AT) )
#define INVALID_BUFFER_SIZE(s, a) ( String("Invalid buffer size: ").append(String::createFrom((int64)s)).append(String(" bytes, allowed: ")).append(String::createFrom((int64)a)).append(String(" !")).append(ERROR_AT) )
#define VALUE_TOO_LARGE(v, max) ( String("Value too large to be casted into a smaller type !").append(ERROR_AT) )
#define ILLEGAL_COMPRESSION_LEVEL(l) ( String("Compression level of: ").append(String::createFrom(l)).append(String(" is out of the valid range of 0.0 - 1.0 !")).append(SYSTEM_ERROR).append(ERROR_AT)  )
#define ZLIB_ERROR(e) ( String("Error in the compression library zlib: ").append(String(e)).append(String(" !")).append(SYSTEM_ERROR).append(ERROR_AT)  )
#define INVALID_NET_ADDRESS_STRING(s) ( String("\"").append(String(s)).append(String("\" is not a valid IP/Port address!")).append(ERROR_AT) )
#define PROXY_CONSOLE_HAS_NO_DRIVER(m) ( String("Call to ").append(String(m)).append(String("is illegal because proxy-console has no driver!")).append(ERROR_AT) )
#define STANDARD_CONSOLE_ERROR(e)  ( String("Standard-console error in ").append(String(e)).append(String("!")).append(ERROR_AT) )
#define STDIO_CONSOLE_ERROR(e)  ( String("stdio-console error in ").append(String(e)).append(String("!")).append(ERROR_AT) )
#define NO_STREAM_CONNECTED_FOR_UNREAD ( String("Can't unread because no stream is connected!").append(ERROR_AT) )
#define NO_STREAM_OR_BUFFER_CONNECTED_FOR_UNREAD ( String("Can't unread because no stream or buffer is connected!").append(ERROR_AT) )
#define NO_STREAM_CONNECTED_FOR_WRITE ( String("Can't write because no stream is connected!").append(ERROR_AT) )
#define NO_STREAM_OR_BUFFER_CONNECTED_FOR_WRITE ( String("Can't write because no stream or buffer is connected!").append(ERROR_AT) )
#define NO_STREAM_OR_FUNCTOR_CONNECTED_FOR_WRITE ( String("Can't write because no stream or functor is connected!").append(ERROR_AT) )
#define NO_LINE_END_CHARS_DEFINED ( String("Can't read line, because no line end characters are defined!").append(ERROR_AT) )
#define SOCKET_SEND_TIMEOUT ( String("Socket::sendAll() timeout!").append(ERROR_AT) )
#define WINSOCK_ERROR(e) ( String("Winsock-error: ").append(String(e)).append(ERROR_AT) )
#define SUBMIT_TEXT_LINE_RESPONSE_NO_NUMBER(r) (String("Response to submitTextLine() is not a number (").append(r).append(String(")!")).append(ERROR_AT) )
#define CPP_PROPERTIES_REMOTE_CONNECTION_WRONG_RESPONSE (String("Wrong response message-type at CppProperties remote-connection!").append(ERROR_AT) )
#define READ_NOT_ALLOWED ( String("Read operation not allowed!").append(ERROR_AT) )
#define WRITE_NOT_ALLOWED ( String("Write operation not allowed!").append(ERROR_AT) )
#define LINE_OUT_OF_RANGE(l, s) ( String("Line ").append(String::createFrom(l)).append(String(" out of range [0..")).append(String::createFrom(s-1)).append(String("]!")).append(ERROR_AT) )
#define ATTRIBUTE_DOESNT_EXIST(a) ( String("Attribute \"").append(String(a)).append(String("\" doesn't exist !")).append(ERROR_AT) )


#endif // #ifndef BaseLib_Errors_h
