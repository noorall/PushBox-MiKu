#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    numberOfLevels=15;
    moves=0;
    nowLevel=0;
    ui->lblLevel->setText("当前等级： "+QString::number(nowLevel+1));
    ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
    for (int n = 0; n < numberOfLevels; ++n) {
        for (int x = 0; x < 16; ++x) {
            for (int y = 0; y < 16; ++y) {
                this->levels[n][x][y]=levels[n][x][y];
                if (n==nowLevel){
                    nowContent[x][y]=levels[n][x][y];
                    resetContent[x][y]=levels[n][x][y];
                     if (nowContent[x][y] ==6 || nowContent[x][y] ==7){
                        playerX = x;
                        playerY = y;
                    }
                }
            }
        }
    }
    for (int x = 0; x < 16; ++x) {
        for (int y = 0; y < 16; ++y) {
            nowImgs[y][x] = new QLabel(this);
            nowImgs[y][x]->setGeometry(x*50,y*50,50,50);
        }
    }
    drawLevel();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::drawLevel(){
                /*
                #########################################
                # 地图绘制
                # 0 空地
                # 1 路
                # 2 墙
                # 3 目的地
                # 4 箱子
                # 5 完成的箱子
                # 6 玩家
                # 7 在目的地上的玩家
                #########################################
                */

    for (int j = 0;j < 16; ++j) {
        for (int i = 0; i< 16; ++i) {
            if (nowContent[i][j] == 0){
                nowImgs[i][j]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);}");
            }else if (nowContent[i][j] == 1){
                nowImgs[i][j]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);}");
            }else if (nowContent[i][j] == 2){
                nowImgs[i][j]->setStyleSheet("QLabel{ background-image: url(:/imgs/wall/wall.png);}");
            }else if (nowContent[i][j] == 3){
                nowImgs[i][j]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/place/destination.png);}");
            }else if ( nowContent[i][j] == 4){
                nowImgs[i][j]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/box.png);}");
            }else if ( nowContent[i][j] == 5) {
                nowImgs[i][j]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/completedBox.png);}");
            }else if ( nowContent[i][j] == 6){
                nowImgs[i][j]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/player.png);}");
            }else if ( nowContent[i][j] == 7){
                nowImgs[i][j]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/playerOnDestination.png);}");
            }else{
                nowImgs[i][j]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);}");
            }
        }
    }

}


void MainWindow::keyPressEvent(QKeyEvent *e)
{
    this->setFocus();
    switch (e->key()) {
        case 'W':
        case Qt::Key_Up:
            up();
            break;
        case 'S':
        case Qt::Key_Down:
            down();
            break;
        case 'A':
        case Qt::Key_Left:
            left();
            break;
        case 'D':
        case Qt::Key_Right:
            right();
            break;
        case 'R':
            on_reload_clicked();
            break;
        default :
            break;
    }
}


