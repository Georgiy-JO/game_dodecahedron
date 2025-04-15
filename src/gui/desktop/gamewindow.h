#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QStackedWidget>
#include <QToolTip>

#include <QGraphicsView>
#include <QTimer>

#include <QKeyEvent>


#include "gridscene_.h"

#ifdef TE_TRIS
#include "../../brick_game/tetris/tetris.h"
#endif
#ifdef S_SNAKE
#include "../../brick_game/snake/s-snake.h"
#endif





// #include "../../brick_game/snake/s-snake.h"           //temp
typedef enum{          //temp
    RelativeSize=0,
    Width=10,
    Height=20,
    Second_RelativeSize=-1,
    Second_Width=4,
    Second_Height=4
}FieldSize_c;
enum UserAction_t{          //temp
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action
} ;











QT_BEGIN_NAMESPACE
namespace Ui {
class GameWindow;
}
QT_END_NAMESPACE

class GameWindow : public QMainWindow
{
    Q_OBJECT
private:
    static constexpr int ACT_GAMES_AMO=1;
    static constexpr int GAMES_AMO=5;
    static constexpr const char* TTT_ctrl_file = "data/te-tris_ctrl.txt";
    static constexpr const char* TSS_ctrl_file = "data/s-stake_ctrl.txt";
    
public:
    static constexpr const char* NOINFO = "NoInfo";
    
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

private slots:

    void on_gamesList_itemClicked(QListWidgetItem *item);
    void on_gamesList_itemDoubleClicked(QListWidgetItem *item);
    void on_workSpaces_currentChanged(int arg1);
    void on_backToGameListButton_pressed();
    void on_startButton_pressed();

private:
    int active_game=-1;
    const char* note_file=nullptr;
    Ui::GameWindow *ui;
    QTimer* timer;
    GridScene_ main_scene;
    GridScene_ second_scene;

    void unactivateItem (QListWidgetItem* item);
    bool isFromFirstGroup(const QListWidgetItem *item) const;
    void secondWorkSpaceInitial();
    void firstWorkSpaceInitial();
    void textIndication(const QString str);
    void winNameSetter();
    void thirdWorkSpaceInitial();
    void setNoteFile();

    void getViewReady();
    void displayGameState();
    // void keyPressEvent(QKeyEvent *event);

    void gameOverScreen();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;


};


#endif // GAMEWINDOW_H
