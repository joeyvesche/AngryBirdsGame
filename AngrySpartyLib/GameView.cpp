/**
 * @file GameView.cpp
 * @author Will Morant
 * @author Joey Vesche
 * @author Joseph Pauls
 * @author Yuqi Pan
 */
#include "pch.h"
#include "GameView.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include <iostream>
#include "ids.h"
#include "Block.h"
#include "SlingShot.h"
#include "Consts.h"
#include <memory>
#include "ShooterVisitor.h"
#include <algorithm>

/// Frame duration in seconds
const double FrameDuration = 1.0/60.0;

const double ShooterMaximumNegativePullAngle = -1.7;

/// Pull angles from +pi to this value are allowed
const double ShooterMinimumPositivePullAngle = 2.42;


/**
 * Add menus specific to the view
 * @param mainFrame The main frame that owns the menu bar
 * @param menuBar The menu bar to add menus to
 * @param viewMenu The view menu, so we can add to it if we wish
 */
void GameView::AddMenus(wxFrame* mainFrame, wxMenuBar *menuBar, wxMenu* viewMenu)
{
    viewMenu->Append(IDM_DEBUGVIEW, L"&Debug View", L"box2d debug view display", wxITEM_CHECK);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnDebugView, this, IDM_DEBUGVIEW);
    mainFrame->Bind(wxEVT_UPDATE_UI, &GameView::OnUpdateDebugView, this, IDM_DEBUGVIEW);
}

/**
 * Initialize the Game view class.
 * @param parent The parent window for this class
 */
void GameView::Initialize(wxFrame* parent)
{
    Create(parent, wxID_ANY,
            wxDefaultPosition, wxDefaultSize,
            wxFULL_REPAINT_ON_RESIZE);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &GameView::OnPaint, this);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLoadLevelZero, this,
            IDM_LOADLEVELZERO);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLoadLevelOne, this,
            IDM_LOADLEVELONE);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLoadLevelTwo, this,
            IDM_LOADLEVELTWO);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLoadLevelThree, this,
            IDM_LOADLEVELTHREE);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::LoadItems, this, wxID_OPEN);

    Bind(wxEVT_LEFT_DOWN, &GameView::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &GameView::OnLeftUp, this);
    Bind(wxEVT_MOTION, &GameView::OnMouseMove, this);
    Bind(wxEVT_TIMER, &GameView::OnTimeGo, this);

    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);
    mStopWatch.Start();

}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void GameView::OnPaint(wxPaintEvent& event)
{

    // Update until the game time matches
    // the current time.
    auto newTime = mStopWatch.Time() * 0.001;
    while(mTime < newTime)
    {
        mTime += FrameDuration;
        mGame.Update(FrameDuration);
        Refresh();
    }


    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    auto size = GetClientSize();

    auto graphics =
            std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create( dc));
    graphics->SetInterpolationQuality(wxINTERPOLATION_BEST);

    mGame.OnDraw(graphics, size.GetWidth(), size.GetHeight());

}

/**
 * Convert wxWidgets coordinates to our virtual coordinate system
 *
 * @param x x position in wxWidgets coordinates in pixels
 * @param y y position in wxWidgets coordinates in pixels
 * @return position in the virtual coordinate system
 */
b2Vec2 GameView::ToVirtual(int x, int y)
{
    auto clientSize = GetClientSize();
    double width = clientSize.x, height = clientSize.y;

    b2Vec2 playingAreaSize = b2Vec2(mGame.GetWidth(), mGame.GetHeight());
    playingAreaSize *= Consts::MtoCM;

    auto scaleX = playingAreaSize.y / height;
    auto scaleY = playingAreaSize.x / width;
    auto scale = std::max(scaleX, scaleY);

    auto playingAreaPx = (1 / scale) * playingAreaSize;

    b2Vec2 originPx(width / 2, -(height + playingAreaPx.y) / 2);
    b2Vec2 clickPx(x, -y);
    return scale * (clickPx - originPx);
}

/**
 * Handle the left mouse button down event
 * @param event Mouse event
 */
