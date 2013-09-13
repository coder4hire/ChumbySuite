#include "cwidgetbase.h"
#include "ui_cwidgetbase.h"

CWidgetBase::CWidgetBase(QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::CWidgetBase)
{
    ui->setupUi(this);
    memset(widgets,0,sizeof(widgets));
}

CWidgetBase::~CWidgetBase()
{
    delete ui;
}

CWidgetBase* CWidgetBase::operator [](int i)
{
    if(i<count)
    {
        return widgets[i];
    }
    return NULL;
}
