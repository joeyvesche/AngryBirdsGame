/**
 * @file Item.cpp
 * @author Joseph Pauls, Joey Vesche
 */

#include "pch.h"
#include "Item.h"
#include "Consts.h"
#include <utility>

using namespace std;
/// Directory of the images used for the game
const std::wstring ResDir = L"./images/";
/**
 * Constructor
 * @param level level this item belongs to
 * @param filename file for image
 */
Item::Item(Level* level, const std::wstring& filename) : mLevel(level)
{
    auto [img, bitmap] = LoadImage(filename);
    mItemImage = img;
    mItemBitmap = bitmap;
}

/**
 * Destructor
 */
Item::~Item()
{

}

/**
 * Loads an image file and stores it in a common database of item images.
 * If the image file was previously loaded, it will not be loaded again
 *
 * @param filename the filename and extension of the image file
 * @return shared_ptr to both the loaded image and bitmap objects
 */
std::pair<std::shared_ptr<wxImage>, std::shared_ptr<wxBitmap>> Item::LoadImage(std::wstring const & filename)
{
    // if this is the first time we are loading in the file image, save it in the texture packs
    if (mImagePack.find(filename) == mImagePack.end())
    {
        mImagePack.insert({filename, make_shared<wxImage>(ResDir + filename, wxBITMAP_TYPE_ANY)});
        mBitmapPack.insert({filename, make_shared<wxBitmap>(*mImagePack[filename])});
    }

    // load shared image and bitmap into this object
    return {mImagePack[filename], mBitmapPack[filename]};
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
 * Draw this Item
 * @param graphics Context to draw on
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
}
