/**
 * Static memory allocation techniques, for a requested memory size, and memory blocks. The memory remains intact, no 
 * segments are added, removed or changed.
 * 
 * @param memList The blocks of memory that we are about to access.
 * @param requestedMem The requested memory size to be allocated.
 * @return memorySegment* The memory block that is available for allocation.
 */
memorySegment *assignFirst(memorySegment *memList, uint requestedMem);
memorySegment *assignBest(memorySegment *memList, uint requestedMem);
memorySegment *assignNext(memorySegment *memList, uint requestedMem);
void reclaim(memorySegment *memList, memorySegment* thisOne);

/**
 * Pointer to the last allocated block in the memory, that works as an indicator for the starting point of the Next Fit search.
 */
memorySegment *lastAllocatedBlock;

memorySegment *assignFirst(memorySegment *memList, uint requestedMem) {
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

memorySegment *assignBest(memorySegment *memList, uint requestedMem) {
    memorySegment *currentSegment;
    currentSegment = memList;
    memorySegment *bestBlock;
    uint bestFit = UINT_MAX;

    while(currentSegment != NULL) {
        if (currentSegment->occupied) {
            currentSegment = currentSegment->next;
            continue;
        } 
        if (currentSegment->length >= requestedMem) {
            uint currentFit = currentSegment->length - requestedMem;
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
            currentSegment->occupied = true;
            return currentSegment;
        }
        currentSegment = currentSegment->next; 
    }

    return (NULL);
}

memorySegment *assignNext(memorySegment *memList, uint requestedMem) {
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

void reclaim(memorySegment *memList, memorySegment* thisOne) {
    memorySegment *currentSegment;
    currentSegment = memList;

    while (currentSegment != NULL) {
        if (currentSegment->startAddress == thisOne->startAddress) {
            currentSegment->occupied = false;
            break;
        }
    }
}