#ifndef CHOOSECARD_H
#define CHOOSECARD_H

#include <QObject>

class ChooseCard : public QObject
{
    Q_OBJECT
public:
    explicit ChooseCard(QObject *parent = 0);

signals:
    void card(int i);

public slots:    
    void card1_pressed();
    void card2_pressed();
    void card3_pressed();
    void card4_pressed();
    void card5_pressed();
private:
    int i;
};

#endif // CHOOSECARD_H
