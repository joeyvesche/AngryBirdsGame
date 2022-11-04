/**
 * @file LimpetSparty.cpp
 * @author Will Morant
 */

#include "pch.h"
#include "Level.h"
#include "LimpetSparty.h"
#include "LimpetKillVisitor.h"
#include "ItemVisitor.h"

/// Useful Constants
/// The image to use for this sparty
const std::wstring LimpetSpartyImage = L"limpet.png";

/**
 * Limpet Sparty Constructor
 * @param level Level
 */
LimpetSparty::LimpetSparty(Level *level) : AngrySparty(level, LimpetSpartyImage)
{

}

/**
 * Gets the Radius and Velocity Factor
 * @return Pair of Radius and Velocity Factor
 */
std::pair<double,float> LimpetSparty::GetConstants()
{
    return std::pair<double,float>(mLimpetSpartyRadius, mLimpetSpartyVelocityFactor);
}

/**
 * Deletes objects it comes into contact with
 * @param body Body Object
 * @return True if deleted
 */
bool LimpetSparty::Obliterate(b2Body *body)
{
    if (body != nullptr)
    {
        if (mDestroyedItems < 50) {
            LimpetKillVisitor visitor;
            for (auto i = GetLevel()->begin(); i!=GetLevel()->end(); i++) {
                if (body==(*i)->GetBody() && body->GetType()==b2BodyType::b2_dynamicBody) {
                    (*i)->Accept(&visitor);
                    if (visitor.GetKey()==false) {
                        body->GetWorld()->DestroyBody(body);
                        GetLevel()->remove(i);
                        mDestroyedItems++;
                        break;
                    }
                }
            }
            return true;
        }
    }
    return false;
}
/**
 * Accept an item visitor
 * @param visitor
 */
void LimpetSparty::Accept(ItemVisitor* visitor)
{
    visitor->VisitLimpet(this);
}