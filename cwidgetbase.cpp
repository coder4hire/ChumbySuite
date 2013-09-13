#include <QString>
#include <QMessageBox>
#include <QStyleOption>
#include <QPainter>

#include "cwidgetbase.h"
#include "WidgetSelector.h"
#include "Fader.h"
#include "Log.h"

CWidgetBase::CWidgetBase(QWidget *parent)
    :QWidget(parent,Qt::FramelessWindowHint)
{
    pConfigWidget=NULL;
}

CWidgetBase::~CWidgetBase()
{
}

void CWidgetBase::setBackground(QString fileName)
{
    //setStyleSheet("background-image: url(./"+fileName+")");

    QPixmap pixmapOriginal;
    if(pixmapOriginal.load(fileName))
    {
        QPalette p = palette();
        QPixmap pixmap(pixmapOriginal.scaled(size()));
        p.setBrush(QPalette::Background,QBrush(pixmap));
        setPalette(p);
    }
    else
    {
        QMessageBox::warning(this,"Problem","Can't load image: "+fileName);
        CLog::Log("Can't load background image file");
    }
}

void CWidgetBase::Initialize(CWidgetSelector* pSelector, QSettings* pSettings)
{
    this->pSettings = pSettings;
    this->pSelector = pSelector;
}

void CWidgetBase::paintEvent (QPaintEvent *)
{
    QStyleOption opt;
    opt.init (this);
    QPainter p (this);
    style ()->drawPrimitive (QStyle::PE_Widget, &opt, &p, this);
}
