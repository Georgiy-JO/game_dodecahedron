#include "gamewindow.h"

#include "./ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::GameWindow),
      timer(new QTimer(this)),
      main_scene(this),
      second_scene(this) {
  ui->setupUi(this);

  QToolTip::setFont(QFont("Arial", 12, QFont::Bold));

#ifdef TE_TRIS
  deactivateItem(ui->gamesList->item(1));
#endif
#ifdef S_SNAKE
  deactivateItem(ui->gamesList->item(0));
#endif

  for (int i = ACT_GAMES_AMO + 1; i < GAMES_AMO; i++) {
    deactivateItem(ui->gamesList->item(i));
  }

  firstWorkSpaceInitial();

  qApp->installEventFilter(this);
}

GameWindow::~GameWindow() {
  endGame();
  delete timer;
  delete ui;
}

void GameWindow::deactivateItem(QListWidgetItem *item) {
  QFont strikeTFont = item->font();
  strikeTFont.setStrikeOut(true);
  item->setFont(strikeTFont);
  item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
  item->setForeground(QColor(192, 191, 188));
}

void GameWindow::textIndication(const QString str) {
  ui->indicator->setText(str);
}

void GameWindow::on_toSelectionButton_pressed() {
  if (ui->workSpaces->currentIndex() == 1)
    ui->workSpaces->setCurrentIndex(0);
  else if (ui->workSpaces->currentIndex() == 2) {
    endGame();
    ui->workSpaces->setCurrentIndex(0);
  }
}
