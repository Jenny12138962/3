#ifndef CHESSFORM_H
#define CHESSFORM_H
#include"chess.h"
#include"mainwindow.h"
#include <QWidget>

namespace Ui {
class ChessForm;
}
class ChessForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChessForm(QWidget *parent = 0);
    ~ChessForm();

protected:
    void paintEvent(QPaintEvent *);


private:
    Ui::ChessForm *ui;
    MainWindow *myChess;
    void Init();
    bool isDown;
};

#endif // CHESSFORM_H
