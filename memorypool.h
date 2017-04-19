/* ***********************************************
MYID	: Chen Fan
LANG	: G++11
PROG	: Memory Pool Head File
************************************************ */

#include <cstdlib>
#include <unordered_map>
#include <iostream>

#define OUTC(data) std::cout << data << std::endl

namespace MemoryPoolNamespace{

class MemoryPool;

typedef struct Block_Struct Block;
Block* CreateBlock(MemoryPool* mempool, void* memblock, int size,
                    Block* next = NULL, Block* prev = NULL,
                    Block* Nextfreeblock = NULL);

struct Block_Struct
{
    void* _blockaddr;
    int _blocksize;
    MemoryPool* _mempool;
    bool _inuse;
    Block* Next;
    Block* Prev;
    Block* Nextfreeblock;
};
#define BLOCK_OFFSET sizeof(Block)

class MemoryPool
{
    public:
        MemoryPool(int size)
        {
            _memblock = malloc(size+BLOCK_OFFSET);
            _freeblock = CreateBlock(this, _memblock, size);
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

        typedef std::unordered_map<int, void*> id_pointer_map;
        
        typedef std::unordered_map<void*, int> pointer_id_map;
};

}