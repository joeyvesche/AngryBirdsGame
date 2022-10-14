/**
 * @file GameView.h
 * @author Will Morant
 * GameView class
 */

#ifndef PROJECT1_GAMEVIEW_H
#define PROJECT1_GAMEVIEW_H
#include "Game.h"
/**
 * View class for the AngrySparty Game
 */
class GameView: public wxWindow {
private:
    void OnPaint(wxPaintEvent& event);
    /// Game class object

    Game  mGame; //- Uncomment when Game class is initialized

    /// Any Item we are currently dragging
    ///std::shared_ptr<int> mGrabbedObject; - Uncomment when Object class is created

    /**
     * Might need these later for object movement
    /// The timer that allows for animation
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    long mTime = 0;
     */

    bool mOutlines = false;

    void OnLeftDown(wxMouseEvent &event);
    void OnLeftUp(wxMouseEvent &event);
    void OnMouseMove(wxMouseEvent &event);
    /**
     * Might need this later for object movement
    void OnTimer(wxTimerEvent& event);
     */

    //
    // Level loading functions
    //
    void OnLoadLevelZero(wxCommandEvent& event);
    void OnLoadLevelOne(wxCommandEvent& event);
    void OnLoadLevelTwo(wxCommandEvent& event);
    void OnLoadLevelThree(wxCommandEvent& event);

    //
    //Debug View functions
    //
    void OnDebugView(wxCommandEvent& event);
    void OnUpdateDebugView(wxUpdateUIEvent& event);


public:
    void Initialize(wxFrame* parent);

    void AddMenus(wxFrame* mainFrame, wxMenuBar *menuBar, wxMenu* viewMenu);

};

#endif //PROJECT1_GAMEVIEW_H
