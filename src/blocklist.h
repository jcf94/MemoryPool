/* ***********************************************
MYID   : Chen Fan
LANG   : G++
PROG   : BLOCKLIST_H
************************************************ */

#ifndef BLOCKLIST_H
#define BLOCKLIST_H

#include "baseblock.h"

#include <vector>
#include <mutex>

#define KB (1024)
#define MB (1024 * KB)
#define GM (1024 * MB)

class BlockList
{
public:
    BlockList(int blocksize, BaseBlockFactory* factory);
    ~BlockList();

    inline int blocksize() const {return blocksize_;}
    inline int total() const {return blockbackup_.size();}

    BaseBlock* malloc();
    void free(BaseBlock* target);

    // For Debug
    void travel();

    int inuse;

private:
    BaseBlock* new_block();

    BaseBlock* listhead_;
    BaseBlock* listtail_;
    std::vector<BaseBlock*> blockbackup_;
    BaseBlockFactory* factory_;

    std::mutex list_lock_;

    int blocksize_;
};

#endif // !BLOCKLIST_H