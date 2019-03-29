/* ***********************************************
MYID   : Chen Fan
LANG   : G++
PROG   : BASEBLOCK_CPP
************************************************ */

#include "blocklist.h"

#include <stdlib.h>
#include <iostream>

BaseBlock::BaseBlock(BlockList* blocklist, int size)
    : blocklist_(blocklist), size_(size),
    prev_(NULL), next_(NULL), status_(READY)
{
    if (size > 0) blockaddr_ = malloc(size+sizeof(void*));
    dataaddr_ = blockaddr_ + sizeof(void*);
}

BaseBlock::~BaseBlock()
{
    if (size_ > 0) ::free(blockaddr_);
}

void BaseBlock::free()
{
    if (status_ == READY)
    {
        std::cout << "Error: Only Block in use can be freed\n";
        return;
    } else
    {
        status_ = READY;
        --blocklist_->inuse;

        prev_->next_ = this;
        if (next_) next_->prev_ = this;
    }
}
