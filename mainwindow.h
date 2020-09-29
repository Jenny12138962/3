#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPushButton>
#include <QMainWindow>
#include "chess.h"
#include <QNetworkInterface>
#include <QTcpServer>
#include <QHostAddress>
#include <QTcpSocket>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // 绘制
    void paintEvent(QPaintEvent *);

private:
    Ui::MainWindow *ui;
    void Init();
    void InitChess();
    chess *game; // 游戏指针
    Type chesstype; // 游戏类型
    int Rowclick, Colclick; // 存储将点击的位置
    bool sPos = false; // 是否移动到合适的位置，以选中摸个交叉点
    QTcpServer *ser;
protected:
    void mouseMoveEvent(QMouseEvent *mouse);
    void mouseReleaseEvent(QMouseEvent *);
private slots:
    void Con();
    void dealData();
    void chessAI();
    void on_btn_PVP_clicked();
    void on_btn_PVC_clicked();
    void on_btn_CVC_clicked();
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
};
#endif // MAINWINDOW_H
