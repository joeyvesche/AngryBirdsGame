/**
 * @file Item.cpp
 * @author Joseph Pauls
 */

#include "pch.h"
#include "Item.h"
#include "Consts.h"

using namespace std;
const std::wstring ResDir = L"./images/";
/**
*  Constructor
*/
Item::Item(Level* level, const wstring& filename) :mLevel(level)
{
    mItemImage = make_unique<wxImage>(ResDir + filename, wxBITMAP_TYPE_ANY);
    mItemBitmap = make_unique<wxBitmap>(*mItemImage);

}

/**
 * Destructor
 */
Item::~Item()
{

}

/**
 * Compute the distance from this item to another item
 * @return Distance in pixels
 */
double Item::DistanceTo(std::shared_ptr<Item> item)
{
    auto dx = item->GetX() - GetX();
    auto dy = item->GetY() - GetY();
    return sqrt(dx * dx + dy * dy);
}

/**
 * Test to see if we hit this object with a mouse.
 * @param x X position to test
 * @param y Y position to test
 * @return true if hit.
 */
bool Item::HitTest(int x, int y)
{
    double wid = mItemBitmap->GetWidth();
    double hit = mItemBitmap->GetHeight();

    // Make x and y relative to the top-left corner of the bitmap image
    // Subtracting the center makes x, y relative to the image center
    // Adding half the size makes x, y relative to the image top corner
    double testX = x - GetX() + wid / 2;
    double testY = y - GetY() + hit / 2;

    // Test to see if x, y are in the image
    if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
    {
        // We are outside the image
        return false;
    }

    // Test to see if x, y are in the drawn part of the image
    // If the location is transparent, we are not in the drawn
    // part of the image
    return !mItemImage->IsTransparent((int)testX, (int)testY);
}

/**
 * Draw this item
 */
void Item::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    double wid = mItemBitmap->GetWidth();
    double hit = mItemBitmap->GetHeight();
    graphics->PushState();
    graphics->Translate(mX, mY);
    graphics->Scale(1, -1);	// Negate Y
    graphics->DrawBitmap(*mItemBitmap,
            int(GetX() - wid / 2),
            int(GetY() - hit / 2),
            wid, hit);
    graphics->PopState();

}


/**
 * Load the attributes for an item node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * @param node The Xml node we are loading the item from
 */
void Item::XmlLoad(wxXmlNode *node)
{
    node->GetAttribute(L"x", L"0").ToDouble(&mX);
    node->GetAttribute(L"y", L"0").ToDouble(&mY);
    node->GetAttribute(L"angle", L"0").ToDouble(&mAngle);

    SetLocation(GetX() * Consts::MtoCM, GetY() * Consts::MtoCM);
}
