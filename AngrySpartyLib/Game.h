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
#include "Level.h"

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

    std::vector<Level> mLevels; ///< A list of all levels
    Level mLevel; ///< The currently loaded level

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

    void Accept(ItemVisitor * visitor);
};

#endif //PROJECT1_GAME_H
