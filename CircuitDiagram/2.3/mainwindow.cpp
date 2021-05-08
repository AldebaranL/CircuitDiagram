#include "global.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

  //  QMenu menu=
    QToolBar *tbar = addToolBar(tr("工具栏"));
    tbar->setMovable(false);//工具栏不可移动
    tbar->setIconSize(QSize(50, 30));//设置动作图标的尺寸
    tbar->setStyleSheet("color: rgb(255, 255, 255);\nfont: 75 14pt 'Century Gothic';\nborder:2px solid rgb(48, 140, 98);\nbackground-color: rgb(48, 140, 98);");//背景色

    QAction *saveAction = new QAction(tr("Save"), this);//保存动作
    tbar->addAction(saveAction);//添加到工具栏
    connect(saveAction, SIGNAL(triggered()), this, SLOT(SavePic()));
}
void MainWindow::SavePic()
{
    //弹出文件保存对话框
    QString fileName = QFileDialog::getSaveFileName(this, tr("保存"), "new.jpg", "Image (*.jpg *.png *.bmp)");

    if (fileName.length() > 0)
    {
       // _tEdit->hide();//防止文本输入框显示时，将文本框保存到图片
        QPixmap pixmap(size());//新建窗体大小的pixmap
        QPainter painter(&pixmap);//将pixmap作为画布
        painter.fillRect(QRect(0, 0, size().width(), size().height()), Qt::white);//设置绘画区域、画布颜色
        this->render(&painter);//将窗体渲染到painter，再由painter画到画布
        pixmap.copy(QRect(boardx,boardy,boardwidth,boardheight)).save(fileName);//不包含工具栏
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
void getPos(int lable,int dir,int &x,int &y){
    int tx=eleList.find(lable)->Posx,ty=eleList.find(lable)->Posy;
    int len,wid;
    switch(eleList.find(lable)->type){
    case 1:
        if(eleList.find(lable)->dir==1){
            len=Rlength;wid=Rwidth;
        }
        else{
            len=Rwidth;wid=Rlength;
        }
        break;
    case 2:
        len=Rlength;wid=Rlength;
        break;
    }



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
    /*//help box
    painter.setPen(QPen(QColor(255, 255, 255), 2));
    painter.setBrush(QColor(255, 255, 255));
    painter.drawRect(this->width()*27/32,this->height()*9/32,100,100);
    painter.setPen(QPen(QColor(0, 0, 0), 2));
    painter.drawText(this->width()*27/32+5,this->height()*9/32+5,tr("Help Box"));
*/
    //draw board background
    boardx=((int)this->width()*3/32/gap)*gap;
    boardy=((int)this->height()*9/32/gap)*gap;
    boardwidth=((int)this->width()*27/32/gap)*gap;
    boardheight=((int)this->height()*14/32/gap)*gap;

    painter.setPen(QPen(QColor(255, 255, 255), 2));
    painter.setBrush(QColor(255, 255, 255));
    painter.drawRect(boardx,boardy,boardwidth,boardheight);
    painter.setPen(QPen(QColor(200, 200, 200), 2));
    for(int i=0;i<=boardwidth;i+=gap){
      //  qDebug()<<i;
        painter.drawLine(boardx+i,boardy,boardx+i,boardy+boardheight);
    }
    for(int i=0;i<=boardheight;i+=gap){
       // qDebug()<<i;
        painter.drawLine(boardx,boardy+i,boardx+boardwidth,boardy+i);
    }

    //draw lines
    painter.setPen(QPen(QColor(0, 0, 0), 2));
    line* iter1;
    for (iter1=lineList.begin;iter1!=nullptr;iter1=iter1->next){
        int tx1,ty1,tx2,ty2;
        getPos(iter1->lable1,iter1->dir1,tx1,ty1);
        getPos(iter1->lable2,iter1->dir2,tx2,ty2);
      //  qDebug()<<tx1<<ty1<<tx2<<ty2;
        painter.drawLine(tx1,ty1,tx2,ty2);
    }

    //draw element
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
            if(iter->dir==1){
                painter.drawText(iter->Posx,iter->Posy-Rwidth/2-3,iter->value);
                painter.drawRect(iter->Posx-Rlength/2,iter->Posy-Rwidth/2,Rlength,Rwidth);
            }
            else{
                painter.drawText(iter->Posx+Rwidth/2+2,iter->Posy,iter->value);
                painter.drawRect(iter->Posx-Rwidth/2,iter->Posy-Rlength/2,Rwidth,Rlength);
            }
            //  qDebug() <<  *iter << "\0";
            break;
        case 2:
            painter.setRenderHint(QPainter::Antialiasing, true);
               // 设置画笔颜色、宽度
            painter.setPen(QPen(QColor(0, 0, 0), 2));
               // 设置画刷颜色
            painter.setBrush(QColor(255, 255, 255));
            if(attention&&iter->order==attention_order) painter.setPen(QPen(QColor(255, 0, 0), 2));

            painter.drawEllipse(iter->Posx-Rlength/2,iter->Posy-Rlength/2,Rlength,Rlength);
            painter.drawText(iter->Posx+Rlength/2,iter->Posy-Rlength/2,iter->value);
            if(iter->dir==1){
                painter.drawLine(iter->Posx-Rlength/2,iter->Posy,iter->Posx+Rlength/2,iter->Posy);
            }
            else{
               //painter.drawText(iter->Posx+Rwidth/2,iter->Posy,iter->value);
                painter.drawLine(iter->Posx,iter->Posy-Rlength/2,iter->Posx,iter->Posy+Rlength/2);
            }
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
      //  int nx=eleList.find(attention_order)->Posx,ny=eleList.find(attention_order)->Posy;
     //   if(!isclose(event->windowPos().x(),event->windowPos().x(),nx,ny)){
                eleList.find(attention_order)->Posx=((int)event->windowPos().x()/gap)*gap;
                eleList.find(attention_order)->Posy=((int)event->windowPos().y()/gap)*gap;
               // update();
                haveMove=1;
    //    }

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
               // qDebug()<<eleList.size;
                button_checked=false;
                switch(button_type){
                case 1:
                    ui->pushButton->setStyleSheet("color: rgb(0, 0, 0);\nfont: 75 14pt 'Century Gothic';\nborder:2px solid rgb(48, 140, 98);\nbackground-color: rgb(255, 255, 255);");
                    break;
                case 2:
                    ui->pushButton_2->setStyleSheet("color: rgb(0, 0, 0);\nfont: 75 14pt 'Century Gothic';\nborder:2px solid rgb(48, 140, 98);\nbackground-color: rgb(255, 255, 255);");
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
        ui->pushButton->setStyleSheet("color: rgb(255, 255, 255);\nfont: 75 14pt 'Century Gothic';\nborder:2px solid rgb(48, 140, 98);\nbackground-color: rgb(48, 140, 98);");
    }
    else{
        button_checked=false;
        ui->pushButton->setStyleSheet("color: rgb(0, 0, 0);\nfont: 75 14pt 'Century Gothic';\nborder:2px solid rgb(48, 140, 98);\nbackground-color: rgb(255, 255, 255);");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(!button_checked) {
        button_checked=true;
        button_type=2;
        ui->pushButton_2->setStyleSheet("color: rgb(255, 255, 255);\nfont: 75 14pt 'Century Gothic';\nborder:2px solid rgb(48, 140, 98);\nbackground-color: rgb(48, 140, 98);");
    }
    else{
        button_checked=false;
        ui->pushButton_2->setStyleSheet("color: rgb(0, 0, 0);\nfont: 75 14pt 'Century Gothic';\nborder:2px solid rgb(48, 140, 98);\nbackground-color: rgb(255, 255, 255);");
    }
}

void MainWindow::on_drawlines_clicked()
{
    if(!draw_line_mod) {
        draw_line_mod=true;
        ui->drawlines->setStyleSheet("color: rgb(255, 255, 255);\nfont: 75 20pt 'Century Gothic';\nborder:2px solid rgb(48, 140, 98);\nbackground-color: rgb(48, 140, 98);");
    }
    else{
        draw_line_mod=false;
        ui->drawlines->setStyleSheet("color: rgb(0, 0, 0);\nfont: 75 20pt 'Century Gothic';\nborder:2px solid rgb(48, 140, 98);\nbackground-color: rgb(255, 255, 255);");
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
                //linenum--;
            }
        }
        eleList.erase(attention_order);
     //   elenum--;
        attention=0;
    }

}

void MainWindow::on_applyButton_clicked()
{
    if(attention){
        eleList.find(attention_order)->value=nodevaluetext;
    }
   // QLineEdit *ie=ui->nodevalue;
   // qDebug()<<ie->text();
}

void MainWindow::on_nodevalue_textChanged(const QString &arg1)
{
    nodevaluetext=arg1;
}
