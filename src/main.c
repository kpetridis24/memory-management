#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include <memorySegment.h>
#include <dynamicMemoryManagement.h>
#include <staticMemoryManagement.h>
#include "tests.h"


int main(int argc, char **argv) {
    memorySegment *seg = NULL;
    switch (atoi(argv[1])) {
        case 0: ;
            test_assignFirst();
            test_assignBest();
            test_assignNext();
            
            // insertListItemAfter(seg);
            // printList(seg);
            break;
        case 1: 
            test_assignFirstDyn();
            test_assignBestDyn();
            test_assignNextDyn();
            break;
        default:
            printf("Input integer does not correspond to any test.");
            exit(1);
    }
}