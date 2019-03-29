/* ***********************************************
MYID   : Chen Fan
LANG   : G++
PROG   : BLOCKLIST_CPP
************************************************ */

#include <iostream>

#include "blocklist.h"

class MemBlock : public BaseBlock
{
public:
    MemBlock(BlockList* blocklist, int size)
        : BaseBlock(blocklist, size) {}
};

class MemBlockFactory: public BaseBlockFactory
{
public:
    BaseBlock* create(BlockList* blocklist, int size)
    {
        return new MemBlock(blocklist, size);
    }
};

BlockList::BlockList(int blocksize, BaseBlockFactory* factory)
    : blocksize_(blocksize), factory_(factory), inuse(0)
{
    if (blocksize_ <= 0)
    {
        std::cout << "Error: size must be a positive integer in BlockList\n";
        return ;
    }
    listhead_ = new BaseBlock();
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

BaseBlock* BlockList::new_block()
{
    if (!factory_) factory_ = new MemBlockFactory();

    BaseBlock* temp = factory_->create(this, blocksize_);
    blockbackup_.push_back(temp);

    listhead_->next_ = temp;
    temp->prev_ = listhead_;

    listtail_->next_ = temp;
    listtail_ = temp;

    return temp;
}

BaseBlock* BlockList::malloc()
{
    BaseBlock* target = listhead_->next_;
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
        std::cout << i->blockaddr() << " " << (i->status()==INUSE?"INUSE":"IDLE") << (listhead_->next_==i?" <-":"") << "\n";
    }
    std::cout << "============\n";
}