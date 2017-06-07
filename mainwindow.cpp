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
int MainWindow::herohealth=50;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    choose(new ChooseCard),
    ui(new Ui::MainWindow),
    Tower(new tower),
    Minion(new minion),
    scene(new QGraphicsScene(0, 0, 1000,540)),
    timer(new QTimer)
{
    ui->setupUi(this);
    connect(ui->card1, SIGNAL(clicked()), choose, SLOT(card1_pressed()));                                  //card1~5 connect to choose card1~5
    connect(ui->card2, SIGNAL(clicked()), choose, SLOT(card2_pressed()));                                  //
    connect(ui->card3, SIGNAL(clicked()), choose, SLOT(card3_pressed()));                                  //
    connect(ui->card4, SIGNAL(clicked()), choose, SLOT(card4_pressed()));                                  //
    connect(ui->card5, SIGNAL(clicked()), choose, SLOT(card5_pressed()));                                  //
    connect(choose, SIGNAL(card(int)), this, SLOT(changecard(int)));                                              //change global int card
    connect(timer, SIGNAL(timeout()),this, SLOT(manaplus()));                                                          //+1mana/s
    connect(timer,SIGNAL(timeout()),this,SLOT(herobeattack()));                                                     //tower attack hero
    connect(this, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));                                                                //hero attack tower
    connect(this, SIGNAL(tatk(int)), this, SLOT(atk(int)));                                                                      //hero attack tower decrease health bar
    connect(timer, SIGNAL(timeout()),this, SLOT(gamestatus()));                                                      //win or lose
    connect(timer,SIGNAL(timeout()),this,SLOT(heroshealth()));

    ui->health->setValue(1000);//tower's health set to 1000

    ui->graphicsView->setScene(scene);

    bg =new QGraphicsPixmapItem(QPixmap(":/res/bg.png"));                                                           //set bg.png as background
    bg->setPixmap(QPixmap(":/res/bg.png").scaled(1200, 600));
    scene->addItem(bg);
    bg->setPos(-100,0);

    hero = new QGraphicsPixmapItem(QPixmap(":/res/2b.jpg"));                                                      //set 2b as hero
    scene->addItem(hero);
    hero->setPixmap(QPixmap(":/res/2b.jpg").scaled(50,50));
    hero->setPos(275, 350);

    wall =new QGraphicsPixmapItem(QPixmap(":/res/tower.png"));                                                 //set tower.png as tower
    wall->setPixmap(QPixmap(":/res/tower.png").scaled(800,50));
    scene->addItem(wall);
    wall->setPos(-100,0);

    end =new QGraphicsPixmapItem(QPixmap(":/res/end.png"));                                                     //new a QGraphics... for battle end

   // timer->start(500);                                                                                                                                      //everything move by 0.5s

    /*if(ui->health->value()==0){
        qDebug()<<"stop";
        timer->stop();
    }*/
}

MainWindow::~MainWindow(){
    delete ui;
    delete choose;}

void MainWindow::heroshealth(){                                                                                                             //if hero is dead,send hero to far ar away
    if(ui->hero->value()==0){
        hero->setPos(100000000,100000000000);
        //qDebug()<<"hero dead";
    }
}

void MainWindow::herobeattack(){                                                                                                            //if hero walk into tower's attack range,be attacked
    if(hero->y()<71){
        herohealth--;
        ui->hero->setValue(herohealth);
        emit tatk(4);                                                                                                                                               //at the same time,hero attack tower
        }
    else if(hero->x()==100000000){                                                                                                          //if hero is far far away,hero's health is still 0
        herohealth=0;
    }
    else{
        herohealth++;
        ui->hero->setValue(herohealth);
        }
}

void MainWindow::keyPressEvent(QKeyEvent *e)                                                                                 //use wasd to control hero,12345678 to choose where your minion born,qwert to choose card
{
    switch(e->key()) {
    case Qt::Key_Up:
        if(hero->y()>50){
          hero->setPos(hero->x(), hero->y() - 10);
        }
        break;
    case Qt::Key_Down:
        if(hero->y()<420){
             hero->setPos(hero->x(), hero->y() + 10);
        }
        break;
     case Qt::Key_Left:
        if(hero->x()>-95){
             hero->setPos(hero->x() - 10, hero->y());
        }
        break;
   case Qt::Key_Right:
        if(hero->x()<645){
            hero->setPos(hero->x() + 10, hero->y());
        }
        break;
    case Qt::Key_1:
        MainWindow::on_but1_clicked();
         break;
    case Qt::Key_2:
        MainWindow::on_but2_clicked();
         break;
    case Qt::Key_3:
         MainWindow::on_but3_clicked();
         break;
    case Qt::Key_4:
        MainWindow::on_but4_clicked();
         break;
    case Qt::Key_5:
         MainWindow::on_but5_clicked();
         break;
    case Qt::Key_6:
        MainWindow::on_but6_clicked();
         break;
    case Qt::Key_7:
        MainWindow::on_but7_clicked();
         break;
    case Qt::Key_8:
         MainWindow::on_but8_clicked();
         break;
    case Qt::Key_Q:
         ui->card1->clicked();
         break;
    case Qt::Key_W:
        ui->card2->clicked();
         break;
    case Qt::Key_E:
         ui->card3->clicked();
         break;
    case Qt::Key_R:
        ui->card4->clicked();
         break;
    case Qt::Key_T:
         ui->card5->clicked();
         break;
   case Qt::Key_Space:
        ui->start->clicked();
        break;
    }
}

