#include "mainwindow.h"
#include "ui_mainwindow.h"


int card;
int t=500;
int MainWindow::mana=0;
int h;
int MainWindow::herohealth=500;
int MainWindow::start=0;
int MainWindow::start1=0;
int MainWindow::started=0;
int MainWindow::count=0;
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
    connect(this,SIGNAL(sst(int)),this,SLOT(st(int)));

    ui->health->setValue(10000);//tower's health set to 1000

    ui->graphicsView->setScene(scene);

    bg =new QGraphicsPixmapItem(QPixmap(":/res/bg.png"));                                                           //set bg.png as background
    bg->setPixmap(QPixmap(":/res/bg.png").scaled(1200, 700));
    scene->addItem(bg);
    bg->setPos(-100,-55);

    hero = new QGraphicsPixmapItem(QPixmap(":/res/emil.png"));                                                      //set 2b as hero
    scene->addItem(hero);
    hero->setPixmap(QPixmap(":/res/emil.png").scaled(50,50));
    hero->setPos(275, 350);

    wall =new QGraphicsPixmapItem(QPixmap(":/res/tower.png"));                                                 //set tower.png as tower
    wall->setPixmap(QPixmap(":/res/tower.png").scaled(800,50));
    scene->addItem(wall);
    wall->setPos(-100,-55);

    back =new QGraphicsPixmapItem(QPixmap(":/res/back.png"));
    back->setPixmap(QPixmap(":/res/back.png").scaled(50,270));
    scene->addItem(back);
    back->setPos(670,130);

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
        if(hero->y()>-5){
          hero->setPos(hero->x(), hero->y() - 10);
        }
        break;
    case Qt::Key_Down:
        if(hero->y()<365){
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
    static int time=2000;
    time--;
    if(time==100)
        QSound::play(":/res/mccreee.wav");
    ui->time->setValue(time);
    if(time==0&&ui->health->value()>=1){//if 100s and tower still alive,you lose
        end->setPixmap(QPixmap(":/res/end.png").scaled(670, 500));
        scene->addItem(end);
        end->setPos(-50,-10);
        MainWindow::timer->stop();
        QSound::play(":/res/defeat.wav");
    }
    else if(ui->health->value()<=0){//if tower destroyed,you win
        end->setPixmap(QPixmap(":/res/victory.png").scaled(670, 500));
        scene->addItem(end);
        end->setPos(-50,-20);
        MainWindow::timer->stop();
        delete wall;
        QSound::play(":/res/victory.wav");
    }

}

void MainWindow::atk(int j){                                                                                                                    //progress bar decrease when tower is attacked
  //  qDebug()<<"atk";
    if(ui->health->value()-j>0){
       ui->health->setValue(ui->health->value()-j);
    }
    else{
        ui->health->setValue(0);    }
    }

void MainWindow::manaplus(){                                                                                                              //mana plus 1 by 1sec and progress bar increase 20%
    if(mana<=200){
        mana++;
    }
    //qDebug()<<mana;
    ui->mana->setValue(mana);
}
void MainWindow::on_card1_clicked(){
   // qDebug()<<"choose card1";
}
void MainWindow::on_card2_clicked(){
    //qDebug()<<"choose card2";
}
void MainWindow::on_card3_clicked(){
    //qDebug()<<"choose card3";
}
void MainWindow::on_card4_clicked(){
  //  qDebug()<<"choose card4";
}
void MainWindow::on_card5_clicked(){
   // qDebug()<<"choose card5";
}

