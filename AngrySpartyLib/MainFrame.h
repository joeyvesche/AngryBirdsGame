/**
 * @file MainFrame.h
 * @author Will Skaggs
 *
 * The main window of the application
 */

#ifndef PROJECT1_MAINFRAME_H
#define PROJECT1_MAINFRAME_H

class GameView;
/**
 * The main (top-level) frame of the application
 */
class MainFrame : public wxFrame {
private:
    GameView *mGameView;
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

public:
    void Initialize();
};

#endif //PROJECT1_MAINFRAME_H