void MainWindow::up(){


    if (nowContent[playerX - 1][playerY] == 1)//前方是地继续走
    {

        if (nowContent[playerX][playerY] == 6)//当前位置只有人
        {
            nowContent[playerX][playerY] = 1;
            nowContent[playerX - 1][playerY] = 6;
            nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);}");
            nowImgs[playerX - 1][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/player.png);}");
            playerX = playerX - 1;
            moves = moves + 1;
            this->repaint();
            ui->lblMoves->setText("当前步数： "+QString::number(moves)+"");
        }
        else if(nowContent[playerX][playerY] == 7)//当前在目的地上
        {
            nowContent[playerX][playerY] = 3;
            nowContent[playerX - 1][playerY] = 6;
            nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/place/destination.png);}");
            nowImgs[playerX - 1][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/player.png);}");
            playerX = playerX - 1;
            moves = moves + 1;
            this->repaint();
            ui->lblMoves->setText("当前步数： "+QString::number(moves)+"");
        }

    }


    else if(nowContent[playerX - 1][playerY] == 2)//前方是墙不处理
    {

    }


    else if(nowContent[playerX - 1][playerY] == 3)//前方是目标点继续走
    {

        if (nowContent[playerX][playerY] == 6)
        {
            nowContent[playerX][playerY] = 1;
            nowContent[playerX - 1][playerY] = 7;
            nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);}");
            nowImgs[playerX - 1][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/playerOnDestination.png);}");
            playerX = playerX - 1;
            moves = moves + 1;
            this->repaint();
            ui->lblMoves->setText("当前步数： "+QString::number(moves)+"");
        }
        else if(nowContent[playerX][playerY] == 7)
        {
            nowContent[playerX][playerY] = 3;
            nowContent[playerX - 1][playerY] = 7;
            nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/place/destination.png);}");
            nowImgs[playerX - 1][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/playerOnDestination.png);}");
            playerX = playerX - 1;
            moves = moves + 1;
            this->repaint();
            ui->lblMoves->setText("当前步数： "+QString::number(moves)+"");
        }

    }


    else if(nowContent[playerX - 1][playerY] == 4)//前方是箱子
    {

        if(nowContent[playerX-2][playerY] == 1)//箱子前是空地
        {
            if (nowContent[playerX][playerY] == 6)
            {
                nowContent[playerX][playerY] = 1;
                nowContent[playerX - 1][playerY] = 6;
                nowContent[playerX - 2][playerY] = 4;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);}");
                nowImgs[playerX - 1][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/player.png);}");
                nowImgs[playerX - 2][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/box.png);}");
                playerX = playerX - 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： "+QString::number(moves)+"");
            }
            else if(nowContent[playerX][playerY] == 7)
            {
                nowContent[playerX][playerY] = 3;
                nowContent[playerX - 1][playerY] = 6;
                nowContent[playerX - 2][playerY] = 4;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/place/destination.png);}");
                nowImgs[playerX - 1][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/player.png);}");
                nowImgs[playerX - 2][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/box.png);}");
                playerX = playerX - 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： "+QString::number(moves)+"");
            }
        }

        else if(nowContent[playerX-2][playerY] == 3)//箱子前是目的地
        {
            if (nowContent[playerX][playerY] == 6)
            {
                nowContent[playerX][playerY] = 1;
                nowContent[playerX - 1][playerY] = 6;
                nowContent[playerX - 2][playerY] = 5;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);}");
                nowImgs[playerX - 1][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/player.png);}");
                nowImgs[playerX - 2][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/completedBox.png);}");
                playerX = playerX - 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： "+QString::number(moves)+"");
            }
            else if(nowContent[playerX][playerY] == 7)
            {
                nowContent[playerX][playerY] = 3;
                nowContent[playerX - 1][playerY] = 6;
                nowContent[playerX - 2][playerY] = 5;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/place/destination.png);}");
                nowImgs[playerX - 1][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/player.png);}");
                nowImgs[playerX - 2][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/completedBox.png);}");
                playerX = playerX - 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： "+QString::number(moves)+"");
            }
        }

        else//其他情况不可推
        {

        }

    }


    else if(nowContent[playerX - 1][playerY] == 5)//前方是已完成的箱子
    {

        if(nowContent[playerX-2][playerY] == 1)//箱子前是空地
        {
            if (nowContent[playerX][playerY] == 6)
            {
                nowContent[playerX][playerY] = 1;
                nowContent[playerX - 1][playerY] = 7;
                nowContent[playerX - 2][playerY] = 4;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);}");
                nowImgs[playerX - 1][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/playerOnDestination.png);}");
                nowImgs[playerX - 2][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/box.png);}");
                playerX = playerX - 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： "+QString::number(moves)+"");
            }
            else if(nowContent[playerX][playerY] == 7)
            {
                nowContent[playerX][playerY] = 3;
                nowContent[playerX - 1][playerY] = 7;
                nowContent[playerX - 2][playerY] = 4;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/place/destination.png);}");
                nowImgs[playerX - 1][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/playerOnDestination.png);}");
                nowImgs[playerX - 2][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/box.png);}");
                playerX = playerX - 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： "+QString::number(moves)+"");
            }
        }

        else if(nowContent[playerX-2][playerY] == 3)//箱子前是目的地
        {
            if (nowContent[playerX][playerY] == 6)
            {
                nowContent[playerX][playerY] = 1;
                nowContent[playerX - 1][playerY] = 7;
                nowContent[playerX - 2][playerY] = 5;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);}");
                nowImgs[playerX - 1][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/playerOnDestination.png);}");
                nowImgs[playerX - 2][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/completedBox.png);}");
                playerX = playerX - 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： "+QString::number(moves)+"");
            }
            else if(nowContent[playerX][playerY] == 7)
            {
                nowContent[playerX][playerY] = 3;
                nowContent[playerX - 1][playerY] = 7;
                nowContent[playerX - 2][playerY] = 5;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/place/destination.png);}");
                nowImgs[playerX - 1][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/playerOnDestination.png);}");
                nowImgs[playerX - 2][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/completedBox.png);}");
                playerX = playerX - 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： "+QString::number(moves)+"");
            }
        }

        else//其他情况不可推
        {

        }

    }


    else//其他情况不处理
    {

    }
    isWin();
}



