#ifndef MINION_H
#define MINION_H

#include <QObject>
#include <QGraphicsPixmapItem>

class minion : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    minion();
   int health1=10;
   int health2=10;
   int health3=15;
   int health4=5;
   int health5=20;

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
