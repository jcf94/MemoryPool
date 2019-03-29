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
    MemoryPool(BaseBlockFactory* factory = 0);
    ~MemoryPool();

    BaseBlock* blockalloc(int size);
    void* malloc(int size);
    void free(void* dataaddr);
    BaseBlock* getblock(void* dataaddr);

    // For Debug
    void travel();

private:
    std::vector<BlockList*> bllist_;
    BaseBlockFactory* factory_;
};

#endif // !MEMORYPOOL_H