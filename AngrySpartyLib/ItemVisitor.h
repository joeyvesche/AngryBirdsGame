/**
 * @file ItemVisitor.h
 * @author Joey Vesche
 *
 * Visitor Class for all Objects
 */

#ifndef PROJECT1_ITEMVISITOR_H
#define PROJECT1_ITEMVISITOR_H



// Forward references
class Scoreboard;
class Block;
class Poly;
class Foe;
class AngrySparty;
class Shooter;

class ItemVisitor {
private:

public:
    virtual ~ItemVisitor(){}

    /**
     * Visit a Scoreboard Object
     * @param The scoreboard we are visiting
     */
     virtual void VisitScoreboard(Scoreboard* scoreboard) {}

    /**
    * Visit a Block Object
    * @param The block we are visiting
    */
     virtual void VisitBlock(Block* block){}

    /**
    * Visit a Poly Object
    * @param The poly we are visiting
    */
     virtual void VisitPoly(Poly* poly){}

    /**
    * Visit a Foe Object
    * @param The foe we are visiting
    */
     virtual void VisitFoe(Foe* foe){}

    /**
    * Visit a Sparty Object
    * @param The sparty we are visiting
    */
     virtual void VisitSparty(AngrySparty* sparty){}

    /**
    * Visit a Shooter Object
    * @param The shooter we are visiting
    */
     virtual void VisitShooter(Shooter * shooter) {}
};

#endif //PROJECT1_ITEMVISITOR_H
