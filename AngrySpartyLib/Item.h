#include <wx/xml/xml.h>
#include <wx/graphics.h>
/**
 * @file Item.h
 * @author Joseph Pauls
 *
 * The underlying base class for all items in the game
 */

class Game;
#ifndef PROJECT1_ITEM_H
#define PROJECT1_ITEM_H
/**
 * Base Class for items used in the game
 */
class Item {
private:
    /// The game this Item is contained in
    Game *mGame;

    /// Item location in the game
    double mX = 0;
    double mY = 0;

    /// The underlying Item image
    std::unique_ptr<wxImage> mItemImage;

    /// The displayable bitmap for this Item
    std::unique_ptr<wxBitmap> mItemBitmap;

protected:
    /// game constructor
    /// \param game
    /// \param filename
    Item(Game *game, const std::wstring &filename);

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


    virtual wxXmlNode* XmlSave(wxXmlNode* node);

    virtual void XmlLoad(wxXmlNode* node);



    /**
    * Handle updates for animation
    * @param elapsed The time since the last update
    */
    virtual void Update(double elapsed) {}

    /**
     * Get the pointer to the Game object
     * @return Pointer to Game object
     */
    Game *GetGame() {return mGame; }

    /**
    * Get the width of the object
    * @return int representing the width
    */
    int GetWidth() const { return mItemBitmap->GetWidth(); }

    /**
     * Get the height of the object
     * @return int representing the height
     */
    int GetHeight() const {return mItemBitmap->GetHeight(); }



};

#endif //PROJECT1_ITEM_H