void MainWindow::down() {


    if (nowContent[playerX + 1][playerY] == 1)//前方是地继续走
    {

        if (nowContent[playerX][playerY] == 6)//当前位置只有人
        {
            nowContent[playerX][playerY] = 1;
            nowContent[playerX + 1][playerY] = 6;
            nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);}");
            nowImgs[playerX + 1][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/player.png);}");
            playerX = playerX + 1;
            moves = moves + 1;
            this->repaint();
            ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
        }
        else if (nowContent[playerX][playerY] == 7)//当前在目的地上
        {
            nowContent[playerX][playerY] = 3;
            nowContent[playerX + 1][playerY] = 6;
            nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/place/destination.png);}");
            nowImgs[playerX + 1][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/player.png);}");
            playerX = playerX + 1;
            moves = moves + 1;
            this->repaint();
            ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
        }

    }


    else if (nowContent[playerX + 1][playerY] == 2)//前方是墙不处理
    {

    }


    else if (nowContent[playerX + 1][playerY] == 3)//前方是目标点继续走
    {

        if (nowContent[playerX][playerY] == 6)
        {
            nowContent[playerX][playerY] = 1;
            nowContent[playerX + 1][playerY] = 7;
            nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);}");
            nowImgs[playerX + 1][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/playerOnDestination.png);}");
            playerX = playerX + 1;
            moves = moves + 1;
            this->repaint();
            ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
        }
        else if (nowContent[playerX][playerY] == 7)
        {
            nowContent[playerX][playerY] = 3;
            nowContent[playerX + 1][playerY] = 7;
            nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/place/destination.png);}");
            nowImgs[playerX + 1][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/playerOnDestination.png);}");
            playerX = playerX + 1;
            moves = moves + 1;
            this->repaint();
            ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
        }

    }


    else if (nowContent[playerX + 1][playerY] == 4)//前方是箱子
    {

        if (nowContent[playerX + 2][playerY] == 1)//箱子前是空地
        {
            if (nowContent[playerX][playerY] == 6)
            {
                nowContent[playerX][playerY] = 1;
                nowContent[playerX + 1][playerY] = 6;
                nowContent[playerX + 2][playerY] = 4;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);}");
                nowImgs[playerX + 1][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/player.png);}");
                nowImgs[playerX + 2][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/box.png);}");
                playerX = playerX + 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
            }
            else if (nowContent[playerX][playerY] == 7)
            {
                nowContent[playerX][playerY] = 3;
                nowContent[playerX + 1][playerY] = 6;
                nowContent[playerX + 2][playerY] = 4;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/place/destination.png);}");
                nowImgs[playerX + 1][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/player.png);}");
                nowImgs[playerX + 2][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/box.png);}");
                playerX = playerX + 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
            }
        }

        else if (nowContent[playerX + 2][playerY] == 3)//箱子前是目的地
        {
            if (nowContent[playerX][playerY] == 6)
            {
                nowContent[playerX][playerY] = 1;
                nowContent[playerX + 1][playerY] = 6;
                nowContent[playerX + 2][playerY] = 5;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);}");
                nowImgs[playerX + 1][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/player.png);}");
                nowImgs[playerX + 2][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/completedBox.png);}");
                playerX = playerX + 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
            }
            else if (nowContent[playerX][playerY] == 7)
            {
                nowContent[playerX][playerY] = 3;
                nowContent[playerX + 1][playerY] = 6;
                nowContent[playerX + 2][playerY] = 5;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/place/destination.png);}");
                nowImgs[playerX + 1][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/player.png);}");
                nowImgs[playerX + 2][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/completedBox.png);}");
                playerX = playerX + 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
            }
        }

        else//其他情况不可推
        {

        }

    }


    else if (nowContent[playerX + 1][playerY] == 5)//前方是已完成的箱子
    {

        if (nowContent[playerX + 2][playerY] == 1)//箱子前是空地
        {
            if (nowContent[playerX][playerY] == 6)
            {
                nowContent[playerX][playerY] = 1;
                nowContent[playerX + 1][playerY] = 7;
                nowContent[playerX + 2][playerY] = 4;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);}");
                nowImgs[playerX + 1][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/playerOnDestination.png);}");
                nowImgs[playerX + 2][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/box.png);}");
                playerX = playerX + 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
            }
            else if (nowContent[playerX][playerY] == 7)
            {
                nowContent[playerX][playerY] = 3;
                nowContent[playerX + 1][playerY] = 7;
                nowContent[playerX + 2][playerY] = 4;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/place/destination.png);}");
                nowImgs[playerX + 1][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/playerOnDestination.png);}");
                nowImgs[playerX + 2][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/box.png);}");
                playerX = playerX + 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
            }
        }

        else if (nowContent[playerX + 2][playerY] == 3)//箱子前是目的地
        {
            if (nowContent[playerX][playerY] == 6)
            {
                nowContent[playerX][playerY] = 1;
                nowContent[playerX + 1][playerY] = 7;
                nowContent[playerX + 2][playerY] = 5;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);}");
                nowImgs[playerX + 1][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/playerOnDestination.png);}");
                nowImgs[playerX + 2][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/completedBox.png);}");
                playerX = playerX + 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
            }
            else if (nowContent[playerX][playerY] == 7)
            {
                nowContent[playerX][playerY] = 3;
                nowContent[playerX + 1][playerY] = 7;
                nowContent[playerX + 2][playerY] = 5;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/place/destination.png);}");
                nowImgs[playerX + 1][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/playerOnDestination.png);}");
                nowImgs[playerX + 2][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/completedBox.png);}");
                playerX = playerX + 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
            }
        }

        else//其他情况不可推
        {

        }

    }


    else//其他情况不处理
    {

    }

    isWin();
}


