/**
 * @file DebugDraw.h
 * @author Charles Owen
 *
 * Debugging support to draw the world from the viewpoint of the physics system.
 */

#ifndef ANGRYSPARTY_DEBUGDRAW_H
#define ANGRYSPARTY_DEBUGDRAW_H

#include <b2_draw.h>

/**
 * Debugging support to draw the world from the viewpoint of the physics system.
 */
class DebugDraw : public b2Draw {
private:
    /// Graphics context to draw on
    std::shared_ptr<wxGraphicsContext> mGraphics;

    void SetPenColor(const b2Color& color, int width=1);

    /// Size of a crosshair in meters
    double mCrosshairSize = 0.2;

public:
    DebugDraw(std::shared_ptr<wxGraphicsContext> graphics);

    /// Default constructor (disabled)
    DebugDraw() = delete;

    /// Copy constructor (disabled)
    DebugDraw(const DebugDraw &) = delete;

    /// Assignment operator
    void operator=(const DebugDraw &) = delete;

    void DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) override;
    void DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color)  override;
    void DrawCircle (const b2Vec2 &center, float radius, const b2Color &color) override;
    void DrawSolidCircle (const b2Vec2 &center, float radius, const b2Vec2 &axis, const b2Color &color) override;
    void DrawSegment (const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) override;
    void DrawTransform(const b2Transform &xf) override;
    void DrawPoint (const b2Vec2 &p, float size, const b2Color &color) override;

};

#endif //ANGRYSPARTY_DEBUGDRAW_H
