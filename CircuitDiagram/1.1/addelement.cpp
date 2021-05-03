#include "addelement.h"
#include "ui_addelement.h"

AddElement::AddElement(CircuitDig *circuitdig, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddElement)
{
    ui->setupUi(this);
    _cd=circuitdig;
    ed=new edge;
    ed->valuen=0;
}

AddElement::~AddElement()
{
    delete ui;
}

void AddElement::on_comboBox_activated(const QString &arg1)
{
    if(arg1=="电阻"){
        ed->type=1;
    }
}

void AddElement::on_buttonBox_accepted()
{
    ed->valuen++;
    ed->value[ed->valuen]=ui->value->text().toInt();
    ed->x=ui->x->text().toInt();
    ed->y=ui->y->text().toInt();
    _cd->in[ed->x]=1;
    _cd->in[ed->y]=1;
    _cd->map[ed->x].push_back(*ed);
    _cd->map[ed->y].push_back((edge){ed->y,ed->x});
}
