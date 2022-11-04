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
class AngrySparty;
class Shooter;
class LimpetSparty;

/**
 * A parent class for an item visitor
 */
class ItemVisitor {
private:

public:
    virtual ~ItemVisitor(){}

     /**
      * Visit a block object
      * @param block
      */
     virtual void VisitBlock(Block* block){}

     /**
      * Visit a poly object
      * @param poly
      */
    virtual void VisitPoly(Poly* poly){}
    /**
     * Visit a foe object
     * @param foe
     */
    virtual void VisitFoe(Foe* foe){}
    /**
     * Visit a sparty object
     * @param sparty
     */
    virtual void VisitSparty(AngrySparty* sparty){}
    /**
     * visit a shooter object
     * @param shooter
     */
    virtual void VisitShooter(Shooter * shooter) {}
    /**
     * visit a limpet object
     * @param limpet
     */
    virtual void VisitLimpet(LimpetSparty* limpet) {}
};

#endif //PROJECT1_ITEMVISITOR_H
