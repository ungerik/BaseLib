/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Ramin Dalkouhi (Bouncing Bytes)          
                                      
Contact: romout@bouncingbytes.at
                                      
******************************************************************************/

// Included by BaseLib/Strings/String.h



class BL_EXPORT RegExMatch {
public:



	inline RegExMatch()
		: text()
		, start(0)
		, end(0)	  
	{
	}



	inline RegExMatch(String text)
		: text(text)
		, start(0)
	{
		end = text.getLength();
	}



	inline RegExMatch(String text, int start, int end)
		: text(text)
		, start(start)
		, end(end)
	{
	}



	inline String getString() const
	{
		return text;
	}



	inline int getStart() const
	{
		return start;
	}



	inline int getEnd() const
	{
		return end;
	}



protected:
	String text;
	int    start;
	int    end;



};