void MainWindow::changecard(int i){                                                                                                    //let but1~5 know you choose which card
    card=i;}

void MainWindow::gamestatus(){                                                                                                           //system will know you win or lose
    static int time=0;
    time++;
    if(time==200&&ui->health->value()>=1){//if 100s and tower still alive,you lose
        end->setPixmap(QPixmap(":/res/end.png").scaled(800, 600));
        scene->addItem(end);
        end->setPos(-100,0);
        MainWindow::timer->stop();
    }
    else if(ui->health->value()==0){//if tower destroyed,you win
        end->setPixmap(QPixmap(":/res/victory.png").scaled(800, 600));
        scene->addItem(end);
        end->setPos(-100,0);
        MainWindow::timer->stop();
    }

}

void MainWindow::atk(int j){                                                                                                                    //progress bar decrease when tower is attacked
  //  qDebug()<<"atk";
    ui->health->setValue(ui->health->value()-j);

    }

void MainWindow::manaplus(){                                                                                                              //mana plus 1 by 1sec and progress bar increase 20%
    if(mana<=10){
        mana++;
    }
    //qDebug()<<mana;
    ui->mana->setValue(mana*10);
}
/*void MainWindow::on_card1_clicked(){
    qDebug()<<"choose card1";}
void MainWindow::on_card2_clicked(){
    qDebug()<<"choose card2";}
void MainWindow::on_card3_clicked(){
    qDebug()<<"choose card3";}
void MainWindow::on_card4_clicked(){
    qDebug()<<"choose card4";}
void MainWindow::on_card5_clicked(){
    qDebug()<<"choose card5";}*/

