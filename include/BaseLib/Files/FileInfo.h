/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Files_FileInfo_h
#define BaseLib_Files_FileInfo_h



#include "BaseLib/System/DateTime.h"



namespace BaseLib {
namespace Files {



using BaseLib::Strings::String;
using BaseLib::System::DateTime;



struct FileInfo {

	//struct Time {
	//	uint16 year;
	//	uint16 month;
	//	uint16 dayOfWeek;
	//	uint16 day;
	//	uint16 hour;
	//	uint16 minute;
	//	uint16 second;
	//	uint16 milliseconds;

	//	Time() : year(0), month(0), dayOfWeek(0), day(0), hour(0), minute(0), second(0), milliseconds(0) {}

	//};

	String name;
	int64 size;
	bool archive;
	bool hidden;
	bool directory;
	bool readable;
	bool writeable;
	DateTime creationTime;
	DateTime accessTime;
	DateTime writeTime;
};




//inline bool operator ==(const FileInfo::Time& lhs, const FileInfo::Time& rhs)
//{
//	return 
//		lhs.year         == rhs.year   && 
//		lhs.month        == rhs.month  && 
//		lhs.day          == rhs.day    && 
//		lhs.hour         == rhs.hour   && 
//		lhs.minute       == rhs.minute && 
//		lhs.second       == rhs.second && 
//		lhs.milliseconds == rhs.milliseconds;
//}
//
//
//
//inline bool operator >(const FileInfo::Time& lhs, const FileInfo::Time& rhs)
//{
//	if (operator ==(lhs, rhs))
//		return false;
//
//	if (lhs.year > rhs.year)
//		return true;
//	else if (lhs.year < rhs.year)
//		return false;
//
//	if (lhs.month > rhs.month)
//		return true;
//	else if (lhs.month < rhs.month)
//		return false;
//
//	if (lhs.day > rhs.day)
//		return true;
//	else if (lhs.day < rhs.day)
//		return false;
//
//	if (lhs.hour > rhs.hour)
//		return true;
//	else if (lhs.hour < rhs.hour)
//		return false;
//
//	if (lhs.minute > rhs.minute)
//		return true;
//	else if (lhs.minute < rhs.minute)
//		return false;
//
//	if (lhs.second > rhs.second)
//		return true;
//	else if (lhs.second < rhs.second)
//		return false;
//
//	if (lhs.milliseconds > rhs.milliseconds)
//		return true;
//
//	return false;
//}
//
//
//
//inline bool operator <(const FileInfo::Time& lhs, const FileInfo::Time& rhs)
//{
//	return !(lhs > rhs); /// BUG BUG BUG: should be >= but >= is not defined!
//}



} // namespace Files
} // namespace BaseLib



#endif // #ifndef BaseLib_Files_FileInfo_h
