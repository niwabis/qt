#include "choosecard.h"

ChooseCard::ChooseCard(QObject *parent) : QObject(parent),i(0)
{

}

void ChooseCard::card1_pressed()                                                //emit a signal let buttom know which card you choose
{
    int i=1;
    emit card(i);
}
void ChooseCard::card2_pressed()
{
    int i=2;
    emit card(i);
}
void ChooseCard::card3_pressed()
{
    int i=3;
    emit card(i);
}
void ChooseCard::card4_pressed()
{
    int i=4;
    emit card(i);
}
void ChooseCard::card5_pressed()
{
    int i=5;
    emit card(i);
}
