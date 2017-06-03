#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include<QDebug>

class tower : public QObject
{
    Q_OBJECT
public:
    explicit tower(QObject *parent = 0);

signals:

public slots:
    void attacked(int);
};

#endif // TOWER_H
