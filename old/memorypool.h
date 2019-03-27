/* ***********************************************
MYID	: Chen Fan
LANG	: G++11
PROG	: Memory Pool Head File
************************************************ */

#include <cstdlib>

namespace MemoryPoolNamespace{

class MemoryPool;

typedef struct Block_Head_Struct Block;
Block* CreateBlock(void* memblock, int size,
                    Block* next = NULL, Block* prev = NULL,
                    Block* Nextfreeblock = NULL);

struct Block_Head_Struct
{
    void* _blockaddr;
    int _blocksize;
    bool _inuse;
    Block* Next;
    Block* Prev;
    Block* Nextfreeblock;
};
#define BLOCK_OFFSET sizeof(Block)

class MemoryPool
{
    public:
        MemoryPool(int size = 16384)
        {
            _memblock = malloc(size+BLOCK_OFFSET);
            _freeblock = CreateBlock(_memblock, size);
        }
        ~MemoryPool()
        {
            free(_memblock);
        }
        void* mbmalloc(int size);
        void mbfree(void* memaddr);
        void freeblocktravel();
        void blocktravel();
    private:
        void* _memblock;
        Block* _freeblock;
        void mbmerge(Block* block);
};

}