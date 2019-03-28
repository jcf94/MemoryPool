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

class MemBlock
{
    friend class BlockList;

public:
    MemBlock(int size = 0);
    ~MemBlock();

    inline void* block() const {return block_;}
    inline int size() const {return size_;}
    inline BlockStatus status() const {return status_;}

    void free();

private:
    MemBlock* prev_;
    MemBlock* next_;

    void* block_;
    int size_;
    BlockStatus status_;
};

class BlockList
{
public:
    BlockList(int size);
    ~BlockList();

    MemBlock* malloc();

    // For Debug
    void travel();

private:
    MemBlock* new_block();

    MemBlock* listhead_;
    MemBlock* listtail_;
    std::vector<MemBlock*> blockbackup_;

    int size_;
};

#endif // !BLOCKLIST_H