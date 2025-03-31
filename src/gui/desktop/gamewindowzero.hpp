#ifndef GAMEWINDOWZERO_HPP
#define GAMEWINDOWZERO_HPP

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class GameWindowZero;
}
QT_END_NAMESPACE

class GameWindowZero : public QMainWindow
{
    Q_OBJECT

public:
    GameWindowZero(QWidget *parent = nullptr);
    ~GameWindowZero();

private:
    Ui::GameWindowZero *ui;
};
#endif // GAMEWINDOWZERO_HPP
