#include "./ui_gamewindow.h"
#include "gamewindow.h"

void GameWindow::getViewReady() {
  main_scene.setupScene(FieldSize_c::Width, FieldSize_c::Height,
                        pixelSizeDecoder(FieldSize_c::RelativeSize));
  QGraphicsScene *scene = const_cast<QGraphicsScene *>(main_scene.getScene());
  ui->mainView->setScene(scene);
  ui->mainView->setFixedSize(scene->width() + 2, scene->height() + 2);

  connect(timer, &QTimer::timeout, this, &GameWindow::displayGameState);
  timer->start(50);

  userInput(UserAction_t::Start, true);
  GameInfo_t info = updateCurrentState();

  if (info.next) {
    second_scene.setupScene(FieldSize_c::Second_Width,
                            FieldSize_c::Second_Height,
                            pixelSizeDecoder(FieldSize_c::Second_RelativeSize));
    scene = const_cast<QGraphicsScene *>(second_scene.getScene());
    ui->secondView->setScene(scene);
    ui->secondView->setFixedSize(scene->width() + 2, scene->height() + 2);
  } else
    ui->secondView->setVisible(false);
  if (info.score < 0) {
    ui->scoreDisplay->setVisible(false);
    ui->scoreTitel->setVisible(false);
  }
  if (info.high_score < 0) {
    ui->recordDisplay->setVisible(false);
    ui->recordTitel->setVisible(false);
  }
  if (info.level < 0) {
    ui->levelDisplay->setVisible(false);
    ui->levelTitel->setVisible(false);
  }

  displayGameState();
}

void GameWindow::displayGameState() {
  ui->gameResultLabel->hide();

  GameInfo_t info = updateCurrentState();
  if (info.field)
    displayScene(main_scene, FieldSize_c::Height, FieldSize_c::Width,
                 const_cast<const int **>(info.field));
  else
    gameOverScreen(info.speed == -1);

  if (info.next)
    displayScene(second_scene, FieldSize_c::Second_Height,
                 FieldSize_c::Second_Width,
                 const_cast<const int **>(info.next));

  ui->scoreDisplay->display(info.score);
  ui->recordDisplay->display(info.high_score);
  ui->levelDisplay->display(info.level);
}

void GameWindow::displayScene(GridScene_ &scene, const int loc_height,
                              const int loc_width, const int **field) {
  if (field) {
    for (int y = 0; y < loc_height; y++) {
      for (int x = 0; x < loc_width; x++) {
        scene.setItem(x, y, field[y][x]);
      }
    }
  }
}

bool GameWindow::eventFilter(QObject *obj, QEvent *event) {
  if (event->type() == QEvent::KeyPress) {
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

    if (ui->workSpaces->currentIndex() == 1) secondWorkSpaceKeyPress(keyEvent);
    if (ui->workSpaces->currentIndex() == 2) thirdWorkSpaceKeyPress(keyEvent);

    return true;  // Prevent other widgets from handling the key
  }
  return QMainWindow::eventFilter(obj, event);  // For other events, pass it on
}

void GameWindow::secondWorkSpaceKeyPress(QKeyEvent *keyEvent) {
  if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return)
    ui->workSpaces->setCurrentIndex(2);
}

void GameWindow::thirdWorkSpaceKeyPress(QKeyEvent *keyEvent) {
  bool flag = 1;
  switch (keyEvent->key()) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
      userInput(UserAction_t::Start, flag);
      break;
    case Qt::Key_Z:
    case Qt::Key_Space:
      userInput(UserAction_t::Action, flag);
      break;
    case Qt::Key_Up:
      userInput(UserAction_t::Up, flag);
      break;
    case Qt::Key_Down:
      userInput(UserAction_t::Down, flag);
      break;
    case Qt::Key_Left:
      userInput(UserAction_t::Left, flag);
      break;
    case Qt::Key_Right:
      userInput(UserAction_t::Right, flag);
      break;
    case Qt::Key_Escape:
    case Qt::Key_Q:
      if (updateCurrentState().field)
        userInput(UserAction_t::Terminate, flag);
      else
        close();
      break;
    case Qt::Key_P:
      userInput(UserAction_t::Pause, flag);
      break;
    default:  // inc Key_Shift
      break;
  }
  displayGameState();
}

void GameWindow::endGame() {
  main_scene.cleanScene();
  second_scene.cleanScene();
  timer->stop();
  if (updateCurrentState().field) {
    userInput(UserAction_t::Terminate, 1);
    userInput(UserAction_t::Terminate, 1);
  }
}
