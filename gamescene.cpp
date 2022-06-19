#include "gamescene.h"
#include "ui_gamescene.h"

GameScene::GameScene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameScene),
    timer1s(new QTimer),
    remaintime(10),
    grandsquare(new GrandSquare)
{

    ui->setupUi(this);
    timer1s->start(1000);
    connect(timer1s,&QTimer::timeout,this,&GameScene::timer1sout);
    ui->graphicsView->setScene(grandsquare);
}

GameScene::~GameScene()
{
    delete ui;
}

void GameScene::on_commandLinkButton_clicked()
{
    emit returnmenu();
}

void GameScene::timer1sout()
{
    ui->lcdNumber->display(QString::number((remaintime--)/60)+":"+QString::number(remaintime%60));
    if(remaintime==0) {
        timer1s->stop();
        emit timeout();
        return;
    }
}


