/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Utilities_MemPoolObject_h
#define BaseLib_Utilities_MemPoolObject_h



#include "BaseLib/Defines.h"



namespace BaseLib {
namespace Utilities {



//template<class C, int maxObjectCount>
//class MemPoolObject {
//
//};
//
//template<class C, int maxObjectCount>
//MemBlockPool MemPoolObject<C, maxObjectCount>::memBlockPool(sizeof(C), maxObjectCount);



#define DECLARE_OBJECT_ALLOCATION_POOL(C, BlockAllocationPool, maxInstanceCount) \
public: \
	inline void* operator new(size_t byteCount) \
	{ \
		BL_ASSERT((int)byteCount <= blockAllocationPool.getBlockSize(), "Requested instance larget than block size!"); \
		return blockAllocationPool.allocateBlock(); \
	} \
	inline void operator delete(void* instance) \
	{ \
		blockAllocationPool.freeBlock(instance); \
	} \
	inline static int getInstanceCountInPool() \
	{ \
		return blockAllocationPool.getBlockCount(); \
	} \
	inline static int getMaxInstanceCountInPool() \
	{ \
		return blockAllocationPool.getBlockCapacity(); \
	} \
	inline static void deleteAllInstancesInPool() \
	{ \
		if (isValueType<C>() == true) \
		{ \
			foreach (BlockAllocationPool::Iterator, i, blockAllocationPool) \
			{ \
				(*i)->~C(); \
			} \
		} \
		blockAllocationPool.freeAllBlocks(); \
	} \
private: \
	static BlockAllocationPool blockAllocationPool;



#define DEFINE_OBJECT_ALLOCATION_POOL(C) \
	BlockAllocationPool C::blockAllocationPool(sizeof(C), C::getInstanceCountInPool());



} // namespace Utilities
} // namespace BaseLib



#endif // BaseLib_Utilities_MemPoolObject_h

