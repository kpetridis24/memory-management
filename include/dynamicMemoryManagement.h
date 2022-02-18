#ifndef DYNAMICMEMORYMANAGEMENT
#define DYNAMICMEMORYMANAGEMENT

#include "memorySegment.h"
#include "staticMemoryManagement.h"

/**
 * Dynamic memory allocation techniques, for a requested memory size, and memory blocks. Each time a block is allocated, 
 * the remaining unallocated space of the block, is concatenated to the next, if it exists and is free. Otherwise, we
 * insert a new, independent block of the corresponding size, after the allocated space.
 */

/**
 * Accesses the memory in a linear fashion, iterating over one block at a time. It assigns the first memory block, 
 * that fits the requested memory. 
 * 
 * @param memList the memory as a linked list, with each node representing a memory block.
 * @param requestedMem the memory requested by a process.
 * @return memorySegment* the memory block that was allocated by the memory management service.
 */
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

/**
 * Accesses the memory in a linear fashion, iterating over one block at a time. It locates the memory block that both 
 * fits the requested memory and is closest to it, in order to minimize memory gaps after memory assignement.
 * 
 * @param memList the memory as a linked list, with each node representing a memory block.
 * @param requestedMem the memory requested by a process.
 * @return memorySegment* the memory block that was allocated by the memory management service.
 */
memorySegment *assignBestDyn(memorySegment *memList, uint16_t requestedMem) {
    memorySegment *currentSegment;
    currentSegment = memList;
    memorySegment *bestBlock = NULL;
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

    if (bestBlock == NULL) {
        return (NULL);
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

/**
 * Accesses the memory in a linear fashion, iterating over one block at a time. It has the same functionality as the 
 * Firs Fit, but the searching starts from the block that was allocated during the last memory assignement. It tends to 
 * allocate memory segments at the end of the memory list, leaving gaps which need to be concatenated in order to boost
 * the efficiency of the method.
 * 
 * @param memList the memory as a linked list, with each node representing a memory block.
 * @param requestedMem the memory requested by a process.
 * @return memorySegment* the memory block that was allocated by the memory management service.
 */
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

/**
 * Dynamically frees the requested memory block. If the next memory block is free as well, it concatenates the two.
 * 
 * @param memList the memory as a linked list, with each node representing a memory block.
 * @param thisOne the memory block to reclaim.
 */
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
        currentSegment = currentSegment->next;
    }
}

#endif