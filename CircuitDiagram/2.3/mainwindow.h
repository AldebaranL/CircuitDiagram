#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//#include <math.h>
//#include "global.h"
#include <qpainter.h>
#include <QMouseEvent>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();//元件1
    void on_pushButton_2_clicked();//元件2
    void on_drawlines_clicked();//drawlines模式
    void on_changeDir_clicked();
    void on_nodeDeletButton_clicked();
    void on_applyButton_clicked();
    void on_nodevalue_textChanged(const QString &arg1);
    void SavePic();//保存图片

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent* event);
private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
