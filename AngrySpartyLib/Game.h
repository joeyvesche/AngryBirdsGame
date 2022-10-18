/**
 * @file Game.h
 * @authors Yuqi Pan, Joey Vesche, Joseph Pauls
 *
 *
 */

#ifndef PROJECT1_GAME_H
#define PROJECT1_GAME_H

#include <wx/xml/xml.h>
#include <memory>
#include <string>

class Item;
class ItemVisitor;
/**
 * Class of game
 */
class Game {
private:
    /// width of game
    double mWidth = 14.22;
    /// height of game
    int mHeight = 8;

    /// scale
    double mScale = 10;
    /// X offset
    double mXOffset = 1;
    /// Y offset
    double mYOffset = 1;

    std::unique_ptr<wxBitmap> mBackground;  ///< Background image to use
    std::unique_ptr<wxBitmap> mSlingshot; ///< Slingshot image to use
    /// All of the items to populate our game
    std::vector<std::shared_ptr<Item>> mItems;

    /// A list holding lists of items, which are the levels
    std::vector<std::vector<std::shared_ptr<Item>>> mLevels;
public:
    Game();

    /**
     * Get the width of the aquarium
     * @return Aquarium width in pixels
     */
    int GetWidth() const { return mWidth; }

    /**
     * Get the height of the aquarium
     * @return Aquarium height in pixels
     */
    int GetHeight() const { return mHeight; }

    void Save(const wxString& filename);

    void Load(const wxString& filename);

    void Clear();

    void XmlItem(wxXmlNode* node);

    void Update(double elapsed);

    void Add(std::shared_ptr<Item> item);

    std::shared_ptr<Item> HitTest(int x, int y);

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

    /**
     * Set width of game to n meters
     * @param meters n
     */
    void SetWidth(int meters) { mWidth = meters; }

    /**
     * Set Height of game to n meters
     * @param meters n
     */
    void SetHeight(int meters) { mHeight = meters; }

    /**
     * A getter for items to be used when loading a level.
     * @return the list of items
     */
    std::vector<std::shared_ptr<Item>> GetItems()
    {
        return mItems;
    };

    /**
     * A getter for Levels to be used when loading a level.
     * @return the list of items
     */
    std::vector<std::vector<std::shared_ptr<Item>>> GetLevels()
    {
        return mLevels;
    }

    /**
     * A setter to set our items list to be used when loading a level
     */
    void SetItems(std::vector<std::shared_ptr<Item>> loadList)
    {
        mItems = loadList;
    };

    /**
     * A setter to create the level list held in Game
     */
    void SetLevels(std::vector<std::shared_ptr<Item>> level)
    {
        mLevels.push_back(level);
    };

    void Accept(ItemVisitor * visitor);
};

#endif //PROJECT1_GAME_H