void MainWindow::left() {


    if (nowContent[playerX][playerY - 1] == 1)//前方是地继续走
    {

        if (nowContent[playerX][playerY] == 6)//当前位置只有人
        {
            nowContent[playerX][playerY] = 1;
            nowContent[playerX][playerY - 1] = 6;
            nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);}");
            nowImgs[playerX][playerY - 1]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/player.png);}");
            playerY = playerY - 1;
            moves = moves + 1;
            this->repaint();
            ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
        }
        else if (nowContent[playerX][playerY] == 7)//当前在目的地上
        {
            nowContent[playerX][playerY] = 3;
            nowContent[playerX][playerY - 1] = 6;
            nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/place/destination.png);}");
            nowImgs[playerX][playerY - 1]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/player.png);}");
            playerY = playerY - 1;
            moves = moves + 1;
            this->repaint();
            ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
        }

    }


    else if (nowContent[playerX][playerY - 1] == 2)//前方是墙不处理
    {

    }


    else if (nowContent[playerX][playerY - 1] == 3)//前方是目标点继续走
    {

        if (nowContent[playerX][playerY] == 6)
        {
            nowContent[playerX][playerY] = 1;
            nowContent[playerX][playerY - 1] = 7;
            nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);}");
            nowImgs[playerX][playerY - 1]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/playerOnDestination.png);}");
            playerY = playerY - 1;
            moves = moves + 1;
            this->repaint();
            ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
        }
        else if (nowContent[playerX][playerY] == 7)
        {
            nowContent[playerX][playerY] = 3;
            nowContent[playerX][playerY - 1] = 7;
            nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/place/destination.png);}");
            nowImgs[playerX][playerY - 1]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/playerOnDestination.png);}");
            playerY = playerY - 1;
            moves = moves + 1;
            this->repaint();
            ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
        }

    }


    else if (nowContent[playerX][playerY - 1] == 4)//前方是箱子
    {

        if (nowContent[playerX][playerY - 2] == 1)//箱子前是空地
        {
            if (nowContent[playerX][playerY] == 6)
            {
                nowContent[playerX][playerY] = 1;
                nowContent[playerX][playerY - 1] = 6;
                nowContent[playerX][playerY - 2] = 4;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);}");
                nowImgs[playerX][playerY - 1]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/player.png);}");
                nowImgs[playerX][playerY - 2]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/box.png);}");
                playerY = playerY - 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
            }
            else if (nowContent[playerX][playerY] == 7)
            {
                nowContent[playerX][playerY] = 3;
                nowContent[playerX][playerY - 1] = 6;
                nowContent[playerX][playerY - 2] = 4;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/place/destination.png);}");
                nowImgs[playerX][playerY - 1]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/player.png);}");
                nowImgs[playerX][playerY - 2]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/box.png);}");
                playerY = playerY - 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
            }
        }

        else if (nowContent[playerX][playerY - 2] == 3)//箱子前是目的地
        {
            if (nowContent[playerX][playerY] == 6)
            {
                nowContent[playerX][playerY] = 1;
                nowContent[playerX][playerY - 1] = 6;
                nowContent[playerX][playerY - 2] = 5;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);}");
                nowImgs[playerX][playerY - 1]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/player.png);}");
                nowImgs[playerX][playerY - 2]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/completedBox.png);}");
                playerY = playerY - 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
            }
            else if (nowContent[playerX][playerY] == 7)
            {
                nowContent[playerX][playerY] = 3;
                nowContent[playerX][playerY - 1] = 6;
                nowContent[playerX][playerY - 2] = 5;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/place/destination.png);}");
                nowImgs[playerX][playerY - 1]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/player.png);}");
                nowImgs[playerX][playerY - 2]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/completedBox.png);}");
                playerY = playerY - 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
            }
        }

        else//其他情况不可推
        {

        }

    }


    else if (nowContent[playerX][playerY - 1] == 5)//前方是已完成的箱子
    {

        if (nowContent[playerX][playerY - 2] == 1)//箱子前是空地
        {
            if (nowContent[playerX][playerY] == 6)
            {
                nowContent[playerX][playerY] = 1;
                nowContent[playerX][playerY - 1] = 7;
                nowContent[playerX][playerY - 2] = 4;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);}");
                nowImgs[playerX][playerY - 1]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/playerOnDestination.png);}");
                nowImgs[playerX][playerY - 2]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/box.png);}");
                playerY = playerY - 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
            }
            else if (nowContent[playerX][playerY] == 7)
            {
                nowContent[playerX][playerY] = 3;
                nowContent[playerX][playerY - 1] = 7;
                nowContent[playerX][playerY - 2] = 4;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/place/destination.png);}");
                nowImgs[playerX][playerY - 1]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/playerOnDestination.png);}");
                nowImgs[playerX][playerY - 2]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/box.png);}");
                playerY = playerY - 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
            }
        }

        else if (nowContent[playerX][playerY - 2] == 3)//箱子前是目的地
        {
            if (nowContent[playerX][playerY] == 6)
            {
                nowContent[playerX][playerY] = 1;
                nowContent[playerX][playerY - 1] = 7;
                nowContent[playerX][playerY - 2] = 5;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);}");
                nowImgs[playerX][playerY - 1]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/playerOnDestination.png);}");
                nowImgs[playerX][playerY - 2]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/completedBox.png);}");
                playerY = playerY - 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
            }
            else if (nowContent[playerX][playerY] == 7)
            {
                nowContent[playerX][playerY] = 3;
                nowContent[playerX][playerY - 1] = 7;
                nowContent[playerX][playerY - 2] = 5;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/place/destination.png);}");
                nowImgs[playerX][playerY - 1]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/playerOnDestination.png);}");
                nowImgs[playerX][playerY - 2]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/completedBox.png);}");
                playerY = playerY - 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
            }
        }

        else//其他情况不可推
        {

        }


    }
    else//其他情况不处理
    {

    }

    isWin();
}



