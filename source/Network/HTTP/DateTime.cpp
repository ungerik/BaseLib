/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Network/HTTP/DateTime.h"

namespace BaseLib {
namespace Network {
namespace HTTP {



DateTime::DateTime(const String& dateTimeString)
  : defaultFormat(RFC_1123_FORMAT)
{
}

		

String DateTime::getDefaultFormated() const
{
	switch (defaultFormat)
	{
		case RFC_1123_FORMAT:
			return getRfc1123Formated();

		case RFC_850_FORMAT:
			return getRfc850Formated();

		case RFC_ASCTIME_FORMAT:
			return getAsctimeFormated();

		default:
			BL_ASSERT_NEVER_REACHED
			return getRfc1123Formated();
	}
}



String DateTime::getRfc1123Formated() const
{
	return Empty(); ///
}



String DateTime::getRfc850Formated() const
{
	return Empty(); ///
}



String DateTime::getAsctimeFormated() const
{
	return Empty(); ///
}



} // namespace HTTP
} // namespace Network
} // namespace BaseLib