/**
 * @file Game.h
 * @author Yuqi Pan, Joey Vesche
 *
 *
 */

#ifndef PROJECT1_GAME_H
#define PROJECT1_GAME_H

#include <wx/xml/xml.h>
#include <memory>
#include <string>

class Item;
/**
 * Class of game
 */
class Game {
private:
    /// width of game
    int mWidth = 8;
    /// height of game
    int mHeight = 6;

    /// scale
    double mScale = 10;
    /// X offset
    double mXOffset = 1;
    /// Y offset
    double mYOffset = 1;

    std::unique_ptr<wxBitmap> mBackground;  ///< Background image to use
    std::unique_ptr<wxBitmap> mSlingshot; ///< Slingshot image to use+86+
    /// All of the items to populate our game
    std::vector<std::shared_ptr<Item>> mItems;
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
    void Load(const wxString &filename);
    void Clear();
    void XmlItem(wxXmlNode *node);
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

};

#endif //PROJECT1_GAME_H
