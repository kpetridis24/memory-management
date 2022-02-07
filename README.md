# memory-management
Static and dynamic management of memory blocks for memory allocation requests.
This is a C implementation of three basic methods to accomplish practical memory management. The central idea is that, the operational system needs to 
handle requests for memory allocation from processes, who have different requirements. The memory allocation must occur, such that both internal and 
external fragmentation is minimized. This means that during the memory allocation we must re-organize the unallocated space in such a way that it can be 
efficiently used by the next memory allocation requests. A first idea would be to concatenate empty memory spaces after dynamic allocation has occured, so 
that we end up with significantly large chunks of memory, that are more likely to be used, than having scattered, small pieces of free space all over the memory.

The validity of the functions used, is examined by the corresponding tester functions in 'tests.h'. The memory allocation methods used are:
- First Fit
- Best Fit
- Next Fit
Useful information about these methods can be found [here](https://www.tutorialspoint.com/operating_system/os_memory_allocation_qa2.htm)

To run the code follow the steps:

1. Install the repository
```
git clone https://github.com/kpetridis24/memory-management.git
```
2. To run the static allocation memory management demo:
```
make static
```
3. To run the dynamic allocation memory management demo:
```
make dynamic
```