void MainWindow::on_but1_clicked(){                                                                                                  //when but1 is clicked,put a cardX minion on the battle field,and - mana
    //qDebug()<<"1";
    if(card==1&&mana>=20){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m1.jpg").scaled(20,20));
        min->setPos(-50,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk1()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=20;
        emit sst(1);}
   else if(card==2&&mana>=40){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m2.jpg").scaled(20,20));
        min->setPos(-50,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk2()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
       mana-=40;
       emit sst(2);}
   else if(card==3&&mana>=60){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m3.jpg").scaled(20,20));
        min->setPos(-50,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk3()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=60;
        emit sst(3);}
        else if(card==4&&mana>=80){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m4.jpg").scaled(20,20));
        min->setPos(-50,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk4()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=80;
        emit sst(4);}
        else if(card==5&&mana>=100){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m5.jpg").scaled(20,20));
        min->setPos(-50,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk5()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=100;
        emit sst(5);}
}
void MainWindow::on_but2_clicked(){
    //qDebug()<<"2";
        if(card==1&&mana>=20){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m1.jpg").scaled(20,20));
        min->setPos(50,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk1()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=20;
        emit sst(1);}
        else if(card==2&&mana>=40){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m2.jpg").scaled(20,20));
        min->setPos(50,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk2()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
       mana-=40;
       emit sst(2);}
        else if(card==3&&mana>=60){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m3.jpg").scaled(20,20));
        min->setPos(50,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk3()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=60;}
        else if(card==4&&mana>=80){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m4.jpg").scaled(20,20));
        min->setPos(50,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk4()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=80;
        emit sst(4);}
    else if(card==5&&mana>=100){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m5.jpg").scaled(20,20));
        min->setPos(50,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk5()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=100;
        emit sst(5);}
}
void MainWindow::on_but3_clicked(){
   // qDebug()<<"3";
    if(card==1&&mana>=20){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m1.jpg").scaled(20,20));
        min->setPos(150,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk1()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=20;
        emit sst(1);}
    else if(card==2&&mana>=40){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m2.jpg").scaled(20,20));
        min->setPos(150,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk2()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
       mana-=40;
       emit sst(2);}
      else if(card==3&&mana>=60){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m3.jpg").scaled(20,20));
        min->setPos(150,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk3()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=60;
        emit sst(3);}
    else if(card==4&&mana>=80){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m4.jpg").scaled(20,20));
        min->setPos(150,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk4()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=80;
        emit sst(4);}
    else if(card==5&&mana>=100){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m5.jpg").scaled(20,20));
        min->setPos(150,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk5()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=100;
        emit sst(5);}
}
void MainWindow::on_but4_clicked(){
    //qDebug()<<"4";
    if(card==1&&mana>=20){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m1.jpg").scaled(20,20));
        min->setPos(250,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk1()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=20;
        emit sst(1);}
    else if(card==2&&mana>=40){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m2.jpg").scaled(20,20));
        min->setPos(250,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk2()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=40;
        emit sst(2);}
    else if(card==3&&mana>=60){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m3.jpg").scaled(20,20));
        min->setPos(250,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk3()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=60;
        emit sst(3);}
    else if(card==4&&mana>=80){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m4.jpg").scaled(20,20));
        min->setPos(250,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk4()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=80;
        emit sst(4);}
    else if(card==5&&mana>=100){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m5.jpg").scaled(20,20));
        min->setPos(250,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk5()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=100;
        emit sst(5);}
}
void MainWindow::on_but5_clicked(){
 //   qDebug()<<"5";
    if(card==1&&mana>=20){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m1.jpg").scaled(20,20));
        min->setPos(350,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk1()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=20;
        emit sst(1);}
    else if(card==2&&mana>=40){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m2.jpg").scaled(20,20));
        min->setPos(350,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk2()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
       mana-=40;
       emit sst(2);}
    else if(card==3&&mana>=60){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m3.jpg").scaled(20,20));
        min->setPos(350,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk3()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=60;
        emit sst(3);}
    else if(card==4&&mana>=80){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m4.jpg").scaled(20,20));
        min->setPos(350,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk4()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=80;
        emit sst(4);}
    else if(card==5&&mana>=100){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m5.jpg").scaled(20,20));
        min->setPos(350,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk5()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=100;
        emit sst(5);}
}
void MainWindow::on_but6_clicked(){
  //  qDebug()<<"6";
    if(card==1&&mana>=20){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m1.jpg").scaled(20,20));
        min->setPos(450,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk1()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=20;
        emit sst(1);}
    else if(card==2&&mana>=40){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m2.jpg").scaled(20,20));
        min->setPos(450,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk2()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
       mana-=40;
       emit sst(2);}
    else if(card==3&&mana>=60){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m3.jpg").scaled(20,20));
        min->setPos(450,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk3()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=60;
        emit sst(3);}
    else if(card==4&&mana>=80){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m4.jpg").scaled(20,20));
        min->setPos(450,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk4()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=80;
        emit sst(4);}
    else if(card==5&&mana>=100){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m5.jpg").scaled(20,20));
        min->setPos(450,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk5()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=100;
        emit sst(5);}
}
void MainWindow::on_but7_clicked(){
   // qDebug()<<"7";
    if(card==1&&mana>=20){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m1.jpg").scaled(20,20));
        min->setPos(550,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk1()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=20;
        emit sst(1);}
    else if(card==2&&mana>=40){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m2.jpg").scaled(20,20));
        min->setPos(550,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk2()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
       mana-=40;
       emit sst(2);}
    else if(card==3&&mana>=60){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m3.jpg").scaled(20,20));
        min->setPos(550,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk3()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=60;
        emit sst(3);}
    else if(card==4&&mana>=80){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m4.jpg").scaled(20,20));
        min->setPos(550,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk4()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=80;
        emit sst(4);}
    else if(card==5&&mana>=100){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m5.jpg").scaled(20,20));
        min->setPos(550,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk5()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=100;
        emit sst(5);}
}
void MainWindow::on_but8_clicked(){
    //qDebug()<<"8";
    if(card==1&&mana>=20){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m1.jpg").scaled(20,20));
        min->setPos(650,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk1()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=20;
        emit sst(1);}
    else if(card==2&&mana>=40){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m2.jpg").scaled(20,20));
        min->setPos(650,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk2()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
       mana-=40;
       emit sst(2);}
    else if(card==3&&mana>=60){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m3.jpg").scaled(20,20));
        min->setPos(650,395);
         min->connect(timer, SIGNAL(timeout()), min, SLOT(walk3()));
         connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
         connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
         scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
         card=0;
        mana-=60;
        emit sst(3);}
    else if(card==4&&mana>=80){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m4.jpg").scaled(20,20));
        min->setPos(650,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk4()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=80;
        emit sst(4);}
    else if(card==5&&mana>=100){
        minion *min=new minion;
        min->setPixmap(QPixmap(":/res/m5.jpg").scaled(20,20));
        min->setPos(650,395);
        min->connect(timer, SIGNAL(timeout()), min, SLOT(walk5()));
        connect(min, SIGNAL(tatk(int)), this, SLOT(atk(int)));
        connect(min, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(min));
        card=0;
        mana-=100;
        emit sst(5);}
}

void MainWindow::on_x05_clicked(){
    if(started==0){
        start1=1;
    }
    if(started==1){
        t=100;
       MainWindow::timer->start(t);
    }
}
void MainWindow::on_x075_clicked(){
    if(start==0){
        start1=2;
    }
    if(started==1){
        t=75;
       MainWindow::timer->start(t);
       }
}
void MainWindow::on_x1_clicked(){
    if(started==0){
        start1=3;
    }
    if(started==1){
        t=50;
       MainWindow::timer->start(t);
       }
}
void MainWindow::on_x15_clicked(){
    if(started==0){
        start1=4;
    }
    if(started==1){
        t=35;
       MainWindow::timer->start(t);}
}
void MainWindow::on_x2_clicked(){
    if(started==0){
        start1=5;
    }
    if(started==1){
        t=25;
       MainWindow::timer->start(t);}
}

void MainWindow::on_easy_clicked(){                                                                                                 //change game difficulty
    if(started==0){
        start=1;
        mana=180;
        herohealth=400;
        Tower->health=8000;
        ui->health->setValue(8000);
    }
    else if(started==1){
        Tower->tatk(500);
        atk(500);
    }

}
void MainWindow::on_norml_clicked(){
    if(started==0){
        start=1;
        mana=100;
        herohealth=250;
        Tower->health=10000;
        ui->health->setValue(10000);
    }


}
void MainWindow::on_hard_clicked(){
    if(started==0){
        start=1;
        mana=0;
        herohealth=1;
        Tower->health=10000;
        ui->health->setValue(10000);
    }
    else if(started==1){
        if(Tower->health>=9500){
            Tower->health=10000;
            atk(-(10000-Tower->health));
        }
        else{
            Tower->health+=500;
            atk(-500);
        }
    }

}

void MainWindow::on_start_clicked()
{
    if(start==1){
        if(start1==1){
            started=1;
            MainWindow::on_x05_clicked();
            ui->start->hide();
            QSound::play(":/res/mccreec.wav");
        }
        else if(start1==2){
             started=1;
            MainWindow::on_x075_clicked();
            ui->start->hide();
            QSound::play(":/res/mccreec.wav");
         }
        else if(start1==3){
            started=1;
            MainWindow::on_x1_clicked();
            ui->start->hide();
            QSound::play(":/res/mccreec.wav");
        }
        else if(start1==4){
            started=1;
            MainWindow::on_x15_clicked();
            ui->start->hide();
            QSound::play(":/res/mccreec.wav");
        }
        else if(start1==5){
            started=1;
            MainWindow::on_x2_clicked();
            ui->start->hide();
            QSound::play(":/res/mccreec.wav");
        }

    }
    start=0;
    start1=0;
}

void MainWindow::on_magic1_clicked()
{

    if(mana>=150){
        QSound::play(":/res/pharahe.wav");
        QTimer::singleShot( 450,this, SLOT(fireball()) );
        QTimer::singleShot( 500,this, SLOT(fireball()) );
        QTimer::singleShot( 550,this, SLOT(fireball()) );
        QTimer::singleShot( 600,this, SLOT(fireball()) );
        QTimer::singleShot( 650,this, SLOT(fireball()) );
        QTimer::singleShot( 700,this, SLOT(fireball()) );
        QTimer::singleShot( 750,this, SLOT(fireball()) );
        QTimer::singleShot( 800,this, SLOT(fireball()) );
        QTimer::singleShot( 950,this, SLOT(fireball()) );
        QTimer::singleShot( 1000,this, SLOT(fireball()) );
        QTimer::singleShot( 1050,this, SLOT(fireball()) );
        QTimer::singleShot( 1100,this, SLOT(fireball()) );
        QTimer::singleShot( 1150,this, SLOT(fireball()) );
        QTimer::singleShot( 1200,this, SLOT(fireball()) );
        QTimer::singleShot( 1250,this, SLOT(fireball()) );
        QTimer::singleShot( 1300,this, SLOT(fireball()) );
        QTimer::singleShot( 1350,this, SLOT(fireball()) );
        QTimer::singleShot( 1400,this, SLOT(fireball()) );
        QTimer::singleShot( 1450,this, SLOT(fireball()) );
        QTimer::singleShot( 1500,this, SLOT(fireball()) );

        mana-=150;
    }
}
void MainWindow::fireball(){
    static int i=0;
    std::srand(time(NULL)+i);
    i+=10000;
    int x=rand()%8*100;
    QTimer *ti;
    ti = new QTimer;
    ti->start(20);
    magic *fb=new magic;
    scene->addItem(fb);
    fb->setPixmap(QPixmap(":/res/fb.png").scaled(100,200));
    fb->setPos(-100+x,400);
    fb->connect(ti, SIGNAL(timeout()), fb, SLOT(fireball()));
    connect(fb, SIGNAL(tatk(int)), this, SLOT(atk(int)));
    connect(fb, SIGNAL(tatk(int)), Tower, SLOT(tatk(int)));
}

void MainWindow::on_magic2_clicked()
{
    if(mana>=200){
        QSound::play(":/res/mercye.wav");
        hero->setPos(275,350);
        if(herohealth<=350){
        herohealth+=150;}
        else{
            QSound::play(":/res/mercye.wav");
            herohealth=500;        }
        ui->hero->setValue(herohealth);
        mana-=200;
    }

}

void MainWindow::st(int card){
     if(count>=5){
         for(int i=0;i<4;++i){
            number[i]=number[i+1];        }
         number[4]=card;
         for(int j=0;j<count;++j){
             if(number[j]==1){
                 m1 =new QGraphicsPixmapItem(QPixmap(":/res/m1.jpg"));
                 m1->setPixmap(QPixmap(":/res/m1.jpg").scaled(30,30));
                 scene->addItem(m1);
                 m1->setPos(680,350-50*j);
             }
             else if(number[j]==2){
                 m2 =new QGraphicsPixmapItem(QPixmap(":/res/m2.jpg"));
                 m2->setPixmap(QPixmap(":/res/m2.jpg").scaled(30,30));
                 scene->addItem(m2);
                 m2->setPos(680,350-50*j);
             }
             else if(number[j]==3){
                 m3 =new QGraphicsPixmapItem(QPixmap(":/res/m3.jpg"));
                 m3->setPixmap(QPixmap(":/res/m3.jpg").scaled(30,30));
                  scene->addItem(m3);
                  m3->setPos(680,350-50*j);
             }
             else if(number[j]==4){
                 m4 =new QGraphicsPixmapItem(QPixmap(":/res/m4.jpg"));
                 m4->setPixmap(QPixmap(":/res/m4.jpg").scaled(30,30));
                 scene->addItem(m4);
                 m4->setPos(680,350-50*j);
             }
             else if(number[j]==5){
                 m5 =new QGraphicsPixmapItem(QPixmap(":/res/m5.jpg"));
                 m5->setPixmap(QPixmap(":/res/m5.jpg").scaled(30,30));
                 scene->addItem(m5);
                 m5->setPos(680,350-50*j);
             }
          }
    }
    else if(count<5){
            number.push_back(card);
            for(int j=-1;j<count;++j){
                if(number[j+1]==1){
                    m1 =new QGraphicsPixmapItem(QPixmap(":/res/m1.jpg"));
                    m1->setPixmap(QPixmap(":/res/m1.jpg").scaled(30,30));
                    scene->addItem(m1);
                    m1->setPos(680,350-50*(j+1));
                }
                else if(number[j+1]==2){
                    m2 =new QGraphicsPixmapItem(QPixmap(":/res/m2.jpg"));
                    m2->setPixmap(QPixmap(":/res/m2.jpg").scaled(30,30));
                    scene->addItem(m2);
                    m2->setPos(680,350-50*(j+1));
                }
                else if(number[j+1]==3){
                    m3 =new QGraphicsPixmapItem(QPixmap(":/res/m3.jpg"));
                    m3->setPixmap(QPixmap(":/res/m3.jpg").scaled(30,30));
                     scene->addItem(m3);
                     m3->setPos(680,350-50*(j+1));
                }
                else if(number[j+1]==4){
                    m4 =new QGraphicsPixmapItem(QPixmap(":/res/m4.jpg"));
                    m4->setPixmap(QPixmap(":/res/m4.jpg").scaled(30,30));
                    scene->addItem(m4);
                    m4->setPos(680,350-50*(j+1));
                }
                else if(number[j+1]==5){
                    m5 =new QGraphicsPixmapItem(QPixmap(":/res/m5.jpg"));
                    m5->setPixmap(QPixmap(":/res/m5.jpg").scaled(30,30));
                    scene->addItem(m5);
                    m5->setPos(680,350-50*(j+1));
                }
             }
       }

        if(count<5){
            count++;}

        //qDebug()<<number;
}


