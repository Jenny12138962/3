#include "mainwindow.h"
#include "ui_mainwindow.h"
#define M 100
#include <QPainter>
#include <QMouseEvent>
#include <math.h>
#include <QMessageBox>
#include<QDebug>
#include <QTimer>
#include"chess.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
     , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ser=new QTcpServer;
    ser->listen(QHostAddress::AnyIPv4,8888);
    connect(ser,&QTcpServer::newConnection,this,&MainWindow::Con);

    // 设置棋盘大小
    setFixedSize(M * 2 + 35 * 20,M * 2 + 35 * 20);
    // 开始游戏
    game = new chess;
    chesstype = AI;
    game->status = PLAYING;
    game->start(chesstype);
    update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{    // 绘制棋盘
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    for (int i = 0; i < 20 + 1; i++)
    {
        // 从左到右，第(i+1)条竖线
        painter.drawLine(100 + 35 * i, 100, 100 + 35 * i, size().height() - 100);
        // 从上到下，第（i+1)条横线
        painter.drawLine(100, 100 + 35 * i, size().width() - 100, 100 + 35 * i);
    }
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    // 绘制落子标记
    if (Rowclick > 0 && Rowclick < 20 &&Colclick > 0 && Colclick < 20 &&game->mapGV[Rowclick][Colclick] == 0)
    {
        if (game->player)
            brush.setColor(Qt::black);
        else
            brush.setColor(Qt::white);
        painter.setBrush(brush);
        painter.drawRect(100 + 35 * Colclick - 6 / 2, 100 + 35 * Rowclick - 6 / 2, 6, 6);
    }

    // 绘制棋子
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
        {
            if (game->mapGV[i][j] == 1)//黑棋
            {
                brush.setColor(Qt::black);
                painter.setBrush(brush);
                painter.drawEllipse(M + 35 * j - 15, M + 35 * i - 15, 30, 30);
            }
            else if (game->mapGV[i][j] == -1)
            {//白棋
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(M + 35 * j - 15, M + 35 * i - 15, 30, 30);
            }
        }

    // 判断输赢
    if (Rowclick > 0 && Rowclick < 20 &&Colclick > 0 && Colclick < 20 &&(game->mapGV[Rowclick][Colclick] == 1 ||game->mapGV[Rowclick][Colclick] == -1))
    {
        if(game->isFour(Rowclick, Colclick) && game->status == PLAYING&&game->mapGV[Rowclick][Colclick] == 1){
            game->status=WIN;
            QMessageBox::StandardButton btnValue = QMessageBox::information(this, "六子棋", "白棋胜利!");

            if (btnValue == QMessageBox::Ok)
            {
                game->start(chesstype);
                game->status = PLAYING;
            }
        }
        if(game->isFive(Rowclick, Colclick) && game->status == PLAYING&&game->mapGV[Rowclick][Colclick] == 1){
            game->status=WIN;

            QMessageBox::StandardButton btnValue = QMessageBox::information(this, "六子棋",  "白棋胜利!");

            if (btnValue == QMessageBox::Ok)
            {
                game->start(chesstype);
                game->status = PLAYING;
            }
        }
        if (game->winorlose(Rowclick, Colclick) && game->status == PLAYING&&game->mapGV[Rowclick][Colclick] == 1)
        {
            game->status = WIN;
            QMessageBox::StandardButton btnValue = QMessageBox::information(this, "六子棋", "黑棋胜利!");
            // 重置游戏状态
            if (btnValue == QMessageBox::Ok)
            {
                game->start(chesstype);
                game->status = PLAYING;
            }
        }
        if (game->winorlose(Rowclick, Colclick) && game->status == PLAYING&&game->mapGV[Rowclick][Colclick] ==-1){
             game->status = WIN;
              QMessageBox::StandardButton btnValue = QMessageBox::information(this, "六子棋", "白棋胜利!");
              if (btnValue == QMessageBox::Ok)
              {
                  game->start(chesstype);
                  game->status = PLAYING;
              }
        }
    }
    if (game->isDead())
    {
        QMessageBox::StandardButton btnValue = QMessageBox::information(this, "六子棋", "和棋!");
        if (btnValue == QMessageBox::Ok)
        {
            game->start(chesstype);
            game->status = PLAYING;
        }

    }

}
void MainWindow::Con()
{
    QTcpSocket *socket=ser->nextPendingConnection(); //创建socket连接

    QHostAddress clientAddress =socket->peerAddress();
    quint16 clientPort=socket->peerPort();

    ui->addressLineEdit->setText(clientAddress.toString());
    ui->portlineEdit->setText(QString::number(clientPort));

    connect(socket,&QTcpSocket::readyRead,this,&MainWindow::dealData);
}

void MainWindow::dealData()
{
    QTcpSocket *socket=(QTcpSocket *)sender(); //获取信号的发出者

    ui->textEdit->setText(QString(socket->readAll()));
}
void MainWindow::mouseMoveEvent(QMouseEvent *mouse)
{
    int x = mouse->x();
    int y = mouse->y();
    if (x >= M + 35 / 2 &&x < size().width() - M - 35 / 2  &&y >= M + 35 / 2 &&y < size().height()- M - 35 / 2)
    {
        // 获取最近的左上角的点
        int col = (x - M) / 35;
        int row = (y - M) / 35;
        Rowclick = -1; // 初始化最终的值
        Colclick = -1;
        sPos = false;
        Rowclick = row;
        Colclick = col;
        if (game->mapGV[Rowclick][Colclick]==0) {
            sPos = true;
        }
        // 存了坐标后也要重绘
        update();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
    if (sPos == false)
        return;
    else sPos = false;

    if(chesstype==PERSON){//人人模式
        if (Rowclick != -1 && Colclick != -1 && game->mapGV[Rowclick][Colclick] == 0)
        {
            game->updateMap(Rowclick, Colclick);
            update();
        }
    }

    else if (chesstype == AI) { //人机模式
        // AI 下棋
        if (Rowclick != -1 && Colclick != -1 && game->mapGV[Rowclick][Colclick] == 0)
        {
            game->updateMap(Rowclick, Colclick);
            update();
        }
        QTimer::singleShot(300, this, SLOT(chessAI()));
    }
}

void MainWindow::chessAI()
{
    if(chesstype==AI){
        game->actAI(Rowclick, Colclick);
        update();
    }
}


void MainWindow::on_btn_PVP_clicked()
{
    chesstype=PERSON;
    game->start(chesstype);
    game->status = PLAYING;
}

void MainWindow::on_btn_PVC_clicked()
{
    chesstype=AI;
    game->start(chesstype);
    game->status = PLAYING;
}

void MainWindow::on_btn_CVC_clicked()
{
    game->actAI(Rowclick, Colclick);
    update();
}

void MainWindow::on_radioButton_clicked()
{
    game->start(chesstype);
    game->status = PLAYING;
    game->player = true;
}

void MainWindow::on_radioButton_2_clicked()
{
   game->status = PLAYING;
   game->start(chesstype);
   game->actAIAfter(Rowclick, Colclick);
   game->player = false;
   update();
}
