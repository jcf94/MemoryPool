/* ***********************************************
MYID	: Chen Fan
LANG	: G++11
PROG	: Memory Pool Function File
************************************************ */

#include "memorypool.h"

namespace MemoryPoolNamespace{


void* MemoryPool::mbmalloc(int size)
{
    Block* source = this->_freeblock;
    Block* last = NULL;

    while (source)
    {
        if (source->_blocksize > size+BLOCK_OFFSET)
        {
            // Cut the original freeblock
            // Create New freeblock header
            Block* temp = CreateBlock(source->_mempool, source->_blockaddr+size, source->_blocksize-size-BLOCK_OFFSET, source->Next, source);
            // Change _freeblock
            temp->Nextfreeblock = source->Nextfreeblock;
            if (source->Next)
                source->Next->Prev = temp;

            if (last)
                last->Nextfreeblock = temp;
            else 
                this->_freeblock = temp;
            
            // Prepare the return block
            source->_blocksize = size;
            source->Next = temp;
            source->_inuse = true;

            return source->_blockaddr;
        } else if (source->_blocksize >= size)
        {
            if (last)
                last->Nextfreeblock = source->Nextfreeblock;
            else 
                this->_freeblock = source->Nextfreeblock;

            // Prepare the return block
            source->_inuse = true;

            return source->_blockaddr;
        } else
        {
            last = source;
            source = source->Nextfreeblock;
        }
    }
}

void MemoryPool::mbfree(void* memaddr)
{
    Block* block = (Block*)(memaddr-BLOCK_OFFSET);
    Block* frontfreeblock = NULL;
    Block* backfreeblock = this->_freeblock;
    while (backfreeblock < block)
    {
        frontfreeblock = backfreeblock;
        backfreeblock = backfreeblock->Nextfreeblock;
    }

    if (frontfreeblock)
        frontfreeblock->Nextfreeblock = block;
    else 
        this->_freeblock = block;
    block->Nextfreeblock = backfreeblock;
    block->_inuse = false;

    mbmerge(block);
}

void MemoryPool::mbmerge(Block* block)
{
    if (block->Prev && (!block->Prev->_inuse))
    {
        block->Prev->_blocksize += block->_blocksize+BLOCK_OFFSET;
        block->Prev->Next = block->Next;
        block->Prev->Nextfreeblock = block->Nextfreeblock;
        block->Next->Prev = block->Prev;
        block = block->Prev;
    }
    if (block->Next && (!block->Next->_inuse))
    {
        block->_blocksize += block->Next->_blocksize+BLOCK_OFFSET;
        block->Nextfreeblock = block->Next->Nextfreeblock;
        if (block->Next->Next)
            block->Next->Next->Prev = block;
        block->Next = block->Next->Next;
    }
}

void MemoryPool::freeblocktravel()
{
    Block* now = this->_freeblock;
    OUTC("--- freeblock: ---");
    while (now)
    {
        OUTC("Block: " << now);
        OUTC("DataAddr: " << now->_blockaddr);
        OUTC("BlockSize: " << now->_blocksize);
        OUTC("NextBlock: " << now->Next);
        OUTC("PrevBlock: " << now->Prev);
        OUTC("NextFreeBlock: " << now->Nextfreeblock);
        OUTC("");
        now = now->Nextfreeblock;
    }
}

void MemoryPool::blocktravel()
{
    Block* now = (Block*)this->_memblock;
    OUTC("--- block: ---");
    OUTC("Freeblock: " << this->_freeblock);
    while (now)
    {
        OUTC("Block: " << now);
        OUTC("Used: " << now->_inuse);
        OUTC("DataAddr: " << now->_blockaddr);
        OUTC("BlockSize: " << now->_blocksize);
        OUTC("NextBlock: " << now->Next);
        OUTC("PrevBlock: " << now->Prev);
        OUTC("NextFreeBlock: " << now->Nextfreeblock);
        OUTC("");
        now = now->Next;
    }
}

Block* CreateBlock(MemoryPool* mempool, void* memblock, int size,
                    Block* next, Block* prev, Block* Nextfreeblock)
{
    Block* temp = (Block*)memblock;
    temp->_blockaddr = (void*)temp+BLOCK_OFFSET;
    temp->_blocksize = size;
    temp->_mempool = mempool;
    temp->_inuse = false;
    temp->Next = next;
    temp->Prev = prev;
    temp->Nextfreeblock = Nextfreeblock;

    return temp;
}

}
