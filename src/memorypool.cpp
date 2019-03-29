/* ***********************************************
MYID   : Chen Fan
LANG   : G++
PROG   : MEMORYPOOL_CPP
************************************************ */

#include <string.h>
#include <iostream>

#include "memorypool.h"

MemoryPool::MemoryPool(BaseBlockFactory* factory)
    : factory_(factory)
{
    int blocksize = MIN_BLOCK_SIZE;
    for (int i=0;i<INIT_LISTS;++i)
    {
        bllist_.push_back(new BlockList(blocksize, factory));
        blocksize <<= 1;
    }
}

MemoryPool::~MemoryPool()
{
    for (auto i:bllist_)
    {
        delete i;
    }
}

BaseBlock* MemoryPool::blockalloc(int size)
{
    size = (size - 1) / MIN_BLOCK_SIZE;
    int count = 0;
    while (size)
    {
        ++count;
        if (count == bllist_.size())
        {
            bllist_.push_back(new BlockList(bllist_[count-1]->blocksize()*2, factory_));
        }
        size /= 2;
    }
    return bllist_[count]->malloc();
}

void* MemoryPool::malloc(int size)
{
    BaseBlock* target = blockalloc(size);
    memcpy(target->blockaddr(), &target, sizeof(void*));

    return target->dataaddr();
}

void MemoryPool::free(void* dataaddr)
{
    BaseBlock* target;
    memcpy(&target, dataaddr-sizeof(void*), sizeof(void*));

    target->free();
}

void MemoryPool::travel()
{
    std::cout << "============\n";
    for (auto i:bllist_)
    {
        std::cout << "Size: " << i->blocksize() << " " << i->inuse << "/" << i->total() << "\n";
    }
    std::cout << "============\n";
}