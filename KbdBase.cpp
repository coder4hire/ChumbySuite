#include "KbdBase.h"
#include "QTimerEvent"

CKbdBase::CKbdBase(QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint)
{
    closeTimer=0;
}

CKbdBase::~CKbdBase()
{
}

void CKbdBase::ShowKbd(QLineEdit* pCallerEdit,QWidget* parent)
{
     //-F- Killing close timer if is counting down
    CancelDelayedClosing();

    //-F- Moving keyboard to lower right corner
    this->pCallerEdit = pCallerEdit;

    if(!isVisible())
    {
        setParent(parent);
        QSize parentSize = parent->size();
        move(parentSize.width()-size().width(),parentSize.height()-size().height());
    }

    show();
}

void CKbdBase::closeEvent(QCloseEvent *)
{
    if(closeTimer)
    {
        killTimer(closeTimer);
        closeTimer=0;
    }
    pCallerEdit=NULL;
}

void CKbdBase::CloseKbdDelayed()
{
    if(isVisible())
    {
        closeTimer = startTimer(1000);
    }
}

void CKbdBase::CancelDelayedClosing()
{
    if(closeTimer)
    {
        killTimer(closeTimer);
        closeTimer=0;
    }
}

void CKbdBase::timerEvent(QTimerEvent *ev)
{
    if(ev->timerId()==closeTimer)
    {
        close();
    }
}
