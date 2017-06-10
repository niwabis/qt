#include "magic.h"
#include<QDebug>
magic::magic(QObject *parent) : QObject(parent)
{

}

void magic::fireball(){
    if(y()>-50){                                                         //if y>50,keep walking
        setPos(x(), y() - 15);   }
   else {                                                                   //else,stop and attack tower
        int j=35;
       emit tatk(j);
       delete this;    }
}
