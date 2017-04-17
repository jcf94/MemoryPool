/* ***********************************************
MYID	: Chen Fan
LANG	: G++11
PROG	: Memory Pool Test File
************************************************ */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include "memorypool.h"

using namespace std;
using namespace MemoryPoolNamespace;

#define OUTC(data) cout << data << endl

int main()
{
    MemoryPool mem = MemoryPool(100);
    OUTC(mem.gettotalsize());
    OUTC(mem._mainblock);
    
    int* a = (int*)mem.mpmalloc(sizeof(int));
    *a = 12;
    OUTC(mem.used());
    OUTC(a);
    OUTC(*a);

    float* b = (float*)mem.mpmalloc(sizeof(float));
    OUTC(mem.used());
    OUTC(b);
    OUTC(*b);

    double *c = (double*)mem.mbmalloc(sizeof(double));
    OUTC(mem.used());
    OUTC(c);
    OUTC(*c);

    OUTC(sizeof(void*));

    return 0;
}