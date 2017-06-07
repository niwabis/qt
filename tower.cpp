#include "tower.h"

tower::tower(QObject *parent) : QObject(parent)
{

}

void tower::tatk(int i){
    health-=i;
    /*if(health<=0){
        qDebug()<<"game over";
    }*/
}
