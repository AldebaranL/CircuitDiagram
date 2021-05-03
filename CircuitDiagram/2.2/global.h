#ifndef GLOBAL_H
#define GLOBAL_H

#include<QList>
#include<QPoint>
#include <qdebug.h>
#include"mylist.cpp"
#include <QString>
#include <QToolBar>
#include <QFileDialog>
//int elenum=0;
//int linenum=0;
class node{
public:
    int Posx,Posy;
    QString value;
    int type;
    int dir;
    int order;
    node *next;
    node(int x1,int y1,int typ1){
        Posx=x1;
        Posy=y1;
        type=typ1;
      //  elenum++;
        dir=0;
        next=nullptr;
        value='\0';
      //  qDebug()<<x1<<y1<<type;
    }
};
struct line{
    int lable1, lable2;
    int dir1,dir2;
    line(int l1,int l2,int d1,int d2){
        lable1=l1;lable2=l2;dir1=d1;dir2=d2;
     //   linenum++;
        next=nullptr;
    }
    int order;
    line* next;
};
//enum dirn{up,down,left,right};
MyList<node> eleList;
MyList<line> lineList;
const int gap=20;
bool button_checked=false;
int button_type=0;
bool attention=0;
int attention_order;
bool haveMove=0;

bool draw_line_mod=false;
bool line_button_checked=true;

bool point_attention=0;
int point_attention_order;
int tem_point_attention_order;
int tem_point_dir;

int point_dir=1;

const int nodesize=5;
const int Rlength=40;
const int Rwidth=16;

QString nodevaluetext;

int boardx,boardy,boardwidth,boardheight;
#endif // GLOBAL_H


