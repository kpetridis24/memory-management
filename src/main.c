#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include "memorySegment.cpp"
#include "staticMemoryManagement.cpp"
#include "dynamicMemoryManagement.cpp"
#include "tests.cpp"

int main(int argc, char **argv) {
    switch (atoi(argv[1])) {
        case 0: 
            test_assignFirst();
            test_assignBest();
            test_assignNext();
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