void MainWindow::right() {


    if (nowContent[playerX][playerY + 1] == 1)//前方是地继续走
    {

        if (nowContent[playerX][playerY] == 6)//当前位置只有人
        {
            nowContent[playerX][playerY] = 1;
            nowContent[playerX][playerY + 1] = 6;
            nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);}");
            nowImgs[playerX][playerY + 1]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/player.png);}");
            playerY = playerY + 1;
            moves = moves + 1;
            this->repaint();
            ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
        }
        else if (nowContent[playerX][playerY] == 7)//当前在目的地上
        {
            nowContent[playerX][playerY] = 3;
            nowContent[playerX][playerY + 1] = 6;
            nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/place/destination.png);}");
            nowImgs[playerX][playerY + 1]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/player.png);}");
            playerY = playerY + 1;
            moves = moves + 1;
            this->repaint();
            ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
        }

    }


    else if (nowContent[playerX][playerY + 1] == 2)//前方是墙不处理
    {

    }


    else if (nowContent[playerX][playerY + 1] == 3)//前方是目标点继续走
    {

        if (nowContent[playerX][playerY] == 6)
        {
            nowContent[playerX][playerY] = 1;
            nowContent[playerX][playerY + 1] = 7;
            nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);}");
            nowImgs[playerX][playerY + 1]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/playerOnDestination.png);}");
            playerY = playerY + 1;
            moves = moves + 1;
            this->repaint();
            ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
        }
        else if (nowContent[playerX][playerY] == 7)
        {
            nowContent[playerX][playerY] = 3;
            nowContent[playerX][playerY + 1] = 7;
            nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/place/destination.png);}");
            nowImgs[playerX][playerY + 1]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/playerOnDestination.png);}");
            playerY = playerY + 1;
            moves = moves + 1;
            this->repaint();
            ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
        }

    }


    else if (nowContent[playerX][playerY + 1] == 4)//前方是箱子
    {

        if (nowContent[playerX][playerY + 2] == 1)//箱子前是空地
        {
            if (nowContent[playerX][playerY] == 6)
            {
                nowContent[playerX][playerY] = 1;
                nowContent[playerX][playerY + 1] = 6;
                nowContent[playerX][playerY + 2] = 4;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);}");
                nowImgs[playerX][playerY + 1]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/player.png);}");
                nowImgs[playerX][playerY + 2]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/box.png);}");
                playerY = playerY + 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
            }
            else if (nowContent[playerX][playerY] == 7)
            {
                nowContent[playerX][playerY] = 3;
                nowContent[playerX][playerY + 1] = 6;
                nowContent[playerX][playerY + 2] = 4;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/place/destination.png);}");
                nowImgs[playerX][playerY + 1]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/player.png);}");
                nowImgs[playerX][playerY + 2]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/box.png);}");
                playerY = playerY + 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
            }
        }

        else if (nowContent[playerX][playerY + 2] == 3)//箱子前是目的地
        {
            if (nowContent[playerX][playerY] == 6)
            {
                nowContent[playerX][playerY] = 1;
                nowContent[playerX][playerY + 1] = 6;
                nowContent[playerX][playerY + 2] = 5;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);}");
                nowImgs[playerX][playerY + 1]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/player.png);}");
                nowImgs[playerX][playerY + 2]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/completedBox.png);}");
                playerY = playerY + 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
            }
            else if (nowContent[playerX][playerY] == 7)
            {
                nowContent[playerX][playerY] = 3;
                nowContent[playerX][playerY + 1] = 6;
                nowContent[playerX][playerY + 2] = 5;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/place/destination.png);}");
                nowImgs[playerX][playerY + 1]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/player.png);}");
                nowImgs[playerX][playerY + 2]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/completedBox.png);}");
                playerY = playerY + 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
            }
        }

        else//其他情况不可推
        {

        }

    }


    else if (nowContent[playerX][playerY + 1] == 5)//前方是已完成的箱子
    {

        if (nowContent[playerX][playerY + 2] == 1)//箱子前是空地
        {
            if (nowContent[playerX][playerY] == 6)
            {
                nowContent[playerX][playerY] = 1;
                nowContent[playerX][playerY + 1] = 7;
                nowContent[playerX][playerY + 2] = 4;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);}");
                nowImgs[playerX][playerY + 1]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/playerOnDestination.png);}");
                nowImgs[playerX][playerY + 2]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/box.png);}");
                playerY = playerY + 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
            }
            else if (nowContent[playerX][playerY] == 7)
            {
                nowContent[playerX][playerY] = 3;
                nowContent[playerX][playerY + 1] = 7;
                nowContent[playerX][playerY + 2] = 4;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/place/destination.png);}");
                nowImgs[playerX][playerY + 1]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/playerOnDestination.png);}");
                nowImgs[playerX][playerY + 2]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/box.png);}");
                playerY = playerY + 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
            }
        }

        else if (nowContent[playerX][playerY + 2] == 3)//箱子前是目的地
        {
            if (nowContent[playerX][playerY] == 6)
            {
                nowContent[playerX][playerY] = 1;
                nowContent[playerX][playerY + 1] = 7;
                nowContent[playerX][playerY + 2] = 5;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);}");
                nowImgs[playerX][playerY + 1]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/playerOnDestination.png);}");
                nowImgs[playerX][playerY + 2]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/completedBox.png);}");
                playerY = playerY + 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
            }
            else if (nowContent[playerX][playerY] == 7)
            {
                nowContent[playerX][playerY] = 3;
                nowContent[playerX][playerY + 1] = 7;
                nowContent[playerX][playerY + 2] = 5;
                nowImgs[playerX][playerY]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/place/destination.png);}");
                nowImgs[playerX][playerY + 1]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/player/playerOnDestination.png);}");
                nowImgs[playerX][playerY + 2]->setStyleSheet("QLabel{ background-image: url(:/imgs/place/field.png);image: url(:/imgs/box/completedBox.png);}");
                playerY = playerY + 1;
                moves = moves + 1;
                this->repaint();
                ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
            }
        }

        else//其他情况不可推
        {

        }


    }
    else//其他情况不处理
    {

    }

    isWin();

}


