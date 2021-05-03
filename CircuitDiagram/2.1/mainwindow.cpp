#include "global.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void getPos(int lable,int dir,int &x,int &y){
    int tx=eleList.find(lable)->Posx,ty=eleList.find(lable)->Posy;
    int len=Rlength,wid=Rwidth;
    switch(dir){
    case 0://center
        x=tx,y=ty;
        break;
    case 1://up
        x=tx,y=ty-wid/2;
        break;
    case 2://right
        x=tx+len/2,y=ty;
        break;
    case 3://down
        x=tx,y=ty+wid/2;
        break;
    case 4://left
        x=tx-len/2,y=ty;
        break;
    }
}
bool isclose(int x1,int y1,int x2,int y2){
    return (abs(x1-x2)<=10)&&(abs(y1-y2)<=10);
}
int in(int x,int y,int lable){
    for(int i=1;i<=4;i++){
        int x1,y1;
        getPos(lable,i,x1,y1);
        if(isclose(x1,y1,x,y))return i;
    }
    return 0;
}


void MainWindow::paintEvent(QPaintEvent *){

    QPainter painter(this);
    painter.setPen(QPen(QColor(0, 0, 0), 2));

    line* iter1;
    for (iter1=lineList.begin;iter1!=nullptr;iter1=iter1->next){
        int tx1,ty1,tx2,ty2;
        getPos(iter1->lable1,iter1->dir1,tx1,ty1);
        getPos(iter1->lable2,iter1->dir2,tx2,ty2);
      //  qDebug()<<tx1<<ty1<<tx2<<ty2;
        painter.drawLine(tx1,ty1,tx2,ty2);
    }
    node* iter;
    for (iter=eleList.begin;iter!=nullptr;iter=iter->next)
    {
        switch(iter->type){
        case 1:
            painter.setRenderHint(QPainter::Antialiasing, true);
               // 设置画笔颜色、宽度
            painter.setPen(QPen(QColor(0, 0, 0), 2));
               // 设置画刷颜色
            painter.setBrush(QColor(255, 255, 255));
            if(attention&&iter->order==attention_order) painter.setPen(QPen(QColor(255, 0, 0), 2));
            painter.drawRect(iter->Posx-Rlength/2,iter->Posy-Rwidth/2,Rlength,Rwidth);
            //  qDebug() <<  *iter << "\0";
            break;
        case 2:
            painter.setRenderHint(QPainter::Antialiasing, true);
               // 设置画笔颜色、宽度
            painter.setPen(QPen(QColor(100, 0, 0), 2));
               // 设置画刷颜色
            painter.setBrush(QColor(100, 255, 255));
            if(attention&&iter->order==attention_order) painter.setPen(QPen(QColor(255, 0, 0), 2));
            painter.drawRect(iter->Posx-Rlength/2,iter->Posy-Rwidth/2,Rlength,Rwidth);
            //  qDebug() <<  iter;
            break;
        case 3:
            painter.setRenderHint(QPainter::Antialiasing, true);
               // 设置画笔颜色、宽度
            painter.setPen(QPen(QColor(0, 0, 0), 2));
               // 设置画刷颜色
            painter.setBrush(QColor(0, 0, 0));
            if(attention&&iter->order==attention_order) painter.setPen(QPen(QColor(255, 0, 0), 2));
            painter.drawEllipse(iter->Posx-nodesize/2,iter->Posy-nodesize/2,nodesize,nodesize);
            //  qDebug() <<  iter;
            break;
        }

    }

   update();
}
void MainWindow::mouseMoveEvent(QMouseEvent* event){
    if(attention){
      //  qDebug()<<"!!";
        eleList.find(attention_order)->Posx=((int)event->windowPos().x()/gap)*gap;
        eleList.find(attention_order)->Posy=((int)event->windowPos().y()/gap)*gap;
       // update();
        haveMove=1;
    }

}
void MainWindow::mouseReleaseEvent(QMouseEvent* ){
    if(haveMove){
        attention=0;
        haveMove=0;
    }
}


