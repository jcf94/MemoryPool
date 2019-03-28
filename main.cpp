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

    auto a = mp.malloc(513);
    auto b = mp.malloc(2048);
    auto c = mp.malloc(10240);
    mp.travel();

    a->free();
    b->free();
    mp.travel();

    b = mp.malloc(2047);
    mp.travel();

    return 0;
}