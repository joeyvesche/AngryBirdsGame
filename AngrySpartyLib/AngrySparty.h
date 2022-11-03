/**
 * @file AngrySparty.h
 * @author Will Morant
 *
 * AngrySparty Base Class
 */

#ifndef PROJECT1_ANGRYSPARTY_H
#define PROJECT1_ANGRYSPARTY_H

#include "Item.h"
#include "Level.h"
#include "ItemBody.h"
#include <b2_body.h>
#include "Consts.h"


/**
 * Base class that describes any AngrySparty Object
 */
class AngrySparty: public Item {
private:
        ///Body of the AngrySparty object
        b2Body* mBody;

public:

    AngrySparty(Level *level, const std::wstring &filename);

    /// Default constructor (disabled)
    AngrySparty() = delete;

    /// Copy constructor (disabled)
    AngrySparty(const AngrySparty &) = delete;

    /// Assignment operator
    void operator=(const AngrySparty &) = delete;

    /**
     * Draw this item
     * @param dc Device context to draw on
     */
     void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
     void SetBody(Level *level, int key);
     b2Body* GetBody() override {return mBody;}

     virtual std::pair<double,float> GetConstants() = 0;
     void Accept(ItemVisitor * visitor) override;

     /**
      *
      * @param x
      * @param y
      * @return
      */
     bool HitTest(int x, int y) override
     {
         b2Vec2 click(x, y);
         b2Vec2 posCM = Consts::MtoCM * mBody->GetPosition();
         auto length = (click - posCM).Length();
         auto radius = Consts::MtoCM * GetConstants().first;
         return length < radius;
     }
     void SetDynamic();
};

#endif //PROJECT1_ANGRYSPARTY_H
