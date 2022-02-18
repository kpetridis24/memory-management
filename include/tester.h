#ifndef TESTER
#define TESTER

#include <memorySegment.h>
#include <dynamicMemoryManagement.h>
#include <string.h>

#define MaxBufferSize 200

memorySegment *initializeStaticMemory(int memorySize, int blockSize) {
    int numberOfBlocks = memorySize / blockSize;
    int remainderSize = memorySize % blockSize;

    memorySegment *firstBlock = (memorySegment *)malloc(sizeof(memorySegment));
    firstBlock->occupied = false;
    firstBlock->length = blockSize;
    firstBlock->startAddress = 0;

    memorySegment *previousSegment = firstBlock;

    for (int i = 0; i < numberOfBlocks - 1; i++) {
        memorySegment *nextMemorySegment = (memorySegment *)malloc(sizeof(memorySegment));
        nextMemorySegment->occupied = false;
        nextMemorySegment->startAddress = previousSegment->startAddress + blockSize;
        nextMemorySegment->length = blockSize;
        previousSegment->next = nextMemorySegment;
        previousSegment = nextMemorySegment;
    }
    if (remainderSize > 0) {
        memorySegment *lastMemorySegment = (memorySegment *)malloc(sizeof(memorySegment));
        lastMemorySegment->length = remainderSize;
        lastMemorySegment->occupied = false;
        lastMemorySegment->startAddress = previousSegment->startAddress + blockSize;
        previousSegment->next = lastMemorySegment;
    } 
    return firstBlock;
}

memorySegment *initializeDynamicMemory(int memorySize) {
    memorySegment *memory = (memorySegment *)malloc(sizeof(memorySegment));
    memory->startAddress = 0;
    memory->length = memorySize;
    memory->occupied = false;
    return memory;
}

void execute(char *token, memorySegment *(*assignMemory)(memorySegment *mem, uint16_t size), 
             void (*reclaimMemory)(memorySegment *mem, memorySegment *thisOne), 
             memorySegment *memList, char *savePointer1, char *savePointer2) {
    if (token[0] == 'A') {
            char *requestedMemory = strtok_r(token, "A", &savePointer1);
            printf("Requested %s\n\n", requestedMemory);
            (*assignMemory)(memList, atoi(requestedMemory));
    } else if (token[0] == 'R') {
        int indexOfBlockToReclaim = atoi(strtok_r(token, "R", &savePointer2));
        printf("\nFree block %d\n\n", indexOfBlockToReclaim);
        memorySegment *blockToReclaim = memList;
        if (indexOfBlockToReclaim <= 0) {   // 1-based, first block is block-1
            printf("Requested reclaim of invalid block.");
            exit(1);
        } 
        if (indexOfBlockToReclaim > 1) {
            while (indexOfBlockToReclaim > 1) {
                blockToReclaim = blockToReclaim->next;
                indexOfBlockToReclaim--;
            }
        }
        (*reclaimMemory)(memList, blockToReclaim);
    }
}

void parseMessage(char *buffer, size_t size) {
    /* read the string from the stdin and check for error */
    if (fgets(buffer, size, stdin) == NULL) {
        printf("Error reading stdint.");
        exit(1);
    }

    /* pointer to the memory, which is represented by a linked list */
    memorySegment *memList;

    /* declare the delimiter, so that the string is divided in separate tokens */
    const char delimiter[2] = " ";

    /* used to specify on which string, the strtok_r performs */
    char *savePointer1;
    char *savePointer2;
    char *savePointer3;
    char *savePointer4;

    /* reading of the string's header with the necessary information about the test */
    char *sizeOfMemory = strtok_r(buffer, delimiter, &savePointer1);
    char *typeOfMemory = strtok_r(NULL, delimiter, &savePointer1);
    char *assignMethod = strtok_r(NULL, delimiter, &savePointer1);

    /* array of pointers to the appropriate memory management methods */
    memorySegment *(*methodOfAssignement) (memorySegment *memList, uint16_t requestedMem);
    void (*methodOfReclaim) (memorySegment *memList, memorySegment* thisOne);
    
    if (typeOfMemory[0] == 'S') {
        if (strcmp(assignMethod, "AF") == 0) {
            methodOfAssignement = assignFirst;
        } else if (strcmp(assignMethod, "AB") == 0) {
            methodOfAssignement = assignBest;
        } else if (strcmp(assignMethod, "AN") == 0) {
            methodOfAssignement = assignNext;
        } else {
            printf("Unknown memory assignement method.");
            exit(1);
        }
        methodOfReclaim = reclaim;
        char *blockSize = strtok_r(typeOfMemory, "S", &savePointer2);
        memList = initializeStaticMemory(atoi(sizeOfMemory), atoi(blockSize));
    } else if (typeOfMemory[0] == 'D') {
        if (strcmp(assignMethod, "AF") == 0) {
            methodOfAssignement = assignFirstDyn;
        } else if (strcmp(assignMethod, "AB") == 0) {
            methodOfAssignement = assignBestDyn;
        } else if (strcmp(assignMethod, "AN") == 0) {
            methodOfAssignement = assignNextDyn;
        } else {
            printf("Unknown memory assignement method.");
            exit(1);
        }
        methodOfReclaim = reclaimDyn;
        memList = initializeDynamicMemory(atoi(sizeOfMemory));
    } else {
        printf("Invalid memory type.");
        exit(1);
    }
    
    char *token = strtok_r(NULL, delimiter, &savePointer1);
    
    while (true) {
        token = strtok_r(NULL, delimiter, &savePointer1);
        if (token == NULL) {
            break;
        }
        execute(token, (*methodOfAssignement), methodOfReclaim, memList, savePointer3, savePointer4);
        printList(memList); printf("\n");
    }   

}

#endif 