/* ***********************************************
MYID   : Chen Fan
LANG   : G++
PROG   : BLOCKLIST_H
************************************************ */

#ifndef BLOCKLIST_H
#define BLOCKLIST_H

#include "baseblock.h"

#include <vector>

#define KB 1024
#define MB 1024*KB

class BlockList
{
public:
    BlockList(int blocksize, BaseBlockFactory* factory = 0);
    ~BlockList();

    inline int blocksize() const {return blocksize_;}
    inline int total() const {return blockbackup_.size();}

    BaseBlock* malloc();

    // For Debug
    void travel();

    int inuse;

private:
    BaseBlock* new_block();

    BaseBlock* listhead_;
    BaseBlock* listtail_;
    std::vector<BaseBlock*> blockbackup_;
    BaseBlockFactory* factory_;

    int blocksize_;
};

#endif // !BLOCKLIST_H