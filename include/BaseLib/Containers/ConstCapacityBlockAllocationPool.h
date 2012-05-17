/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Containers_ConstCapacityBlockAllocationPool_h
#define BaseLib_Containers_ConstCapacityBlockAllocationPool_h



#include "BaseLib/ErrorHandling.h"
//#include "BaseLib/Containers/IteratorTemplate.h"



namespace BaseLib {
namespace Containers {



using namespace BaseLib::ErrorHandling;








template<int BLOCK_SIZE>
class BL_EXPORT ConstCapacityBlockAllocationPool {
public:

	//template<typename T>
	//class IteratorImplementation {

	//	friend IteratorImplementation;

	//protected:

	//	typedef T* InitParam;

	//	inline IteratorImplementation(InitParam initParam)
	//		: pointer(initParam)
	//	{
	//	}

	//	inline IteratorImplementation(const IteratorImplementation& other)
	//		: pointer(other.pointer)
	//	{
	//	}

	//	inline void assign(const IteratorImplementation& other)
	//	{
	//		pointer = other.pointer;
	//	}

	//	inline void increment()
	//	{
	//		++pointer;
	//	}

	//	inline void decrement()
	//	{
	//		--pointer;
	//	}

	//	inline bool equals(const IteratorImplementation& other)
	//	{
	//		return pointer == other.pointer;
	//	}

	//	inline bool lessThan(const IteratorImplementation& other)
	//	{
	//		return pointer < other.pointer;
	//	}

	//	inline void* getValue() const
	//	{
	//		return *pointer;
	//	}

	//private:

	//	InitParam pointer;

	//};

	//typedef IteratorTemplate<void*, IteratorImplementation, Iterator_MovePolicy_IncrementDecrement, Iterator_ComparePolicy_EqualsSmallerThan> Iterator;

	typedef void** Iterator;

	ConstCapacityBlockAllocationPool(int withBlockCapacity)
		: blockCapacity(withBlockCapacity)
		, allocatedBlockCount(0)
		, buffer(NULL)
		, allocationTable(NULL)
		, allocationTableIndices(NULL)
	{
		BL_STATIC_ASSERT(BLOCK_SIZE > 0, BLOCK_SIZE_NOT_GREATER_ZERO);
		if (checkArgumentGreater(NAME_VALUE(withBlockCapacity), 0) == true)
		{
			buffer = malloc((BLOCK_SIZE + sizeof(void*) + sizeof(int)) * blockCapacity);
			allocationTable = static_cast<void* *>(offsetPointer(buffer, BLOCK_SIZE * blockCapacity));
			allocationTableIndices = reinterpret_cast<int *>(&allocationTable[blockCapacity]);

			for (int i = 0; i < blockCapacity; ++i)
			{
				allocationTable[i] = offsetPointer(buffer, BLOCK_SIZE * i);
				allocationTableIndices[i] = i;
			}
		}
	}

	~ConstCapacityBlockAllocationPool();

	inline int getBlockSize() const
	{
		return blockCapacity;
	}

	inline int getBlockCapacity() const
	{
		return blockCapacity;
	}

	inline int getAllocatedBlockCount() const
	{
		return allocatedBlockCount;
	}

	inline void* allocateBlock()
	{
		return allocatedBlockCount < blockCapacity ? allocateBlockUnchecked() : NULL;
	}

	inline void* allocateBlockUnchecked()
	{
		void* result = allocationTable[allocatedBlockCount];
		const int blockIndex = pointerOffset(result, buffer) / BLOCK_SIZE;
		++allocatedBlockCount;
		return result;
	}

	inline void freeBlock(void* blockAddress)
	{
		if (checkArgumentMin(NAME_VALUE(blockAddress), buffer) == true &&
			checkArgumentSmaller(NAME_VALUE(blockAddress), offsetPointer(buffer, blockCapacity * BLOCK_SIZE)) == true &&
			checkArgumentEquals(NAME_VALUE(reinterpret_cast<pint>(blockAddress) % BLOCK_SIZE), 0) == true)
		{
			freeBlockUnchecked(blockAddress);
		}			
	}

	inline void freeBlockUnchecked(void* blockAddress)
	{
		--allocatedBlockCount;

		const int blockIndex = pointerOffset(blockAddress, buffer) / BLOCK_SIZE;
		const int lastAllocatedBlockIndex = pointerOffset(allocationTable[allocatedBlockCount], buffer) / BLOCK_SIZE;

		const int allocationTableIndex = allocationTableIndices[blockIndex];

		swap(allocationTable[allocationTableIndex], allocationTable[allocatedBlockCount]);

		allocationTableIndices[blockIndex] = allocationTableIndices[lastAllocatedBlockIndex];
		allocationTableIndices[lastAllocatedBlockIndex] = allocationTableIndex;
	}

	inline void freeAllBlocks()
	{
		allocatedBlockCount = 0;
	}

	inline Iterator begin() const
	{
		return &allocationTable[0];
	}

	inline Iterator end() const
	{
		return &allocationTable[allocatedBlockCount];
	}

protected:

	const int blockCapacity;
	int allocatedBlockCount;
	void* buffer;
	void* * allocationTable;
	int * allocationTableIndices;
};



} // namespace Containers
} // namespace BaseLib



#endif // #ifndef BaseLib_Containers_ConstCapacityBlockAllocationPool_h