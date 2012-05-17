/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib.h"



BaseLib::Containers::HashMap<int, int> hashMap;



namespace BaseLib {



#ifdef BL_CPU_SMALL_ENDIAN
	const Endian SYSTEM_ENDIAN = SMALL_ENDIAN;
#else
	const Endian SYSTEM_ENDIAN = BIG_ENDIAN;
#endif



Interface::~Interface()
{
}



namespace ErrorHandling {

	bool ErrorHandler::currentlyWritingLog = false;

}


namespace Testing {

	int TestCase::testCount = 0;
	int TestCase::failedTestCount = 0;
	int TestCase::exceptionsCount = 0;

} // namespace Testing



namespace Buffers {

	const int BinaryFileBuffer::CLUSTER_SIZE = 4*1024;

}


namespace Streams {

	int BufferedBinaryInputStream::defaultBufferSize = 4*1024;
	int BufferedBinaryOutputStream::defaultBufferSize = 4*1024;
	int DeflateOutputStream::defaultMaxCompressionBufferSize = 64*1024;

}


namespace Strings {

	StringEncoding BaseLib::Strings::String::defaultEncoding = CHAR8_ENCODING;
	std::locale defaultLocale = std::locale::classic();
	char8 narrowReplaceCharacter = ' ';

	const char8 * EmptyStringImplementation::EMPTY_CHAR8_CSTRING = "";
	const char16 * EmptyStringImplementation::EMPTY_CHAR16_CSTRING = BL_WSTRING("");

	EmptyStringImplementation EmptyStringImplementation::CHAR8_SINGLETON(CHAR8_ENCODING);
	EmptyStringImplementation EmptyStringImplementation::CHAR16_SINGLETON(CHAR16_ENCODING);

	AbstractStringImplementation::Factory AbstractStringImplementation::defaultFactory;
	AbstractStringImplementation::Factory* AbstractStringImplementation::factory = getDefaultFactory();

	BaseLib::Strings::String defaultTokenDelimiters(" \b\f\n\r\t");
	BaseLib::Strings::String defaultLineEndChars("\r\n");

	const char8 WINDOWS_LINE_END_CHARS[] = "\r\n";
	const char8 UNIX_LINE_END_CHARS[] = "\n";
	const char8 MAC_LINE_END_CHARS[] = "\r";

	const NumberFormat NumberFormat::ENGLISH(false, "en");
	const NumberFormat NumberFormat::ENGLISH_SCIENTIFIC(true, "en");
	const NumberFormat NumberFormat::LOCALIZED;
	const NumberFormat* NumberFormat::defaultNumberFormat = &NumberFormat::LOCALIZED;

	const std::wstring hexDigitsW(string2wstring(hexDigits));
}



namespace System {

	const String Locale::CHINESE = "zh";
	const String Locale::ENGLISH = "en";
	const String Locale::FRENCH = "fr";
	const String Locale::GERMAN = "de";
	const String Locale::ITALIAN = "it";
	const String Locale::JAPANESE = "ja";
	const String Locale::KOREAN = "ko";
	const String Locale::SIMPLIFIED_CHINESE = "zh_CN";
	const String Locale::TRADITIONAL_CHINESE = "zh_TW";
	const String Locale::CANADA = "en_CA";
	const String Locale::CANADA_FRENCH = "fr_CA";
	const String Locale::CHINA = "zh_CN";
	const String Locale::PRC = "zh_CN";
	const String Locale::FRANCE = "fr_FR";
	const String Locale::GERMANY = "de_DE";
	const String Locale::ITALY = "it_IT";
	const String Locale::JAPAN = "ja_JP";
	const String Locale::KOREA = "ko_KR";
	const String Locale::TAIWAN = "zh_TW";
	const String Locale::UK = "en_GB";
	const String Locale::US = "en_US";

	const NullHandle NullHandle::INSTANCE;
}



namespace Console {

	SystemDriver systemConsole;
	StdioDriver stdioConsole(stdin, stdout);
	StdioDriver stderrConsole(stdin, stderr);
	DebugTraceDriver debugTraceConsole;

	ProxyDriver defaultConsole(&systemConsole);
	ProxyDriver errorConsole(&stderrConsole);

	InputStream& in = defaultConsole.getInputStream();
	OutputStream& out = stdioConsole.getOutputStream();
	OutputStream& err = errorConsole.getOutputStream();
	OutputStream& trace = debugTraceConsole.getOutputStream();

}



namespace Reflection {

	const BaseLib::Strings::String Class::NON_SERIALIZEABLE = "NonSerializeable";
	const BaseLib::Strings::String Object::NON_SERIALIZEABLE = "NonSerializeable";
	const BaseLib::Strings::String Property::NON_SERIALIZEABLE = "NonSerializeable";
}



namespace Xml {

	const BaseLib::Strings::String XmlTreeSerializer::NON_SERIALIZEABLE = "NonSerializeable";

}



} // namespace BaseLib
