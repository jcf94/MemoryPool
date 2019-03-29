/* ***********************************************
MYID   : Chen Fan
LANG   : G++
PROG   : BASEBLOCK_H
************************************************ */

#ifndef BASEBLOCK_H
#define BASEBLOCK_H

enum BlockStatus
{
    INUSE,
    READY
};

class BlockList;

class BaseBlock
{
public:
    BaseBlock(BlockList* blocklist = 0, int size = 0);
    ~BaseBlock();

    inline void* blockaddr() const {return blockaddr_;}
    inline void* dataaddr() const {return dataaddr_;}
    inline int size() const {return size_;}
    inline BlockStatus status() const {return status_;}

    void free();

protected:
    BaseBlock* prev_;
    BaseBlock* next_;

    void* blockaddr_;
    void* dataaddr_;
    int size_;
    BlockStatus status_;

    BlockList* blocklist_;

    friend class BlockList;
};

class BaseBlockFactory
{
public:
    virtual BaseBlock* create(BlockList* blocklist = 0, int size = 0) = 0;
};

#endif // !BASEBLOCK_H