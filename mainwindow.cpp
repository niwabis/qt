#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"minion.h"
#include"choosecard.h"
#include"tower.h"
#include<QPushButton>
#include <QDebug>

int card;
int t=500;
int MainWindow::mana=0;
int h;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    choose(new ChooseCard),
    Tower(new tower),
    Minion(new minion),
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
    connect(timer, SIGNAL(timeout()),this, SLOT(manaplus()));

    ui->health->setValue(100);

    ui->graphicsView->setScene(scene);

    bg =new QGraphicsPixmapItem(QPixmap(":/res/bg.png"));
    bg->setPixmap(QPixmap(":/res/bg.png").scaled(1100, 600));
    scene->addItem(bg);
    bg->setPos(-50,0);

    wall =new QGraphicsPixmapItem(QPixmap(":/res/tower.png"));
    wall->setPixmap(QPixmap(":/res/tower.png").scaled(800,50));
    scene->addItem(wall);
    wall->setPos(-50,0);

    timer->start(500);

    /*if(ui->health->value()==0){
        qDebug()<<"stop";
        timer->stop();
    }*/
}

MainWindow::~MainWindow(){
    delete ui;
    delete choose;}

void MainWindow::changecard(int i){
    card=i;}

void MainWindow::atk(int j){
  //  qDebug()<<"atk";
    ui->health->setValue(ui->health->value()-j);}
void MainWindow::manaplus(){
    if(mana<=5){
        mana++;
    }
    //qDebug()<<mana;
    ui->mana->setValue(mana*20);
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
    //qDebug()<<"1";
    if(card==1&&mana>=1){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/giant.png").scaled(20,20));
        min->setPos(-5,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=1;}
   else if(card==2&&mana>=2){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/2b.jpg").scaled(20,20));
        min->setPos(-5,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
       mana-=2;}
   else if(card==3&&mana>=3){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/a2.png").scaled(20,20));
        min->setPos(-5,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=3;}
   else if(card==4&&mana>=4){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/9s.png").scaled(20,20));
        min->setPos(-5,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=4;}
   else if(card==5&&mana>=5){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/emil.png").scaled(20,20));
        min->setPos(-5,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=5;}
}
void MainWindow::on_but2_clicked(){
    //qDebug()<<"2";
        if(card==1&&mana>=1){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/giant.png").scaled(20,20));
        min->setPos(95,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=1;}
        else if(card==2&&mana>=2){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/2b.jpg").scaled(20,20));
        min->setPos(95,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
       mana-=2;}
    else if(card==3&&mana>=3){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/a2.png").scaled(20,20));
        min->setPos(95,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=3;}
    else if(card==4&&mana>=4){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/9s.png").scaled(20,20));
        min->setPos(95,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=4;}
    else if(card==5&&mana>=5){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/emil.png").scaled(20,20));
        min->setPos(95,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=5;}
}
void MainWindow::on_but3_clicked(){
   // qDebug()<<"3";
    if(card==1&&mana>=1){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/giant.png").scaled(20,20));
        min->setPos(195,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=1;}
    else if(card==2&&mana>=2){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/2b.jpg").scaled(20,20));
        min->setPos(195,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
       mana-=2;}
      else if(card==3&&mana>=3){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/a2.png").scaled(20,20));
        min->setPos(195,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=3;}
    else if(card==4&&mana>=4){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/9s.png").scaled(20,20));
        min->setPos(195,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=4;}
    else if(card==5&&mana>=5){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/emil.png").scaled(20,20));
        min->setPos(195,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=5;}
}
void MainWindow::on_but4_clicked(){
    //qDebug()<<"4";
    if(card==1&&mana>=1){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/giant.png").scaled(20,20));
        min->setPos(295,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=1;}
    else if(card==2&&mana>=2){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/2b.jpg").scaled(20,20));
        min->setPos(295,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=2;}
    else if(card==3&&mana>=3){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/a2.png").scaled(20,20));
        min->setPos(295,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=3;}
    else if(card==4&&mana>=4){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/9s.png").scaled(20,20));
        min->setPos(295,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=4;}
    else if(card==5&&mana>=5){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/emil.png").scaled(20,20));
        min->setPos(295,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=5;}
}
void MainWindow::on_but5_clicked(){
 //   qDebug()<<"5";
    if(card==1&&mana>=1){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/giant.png").scaled(20,20));
        min->setPos(395,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=1;}
    else if(card==2&&mana>=2){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/2b.jpg").scaled(20,20));
        min->setPos(395,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
       mana-=2;}
    else if(card==3&&mana>=3){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/a2.png").scaled(20,20));
        min->setPos(395,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=3;}
    else if(card==4&&mana>=4){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/9s.png").scaled(20,20));
        min->setPos(395,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=4;}
    else if(card==5&&mana>=5){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/emil.png").scaled(20,20));
        min->setPos(395,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=5;}
}
void MainWindow::on_but6_clicked(){
  //  qDebug()<<"6";
    if(card==1&&mana>=1){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/giant.png").scaled(20,20));
        min->setPos(495,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=1;}
    else if(card==2&&mana>=2){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/2b.jpg").scaled(20,20));
        min->setPos(495,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
       mana-=2;}
    else if(card==3&&mana>=3){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/a2.png").scaled(20,20));
        min->setPos(495,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=3;}
    else if(card==4&&mana>=4){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/9s.png").scaled(20,20));
        min->setPos(495,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=4;}
    else if(card==5&&mana>=5){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/emil.png").scaled(20,20));
        min->setPos(495,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=5;}
}
void MainWindow::on_but7_clicked(){
   // qDebug()<<"7";
    if(card==1&&mana>=1){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/giant.png").scaled(20,20));
        min->setPos(595,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=1;}
    else if(card==2&&mana>=2){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/2b.jpg").scaled(20,20));
        min->setPos(595,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
       mana-=2;}
    else if(card==3&&mana>=3){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/a2.png").scaled(20,20));
        min->setPos(595,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=3;}
    else if(card==4&&mana>=4){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/9s.png").scaled(20,20));
        min->setPos(595,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=4;}
    else if(card==5&&mana>=5){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/emil.png").scaled(20,20));
        min->setPos(595,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=5;}
}
void MainWindow::on_but8_clicked(){
    //qDebug()<<"8";
    if(card==1&&mana>=1){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/giant.png").scaled(20,20));
        min->setPos(695,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=1;}
    else if(card==2&&mana>=2){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/2b.jpg").scaled(20,20));
        min->setPos(695,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
       mana-=2;}
    else if(card==3&&mana>=3){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/a2.png").scaled(20,20));
        min->setPos(695,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
         connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
         connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;
        mana-=3;}
    else if(card==4&&mana>=4){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/9s.png").scaled(20,20));
        min->setPos(695,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=4;}
    else if(card==5&&mana>=5){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/emil.png").scaled(20,20));
        min->setPos(695,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=5;}
}
void MainWindow::on_x05_clicked(){
    qDebug()<<"x0.5";
    t=1000;
    timer->start(t);}
void MainWindow::on_x075_clicked(){
    qDebug()<<"x0.75";
    t=750;
    timer->start(t);}
void MainWindow::on_x1_clicked(){
    qDebug()<<"x1";
    t=500;
    timer->start(t);}
void MainWindow::on_x15_clicked(){
    qDebug()<<"x1.5";
    t=375;
    timer->start(t);}
void MainWindow::on_x2_clicked(){
    qDebug()<<"x2";
    t=500;
    timer->start(t);}
