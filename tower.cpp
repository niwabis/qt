#include "tower.h"

tower::tower(QObject *parent) : QObject(parent)
{

}

void tower::tatk(int i){
    health-=i;

}
