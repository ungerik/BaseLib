/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_HTTP_Request_h
#define BaseLib_HTTP_Request_h



#include "Message.h"
#include "Header.h"
#include <map>


namespace BaseLib {
namespace Network {
namespace HTTP {



class Request : public Message {
public:

	enum Method {
		OPTIONS,
        GET,
        HEAD,
        POST,
        PUT,
        DELETE,
		TRACE,
        CONNECT
	};

	inline String getHeaderField_Accept() const { return getHeaderField(HeaderField::ACCEPT); }
	inline void setHeaderField_Accept(const String& newHeaderFieldValue) { setHeaderField(HeaderField::ACCEPT, newHeaderFieldValue); }

	String getHeaderField_AcceptCharset() const;
	void setHeaderField_AcceptCharset(const String& newHeaderField_AcceptCharset);

	String getHeaderField_() const;
	void setHeaderField_(const String& newHeaderField);


/*		
		; Section 14.1
                      |            ; Section 14.2
                      | Accept-Encoding          ; Section 14.3
                      | Accept-Language          ; Section 14.4
                      | Authorization            ; Section 14.8
                      | Expect                   ; Section 14.20
                      | From                     ; Section 14.22
                      | Host                     ; Section 14.23
                      | If-Match                 ; Section 14.24

                      | If-Modified-Since        ; Section 14.25
                      | If-None-Match            ; Section 14.26
                      | If-Range                 ; Section 14.27
                      | If-Unmodified-Since      ; Section 14.28
                      | Max-Forwards             ; Section 14.31
                      | Proxy-Authorization      ; Section 14.34
                      | Range                    ; Section 14.35
                      | Referer                  ; Section 14.36
                      | TE                       ; Section 14.39
                      | User-Agent  
*/

};

} // namespace HTTP
} // namespace Network
} // namespace BaseLib


#endif // #ifndef BaseLib_HTTP_Request_h
