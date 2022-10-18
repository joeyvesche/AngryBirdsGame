/**
 * @file Scoreboard.h
 * @author joeyv
 *
 *
 */

#ifndef PROJECT1_SCOREBOARD_H
#define PROJECT1_SCOREBOARD_H
#include "Item.h"
#include "ItemVisitor.h"

class Scoreboard : public Item{
public:
    Scoreboard(Game *game);

    /// Default constructor disabled
    Scoreboard() = delete;

    /// Copy constructor disabled
    Scoreboard(const Scoreboard &) = delete;

    /// Assignment operator
    void operator=(const Scoreboard &) = delete;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
  //  virtual void Accept(ItemVisitor* visitor) override {visitor->VisitScoreboard(this);}


};

#endif //PROJECT1_SCOREBOARD_H
