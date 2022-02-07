#ifndef DYNAMICMEMORYMANAGEMENT
#define DYNAMICMEMORYMANAGEMENT

#include "memorySegment.h"
#include "staticMemoryManagement.h"

/**
 * Dynamic memory allocation techniques, for a requested memory size, and memory blocks. Each time a block is allocated, 
 * the remaining unallocated space of the block, is concatenated to the next, if it exists and is free. Otherwise, we
 * insert a new, independent block of the corresponding size, after the allocated space.
 * 
 * @param memList The blocks of memory that we are about to access.
 * @param requestedMem The requested memory size to be allocated.
 * @return memorySegment* The memory block that is available for allocation.
 */
memorySegment *assignFirstDyn(memorySegment *memList, uint16_t requestedMem);
memorySegment *assignBestDyn(memorySegment *memList, uint16_t requestedMem);
memorySegment *assignNextDyn(memorySegment *memList, uint16_t requestedMem);
void reclaimDyn(memorySegment *memList, memorySegment *thisOne);

memorySegment *assignFirstDyn(memorySegment *memList, uint16_t requestedMem) {
    memorySegment *currentSegment;
    currentSegment = memList;

    while(currentSegment != NULL) {
        if (currentSegment->occupied) {
            currentSegment = currentSegment->next;
            continue;
        } 
        if (currentSegment->length == requestedMem) {
            currentSegment->occupied = true;
            return currentSegment;
        }
        if (currentSegment->length > requestedMem) {
            uint16_t freeMemory = currentSegment->length - requestedMem;
            currentSegment->occupied = true;
            currentSegment->length = requestedMem;
            if (currentSegment->next) {
                if (currentSegment->next->occupied == false) {
                    currentSegment->next->startAddress = currentSegment->startAddress + requestedMem;
                    currentSegment->next->length += freeMemory;
                    return currentSegment;
                } 
            }
            lengthOfNewBlock = freeMemory;
            startAddressOfNewBlock = currentSegment->startAddress + requestedMem;
            insertListItemAfter(currentSegment);
            return currentSegment;
        } 
        currentSegment = currentSegment->next;
    }

    return (NULL);
}

memorySegment *assignBestDyn(memorySegment *memList, uint16_t requestedMem) {
    memorySegment *currentSegment;
    currentSegment = memList;
    memorySegment *bestBlock;
    uint16_t bestFit = UINT16_MAX;
    bool exactFit = false;

    while(currentSegment != NULL) {
        if (currentSegment->occupied) {
            currentSegment = currentSegment->next;
            continue;
        } 
        if (currentSegment->length == requestedMem) {
            bestBlock = currentSegment;
            exactFit = true;
            break; 
        }
        if (currentSegment->length > requestedMem) {
            uint16_t currentFit = currentSegment->length - requestedMem;
            if (currentFit <= bestFit) {
                bestFit = currentFit;
                bestBlock = currentSegment;
            }
        }
        currentSegment = currentSegment->next; 
    }

    currentSegment = memList;

    while (currentSegment != NULL) {
        if (currentSegment->occupied) {
            currentSegment = currentSegment->next;
            continue;
        }
        if (currentSegment->startAddress == bestBlock->startAddress) {
            uint16_t freeMemory = currentSegment->length - requestedMem;
            currentSegment->occupied = true;
            if (exactFit) {
                return currentSegment;
            }
            currentSegment->length = requestedMem;
            if (currentSegment->next) {
                if (currentSegment->next->occupied == false) {
                    currentSegment->next->startAddress = currentSegment->startAddress + requestedMem;
                    currentSegment->next->length += freeMemory;
                    return currentSegment;
                } 
            }
            lengthOfNewBlock = freeMemory;
            startAddressOfNewBlock = currentSegment->startAddress + requestedMem;
            insertListItemAfter(currentSegment);
            return currentSegment;
        }
        currentSegment = currentSegment->next; 
    }

    return (NULL);
}

memorySegment *assignNextDyn(memorySegment *memList, uint16_t requestedMem) {
    memorySegment *currentSegment;
    if (lastAllocatedBlock == NULL) {
        currentSegment = memList;
    } else {
        currentSegment = lastAllocatedBlock;
    }

    while(currentSegment != NULL) {
        if (currentSegment->occupied) {
            currentSegment = currentSegment->next;
            continue;
        } 
        if (currentSegment->length == requestedMem) {
            currentSegment->occupied = true;
            return currentSegment;
        }
        if (currentSegment->length > requestedMem) {
            uint16_t freeMemory = currentSegment->length - requestedMem;
            currentSegment->occupied = true;
            currentSegment->length = requestedMem;
            lastAllocatedBlock = currentSegment;
            if (currentSegment->next) {
                if (currentSegment->next->occupied == false) {
                    currentSegment->next->startAddress = currentSegment->startAddress + requestedMem;
                    currentSegment->next->length += freeMemory;
                    return currentSegment;
                } 
            }
            lengthOfNewBlock = freeMemory;
            startAddressOfNewBlock = currentSegment->startAddress + requestedMem;
            insertListItemAfter(currentSegment);
            return currentSegment;
        }
        currentSegment = currentSegment->next;
    }

    return (NULL);
}

void reclaimDyn(memorySegment *memList, memorySegment *thisOne) {
    memorySegment *currentSegment;
    currentSegment = memList;

    while (currentSegment != NULL) {
        if (currentSegment->startAddress == thisOne->startAddress) {
            currentSegment->occupied = false;
            if (currentSegment->next) {
                if (currentSegment->next->occupied == false) {
                    currentSegment->length += currentSegment->next->length;
                    currentSegment->next = currentSegment->next->next;
                }
            }
            break;
        }
    }
}

#endif