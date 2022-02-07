#ifndef TESTS
#define TESTS

#include "staticMemoryManagement.h"
#include "dynamicMemoryManagement.h"

/**
 * Functions that perform validity-functionality tests, for the memory-segment handling functions.
 */
memorySegment *initializeMemory();
void test_printList();
void test_insertListItemAfter();
void test_removeListItemAfter();
void test_assignFirst();
void test_assignBest();
void test_assignNext();
void test_assignFirstDyn();
void test_assignBestDyn();
void test_assignNextDyn();

memorySegment *initializeMemory() {
    memorySegment *segment1 = (memorySegment *)malloc(sizeof(memorySegment));
    memorySegment *segment2 = (memorySegment *)malloc(sizeof(memorySegment));
    memorySegment *segment3 = (memorySegment *)malloc(sizeof(memorySegment));
    memorySegment *segment4 = (memorySegment *)malloc(sizeof(memorySegment));

    segment1->length = 100;
    segment1->startAddress = 0;
    segment1->occupied = true;

    segment2->length = 50;
    segment2->startAddress = 100;
    segment2->occupied = false;

    segment3->length = 200;
    segment3->startAddress = 150;
    segment3->occupied = false;

    segment4->length = 300;
    segment4->startAddress = 350;
    segment4->occupied = false;
    
    segment3->next = segment4;
    segment2->next = segment3;
    segment1->next = segment2;

    return segment1;
}

void test_printList() {
    memorySegment *segment1 = initializeMemory();
    printList(segment1);
}

void test_insertListItemAfter() {
    memorySegment *firstSegment = initializeMemory();
    printf("Segments before insertion!\n\n");
    printList(firstSegment);

    memorySegment *thirdSegment = firstSegment->next->next;
    lengthOfNewBlock = 150;
    startAddressOfNewBlock = 350;
    insertListItemAfter(thirdSegment);

    printf("\nSegments after insertion (after 3rd segment!)\n\n");
    printList(firstSegment);
}

void test_removeListItemAfter() {
    memorySegment *firstSegment = initializeMemory();
    printf("Segments before deletion!\n\n");
    printList(firstSegment);

    removeListItemAfter(firstSegment->next);

    printf("\nSegments after deletion (of second segment!)\n\n");
    printList(firstSegment);
}

void test_assignFirst() {
    printf("\n========================= ASSIGN FIRST =========================\n\n");
    memorySegment *segments;
    segments = initializeMemory();
    uint16_t requiredMemory = 40;

    printf("Available memory:\n");
    printList(segments);

    memorySegment *allocatedBlock = assignFirst(segments, requiredMemory);
    
    printf("\nMemory requested: %d\n\n", requiredMemory);
    printList(segments);

    requiredMemory = 170;
    allocatedBlock = assignFirst(segments, requiredMemory);

    printf("\nMemory requested: %d\n\n", requiredMemory);
    printList(segments);

    requiredMemory = 500;
    allocatedBlock = assignFirst(segments, requiredMemory);
    printf("\nMemory requested: %d\n\n", requiredMemory);

    if (allocatedBlock == NULL) {
        printf("No available memory found.\n");
    } else {
        printf("Memory handling error.\n");
    }

    memorySegment *blockToReclaim = (memorySegment *)malloc(sizeof(memorySegment));
    blockToReclaim->startAddress = 100;
    reclaim(segments, blockToReclaim);

    printf("\nFree block 2.\n\n");
    printList(segments);

    blockToReclaim->startAddress = 0;
    reclaim(segments, blockToReclaim);

    printf("\nFree block 1.\n\n");
    printList(segments);
}

void test_assignBest() {
    printf("\n========================= ASSIGN BEST =========================\n\n");
    memorySegment *segments;
    segments = initializeMemory();

    uint16_t requiredMemory = 190;
    printf("Available memory:\n");
    printList(segments);

    memorySegment *allocatedBlock = assignBest(segments, requiredMemory);
    
    printf("\nMemory requested: %d\n\n", requiredMemory);
    printList(segments);

    requiredMemory = 310;
    allocatedBlock = assignFirst(segments, requiredMemory);
    printf("\nMemory requested: %d\n\n", requiredMemory);

    if (allocatedBlock == NULL) {
        printf("No available memory found.\n");
    } else {
        printf("Memory handling error.\n");
    }

    memorySegment *blockToReclaim = (memorySegment *)malloc(sizeof(memorySegment));
    blockToReclaim->startAddress = 150;
    reclaim(segments, blockToReclaim);

    printf("\nFree block 3.\n\n");
    printList(segments);
}

