#ifndef MAGIC_H
#define MAGIC_H

#include <QObject>
#include<QGraphicsPixmapItem>
class magic : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit magic(QObject *parent = 0);
    int i;
    int health=1;
signals:
    void tatk(int);
public slots:
    void fireball();
private:

};

#endif // MAGIC_H
