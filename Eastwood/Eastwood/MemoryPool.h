#pragma once
#include <vector>

class CMemoryPool
{
public:
	void Initialize(unsigned int aBytesToAllocate);
	unsigned int AddToPool(void* aAddressToObject, unsigned int aSizeOfObject);
	void RemoveFromPool(unsigned int aIndexOfObjectInPool, unsigned int aSizeOfObject);

	void* operator[] (unsigned int aID);
private:
	bool AllocateToFirstFreeSlotOfSize(void* aAddressOfObject, unsigned int aSizeOfObject, unsigned int& aAllocatedAtIndexOut);
	bool IsAtEndOfExistingFreeSlot(void* aAddress, unsigned int& aFreeSlotIndexOnSuccessOut);
	unsigned int PutDataAtAddress(void* aAddressOfObject, void* aAddressToPutAt, unsigned int aSizeOfObject);

	struct SFreeSlot
	{
		void* myAddress;
		unsigned int mySize;
	};

	std::vector<SFreeSlot> myFreeSlots;

	unsigned int myNextAllocationIndex;

	char* myBuffer;
};