void MainWindow::nextLevel(){
    if(nowLevel + 1 < numberOfLevels){
        moves=0;
        nowLevel = nowLevel + 1;
        ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
        ui->lblLevel->setText("当前等级： "+QString::number(nowLevel+1));
        for (int i=0;i<16;i++){
            for (int j=0;j<16;j++){
                nowContent[i][j] = levels[nowLevel][i][j];
                resetContent[i][j] = levels[nowLevel][i][j];
                if (nowContent[i][j] ==6 || nowContent[i][j] ==7){
                    playerX = i;
                    playerY = j;
                }
            }
        }
        drawLevel();
    }
    else
    {
        QMessageBox::warning(this, "Miku提醒", "恭喜您，通关了！");
    }
}



void MainWindow::lastLevel(){
    moves=0;
    if(nowLevel - 1 >= 0)
    {
        nowLevel = nowLevel - 1;
        ui->lblLevel->setText("当前等级： "+QString::number(nowLevel+1));
        ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
        for (int i = 0;i < 16;i++){
            for (int j = 0;j < 16;j++){
                nowContent[i][j] = levels[nowLevel][i][j];
                resetContent[i][j] = levels[nowLevel][i][j];
                if (nowContent[i][j] == 6 || nowContent[i][j] == 7){
                    playerX = i;
                    playerY = j;
                }
            }
        }
        drawLevel();
    }
    else
    {

        QMessageBox::warning(this, "Miku提醒", "这已经是最简单的一关了！");
    }
}



void MainWindow::isWin(){
    int k=0;
    for(int i=0;i<16;i++){
        for(int j=0;j<16;j++){
            if(nowContent[i][j]==4){
                k++;
            }
        }
    }
    if(nowLevel+1<numberOfLevels && k==0)
    {
        nextLevel();
    }
    else
    {


    }
}

void MainWindow::on_reload_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Miku提醒", "确定要重开本局吗?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        for(int i=0;i<16;i++){
            for(int j=0;j<16;j++){
                nowContent[i][j] = resetContent[i][j];
                if (nowContent[i][j] ==6 || nowContent[i][j] ==7){
                    playerX = i;
                    playerY = j;
                }
            }

        }
        moves=0;
        ui->lblMoves->setText("当前步数： " + QString::number(moves) + "");
        drawLevel();
    }
    else
    {
    }

}


void MainWindow::on_pushButton_clicked()
{
    lastLevel();
}

void MainWindow::on_pushButton_2_clicked()
{
    nextLevel();
}
