/**
 * @file Block.cpp
 * @author Joseph Pauls, Will Morant
 */

#include "pch.h"
#include "Block.h"
#include "ItemVisitor.h"

Block::Block(Level* level, const std::wstring& filename)
        :Item(level, filename)
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

void Block::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    b2Body* body = GetBody();
    auto position = body->GetPosition();
    auto angle = body->GetAngle();

    graphics->Translate(position.x * Consts::MtoCM,
            position.y * Consts::MtoCM);
    graphics->Rotate(angle);

    // Make this is left side of the rectangle
    double x = -mSize.x/2 * Consts::MtoCM;

    // And the top
    double y = mSize.y/2 * Consts::MtoCM;

   /** // The width of each repeated block
    double xw = mSize.x / mRepeatX * Consts::MtoCM;

    std::shared_ptr<wxBitmap> bitmap = ;

    graphics->Translate(0, y);
    graphics->Scale(1, -1);
    for(int ix=0; ix<mRepeatX;  ix++)
    {
        graphics->DrawBitmap(mPicture->AsBitmap(),
                x,
                0,
                xw, mSize.y * Consts::MtoCM);

        x += xw;
    }
*/
    graphics->PopState();
}
