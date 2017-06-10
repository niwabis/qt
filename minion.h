#ifndef MINION_H
#define MINION_H

#include <QObject>
#include <QGraphicsPixmapItem>

class minion : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    minion();
   int health1=100;
   int health2=100;
   int health3=150;
   int health4=50;
   int health5=200;

signals:
    void tatk(int);
public slots:
    void walk1();
    void walk2();
    void walk3();
    void walk4();
    void walk5();
};

#endif // BULLET_H
