#include "mainwindow.h"
#include"chessform.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    ChessForm w;
    w.show();
    return a.exec();
}
