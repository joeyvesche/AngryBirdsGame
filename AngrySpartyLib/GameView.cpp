/**
 * @file GameView.cpp
 * @author Will Morant
 * @author Joey Vesche
 * @author Joseph Pauls
 */
#include "pch.h"
#include "GameView.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include "ids.h"
#include "Block.h"
#include "Game.h"
#include "SlingShot.h"
#include "Consts.h"
#include <memory>


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

    /// Load all of the levels when the game is launched and store them for later use.
    mGame.Load(L"levels/level0.xml");
    auto Level0 = mGame.GetItems();
    mGame.SetLevels(Level0);

    mGame.Load(L"levels/level1.xml");
    auto Level1 = mGame.GetItems();
    mGame.SetLevels(Level1);

    mGame.Load(L"levels/level2.xml");
    auto Level2 = mGame.GetItems();
    mGame.SetLevels(Level2);

    mGame.Load(L"levels/level3.xml");
    auto Level3 = mGame.GetItems();
    mGame.SetLevels(Level3);


    /**
     * Might need these later for moving objects
     * --
    Bind(wxEVT_TIMER, &GameView::OnTimer, this);
    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);
    mStopWatch.Start();
     * --
     */
    TestAdd();

}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void GameView::OnPaint(wxPaintEvent& event)
{
    /**
     * May need these later for moving objects
    /// Compute the time that has elapsed
    /// since the last call to OnPaint.
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
     */

    /**
     * Might need this later for moving objects
    mTime = newTime;
     */

    ///mGame.Update(elapsed); - Uncomment when Game class is initialized

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
 * Handle the left mouse button down event
 * @param event
 */
void GameView::OnLeftDown(wxMouseEvent &event)
{

}

/**
 * Handle the left mouse button up event
 * @param event
 */
void GameView::OnLeftUp(wxMouseEvent &event)
{

}

/**
 * Handle the mouse move event
 * @param event
 */
void GameView::OnMouseMove(wxMouseEvent &event)
{

}

/**
 * Function to set/unset debug view
 * @param event  command event
 */
void GameView::OnDebugView(wxCommandEvent& event)
{
    mOutlines = !mOutlines;
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
    mGame.SetItems(mGame.GetLevels()[0]);
    Refresh();
}

/**
 * Event handler for loading level one
 * @param event command event (menu push)
 */
void GameView::OnLoadLevelOne(wxCommandEvent& event)
{
    mGame.SetItems(mGame.GetLevels()[1]);
    Refresh();
}

/**
 * Event handler for loading level two
 * @param event command event (menu push)
 */
void GameView::OnLoadLevelTwo(wxCommandEvent& event)
{
    mGame.SetItems(mGame.GetLevels()[2]);
    Refresh();
}

/**
 * Event handler for loading level three
 * @param event command event (menu push)
 */
void GameView::OnLoadLevelThree(wxCommandEvent& event)
{
    mGame.SetItems(mGame.GetLevels()[3]);
    Refresh();
}

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

void GameView::TestAdd()
{
    const std::wstring filename = L"elementStone047.png";
    auto item = std::make_shared<Block>(&mGame, filename);
    mGame.Add(item);
    item->SetLocation(0,100);
    Refresh();

}


