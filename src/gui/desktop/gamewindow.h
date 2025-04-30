#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QGraphicsView>
#include <QKeyEvent>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QStackedWidget>
#include <QTimer>
#include <QToolTip>

#include "gridscene_/gridscene_.h"

#ifdef TE_TRIS
#include "../../brick_game/tetris/tetris.h"
#endif
#ifdef S_SNAKE
#include "../../brick_game/snake/s-snake.h"
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class GameWindow;
}
QT_END_NAMESPACE

class GameWindow : public QMainWindow {
  Q_OBJECT
 private:
  static constexpr int ACT_GAMES_AMO = 1;
  static constexpr int GAMES_AMO = 5;
  static constexpr const char *TTT_ctrl_file = "data/te-tris_ctrl.txt";
  static constexpr const char *TSS_ctrl_file = "data/s-stake_ctrl.txt";

 public:
  static constexpr const char *NOINFO = "NoInfo";

  GameWindow(QWidget *parent = nullptr);
  ~GameWindow();

 private slots:

  void on_gamesList_itemDoubleClicked(QListWidgetItem *item);
  void on_workSpaces_currentChanged(int arg1);
  void on_toSelectionButton_pressed();
  void on_startButton_pressed();

 private:
  int active_game = -1;
  const char *note_file = nullptr;
  Ui::GameWindow *ui;
  QTimer *timer;
  GridScene_ main_scene;
  GridScene_ second_scene;

  void deactivateItem(QListWidgetItem *item);
  bool isFromFirstGroup(const QListWidgetItem *item) const;
  void firstWorkSpaceInitial();
  void secondWorkSpaceInitial();
  void thirdWorkSpaceInitial();
  void textIndication(const QString str);
  void winNameSetter();
  void setNoteFile();

  void getViewReady();
  void displayGameState();
  void displayScene(GridScene_ &scene, const int height, const int width,
                    const int **field);
  void secondWorkSpaceKeyPress(QKeyEvent *keyEvent);
  void thirdWorkSpaceKeyPress(QKeyEvent *keyEvent);

  void gameOverScreen(bool victory = 0);
  void endGame();

 protected:
  bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif  // GAMEWINDOW_H
