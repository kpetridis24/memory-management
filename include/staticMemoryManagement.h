#ifndef STATICMEMORYMANAGEMENT 
#define STATICMEMORYMANAGEMENT

#include "memorySegment.h"

/**
 * Static memory allocation techniques, for a requested memory size, and memory blocks. The memory remains intact, no 
 * segments are added, removed or changed.
 */

/**
 * Pointer to the last allocated block in the memory, that works as an indicator for the starting point of the Next Fit search.
 */
memorySegment *lastAllocatedBlock;

/**
 * Accesses the memory in a linear fashion, iterating over one block at a time. It assigns the first memory block, 
 * that fits the requested memory.
 * 
 * @param memList the memory as a linked list, with each node representing a memory block.
 * @param requestedMem the memory requested by a process.
 * @return memorySegment* the memory block that was allocated by the memory management service.
 */
memorySegment *assignFirst(memorySegment *memList, uint16_t requestedMem) {
    memorySegment *currentSegment;
    currentSegment = memList;

    while(currentSegment != NULL) {
        if (currentSegment->occupied) {
            currentSegment = currentSegment->next;
            continue;
        } 
        if (currentSegment->length >= requestedMem) {
            currentSegment->occupied = true;
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
memorySegment *assignBest(memorySegment *memList, uint16_t requestedMem) {
    memorySegment *currentSegment;
    currentSegment = memList;
    memorySegment *bestBlock = NULL;
    uint16_t bestFit = UINT16_MAX;

    while(currentSegment != NULL) {
        if (currentSegment->occupied) {
            currentSegment = currentSegment->next;
            continue;
        } 
        if (currentSegment->length >= requestedMem) {
            uint16_t currentFit = currentSegment->length - requestedMem;
            if (currentFit <= bestFit) {
                bestFit = currentFit;
                bestBlock = currentSegment;
            }
        }
        currentSegment = currentSegment->next; 
    }

    if (bestBlock != NULL) {
        bestBlock->occupied = true;
        return bestBlock;
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
memorySegment *assignNext(memorySegment *memList, uint16_t requestedMem) {
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
        if (currentSegment->length >= requestedMem) {
            currentSegment->occupied = true;
            lastAllocatedBlock = currentSegment;
            return currentSegment;
        }
        currentSegment = currentSegment->next;
    }

    return (NULL);
}

/**
 * Statically frees the requested memory block.
 * 
 * @param memList the memory as a linked list, with each node representing a memory block.
 * @param thisOne the memory block to reclaim.
 */
void reclaim(memorySegment *memList, memorySegment* thisOne) {
    memorySegment *currentSegment;
    currentSegment = memList;

    while (currentSegment != NULL) {
        if (currentSegment->startAddress == thisOne->startAddress) {
            currentSegment->occupied = false;
            break;
        }
        currentSegment = currentSegment->next;
    }
}

#endif