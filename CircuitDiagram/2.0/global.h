#ifndef GLOBAL_H
#define GLOBAL_H

#include<QList>
#include<QPoint>
#include <qdebug.h>



int elenum=0;
int linenum=0;
class node{
public:
    int Posx,Posy;
    int v;
    int type;
    int dir;
    node(int x1,int y1,int v1,int typ1){
        Posx=x1;
        Posy=y1;
        v=v1;
        type=typ1;
        elenum++;
        dir=0;
      //  qDebug()<<x1<<y1<<type;
    }
};
struct line{
    QList<node>::iterator lable1, lable2;
    int dir1,dir2;
    line(QList<node>::iterator l1,QList<node>::iterator l2,int d1,int d2){
        lable1=l1;lable2=l2;dir1=d1;dir2=d2;
        linenum++;
    }
};
//enum dirn{up,down,left,right};
QList<node> eleList;
QList<line> lineList;
const int gap=20;
bool button_checked=false;
int button_type=0;
bool attention=0;
QList<node>::iterator attention_iter;
bool haveMove=0;

bool draw_line_mod=false;
bool line_button_checked=true;

bool point_attention=0;
QList<node>::iterator point_attention_iter;
QList<node>::iterator tem_point_attention_iter;
int tem_point_dir;

int point_dir=1;

const int nodesize=5;
const int Rlength=40;
const int Rwidth=20;

#endif // GLOBAL_H


