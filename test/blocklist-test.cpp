/* ***********************************************
MYID   : Chen Fan
LANG   : G++
PROG   : 
************************************************ */

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>

#include "src/blocklist.h"

using namespace std;

int main()
{
    BlockList list(KB);

    auto a = list.malloc();
    auto b = list.malloc();
    list.travel();

    a->free();
    list.travel();
    a = list.malloc();
    list.travel();

    auto c = list.malloc();
    list.travel();

    a->free();
    list.travel();

    a = list.malloc();
    list.travel();

    auto d = list.malloc();
    list.travel();

    return 0;
}