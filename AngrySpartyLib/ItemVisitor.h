/**
 * @file ItemVisitor.h
 * @author joeyv
 *
 *
 */

#ifndef PROJECT1_ITEMVISITOR_H
#define PROJECT1_ITEMVISITOR_H



// Forward references
class Scoreboard;
class Block;
class Poly;
class Foe;
class ItemVisitor {
private:

public:
    virtual ~ItemVisitor(){}

    /**
     * Visit a Scoreboard Object
     * @param The scoreboard we are visiting
     */
     virtual void VisitScoreboard(Scoreboard* scoreboard) {}

     virtual void VisitBlock(Block* block){}

    virtual void VisitPoly(Poly* poly){}
    virtual void VisitFoe(Foe* foe){}

};

#endif //PROJECT1_ITEMVISITOR_H
