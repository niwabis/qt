#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPushButton>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(0, 0, 1000,600)),
    timer(new QTimer)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);

    bg =new QGraphicsPixmapItem(QPixmap(":/res/bg.png"));
    bg->setPixmap(QPixmap(":/res/bg.png").scaled(1000, 545));
    scene->addItem(bg);
    bg->setPos(0,0);

    tower =new QGraphicsPixmapItem(QPixmap(":/res/tower.png"));
    tower->setPixmap(QPixmap(":/res/tower.png").scaled(800,50));
    scene->addItem(tower);
    tower->setPos(0,0);

    item = new QGraphicsPixmapItem(QPixmap(":/res/th.jpg"));
    scene->addItem(item);
    item->setPos(500, 50);

    butt1 = new QGraphicsPixmapItem(QPixmap(":/res/red_bullet.png"));
    butt1->setPixmap(QPixmap(":/res/red_bullet.png").scaled(50,50));
    scene->addItem(butt1);
    butt1->setPos(25,470);

    timer->start(500);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch(e->key()) {
    case Qt::Key_Up:
    case Qt::Key_W:
        item->setPos(item->x(), item->y() - 10);
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        item->setPos(item->x(), item->y() + 10);
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        item->setPos(item->x() - 10, item->y());
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        item->setPos(item->x() + 10, item->y());
        break;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    bullet *b = new bullet;

   b->setPixmap(QPixmap(":/res/giant.png").scaled(20,20));
   b->setPos(item->x() + item->pixmap().width() / 2 - b->pixmap().width() / 2, item->y() - b->pixmap().height());
    b->connect(timer, SIGNAL(timeout()), b, SLOT(fly()));
    scene->addItem(static_cast<QGraphicsPixmapItem*>(b));
}
void MainWindow::on_but1_clicked()
{
    bullet *minion=new bullet;
    minion->setPixmap(QPixmap(":/res/giant.png").scaled(20,20));
    minion->setPos(butt1->x() + butt1->pixmap().width() / 2 - minion->pixmap().width() / 2, butt1->y() - minion->pixmap().height());
     minion->connect(timer, SIGNAL(timeout()), minion, SLOT(fly()));
     scene->addItem(static_cast<QGraphicsPixmapItem*>(minion));
}

