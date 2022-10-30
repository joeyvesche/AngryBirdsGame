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
#include "Scoreboard.h"
#include "Physics.h"

class Item;
class ItemVisitor;
/**
 * Class of game
 */
class Game {
private:
    /// scale
    double mScale = 10;
    /// X offset
    double mXOffset = 1;
    /// Y offset
    double mYOffset = 1;

    int mLevelNo = 1;

    std::vector<std::shared_ptr<Level>> mLevels; ///< A list of all levels
    std::shared_ptr<Level> mLevel; ///< The currently loaded level

    Scoreboard mScore; ///< The scoreboard for the game

    bool mDebug = false;

    std::shared_ptr<Physics> mPhysics;
public:
    Game();

    /**
     * Get the width of the aquarium
     * @return Aquarium width in meters
     */
    double GetWidth() const { return mLevel->GetWidth(); }

    /**
     * Get the height of the aquarium
     * @return Aquarium height in meters
     */
    int GetHeight() const { return mLevel->GetHeight(); }

    void Load(const wxString& filename);

    void Clear();

    void Update(double elapsed);

    void Add(std::shared_ptr<Item> item);

    std::shared_ptr<Item> HitTest(int x, int y);

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

    void Accept(ItemVisitor * visitor);

    void SetLevel(int index);

    /// Get the currently loaded level
    std::shared_ptr<Level> GetLevel() { return mLevel; }

    bool isDebug() {return mDebug; }
    void Debug(bool debug) { mDebug = debug; }
};

#endif //PROJECT1_GAME_H
