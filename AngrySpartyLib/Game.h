/**
 * @file Game.h
 * @authors Yuqi Pan, Joey Vesche, Joseph Pauls
 *
 * Base class for the game
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

    double mLevelTime;

    /// Timer used for delays between states and levels
    double mTimer = 0;

    std::vector<std::shared_ptr<Level>> mLevels; ///< A list of all levels
    std::shared_ptr<Level> mLevel; ///< The currently loaded level

    Scoreboard mScore; ///< The scoreboard for the game

    bool mDebug = false;

    std::shared_ptr<Physics> mPhysics;

    /**
     * The states of the game
     *
     * Loading: the 2 second delay at the start of every level
     * Ready: An angry sparty is ready to be shot
     * Wait: the state between shooting an angry sparty and the next turn
     * Success: All foes of a level have been defeated
     * Failure: No angry spartys left, foes still alive
     */
    enum class State {Loading, Ready, Wait, Success, Failure};

    /// the current state of our game
    State mState = State::Loading;

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

    void Update(double elapsed);

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

    /**
     * Determine if the user is able to pull back on the slingshot
     *
     * @return true if the level is ready, false otherwise
     */
    bool Ready() const { return mState == State::Ready; }

    void Accept(ItemVisitor * visitor);

    void SetLevel(int index);

    /// Get the currently loaded level
    std::shared_ptr<Level> GetLevel() { return mLevel; }

    void Debug(bool debug) { mDebug = debug; }

    void Shoot();
};

#endif //PROJECT1_GAME_H
