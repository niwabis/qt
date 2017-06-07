#ifndef HERO_H
#define HERO_H

#include <QObject>

class hero : public QObject
{
    Q_OBJECT
public:
    explicit hero(QObject *parent = 0);

signals:

public slots:
};

#endif // HERO_H