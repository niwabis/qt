#include "minion.h"

minion::minion()
{

}

void minion::walk1(){                                         //the way card1 walk
    if(y()>-5){                                                         //if y>50,keep walking
        setPos(x(), y() - 2);   }
   else {                                                                   //else,stop and attack tower
       setPos(x(),y());
       int j=1;
       emit tatk(j);   }

    if(y()<=15){                                                     //if y<=70,attacked by tower
        health1--;
         }

   if(health1<=0) {                                             //if health <=0,delete this minion
        delete this;    }
}

void minion::walk2(){                                         //card2~5 follow as card1
    if(y()>5){
        setPos(x(), y() - 2);   }
   else {
       setPos(x(),y());
       int j=2;
       emit tatk(j); }

    if(y()<=15){
        health2--;
           }

   if(health2<=0) {
        delete this;    }
}

void minion::walk3(){
    if(y()==25){
        setPos(x(), y() );
        int j=1;
        emit tatk(j); }
   else {
       setPos(x(),y()-1);  }

    if(y()<=15){
        health3--;
          }

   if(health3<=0) {
        delete this;    }
}

void minion::walk4(){
    if(y()>5){
        setPos(x(), y() - 3);   }
   else {
       setPos(x(),y());
       int j=3;
       emit tatk(j);}

    if(y()<=15){
        health4--;
            }

   if(health4<=0) {
        delete this;    }
}

void minion::walk5(){
    if(y()>0){
        setPos(x(), y() - 1);   }
   else {
       setPos(x(),y());
       int j=2;
       emit tatk(j);  }

    if(y()<=15){
        health5--;
         }

   if(health5<=0) {
        delete this;    }
}
