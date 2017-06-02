#include "bullet.h"

bullet::bullet()
{

}

void bullet::fly()
{
   static int health=10;

    if(y()>50){
        setPos(x(), y() - 20);
   }
   else {
       setPos(x(),y());
   }

    if(y()==50){
        health--;
    }

   if(health<=0) {
        delete this;
    }
}
