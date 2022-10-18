/**
 * @file Block.h
 * @author Joseph Pauls
 *
 *Base Class for block items. inherited from Item
 */

#ifndef PROJECT1_BLOCK_H
#define PROJECT1_BLOCK_H
#include "Item.h"
#include <string>
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

    Block(Game* game, const std::wstring& filename);

    void XmlLoad(wxXmlNode* node) override;
    void Accept(ItemVisitor * visitor) override;

};

#endif //PROJECT1_BLOCK_H
