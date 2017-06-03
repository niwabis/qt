#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>

class minion : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    minion();
   int health=10;
signals:
    void tatk(int);
public slots:
    void walk();
};

#endif // BULLET_H
