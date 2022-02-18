#ifndef MEMORYSEGMENT
#define MEMORYSEGMENT

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

/**
 * Each memory segment (block) is represented by a memorySegment structure object.
 */
typedef struct memorySegment {
    uint16_t startAddress;
    uint16_t length;
    bool occupied;
    struct memorySegment *next;
} memorySegment;

/**
 * Functions for the actual handling of the memory segments.
 */
void printList(memorySegment *memList);
void insertListItemAfter(memorySegment *current);
void removeListItemAfter(memorySegment *current);

/**
 * The length and the starting address of the new block to be added, in the dynamic memory handling functions.
 */
static uint16_t lengthOfNewBlock = 0;
static uint16_t startAddressOfNewBlock = 0;

void printList(memorySegment *memList) {
    memorySegment *current;
    current = memList;

    while (true) {
        printf("%d %d %s\n", current->startAddress, current->length, current->occupied ? "Occupied!" : "Free");
        if (current->next == NULL) {
            break;
        }
        current = current->next;
    }
}

void insertListItemAfter(memorySegment *current) {
    memorySegment *newItem;
    newItem = (memorySegment *)malloc(sizeof(memorySegment));
    newItem->length = lengthOfNewBlock;
    newItem->startAddress = startAddressOfNewBlock;
    newItem->occupied = false;

    if (current != NULL) { printf("ent\n");
        if (current->next) {
            newItem->next = current->next;
            current->next = newItem;
        } else {
            current->next = newItem;
        }
        current = newItem->next;
    } else {
        current = newItem;
    }
}

void removeListItemAfter(memorySegment *current) {
    if (current) {
        if (current->next->next) {
            uint16_t offsetToSubtract = current->next->length;
            current->next = current->next->next;
            current = current->next;
            while (current != NULL) {
                current->startAddress -= offsetToSubtract;
                current = current->next;
            }
        } else {
            current->next = NULL;
        }
    }
}

#endif