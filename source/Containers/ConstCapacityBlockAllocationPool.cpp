/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Containers/ConstCapacityBlockAllocationPool.h"


namespace BaseLib {
namespace Containers {



template<int BLOCK_SIZE>
ConstCapacityBlockAllocationPool<BLOCK_SIZE>::~ConstCapacityBlockAllocationPool()
{
	free(buffer);
}



void test()
{
	ConstCapacityBlockAllocationPool<10> pool(100);

	pool.allocateBlock();
	pool.freeBlock(NULL);
}



} // namespace Containers
} // namespace BaseLib
