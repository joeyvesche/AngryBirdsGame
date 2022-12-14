
/**
 * @file Item.h
 * @author Joseph Pauls
 *
 * The underlying base class for all items in the level
 */


#ifndef PROJECT1_ITEM_H
#define PROJECT1_ITEM_H

#include <memory>
#include <wx/xml/xml.h>
#include <wx/graphics.h>
#include "Physics.h"
#include <unordered_map>

class LimpetKillVisitor;
class ItemVisitor;
class Level;

/**
 * Base Class for items used in the level
 */
class Item {
private:
    /// The level this Item is contained in
    Level *mLevel;

    /// shared collection of images used for items
    inline static std::unordered_map<std::wstring, const std::shared_ptr<wxImage>> mImagePack;

    /// shared collection of bitmaps used for items
    inline static std::unordered_map<std::wstring, const std::shared_ptr<wxBitmap>> mBitmapPack;

    /// Item X location in the level
    double mX = 0;
    /// Item Y location in the level
    double mY = 0;
    /// Item angle in the level
    double mAngle = 0;
    /// The underlying Item image
    std::shared_ptr<wxImage> mItemImage;

    /// The displayable bitmap for this Item
    std::shared_ptr<wxBitmap> mItemBitmap;

protected:

    Item(Level *level, const std::wstring &filename);

public:

    /// Item Destructor
    virtual ~Item();

    /// Test if the item is hit by the mouse
    virtual bool HitTest(int x, int y);

    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    /// Assignment operator
    void operator=(const Item &) = delete;

    /**
     *  The X location of the item
     *  @return X location in pixels
     */
    double GetX() const{ return mX;}

    /**
    * The Y location of the item
    * @return Y location in pixels
    */
    double GetY() const { return mY; }

    /**
    * Set the item location
    * @param x X location in pixels
    * @param y Y location in pixels
    */
    void SetLocation(double x, double y) { mX = x; mY = y; }


    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    virtual void XmlLoad(wxXmlNode* node);

    /**
    * Handle updates for animation
    * @param elapsed The time since the last update
    */
    virtual void Update(double elapsed) {}

    /**
     * Get the pointer to the level object
     * @return Pointer to level object
     */
    Level *GetLevel() {return mLevel; }

    std::pair<std::shared_ptr<wxImage>, std::shared_ptr<wxBitmap>> LoadImage(std::wstring const & filename);

    /**
    * Get the width of the object
    * @return int representing the width
    */
    virtual double GetWidth() const { return mItemBitmap->GetWidth(); }

    /**
     * Get the height of the object
     * @return int representing the height
     */
    virtual double GetHeight() const {return mItemBitmap->GetHeight(); }

    /**
     * Get the bitmap image of this item
     *
     * @return shared_ptr to a bitmap
     */
    std::shared_ptr<wxBitmap> GetBitmap() const { return mItemBitmap; }

    /**
     * Accept an item visitor
     * @param visitor
     */
    virtual void Accept(ItemVisitor * visitor) = 0;

    /**
     * Gets the angle of the item
     * @return
     */
    double GetAngle(){ return mAngle; }

    /**
     * virtual Obliterate function for LimpetSparty
     * @param body
     * @return
     */
    virtual bool Obliterate(b2Body *body) {return false;}

    /**
     * virtual GetBody function for all items
     * @return
     */
    virtual b2Body* GetBody() {return nullptr;}

};

#endif //PROJECT1_ITEM_H
