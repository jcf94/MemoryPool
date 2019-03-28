/* ***********************************************
MYID   : Chen Fan
LANG   : G++
PROG   : MEMORYPOOL_H
************************************************ */

#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H

#include <vector>

#include "blocklist.h"

#define MIN_BLOCK_SIZE 256
#define INIT_LISTS 4

class MemoryPool // BlockList based
{
public:
    MemoryPool();
    ~MemoryPool();

    MemBlock* malloc(int size);

    // For Debug
    void travel();

private:
    std::vector<BlockList*> bllist_;

};

#endif // !MEMORYPOOL_H