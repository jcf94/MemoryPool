/* ***********************************************
MYID   : Chen Fan
LANG   : G++
PROG   : BLOCKLIST_CPP
************************************************ */

#include <stdlib.h>
#include <iostream>

#include "blocklist.h"

MemBlock::MemBlock(BlockList* blocklist, int size)
    : blocklist_(blocklist), size_(size),
    prev_(NULL), next_(NULL), status_(IDLE)
{
    if (size > 0) block_ = malloc(size);
}

MemBlock::~MemBlock()
{
    if (size_ > 0) ::free(block_);
}

void MemBlock::free()
{
    if (status_ == IDLE)
    {
        std::cout << "Error: Only Block in use can be freed\n";
        return;
    } else
    {
        status_ = IDLE;
        --blocklist_->inuse;

        prev_->next_ = this;
        if (next_) next_->prev_ = this;
    }
}

BlockList::BlockList(int blocksize)
    : blocksize_(blocksize), inuse(0)
{
    if (blocksize_ <= 0)
    {
        std::cout << "Error: size must be a positive integer in BlockList\n";
        return ;
    }
    listhead_ = new MemBlock(this);
    listtail_ = listhead_;
}

BlockList::~BlockList()
{
    for (auto i:blockbackup_)
    {
        delete i;
    }
    delete listhead_;
}

MemBlock* BlockList::new_block()
{
    MemBlock* temp = new MemBlock(this, blocksize_);
    blockbackup_.push_back(temp);

    listhead_->next_ = temp;
    temp->prev_ = listhead_;

    listtail_->next_ = temp;
    listtail_ = temp;

    return temp;
}

MemBlock* BlockList::malloc()
{
    MemBlock* target = listhead_->next_;
    while (target && target->status_ == INUSE) target = target->next_;

    if (!target) target = new_block();

    target->status_ = INUSE;
    ++inuse;

    target->prev_->next_ = target->next_;
    if (target->next_) target->next_->prev_ = target->prev_;

    return target;
}

void BlockList::travel()
{
    std::cout << "============\n";
    for (auto i:blockbackup_)
    {
        std::cout << i->block() << " " << (i->status()==INUSE?"INUSE":"IDLE") << (listhead_->next_==i?" <-":"") << "\n";
    }
    std::cout << "============\n";
}