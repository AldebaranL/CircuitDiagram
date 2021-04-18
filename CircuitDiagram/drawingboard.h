#ifndef DRAWINGBOARD_H
#define DRAWINGBOARD_H

#include <QMainWindow>
#include "addelement.h"
#include "circuitdig.h"

#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QVector>
#include <QPoint>
#include <QToolBar>
#include <QAction>
#include <QPalette>
#include <QColor>
#include <QMenu>
#include <QFileDialog>
#include <QTextEdit>

#include<stdio.h>
#include<string>

QT_BEGIN_NAMESPACE
namespace Ui { class DrawingBoard; }
QT_END_NAMESPACE

class DrawingBoard : public QMainWindow
{
    Q_OBJECT

public:
    DrawingBoard(QWidget *parent = nullptr);
    ~DrawingBoard();
    AddElement * addele;
    CircuitDig * circuitdig;

protected:
    void paintEvent(QPaintEvent *);//重写窗体重绘事件
private slots:
    void on_addElementBT_clicked();
    void on_addNodeBT_clicked();

    void SavePic();//保存图片

private:
    Ui::DrawingBoard *ui;
    QPixmap _pixmap;//画布图片
    int _redraw;
};
#endif // DRAWINGBOARD_H
