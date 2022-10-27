/**
 * @file DebugDraw.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "DebugDraw.h"
#include "Consts.h"
#include <wx/graphics.h>

/**
 * Constructor
 * @param graphics Graphics content to draw on
 */
DebugDraw::DebugDraw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mGraphics = graphics;
}


/**
 * Draw a circle
 *
 * Actually just draws the outline, which is more useful for debugging purposes
 *
 * @param center Center of the circle in meters
 * @param radius Radius in meters
 * @param color Color to draw
 */
void DebugDraw::DrawCircle (const b2Vec2 &center, float radius, const b2Color &color)
{
    SetPenColor(color);
    mGraphics->SetBrush(wxNullBrush);

    double x = center.x * Consts::MtoCM;
    double y = center.y * Consts::MtoCM;
    double r = radius * Consts::MtoCM;

    mGraphics->DrawEllipse(x-r, y-r, r*2, r*2);
}


/**
 * Draw a circle
 * @param center Center of the circle in meters
 * @param radius Radius in meters
 * @param axis Axis to indicate any rotation
 * @param color Color to draw
 */
void DebugDraw::DrawSolidCircle (const b2Vec2 &center, float radius, const b2Vec2 &axis, const b2Color &color)
{
    DrawCircle(center, radius, color);
}

/**
 * Draw a polygon outline.
 * @param vertices Vertices, all in meters
 * @param vertexCount Number of vertices
 * @param color Color to draw
 */
void DebugDraw::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color)
{
    SetPenColor(color);

    auto path = mGraphics->CreatePath();
    path.MoveToPoint(vertices[0].x * Consts::MtoCM, vertices[0].y * Consts::MtoCM);
    for(int i=1; i<vertexCount; i++)
    {
        path.AddLineToPoint(vertices[i].x * Consts::MtoCM, vertices[i].y * Consts::MtoCM);
    }
    path.CloseSubpath();

    mGraphics->SetPen(*wxRED_PEN);
    mGraphics->SetBrush(wxNullBrush);
    mGraphics->StrokePath(path);
}

/**
 * Draw a polygon outline.
 *
 * Actually just draws the outline, which is more useful for debugging purposes
 *
 * @param vertices Vertices, all in meters
 * @param vertexCount Number of vertices
 * @param color Color to draw
 */
void DebugDraw::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color)
{
    DrawPolygon(vertices, vertexCount, color);
}

/**
 * Draw a point as a crosshair
 * @param p Point to draw
 * @param size Size of hte point to draw (not used)
 * @param color Color to draw
 */
void DebugDraw::DrawPoint (const b2Vec2 &p, float size, const b2Color &color)
{
    SetPenColor(color);

    auto x = p.x * Consts::MtoCM;
    auto y = p.y * Consts::MtoCM;

    auto crosshairRange = mCrosshairSize / 2 * Consts::MtoCM;

    mGraphics->StrokeLine(x - crosshairRange, y, x + crosshairRange, y);
    mGraphics->StrokeLine(x, y - crosshairRange, x, y + crosshairRange);
}

/**
 * Draw a 2D transform as a rotated crosshair
 * @param xf The transform to draw
 */
void DebugDraw::DrawTransform(const b2Transform &xf)
{
    // The translation position relative to the origin and scaled
    auto x = xf.p.x * Consts::MtoCM;
    auto y = xf.p.y * Consts::MtoCM;

    // How large the crosshairs should be
    float crosshairRange = float( mCrosshairSize / 2 * Consts::MtoCM );

    // The sine and cosine of the rotation angle scaled by the length to draw
    auto s = xf.q.s * crosshairRange;    // sin of angle
    auto c = xf.q.c * crosshairRange;    // cos of angle

    // Draw all but the direction to the right
    mGraphics->SetPen(*wxRED_PEN);
    mGraphics->StrokeLine(x - c, y - s, x, y);
    mGraphics->StrokeLine(x - s, y + c, x + s, y - c);

    // Draw that last part to the right in a different color
    mGraphics->SetPen(*wxGREEN_PEN);
    mGraphics->StrokeLine(x, y, x + c, y + s);
}

/**
 * Set a pen with a given box2d color
 * @param color Color to set
 * @param width Pen width in pixels
 */
void DebugDraw::SetPenColor(const b2Color &color, int width)
{
    wxColour clr(int(color.r*255), int(color.g*255), int(color.b*255), int(color.a*255));
    wxPen pen(clr, width);
    mGraphics->SetPen(pen);
}

/**
 * Draw a line segment
 * @param p1 Point 1 in meters
 * @param p2 Point 2 in meters
 * @param color color to drw
 */
void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    SetPenColor(color);

    auto x1 = p1.x * Consts::MtoCM;
    auto y1 = p1.y * Consts::MtoCM;

    auto x2 = p2.x * Consts::MtoCM;
    auto y2 = p2.y * Consts::MtoCM;

    mGraphics->SetPen(*wxRED_PEN);
    mGraphics->StrokeLine(x1, y1, x2, y2);
}


