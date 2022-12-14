/**
 * @file GameView.h
 * @author Will Morant, Joey Vesche
 *
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
    Game mGame;

    /// Are the outlines on?
    bool mOutlines = false;
    /// Time of the game
    double mTime = 0;

    /// The Angry Sparty we are currently shooting
    std::shared_ptr<AngrySparty> mShooting;

    /// The timer that allows for animation
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    void OnLeftDown(wxMouseEvent &event);
    void OnLeftUp(wxMouseEvent &event);
    void OnMouseMove(wxMouseEvent &event);

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

    //
    //  Load item
    //
    void LoadItems(wxCommandEvent& event);



    void OnTimeGo(wxTimerEvent& event);

    b2Vec2 ToVirtual(int x, int y);

public:
    void Initialize(wxFrame* parent);

    void AddMenus(wxFrame* mainFrame, wxMenuBar *menuBar, wxMenu* viewMenu);

    /**
     * Stop the timer so the window can close
     */
    void Stop() {mTimer.Stop();}
};

#endif //PROJECT1_GAMEVIEW_H
