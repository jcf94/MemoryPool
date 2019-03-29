/* ***********************************************
MYID   : Chen Fan
LANG   : G++
PROG   : MAIN
************************************************ */

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>

#include "src/memorypool.h"

using namespace std;

int main()
{
    MemoryPool mp;

    mp.travel();

    auto a = mp.blockalloc(513);
    auto b = mp.blockalloc(2048);
    auto c = mp.blockalloc(10240);
    mp.travel();

    a->free();
    b->free();
    mp.travel();

    b = mp.blockalloc(2047);
    mp.travel();

    void* d = mp.malloc(1024);
    mp.travel();

    mp.free(d);
    mp.travel();

    return 0;
}