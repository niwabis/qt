#include "tower.h"
tower::tower(QObject *parent) : QObject(parent)
{

}

void tower::attacked(int i){
    static int health=10;
    health--;
    qDebug()<<health;
    if(health<=0){
        qDebug()<<"dead";
    }
}