void GameView::OnLeftDown(wxMouseEvent &event)
{
    // do nothing if we're not ready to pull back
    if (!mGame.Ready()) return;

    // check if game is ready and item clicked on was the sparty on the shooter
    ShooterVisitor shooterVisitor;
    mGame.GetLevel()->Accept(&shooterVisitor);
    auto shooter = shooterVisitor.Get();

    auto virtualCoords = ToVirtual(event.GetX(), event.GetY());

    std::shared_ptr<AngrySparty> hit = nullptr;

    for (auto itr = mGame.GetLevel()->SpartyBegin(); itr != mGame.GetLevel()->SpartyEnd(); ++itr)
    {
        if ((*itr)->HitTest(virtualCoords.x, virtualCoords.y))
        {
            hit = *itr;
        }
    }

    if (hit != nullptr && hit == shooter->GetLoadedSparty())
    {
        mShooting = hit;
    }
}

/**
 * Handle the left mouse button up event
 * @param event Mouse event
 */
void GameView::OnLeftUp(wxMouseEvent &event)
{
    if (mShooting != nullptr)
    {
        mGame.Shoot();
        mShooting = nullptr;
    }
}

/**
 * Handle the mouse move event
 * @param event Mouse event
 */
void GameView::OnMouseMove(wxMouseEvent &event)
{
    if (mShooting != nullptr)
    {
        // grab where the current loaded sparty and mouse position
        ShooterVisitor shooterVisitor;
        mGame.GetLevel()->Accept(&shooterVisitor);
        Shooter * shooter = shooterVisitor.Get();

        std::shared_ptr<AngrySparty> sparty = shooter->GetLoadedSparty();
        auto newLoc = (1 / Consts::MtoCM) * ToVirtual(event.GetX(), event.GetY());

        // clamp the rotation and length of the pull
        auto midpoint = shooter->GetArmMidpoint();
        auto pullVec = newLoc - midpoint;

        if (pullVec.Length() > shooter->GetMaxPull())
        {
            pullVec.Normalize();
            pullVec *= shooter->GetMaxPull();
        }

        auto rotationRad = std::atan2(pullVec.y, pullVec.x);

        if (rotationRad < 0 && rotationRad > ShooterMaximumNegativePullAngle)
        {
            pullVec = pullVec.Length() * b2Vec2(std::cos(ShooterMaximumNegativePullAngle),
                                                std::sin(ShooterMaximumNegativePullAngle));
        } else if (rotationRad > 0 && rotationRad < ShooterMinimumPositivePullAngle)
        {
            pullVec = pullVec.Length() * b2Vec2(std::cos(ShooterMinimumPositivePullAngle),
                                                std::sin(ShooterMinimumPositivePullAngle));
        }

        // set the sparty to the next location
        newLoc = midpoint + pullVec;
        sparty->SetLocation(newLoc.x, newLoc.y);
        sparty->GetBody()->SetTransform(newLoc, sparty->GetAngle());
    }
}

/**
 * Function to set/unset debug view
 * @param event Mouse event
 */
void GameView::OnDebugView(wxCommandEvent& event)
{
    mOutlines = !mOutlines;

    mGame.Debug(mOutlines);
}

/**
 * Update handler for View>Debug View menu option
 * @param event Update event
 */
void GameView::OnUpdateDebugView(wxUpdateUIEvent& event)
{
    event.Check(mOutlines);
}

/**
 * Event handler for loading level zero
 * @param event command event (menu push)
 */
void GameView::OnLoadLevelZero(wxCommandEvent& event)
{
    mGame.SetLevel(0);
    Refresh();
}

/**
 * Event handler for loading level one
 * @param event command event (menu push)
 */
void GameView::OnLoadLevelOne(wxCommandEvent& event)
{
    mGame.SetLevel(1);
    Refresh();
}

/**
 * Event handler for loading level two
 * @param event command event (menu push)
 */
void GameView::OnLoadLevelTwo(wxCommandEvent& event)
{
    mGame.SetLevel(2);
    Refresh();
}

/**
 * Event handler for loading level three
 * @param event command event (menu push)
 */
void GameView::OnLoadLevelThree(wxCommandEvent& event)
{
    mGame.SetLevel(3);
    Refresh();
}

/**
 *  Load the Items
 * @param event Mouse event
 */
void GameView::LoadItems(wxCommandEvent& event)
{
    wxFileDialog loadFileDialog(this, _("Load Game file"), "", "",
            "Aquarium Files (*.xml)|*.xml", wxFD_OPEN);
    if (loadFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    auto filename = loadFileDialog.GetPath();

    mGame.Load(filename);
    Refresh();
}

/**
 * Refresh on Time
 * @param event Mouse event
 */
void GameView::OnTimeGo(wxTimerEvent& event)
{
    Refresh();
}