void MainWindow::on_but1_clicked(){                                                                                                  //when but1 is clicked,put a cardX minion on the battle field,and - mana
    //qDebug()<<"1";
    if(card==1&&mana>=2){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m1.jpg").scaled(20,20));
        min->setPos(-60,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk1()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=2;}
   else if(card==2&&mana>=4){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m2.jpg").scaled(20,20));
        min->setPos(-60,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk2()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
       mana-=4;}
   else if(card==3&&mana>=6){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m3.jpg").scaled(20,20));
        min->setPos(-60,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk3()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=6;}
   else if(card==4&&mana>=8){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m4.jpg").scaled(20,20));
        min->setPos(-60,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk4()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=8;}
   else if(card==5&&mana>=10){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m5.jpg").scaled(20,20));
        min->setPos(-60,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk5()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=10;}
}
void MainWindow::on_but2_clicked(){
    //qDebug()<<"2";
        if(card==1&&mana>=2){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m1.jpg").scaled(20,20));
        min->setPos(40,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk1()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=2;}
        else if(card==2&&mana>=4){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m2.jpg").scaled(20,20));
        min->setPos(40,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk2()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
       mana-=4;}
    else if(card==3&&mana>=6){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m3.jpg").scaled(20,20));
        min->setPos(40,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk3()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=6;}
    else if(card==4&&mana>=8){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m4.jpg").scaled(20,20));
        min->setPos(40,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk4()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=8;}
    else if(card==5&&mana>=10){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m5.jpg").scaled(20,20));
        min->setPos(40,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk5()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=10;}
}
void MainWindow::on_but3_clicked(){
   // qDebug()<<"3";
    if(card==1&&mana>=2){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m1.jpg").scaled(20,20));
        min->setPos(140,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk1()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=2;}
    else if(card==2&&mana>=4){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m2.jpg").scaled(20,20));
        min->setPos(140,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk2()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
       mana-=4;}
      else if(card==3&&mana>=6){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m3.jpg").scaled(20,20));
        min->setPos(140,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk3()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=6;}
    else if(card==4&&mana>=8){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m4.jpg").scaled(20,20));
        min->setPos(140,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk4()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=8;}
    else if(card==5&&mana>=10){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m5.jpg").scaled(20,20));
        min->setPos(140,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk5()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=10;}
}
void MainWindow::on_but4_clicked(){
    //qDebug()<<"4";
    if(card==1&&mana>=2){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m1.jpg").scaled(20,20));
        min->setPos(240,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk1()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=2;}
    else if(card==2&&mana>=4){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m2.jpg").scaled(20,20));
        min->setPos(240,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk2()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=4;}
    else if(card==3&&mana>=6){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m3.jpg").scaled(20,20));
        min->setPos(240,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk3()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=6;}
    else if(card==4&&mana>=8){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m4.jpg").scaled(20,20));
        min->setPos(240,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk4()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=8;}
    else if(card==5&&mana>=10){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m5.jpg").scaled(20,20));
        min->setPos(240,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk5()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=10;}
}
void MainWindow::on_but5_clicked(){
 //   qDebug()<<"5";
    if(card==1&&mana>=2){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m1.jpg").scaled(20,20));
        min->setPos(340,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk1()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=2;}
    else if(card==2&&mana>=4){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m2.jpg").scaled(20,20));
        min->setPos(340,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk2()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
       mana-=4;}
    else if(card==3&&mana>=6){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m3.jpg").scaled(20,20));
        min->setPos(340,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk3()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=6;}
    else if(card==4&&mana>=8){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m4.jpg").scaled(20,20));
        min->setPos(340,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk4()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=8;}
    else if(card==5&&mana>=10){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m5.jpg").scaled(20,20));
        min->setPos(340,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk5()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=10;}
}
void MainWindow::on_but6_clicked(){
  //  qDebug()<<"6";
    if(card==1&&mana>=2){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m1.jpg").scaled(20,20));
        min->setPos(440,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk1()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=2;}
    else if(card==2&&mana>=4){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m2.jpg").scaled(20,20));
        min->setPos(440,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk2()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
       mana-=4;}
    else if(card==3&&mana>=6){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m3.jpg").scaled(20,20));
        min->setPos(440,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk3()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=6;}
    else if(card==4&&mana>=8){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m4.jpg").scaled(20,20));
        min->setPos(440,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk4()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=8;}
    else if(card==5&&mana>=10){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m5.jpg").scaled(20,20));
        min->setPos(440,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk5()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=10;}
}
void MainWindow::on_but7_clicked(){
   // qDebug()<<"7";
    if(card==1&&mana>=2){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m1.jpg").scaled(20,20));
        min->setPos(540,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk1()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=2;}
    else if(card==2&&mana>=4){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m2.jpg").scaled(20,20));
        min->setPos(540,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk2()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
       mana-=4;}
    else if(card==3&&mana>=6){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m3.jpg").scaled(20,20));
        min->setPos(540,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk3()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=6;}
    else if(card==4&&mana>=8){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m4.jpg").scaled(20,20));
        min->setPos(540,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk4()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=8;}
    else if(card==5&&mana>=10){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m5.jpg").scaled(20,20));
        min->setPos(540,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk5()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=10;}
}
void MainWindow::on_but8_clicked(){
    //qDebug()<<"8";
    if(card==1&&mana>=2){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m1.jpg").scaled(20,20));
        min->setPos(640,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk1()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=2;}
    else if(card==2&&mana>=4){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m2.jpg").scaled(20,20));
        min->setPos(640,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk2()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
       mana-=4;}
    else if(card==3&&mana>=6){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m3.jpg").scaled(20,20));
        min->setPos(640,450);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk3()));
         connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
         connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;
        mana-=6;}
    else if(card==4&&mana>=8){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m4.jpg").scaled(20,20));
        min->setPos(640,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk4()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=8;}
    else if(card==5&&mana>=10){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m5.jpg").scaled(20,20));
        min->setPos(645,450);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk5()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=10;}
}

void MainWindow::on_x05_clicked(){                                                                                                    //change game speed
    //qDebug()<<"x0.5";
    t=1000;
    MainWindow::timer->start(t);}
void MainWindow::on_x075_clicked(){
    //qDebug()<<"x0.75";
    t=750;
   MainWindow:: timer->start(t);}
void MainWindow::on_x1_clicked(){
    //qDebug()<<"x1";
    t=500;
    MainWindow::timer->start(t);}
void MainWindow::on_x15_clicked(){
    //qDebug()<<"x1.5";
    t=375;
    MainWindow::timer->start(t);}
void MainWindow::on_x2_clicked(){
    //qDebug()<<"x2";
    MainWindow::t=500;
    timer->start(t);}

void MainWindow::on_easy_clicked(){                                                                                                 //change game difficulty

}
void MainWindow::on_norml_clicked(){

}
void MainWindow::on_hard_clicked(){

}

void MainWindow::on_start_clicked()
{
    MainWindow::on_x1_clicked();
}

//useless funtion
void MainWindow::on_card1_clicked()
{

}
void MainWindow::on_card2_clicked()
{

}
void MainWindow::on_card3_clicked()
{

}
void MainWindow::on_card4_clicked()
{

}
void MainWindow::on_card5_clicked()
{

}


