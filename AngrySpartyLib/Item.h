
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

    /// Item location in the level
    double mX = 0;
    double mY = 0;
    double mAngle = 0;
    /// The underlying Item image
    std::shared_ptr<wxImage> mItemImage;

    /// The displayable bitmap for this Item
    std::shared_ptr<wxBitmap> mItemBitmap;

protected:
    /// level constructor
    /// \param level
    /// \param filename
    Item(Level *level, const std::wstring &filename);

public:

    /// Item Destructor
    virtual ~Item();

    /// Test if the item is hit by the mouse
    bool HitTest(int x, int y);

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

    /**
     * Draw this item
     * @param dc Device context to draw on
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /**
    *
    * @param item
    * @return distance between two items
    */
    double DistanceTo(std::shared_ptr<Item> item);


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

    virtual void Accept(ItemVisitor * visitor) = 0;

    double GetAngle(){ return mAngle; }

    virtual bool Obliterate(b2Body *body) {return false;}

    virtual b2Body* GetBody() {return nullptr;}

};

#endif //PROJECT1_ITEM_H
