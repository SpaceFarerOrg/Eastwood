#include "MemoryPool.h"

void CMemoryPool::Initialize(unsigned int aBytesToAllocate)
{
	myBuffer = new char[aBytesToAllocate];
}

unsigned int CMemoryPool::AddToPool(void * aAddressToObject, unsigned int aSizeOfObject)
{
	unsigned int allocatedAtIndex = 0;

	if (AllocateToFirstFreeSlotOfSize(aAddressToObject, aSizeOfObject, allocatedAtIndex) == false)
	{
		void* addressToAllocateAt = myBuffer + myNextAllocationIndex;
		myNextAllocationIndex += aSizeOfObject;

		allocatedAtIndex = PutDataAtAddress(aAddressToObject, addressToAllocateAt, aSizeOfObject);
	}

	return allocatedAtIndex;
}

void CMemoryPool::RemoveFromPool(unsigned int aIndexOfObjectInPool, unsigned int aSizeOfObject)
{
	char* address = &myBuffer[aIndexOfObjectInPool];
	unsigned int freeSlotIndex;
	
	if (IsAtEndOfExistingFreeSlot(static_cast<void*>(address), freeSlotIndex))
	{
		myFreeSlots[freeSlotIndex].mySize += aSizeOfObject;
	}
	else
	{
		SFreeSlot newFreeSlot;
		newFreeSlot.myAddress = static_cast<void*>(address);
		newFreeSlot.mySize = aSizeOfObject;
		myFreeSlots.push_back(newFreeSlot);
	}
}

void* CMemoryPool::operator[](unsigned int aID)
{
	return &myBuffer[aID];
}

bool CMemoryPool::AllocateToFirstFreeSlotOfSize(void* aAddressToObject, unsigned int aSizeOfObject, unsigned int& aAllocatedAtIndexOut)
{
	for (unsigned int i = 0; i < myFreeSlots.size(); ++i)
	{
		SFreeSlot& slot = myFreeSlots[i];

		if (slot.mySize <= aSizeOfObject)
		{
			aAllocatedAtIndexOut = PutDataAtAddress(aAddressToObject, slot.myAddress, aSizeOfObject);
			slot.mySize -= aSizeOfObject;
			slot.myAddress = static_cast<char*>(slot.myAddress) + aSizeOfObject;

			if (slot.mySize == 0)
			{
				myFreeSlots.erase(myFreeSlots.begin() + i);
				return true;
			}
		}
	}

	return false;
}

bool CMemoryPool::IsAtEndOfExistingFreeSlot(void* aAddress, unsigned int & aFreeSlotIndexOnSuccessOut)
{
	for(unsigned int i = 0; i < myFreeSlots.size(); ++i)
	{
		char* freeSlotAddressAsChar = static_cast<char*>(myFreeSlots[i].myAddress);
		char* endOfFreeSlot = freeSlotAddressAsChar + myFreeSlots[i].mySize;
		char* aAddressToCheckAsChar = static_cast<char*>(aAddress);

		if (aAddressToCheckAsChar == endOfFreeSlot + 1)
		{
			aFreeSlotIndexOnSuccessOut = i;
			return true;
		}
	}

	return false;
}

unsigned int CMemoryPool::PutDataAtAddress(void * aAddressOfObject, void * aAddressToPutAt, unsigned int aSizeOfObject)
{
	memcpy(aAddressToPutAt, aAddressOfObject, aSizeOfObject);

	return static_cast<unsigned int>(static_cast<char*>(aAddressToPutAt) - myBuffer);
}
