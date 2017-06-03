#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"minion.h"
#include"choosecard.h"
#include<QPushButton>
#include <QDebug>

int card;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    choose(new ChooseCard),
    scene(new QGraphicsScene(0, 0, 1000,600)),
    timer(new QTimer)
{
    ui->setupUi(this);
    connect(ui->card1, SIGNAL(clicked()), choose, SLOT(card1_pressed()));
    connect(ui->card2, SIGNAL(clicked()), choose, SLOT(card2_pressed()));
    connect(ui->card3, SIGNAL(clicked()), choose, SLOT(card3_pressed()));
    connect(ui->card4, SIGNAL(clicked()), choose, SLOT(card4_pressed()));
    connect(ui->card5, SIGNAL(clicked()), choose, SLOT(card5_pressed()));
    connect(choose, SIGNAL(card(int)), this, SLOT(changecard(int)));

    ui->graphicsView->setScene(scene);

    bg =new QGraphicsPixmapItem(QPixmap(":/res/bg.png"));
    bg->setPixmap(QPixmap(":/res/bg.png").scaled(1000, 600));
    scene->addItem(bg);
    bg->setPos(0,0);

    tower =new QGraphicsPixmapItem(QPixmap(":/res/tower.png"));
    tower->setPixmap(QPixmap(":/res/tower.png").scaled(800,50));
    scene->addItem(tower);
    tower->setPos(0,0);


    timer->start(500);


}

MainWindow::~MainWindow()
{
    delete ui;
    delete choose;
}

void MainWindow::changecard(int i){
    card=i;
}

void MainWindow::on_card1_clicked(){
    qDebug()<<"choose card1";}
void MainWindow::on_card2_clicked(){
    qDebug()<<"choose card2";}
void MainWindow::on_card3_clicked(){
    qDebug()<<"choose card3";}
void MainWindow::on_card4_clicked(){
    qDebug()<<"choose card4";}
void MainWindow::on_card5_clicked(){
    qDebug()<<"choose card5";}
void MainWindow::on_but1_clicked(){
    qDebug()<<"1";
    if(card==1){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/giant.png").scaled(20,20));
        min->setPos(45,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==2){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/2b.jpg").scaled(20,20));
        min->setPos(45,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==3){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/a2.png").scaled(20,20));
        min->setPos(45,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==4){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/9s.png").scaled(20,20));
        min->setPos(45,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==5){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/emil.png").scaled(20,20));
        min->setPos(45,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
}
void MainWindow::on_but2_clicked(){
    qDebug()<<"2";
    if(card==1){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/giant.png").scaled(20,20));
        min->setPos(145,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==2){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/2b.jpg").scaled(20,20));
        min->setPos(145,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==3){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/a2.png").scaled(20,20));
        min->setPos(145,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==4){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/9s.png").scaled(20,20));
        min->setPos(145,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==5){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/emil.png").scaled(20,20));
        min->setPos(145,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
}
void MainWindow::on_but3_clicked(){
    qDebug()<<"3";
    if(card==1){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/giant.png").scaled(20,20));
        min->setPos(245,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==2){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/2b.jpg").scaled(20,20));
        min->setPos(245,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==3){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/a2.png").scaled(20,20));
        min->setPos(245,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==4){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/9s.png").scaled(20,20));
        min->setPos(245,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==5){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/emil.png").scaled(20,20));
        min->setPos(245,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
}
void MainWindow::on_but4_clicked(){
    qDebug()<<"4";
    if(card==1){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/giant.png").scaled(20,20));
        min->setPos(345,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==2){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/2b.jpg").scaled(20,20));
        min->setPos(345,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==3){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/a2.png").scaled(20,20));
        min->setPos(345,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==4){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/9s.png").scaled(20,20));
        min->setPos(345,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==5){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/emil.png").scaled(20,20));
        min->setPos(345,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
}
void MainWindow::on_but5_clicked(){
    qDebug()<<"5";
    if(card==1){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/giant.png").scaled(20,20));
        min->setPos(445,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==2){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/2b.jpg").scaled(20,20));
        min->setPos(445,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==3){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/a2.png").scaled(20,20));
        min->setPos(445,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==4){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/9s.png").scaled(20,20));
        min->setPos(445,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==5){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/emil.png").scaled(20,20));
        min->setPos(445,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
}
void MainWindow::on_but6_clicked(){
    qDebug()<<"6";
    if(card==1){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/giant.png").scaled(20,20));
        min->setPos(545,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==2){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/2b.jpg").scaled(20,20));
        min->setPos(545,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==3){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/a2.png").scaled(20,20));
        min->setPos(545,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==4){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/9s.png").scaled(20,20));
        min->setPos(545,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==5){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/emil.png").scaled(20,20));
        min->setPos(545,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
}
void MainWindow::on_but7_clicked(){
    qDebug()<<"7";
    if(card==1){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/giant.png").scaled(20,20));
        min->setPos(645,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==2){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/2b.jpg").scaled(20,20));
        min->setPos(645,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==3){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/a2.png").scaled(20,20));
        min->setPos(645,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==4){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/9s.png").scaled(20,20));
        min->setPos(645,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==5){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/emil.png").scaled(20,20));
        min->setPos(645,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
}
void MainWindow::on_but8_clicked(){
    qDebug()<<"8";
    if(card==1){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/giant.png").scaled(20,20));
        min->setPos(745,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==2){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/2b.jpg").scaled(20,20));
        min->setPos(745,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==3){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/a2.png").scaled(20,20));
        min->setPos(745,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==4){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/9s.png").scaled(20,20));
        min->setPos(745,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
    else if(card==5){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/emil.png").scaled(20,20));
        min->setPos(745,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;    }
}

