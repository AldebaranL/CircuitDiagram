#include "circuitdig.h"

CircuitDig::CircuitDig()
{
    nodenumber=1;
    memset(in,0,sizeof in);
    memset(digMap,0,sizeof digMap);
    memset(childrenNum,0,sizeof childrenNum);
    for(int i=0;i<MAXN;i++){
        nodepos[i].x=(float)i/(float)2;
        nodepos[i].y=(float)-1;
    }
    nodepos[0].y=0;

    gap=50;
}
void CircuitDig::drawline(edge ed,QPainter & p){
    int x1=nodepos[ed.x].x,y1=nodepos[ed.x].y;
    int x2=nodepos[ed.y].x,y2=nodepos[ed.y].y;
    p.drawLine(100+x1*gap,100+y1*gap,100+x1*gap,100+y2*gap);
    p.drawLine(100+x1*gap,100+y2*gap,100+x2*gap,100+y2*gap);
   // char str1[3];
  //  p.drawEllipse(x2,y2,4,4);
   // sprintf(str1,"%d",ed.y);
   // p.drawText(x2-2,y2,QString(str1));
}
///*
void CircuitDig::updateNodePos(int s)
{
    bool vis[MAXN];
    memset(vis, false, sizeof(vis)); // 此处vis的含义是节点是否在队列中
    queue<int> Q;
    Q.push(s);
    int x=0,y=0;
    while (!Q.empty())
    {
        s = Q.front();
        Q.pop();
        //执行操作1 begin
        if(nodepos[s].x!=x){
            y=0;
            x=nodepos[s].x;
        }
        //执行操作1 end
        vis[s] = true;
        for (int i = 0; i < map[s].size(); i++)
        {
            //执行操作2 begin

            //执行操作2 end
            if (!vis[map[s][i].y])
            {
                //执行操作3 begin
                int ty=map[s][i].y;
                nodepos[ty].x=nodepos[s].x+1;
                nodepos[ty].y=y;
                y++;
                childrenNum[s]++;
                //执行操作3 end
                Q.push(map[s][i].y);
                vis[map[s][i].y] = true;
            }
        }
        //执行操作4 begin

        //执行操作4 end
    }
}//*/

void CircuitDig::dfs(bool * vis,int s,int x,int y){
    vis[s]=true;
    nodepos[s].x=x;
    nodepos[s].y=y;
    for(int i=0;i<map[s].size();i++){
        int ty=map[s][i].y;
        if(vis[ty])continue;
        childrenNum[s]++;
        dfs(vis,ty,x+1,y);
        if(childrenNum[ty])y+=childrenNum[ty];
        else y++;
    }
}
void CircuitDig::updateNodePos()
{
    bool vis[MAXN];
    memset(vis, false, sizeof(vis));
    memset(childrenNum, 0, sizeof(childrenNum));
    dfs(vis,0,0,0);
}
void CircuitDig::updateEdgePos()
{
    //int x=0,y=0;
    //for(int i=0;i<nodenumber;i++){
    //    for(int j=0;j<map[i].size();j++){

    //    }
    //}
}
void CircuitDig::display(QPainter & p){
    p.setPen(QPen(Qt::black,2));
    p.setBrush(QColor(0,0,0));
    char str1[3];
    for(int i=0;i<nodenumber;i++){
        p.drawEllipse(98+nodepos[i].x*gap,98+nodepos[i].y*gap,4,4);
        sprintf(str1,"%d",i);
        p.drawText(102+nodepos[i].x*gap,116+nodepos[i].y*gap,QString(str1));
       // p.drawLine(100+x1*gap,100+y1*gap,100+x1*gap,100+y2*gap);
    }
  // updateNodePos(0,p);
    for(int i=0;i<nodenumber;i++){
        for(int j=0;j<map[i].size();j++){
            drawline(map[i][j], p);
        }
    }

}
