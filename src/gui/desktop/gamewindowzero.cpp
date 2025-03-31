#include "gamewindowzero.hpp"
#include "./ui_gamewindowzero.h"

GameWindowZero::GameWindowZero(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindowZero)
{
    ui->setupUi(this);
}

GameWindowZero::~GameWindowZero()
{
    delete ui;
}
