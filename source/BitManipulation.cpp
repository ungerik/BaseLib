/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Utilities/BitManipulation.h"
#include "BaseLib/Utilities/AutoArray.h"



namespace BaseLib {



using BaseLib::Utilities::AutoArray;



/*
void bitCopy(void* dest, int destBitOffset, const void* source, int sourceBitOffset, int bitCount)
{
	BL_ASSERT(bitCount >= 0);
	BL_ASSERT(destBitOffset >= 0);
	BL_ASSERT(sourceBitOffset >= 0);

	if ((destBitOffset & 7) == (sourceBitOffset & 7))
	{
		const int bytesToCopy = (bitCount - (destBitOffset & 7)) >> 3;
		memCopy(&static_cast<int8*>(dest)[(destBitOffset+7)>>3], &static_cast<const int8*>(source)[(sourceBitOffset+7)>>3], bytesToCopy);
		
		uint8 sourceFrontByte = static_cast<const int8*>(source)[sourceBitOffset>>3];
		sourceFrontByte &= (1 << (sourceBitOffset & 7)) - 1;
		const uint8 frontMask = (-1 << (8 - (sourceBitOffset & 7))) | (1 << (sourceBitOffset & 7)) - 1;
		static_cast<int8*>(dest)[destBitOffset>>3] &= frontMask;
		static_cast<int8*>(dest)[destBitOffset>>3] &= sourceFrontByte;

		// backByte implementieren
		BL_ASSERT_NEVER_REACHED

	}
	else
	{
		// verschobene bitoffsets implementieren
		BL_ASSERT_NEVER_REACHED
	}
}



void bitCopy(void* dest, const void* source, int sourceBitOffset, int bitCount)
{
	const int dwords = ((bitCount - (8 - (sourceBitOffset&7))) >> 5);
	const uint32 * sourceArray = reinterpret_cast<const uint32*>(&static_cast<const uint8*>(source)[(sourceBitOffset+7)>>3]);
	for (int i = 0; i < dwords; ++i)
	{
	}
	BL_ASSERT_NEVER_REACHED
}



void bitCopy(void* dest, int destBitOffset, const void* source, int bitCount)
{
	BL_ASSERT_NEVER_REACHED
}
*/


AutoArray<uint32> crc32Table;



void createCRC32Table()
{
	crc32Table = new uint32[256];

	uint32 c;
	int n;
	int k;
	uint32 poly; /* polynomial exclusive-or pattern */
	/* terms of polynomial defining this crc (except x^32): */
	static uint8 p[] = {0,1,2,4,5,7,8,10,11,12,16,22,23,26};

	/* make exclusive-or pattern from polynomial (0xedb88320L) */
	poly = 0L;
	for (n = 0; n < sizeof(p)/sizeof(uint8); ++n)
	{
		poly |= 1L << (31 - p[n]);
	}

	for (n = 0; n < 256; ++n)
	{
		c = (uint32)n;
		for (k = 0; k < 8; ++k)
		{
			c = c & 1 ? poly ^ (c >> 1) : c >> 1;
		}
		crc32Table[n] = c;
	}
}



uint32 * getCRC32Table()
{
	if (crc32Table == NULL)
	{
		createCRC32Table();
	}
	return crc32Table;
}



#define CRC32_DO1(buf) crc = crc32Table[((int)crc ^ (*buf++)) & 0xff] ^ (crc >> 8);
#define CRC32_DO2(buf)  CRC32_DO1(buf); CRC32_DO1(buf);
#define CRC32_DO4(buf)  CRC32_DO2(buf); CRC32_DO2(buf);
#define CRC32_DO8(buf)  CRC32_DO4(buf); CRC32_DO4(buf);



uint32 crc32(void * buffer, int length, uint32 crc)
{
	BL_ASSERT(length >= 0);

	uint8 * buf = static_cast<uint8 *>(buffer);

    if (buffer == NULL) return 0;

    crc = crc ^ 0xffffffff;
    while (length >= 8)
    {
      CRC32_DO8(buf);
      length -= 8;
    }

    if (length > 0)
	{
		do {
			CRC32_DO1(buf);
		} while (--length);
	}

    return crc ^ 0xffffffff;
}


} // namespace BaseLib