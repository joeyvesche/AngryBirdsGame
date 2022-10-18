/**
 * @file Block.cpp
 * @author Joseph Pauls
 */

#include "pch.h"
#include "Block.h"
#include "ItemVisitor.h"
Block::Block(Game* game, const std::wstring& filename)
        :Item(game, filename)
{

}

void Block::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);
}

void Block::Accept(ItemVisitor* visitor)
{
    visitor->VisitBlock(this);
}
