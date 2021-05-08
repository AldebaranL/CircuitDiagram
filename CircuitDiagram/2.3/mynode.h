#ifndef MYNODE_H
#define MYNODE_H


#include "global.h"
class MyNode
{
public:
    int Posx,Posy;
    int v;
    int type;
    int dir;
    int order;
    MyNode *next;
    MyNode(int,int,int);
    void display(QPainter *);
};

#endif // MYNODE_H
