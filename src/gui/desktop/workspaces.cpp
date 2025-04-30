#include <fstream>

#include "./ui_gamewindow.h"
#include "gamewindow.h"

void GameWindow::on_gamesList_itemDoubleClicked(QListWidgetItem *item) {
  active_game = ui->gamesList->row(item);
  if (active_game < 0 || active_game > ACT_GAMES_AMO)
    textIndication("Error in game defigning: restart the game.");
  else {
    if (isFromFirstGroup(item)) ui->workSpaces->setCurrentIndex(1);
  }
}

bool GameWindow::isFromFirstGroup(const QListWidgetItem *item) const {
  return ui->gamesList->row(item) == 1 || ui->gamesList->row(item) == 0;
}

void GameWindow::on_workSpaces_currentChanged(int arg1) {
  switch (arg1) {
    case 0:
      firstWorkSpaceInitial();
      break;
    case 1:
      secondWorkSpaceInitial();
      break;
    case 2:
      thirdWorkSpaceInitial();
      break;
    default:
      textIndication(
          QString("Unexpected error:chosen work space - ").arg(arg1));
      firstWorkSpaceInitial();
      break;
  }
}

void GameWindow::setNoteFile() {
  note_file = nullptr;
  switch (active_game) {
    case 0:
      note_file = TTT_ctrl_file;
      break;
    case 1:
      note_file = TSS_ctrl_file;
      break;
    default:
      note_file = "nan";
      break;
  }
}

void GameWindow::firstWorkSpaceInitial() {
  active_game = -1;
  winNameSetter();
  ui->infoPoint->setToolTip("Double click to select game");
  ui->toSelectionButton->hide();
}

void GameWindow::secondWorkSpaceInitial() {
  ui->toSelectionButton->show();
  ui->controlesTable->show();
  ui->controlesTable->setRowCount(0);
  ui->controlesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->controlesTable->setSelectionMode(QAbstractItemView::NoSelection);

  winNameSetter();
  ui->infoPoint->setToolTip("Press Start button to start");

  int cur_row = 0;
  setNoteFile();
  std::ifstream ifs(note_file);
  if (ifs.is_open()) {
    std::string input_str;
    while (!ifs.eof()) {
      getline(ifs, input_str);
      if (input_str.empty()) continue;
      ui->controlesTable->insertRow(cur_row);
      ui->controlesTable->setItem(cur_row, 0,
                                  new QTableWidgetItem(input_str.c_str()));
      getline(ifs, input_str);
      ui->controlesTable->setItem(cur_row, 1,
                                  new QTableWidgetItem(input_str.c_str()));
      cur_row++;
    }
    ifs.close();
  } else
    ui->controlesTable->hide();
}

void GameWindow::thirdWorkSpaceInitial() {
  QString str;
  std::ifstream ifs(note_file);
  if (ifs.is_open()) {
    std::string input_str;
    while (!ifs.eof()) {
      getline(ifs, input_str);
      if (input_str.empty()) continue;
      str += input_str.c_str();
      str += " - ";
      getline(ifs, input_str);
      str += input_str.c_str();
      if (!ifs.eof()) str += "\n";
    }
    ifs.close();
  } else
    str = NOINFO;

  ui->infoPoint->setToolTip(str);

  getViewReady();

  ui->toSelectionButton->hide();  // Will be needed in future versions
}

void GameWindow::winNameSetter() {
  switch (active_game) {
    case 0:
      this->setWindowTitle("The Te-Tris");
      break;
    case 1:
      this->setWindowTitle("The S-Snake (classic)");
      break;
    case 2:
      this->setWindowTitle("The S-Snake (borderless)");
      break;
    case 3:
      this->setWindowTitle("The Big-tac-toe");
      break;
    case 4:
      this->setWindowTitle("The Sudoku-doki");
      break;
    default:  // inc -1
      this->setWindowTitle("Games dodecahedron");
      break;
  }
}

void GameWindow::on_startButton_pressed() {
  ui->workSpaces->setCurrentIndex(2);
}

void GameWindow::gameOverScreen(bool victory) {
  ui->gameResultLabel->show();
  ui->gameResultLabel->setText((victory) ? "You Won!" : "Game Over");
}
