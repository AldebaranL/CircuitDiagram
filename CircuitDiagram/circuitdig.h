#ifndef CIRCUITDIG_H
#define CIRCUITDIG_H
#include<vector>
#include<queue>
#include<string.h>
#include <QPainter>
#include<iostream>
using namespace std;

const int MAXN=20;
const int DIGSIZE=20;
struct positon{
    float x,y;
};
struct edge{
    int x,y;//元件方向由x到y
    int type;//元件类型：1电阻，2电压源，3电流源，4受控电压源，5受控电流源
    int valuen;//元件特征数量
    int value[5];//元件特征
    positon pos;
};

class CircuitDig
{
    bool in[MAXN];//若结点i与图联通，则in[i]为true,反之为false
    int childrenNum[MAXN];
    int gap;
    int nodenumber;//节点数
    void updateNodePos();
    void updateEdgePos();
    void updateNodePos(int);
    vector<edge> map[MAXN];//图的邻接表
    positon nodepos[MAXN];//点的位置
    int digMap[DIGSIZE][DIGSIZE];//线的位置
    void drawline(edge,QPainter &);
public:

    CircuitDig();

    void display(QPainter &);
    friend class AddElement;
    friend class DrawingBoard;
    void dfs(bool * vis,int s,int x,int y);
};

#endif // CIRCUITDIG_H
