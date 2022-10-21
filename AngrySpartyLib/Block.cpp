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
    mBlockImage = std::make_shared<wxImage>(L"images/" + filename, wxBITMAP_TYPE_ANY);
    mBlockBitmap = std::make_shared<wxBitmap>(*mBlockImage);

}

void Block::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);

    node->GetAttribute(L"repeat-x", L"0").ToInt(&mRepeatX);
    double width, height;
    node->GetAttribute(L"width", L"0").ToDouble(&width);
    node->GetAttribute(L"height", L"0").ToDouble(&height);
    mSize.x = width;
    mSize.y = height;

    std::shared_ptr<ItemBody> body = std::make_shared<ItemBody>(this, node);
    Level *level = Item::GetLevel();
    Physics *physics = level->GetPhysics();
    body->MakeBody(physics);
    mBody = body->GetBody();
}

void Block::Accept(ItemVisitor* visitor)
{
    visitor->VisitBlock(this);
}

void Block::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    b2Body* body = mBody;
    auto position = body->GetPosition();
    auto angle = body->GetAngle();

    graphics->Translate(position.x*Consts::MtoCM,
            position.y*Consts::MtoCM);
    graphics->Rotate(angle);

    // Make this is left side of the rectangle
    double x = -mSize.x/2*Consts::MtoCM;

    // And the top
    double y = mSize.y/2*Consts::MtoCM;

    // The width of each repeated block
    double xw = mSize.x/mRepeatX*Consts::MtoCM;

    //std::shared_ptr<wxBitmap> bitmap = ;

    graphics->Translate(0, y);
    graphics->Scale(1, -1);
    for (int ix = 0; ix<mRepeatX; ix++) {
        graphics->DrawBitmap(*mBlockBitmap,
                x,
                0,
                xw, mSize.y*Consts::MtoCM);

        x += xw;
    }

    graphics->PopState();
}