void MainWindow::mousePressEvent(QMouseEvent * event)
{
        if(button_checked){
            if(event->button()==Qt::LeftButton){
                node *tn=new node(((int)event->windowPos().x()/gap)*gap,((int)event->windowPos().y()/gap)*gap,button_type);
                eleList.push_back(tn);
                qDebug()<<eleList.size;
                button_checked=false;
                switch(button_type){
                case 1:
                    ui->pushButton->setStyleSheet("color:blue");
                    break;
                case 2:
                    ui->pushButton_2->setStyleSheet("color:blue");
                    break;
                }
            }
        }
        else if(event->button()==Qt::RightButton){
            node *tn=new node(((int)event->windowPos().x()/gap)*gap,((int)event->windowPos().y()/gap)*gap,3);
            eleList.push_back(tn);
        }
        else if(draw_line_mod&&event->button()==Qt::LeftButton){
            int nx=event->windowPos().x(),ny=event->windowPos().y();

            node* iter;
            for (iter=eleList.begin;iter!=nullptr;iter=iter->next)
            {
                if(iter->type==3&& isclose(nx,ny,iter->Posx,iter->Posy)){
                 //   qDebug()<<i;
                    point_attention=1;
                    point_attention_order=iter->order;
                    point_dir=0;
                    break;
                }
                else if(iter->type!=3&&in(nx,ny,iter->order)){
                    point_attention=1;
                    point_attention_order=iter->order;
                    point_dir=in(nx,ny,iter->order);
                    break;
                }
                else point_attention=0;
            }
         //   qDebug()<<"@";
        //    qDebug()<<point_attention<<point_dir;
            if(point_attention){
            //    qDebug()<<line_button_checked;
                if(line_button_checked){
              //      qDebug()<<"@";
                    tem_point_attention_order=point_attention_order;
                    tem_point_dir=point_dir;

                    line_button_checked=false;
                 //    qDebug()<<"@";
                }
                else{
                    line *lt=new line(tem_point_attention_order,point_attention_order,tem_point_dir,point_dir);
                    lineList.push_back(lt);
                    line_button_checked=true;
                }
            }
        }
        else if(event->button()==Qt::LeftButton){
            int nx=event->windowPos().x(),ny=event->windowPos().y();
            node* iter;
            for (iter=eleList.begin;iter!=nullptr;iter=iter->next)
            {
                if(isclose(nx,ny,iter->Posx,iter->Posy)){
                 //   qDebug()<<i;
                    attention=1;
                    attention_order=iter->order;
                    break;
                }
                else attention=0;
            }
        }
}
void MainWindow::on_pushButton_clicked()
{
    if(!button_checked) {
        button_checked=true;
        button_type=1;
        ui->pushButton->setStyleSheet("color:red");
    }
    else{
        button_checked=false;
        ui->pushButton->setStyleSheet("color:blue");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(!button_checked) {
        button_checked=true;
        button_type=2;
        ui->pushButton_2->setStyleSheet("color:red");
    }
    else{
        button_checked=false;
        ui->pushButton_2->setStyleSheet("color:blue");
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    if(!draw_line_mod) {
        draw_line_mod=true;
        ui->pushButton_3->setStyleSheet("color:red");
    }
    else{
        draw_line_mod=false;
        ui->pushButton_3->setStyleSheet("color:blue");
    }
}

void MainWindow::on_changeDir_clicked()
{
    eleList.find(attention_order)->dir=1-eleList.find(attention_order)->dir;
}

void MainWindow::on_nodeDeletButton_clicked()
{
    if(attention){
        line* iter1;
        for (iter1=lineList.begin;iter1!=nullptr;iter1=iter1->next){
            if(iter1->lable1==attention_order||iter1->lable2==attention_order)
            {
                lineList.erase(iter1->order);
                linenum--;
            }
        }
        eleList.erase(attention_order);
        elenum--;
        attention=0;
    }

}
