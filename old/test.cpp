/* ***********************************************
MYID	: Chen Fan
LANG	: G++11
PROG	: Memory Pool Test File
************************************************ */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include "src/memorypool.h"

#define OUTC(data) std::cout << data << std::endl

using namespace std;
using namespace MemoryPoolNamespace;

int main()
{
    MemoryPool mem = MemoryPool(1000);
    mem.blocktravel();

    OUTC(sizeof(void*));
    OUTC(sizeof(int));
    OUTC(sizeof(MemoryPool*));
    OUTC(sizeof(Block*));
    OUTC(BLOCK_OFFSET);

    int* a = (int*) mem.mbmalloc(sizeof(int));
    mem.blocktravel();
    *a = 12345;
    OUTC(*a);

    float* b = (float*) mem.mbmalloc(sizeof(float));
    mem.blocktravel();

    double* c = (double*) mem.mbmalloc(sizeof(double));
    mem.blocktravel();

    mem.mbfree(a);
    mem.blocktravel();
    mem.mbfree(b);
    mem.blocktravel();

    a = (int*) mem.mbmalloc(sizeof(int));
    mem.blocktravel();
    OUTC(*a);

    mem.mbfree(c);
    mem.blocktravel();

    mem.mbfree(a);
    mem.blocktravel();

    return 0;
}