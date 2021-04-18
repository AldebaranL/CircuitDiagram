#include "drawingboard.h"
#include "ui_drawingboard.h"

DrawingBoard::DrawingBoard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DrawingBoard)
{
    ui->setupUi(this);
    _redraw = 0;
    circuitdig = new CircuitDig;

    QToolBar *tbar = addToolBar(tr("工具栏"));
    tbar->setMovable(false);//工具栏不可移动
    tbar->setIconSize(QSize(20, 20));//设置动作图标的尺寸
    tbar->setStyleSheet("background-color:rgb(100,100,100)");//背景色

    QAction *saveAction = new QAction(tr("&保存"), this);//保存动作
    tbar->addAction(saveAction);//添加到工具栏

    connect(saveAction, SIGNAL(triggered()), this, SLOT(SavePic()));

}

DrawingBoard::~DrawingBoard()
{
    delete ui;
    delete circuitdig;
}


void DrawingBoard::paintEvent(QPaintEvent *){
    _pixmap = QPixmap(size());//新建pixmap
    _pixmap.fill(QColor(192,192,192));//背景色填充为白色
    QPixmap pix = _pixmap;//以_pixmap作为画布
    QPainter p(&pix);//将_pixmap作为画布
    p.setBrush(QColor(255,255,255));
    p.setPen(QColor(255,255,255));
    p.drawRect(50,80,600,300);

    circuitdig->display(p);
    update();
    if(_redraw==1){
       circuitdig->updateNodePos();
        _redraw=0;
    }

    //QPainter painter(this);
   // painter.setPen(QPen(Qt::blue,4));//设置画笔形式
   // painter.setBrush(QColor(255,0,0));//设置画刷，如果不画实现的直接把Brush设置为setBrush(Qt::NoBrush);
   // painter.drawEllipse(20,20,200,200);//画圆

    p.end();
    p.begin(this);//将当前窗体作为画布
    p.drawPixmap(0,0, pix);//将pixmap画到窗体
}

void DrawingBoard::on_addNodeBT_clicked()
{
    _redraw=1;
    circuitdig->nodenumber++;
}

void DrawingBoard::on_addElementBT_clicked()
{

    addele=new AddElement(circuitdig);
    addele->show();
    _redraw=1;
}
void DrawingBoard::SavePic()
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
        pixmap.copy(QRect(50,80,600,300)).save(fileName);//不包含工具栏
    }
}
