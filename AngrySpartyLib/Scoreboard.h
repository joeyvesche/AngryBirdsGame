/**
 * @file Scoreboard.h
 * @authors joeyv, Joseph Pauls
 *
 *
 */

#ifndef PROJECT1_SCOREBOARD_H
#define PROJECT1_SCOREBOARD_H
#include "Item.h"
#include "ItemVisitor.h"

class Scoreboard{

private:

    int mLevelScore = 0;
    int mGameScore = 0;


public:
    Scoreboard();

    /// Copy constructor disabled
    Scoreboard(const Scoreboard &) = delete;

    /// Assignment operator
    void operator=(const Scoreboard &) = delete;

    static void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, double width, double height);

    /// Update the game score by adding current level's score
    void UpdateGameScore(){
        mGameScore += mLevelScore;
        mLevelScore = 0; //Prep Level Score by resetting it to 0 for the next level
    };


};

#endif //PROJECT1_SCOREBOARD_H
