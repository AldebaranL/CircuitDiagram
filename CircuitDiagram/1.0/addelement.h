#ifndef ADDELEMENT_H
#define ADDELEMENT_H

#include <QDialog>
#include "circuitdig.h"
namespace Ui {
class AddElement;
}

class AddElement : public QDialog
{
    Q_OBJECT

public:
    explicit AddElement(CircuitDig*,QWidget *parent = nullptr);
    ~AddElement();

private slots:
    void on_comboBox_activated(const QString &arg1);
    void on_buttonBox_accepted();

private:
    Ui::AddElement *ui;
    CircuitDig * _cd;
    edge * ed;
};

#endif // ADDELEMENT_H