void test_assignNext() {
    printf("\n========================= ASSIGN NEXT =========================\n\n");
    memorySegment *segments;
    segments = initializeMemory();

    uint16_t requiredMemory = 60;
    printf("Available memory:\n");
    printList(segments);

    memorySegment *allocatedBlock = assignNext(segments, requiredMemory);

    printf("\nMemory requested: %d\n\n", requiredMemory);
    printList(segments);

    requiredMemory = 20;
    allocatedBlock = assignNext(segments, requiredMemory);

    printf("\nMemory requested: %d\n\n", requiredMemory);
    printList(segments);

    requiredMemory = 500;
    allocatedBlock = assignNext(segments, requiredMemory);
    printf("\nMemory requested: %d\n\n", requiredMemory);

    if (allocatedBlock == NULL) {
        printf("No available memory found.\n");
    } else {
        printf("Memory handling error.\n");
    }

    memorySegment *blockToReclaim = (memorySegment *)malloc(sizeof(memorySegment));
    blockToReclaim->startAddress = 350;
    reclaim(segments, blockToReclaim);

    printf("\nFree block 4.\n\n");
    printList(segments);
}

void test_assignFirstDyn() {
    printf("\n========================= ASSIGN FIRST =========================\n\n");
    memorySegment *segments;
    segments = initializeMemory();

    printf("Current memory state:\n");
    printList(segments);

    uint16_t requiredMemory = 150;
    memorySegment *allocatedBlock = assignFirstDyn(segments, requiredMemory);
    printf("\nMemory requested: %d\n\n", requiredMemory);
    printList(segments);

    requiredMemory = 40;
    allocatedBlock = assignFirstDyn(segments, requiredMemory);
    printf("\nMemory requested: %d\n\n", requiredMemory);
    printList(segments);

    requiredMemory = 10;
    allocatedBlock = assignFirstDyn(segments, requiredMemory);
    printf("\nMemory requested: %d\n\n", requiredMemory);
    printList(segments);

    requiredMemory = 320;
    allocatedBlock = assignFirstDyn(segments, requiredMemory);
    printf("\nMemory requested: %d\n\n", requiredMemory);
    printList(segments);
}

void test_assignBestDyn() {
    printf("\n========================= ASSIGN BEST =========================\n\n");
    memorySegment *segments;
    segments = initializeMemory();

    printf("Current memory state:\n");
    printList(segments);

    uint16_t requiredMemory = 280;  
    memorySegment *allocatedBlock = assignBestDyn(segments, requiredMemory);
    printf("\nMemory requested: %d\n\n", requiredMemory);
    printList(segments);

    requiredMemory = 10;
    allocatedBlock = assignBestDyn(segments, requiredMemory);
    printf("\nMemory requested: %d\n\n", requiredMemory);
    printList(segments);

    requiredMemory = 30;
    allocatedBlock = assignBestDyn(segments, requiredMemory);
    printf("\nMemory requested: %d\n\n", requiredMemory);
    printList(segments);

    requiredMemory = 10;
    allocatedBlock = assignBestDyn(segments, requiredMemory);
    printf("\nMemory requested: %d\n\n", requiredMemory);
    printList(segments);
}

void test_assignNextDyn() {
    printf("\n========================= ASSIGN NEXT =========================\n\n");
    memorySegment *segments;
    segments = initializeMemory();

    printf("Current memory state:\n");
    printList(segments);

    uint16_t requiredMemory = 170;
    memorySegment *allocatedBlock = assignNextDyn(segments, requiredMemory);
    printf("\nMemory requested: %d\n\n", requiredMemory);
    printList(segments);

    requiredMemory = 40;
    allocatedBlock = assignNextDyn(segments, requiredMemory);
    printf("\nMemory requested: %d\n\n", requiredMemory);
    printList(segments);

    requiredMemory = 230;
    allocatedBlock = assignNextDyn(segments, requiredMemory);
    printf("\nMemory requested: %d\n\n", requiredMemory);
    printList(segments);
}

#endif