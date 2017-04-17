/* ***********************************************
MYID	: Chen Fan
LANG	: G++11
PROG	: Memory Pool Head File
************************************************ */

#include <cstdlib>
#include <unordered_map>

namespace MemoryPoolNamespace{

class MemoryPool
{
    friend class Block;
    public:
        MemoryPool(int size)
        {
            _mainsize = size;
            _mainblock = malloc(_mainsize);
            now = 0;
        }
        ~MemoryPool()
        {
            free(_mainblock);
        }
        int gettotalsize();
        void* mpmalloc(int size);
        int used();
        void* mbmalloc(int size);
    //private:
        void* _mainblock;
        int _mainsize;
        int now;
        typedef std::unordered_map<int, void*> id_pointer_map;
        
        typedef std::unordered_map<void*, int> pointer_id_map;
};

class Block
{
    public:
        Block(MemoryPool* mempool, void* addr, int size): 
            _mempool(mempool), _blockaddr(addr), _blocksize(size){}
    private:
        void* _blockaddr;
        int _blocksize;
        MemoryPool* _mempool;
        int _blockid;
};

}