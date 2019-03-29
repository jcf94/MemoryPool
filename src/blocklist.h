/* ***********************************************
MYID   : Chen Fan
LANG   : G++
PROG   : BLOCKLIST_H
************************************************ */

#ifndef BLOCKLIST_H
#define BLOCKLIST_H

#include <vector>

#define KB 1024
#define MB 1024*KB

enum BlockStatus
{
    INUSE,
    IDLE
};

class BlockList;

class MemBlock
{
    friend class BlockList;

public:
    MemBlock(BlockList* blocklist = NULL, int size = 0);
    ~MemBlock();

    inline void* blockaddr() const {return blockaddr_;}
    inline void* dataaddr() const {return dataaddr_;}
    inline int size() const {return size_;}
    inline BlockStatus status() const {return status_;}

    void free();

private:
    MemBlock* prev_;
    MemBlock* next_;

    void* blockaddr_;
    void* dataaddr_;
    int size_;
    BlockStatus status_;

    BlockList* blocklist_;
};

class BlockList
{
public:
    BlockList(int blocksize);
    ~BlockList();

    inline int blocksize() const {return blocksize_;}
    inline int total() const {return blockbackup_.size();}

    MemBlock* malloc();

    // For Debug
    void travel();

    int inuse;

private:
    MemBlock* new_block();

    MemBlock* listhead_;
    MemBlock* listtail_;
    std::vector<MemBlock*> blockbackup_;

    int blocksize_;
};

#endif // !BLOCKLIST_H