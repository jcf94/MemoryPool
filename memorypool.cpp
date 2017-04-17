/* ***********************************************
MYID	: Chen Fan
LANG	: G++11
PROG	: Memory Pool Function File
************************************************ */

#include "memorypool.h"

namespace MemoryPoolNamespace{

int MemoryPool::gettotalsize()
{
    return _mainsize;
}

void* MemoryPool::mpmalloc(int size)
{
    void* out = _mainblock + now;
    now += size;
    return out;
}

int MemoryPool::used()
{
    return now;
}

void* MemoryPool::mbmalloc(int size)
{
    void* addr = mpmalloc(size);
    Block* block = new Block(this, addr, size);
    return addr;
}

}