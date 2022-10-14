/**
 * @file Block.h
 * @author Joseph Pauls
 *
 *Base Class for block items. inherited from Item
 */

#ifndef PROJECT1_BLOCK_H
#define PROJECT1_BLOCK_H
#include "Item.h"

/**
 * Base Class for a block
 */
class Block : public Item {
private:

public:
    /// Default constructor (disabled)
    Block() = delete;

    /// Copy constructor (disabled)
    Block(const Block &) = delete;


};

#endif //PROJECT1_BLOCK_H
